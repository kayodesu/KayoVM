#include <sstream>
#include "descriptor.h"
#include "../metadata/class.h"
#include "../objects/class_loader.h"
#include "../objects/prims.h"
#include "../objects/array.h"
#include "../runtime/vm_thread.h"
#include "../exception.h"

using namespace std;

// @b: include
// @e：exclude
// eg. Ljava/lang/String;
static Object *convertDescElement2ClassObject(char *&b, char *e, jref loader)
{
    assert(b != nullptr && e != nullptr);

    if (*b == 'L') { // reference
        char *t = strchr(b, ';');
        if (t == nullptr || t >= e) {
            goto error;
        }

//        *t = 0;   // end string
        b++; // jump 'L'
//        string s(b, t-b);
        auto c = loadClass(loader, string(b, t - b).c_str());
//        *t = ';'; // recover
        b = t + 1;
        return c->java_mirror;
    }

    if (*b == '[') { // array reference, 描述符形如 [B 或 [[Ljava/lang/String; 的形式
        char *t = b;
        while (*(++t) == '[');
        if (!isPrimDescriptor(*t)) {
            t = strchr(t, ';');
            if (t == nullptr || t >= e) {
                goto error;
            }
        }

//        char k = *(++t);
//        *t = 0; // end string
        t++;
        auto c = loadArrayClass(loader, string(b, t - b).c_str());
//        *t = k; // recover
        b = t;
        return c->java_mirror;
    }

    if (isPrimDescriptor(*b)) { // prim type
        const char *class_name = getPrimClassName(*b);
        b++;
        return loadBootClass(class_name)->java_mirror;
    }

error:
    throw java_lang_UnknownError(); // todo
}

int numElementsInDescriptor(const char *b, const char *e)
{
    assert(b != nullptr && e != nullptr);

    int no_params;
    b--;
    for(no_params = 0; ++b < e; no_params++) {
        if(*b == '[')
            while(*++b == '[');
        if(*b == 'L')
            while(*++b != ';');
    }

    return no_params;
}

int numElementsInMethodDescriptor(const char *method_descriptor)
{
    assert(method_descriptor != nullptr && method_descriptor[0] == '(');

    const char *b = method_descriptor + 1; // jump '('
    const char *e = strchr(method_descriptor, ')');
    if (e == nullptr) {
        // todo error
        JVM_PANIC("error");
    }
    return numElementsInDescriptor(b, e);
}

//int numElementsInDescriptor(const char *descriptor)
//{
//    assert(descriptor != nullptr);
//    return numElementsInDescriptor(descriptor, descriptor + strlen(descriptor));
//}

// @b: include
// @e：exclude
// eg. I[BLjava/lang/String;ZZ
static Array *convertDesc2ClassObjectArray(char *b, char *e, jref loader)
{
    int num = numElementsInDescriptor(b, e);
    Array *types = newClassArray(num);

    for (int i = 0; b < e; i++) {
        Object *co = convertDescElement2ClassObject(b, e, loader);
        assert(i < num);
        types->setRef(i, co);
    }

    return types;
}

pair<Array *, ClsObj *> parseMethodDescriptor(const char *desc, jref loader)
{
    assert(desc != nullptr);

    char *e = strchr(desc, ')');
    if (e == nullptr || *desc != '(') {
        throw java_lang_UnknownError(); // todo
    }

    Array *ptypes = convertDesc2ClassObjectArray((char *) (desc + 1), e, loader);
    e++; // jump ')'
    ClsObj *rtype = convertDescElement2ClassObject(e, e + strlen(e), loader);
    return make_pair(ptypes, rtype);
}

static string convertTypeToDesc(Class *type)
{
    assert(type != nullptr);

    if (type->isPrimClass()) {
        return getPrimDescriptorByClassName(type->class_name);
    }

    if (type->isArrayClass()) {
        return type->class_name;
    }

    // 普通类
    ostringstream oss;
    oss << 'L';
    oss << type->class_name;
    oss << ';';
    return oss.str();
}

string unparseMethodDescriptor(Array *ptypes /*Class *[]*/, ClsObj *rtype)
{
    ostringstream oss;

    if (ptypes == nullptr) { // no argument
        oss << "()";
    } else {
        oss << "(";
        for (int i = 0; i < ptypes->arr_len; i++) {
            auto co = ptypes->get<ClsObj *>(i);
            assert(co != nullptr);
            oss << convertTypeToDesc(co->jvm_mirror);        
        }
        oss << ")";
    }

    if (rtype == nullptr) { // no return value
        oss << "V";
    } else {
        oss << convertTypeToDesc(rtype->jvm_mirror);
    }

    return oss.str();
}

string unparseMethodDescriptor(jref method_type)
{
    assert(method_type != nullptr);

    // private final Class<?>[] ptypes;
    auto ptypes = method_type->getRefField<Array>("ptypes", S(array_java_lang_Class));
    // private final Class<?> rtype;
    auto rtype = method_type->getRefField<ClsObj>("rtype", S(sig_java_lang_Class));

    return unparseMethodDescriptor(ptypes, rtype);
}