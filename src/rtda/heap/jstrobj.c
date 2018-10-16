/*
 * Author: Jia Yang
 */

#include "jstrobj.h"
#include "mm/halloc.h"
#include "jarrobj.h"

struct jstrobj* jstrobj_create0(struct classloader *loader, const char *str)
{
    HEAP_ALLOC(struct jstrobj, so);

    so->obj = jobject_create(classloader_load_class(loader, "java/lang/String"));
    so->str = str;
    so->wstr = NULL; // todo
    return so;
}

struct jstrobj* jstrobj_create1(struct classloader *loader, const jchar *wstr)
{
    HEAP_ALLOC(struct jstrobj, so);

    so->obj = jobject_create(classloader_load_class(loader, "java/lang/String"));
    so->str = NULL; // todo
    so->wstr = wstr;
    return so;
}

//const jchar* jstrobj_value(struct jstrobj *so)
//{
//    assert(so != NULL);
//    return so->wstr;
//
////    struct slot *slot = jobject_instance_field_value_nt(so->obj, "value", "[C");
////    struct jarrobj *ao = (struct jarrobj *) slot_getr(slot);
////    return ao->data;
//
////    auto v = static_cast<JArrayObj *>(getFieldValue("value", "[C").getRef());
////    jstring s;
////    for (int i = 0; i < v->length(); i++) {
////        s.push_back(v->get<jchar>(i));
////    }
////    return s;
//}
