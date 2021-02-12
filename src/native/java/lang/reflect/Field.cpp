#include "../../../jni_internal.h"

// private native byte[] getTypeAnnotationBytes0();
static jobject getTypeAnnotationBytes0(jobject _this)
{
    JVM_PANIC("getTypeAnnotationBytes0"); // todo
}

static JNINativeMethod methods[] = {
        JNINativeMethod_registerNatives,
        { "getTypeAnnotationBytes0", "()[B", TA(getTypeAnnotationBytes0) },
};

void java_lang_reflect_Field_registerNatives()
{
    registerNatives("java/lang/reflect/Field", methods, ARRAY_LENGTH(methods));
}