#include <string.h>
#include <assert.h>
#include "jtypes.h"
#include "jvm.h"

/*
 * Author: Jia Yang
 */

const char* get_jtype_name(enum jtype t)
{
    static const char* names[] = {
        "jbyte", "jbool", "jchar", "jshort", "jint",
        "jlong", "jfloat", "jdouble", "jref", "placeholder", "not a tpe"
    };

    if (t < 0 || t >= sizeof(names) / sizeof(*names)) {
        printvm("访问越界, %d of %d\n", t, sizeof(names));
        return "unknown";
    }

    return names[t];
}

bool is_primitive_by_class_name(const char *class_name)
{
    for (int i = 0; i < PRIMITIVE_TYPE_COUNT; i++) {
        if (strcmp(primitive_types[i].wrapper_class_name, class_name) == 0) {
            return true;
        }
    }
    return false;
}

const char* primitive_type_get_array_class_name_by_class_name(const char *class_name)
{
    assert(class_name != NULL);

    for (int i = 0; i < PRIMITIVE_TYPE_COUNT; i++) {
        if (strcmp(primitive_types[i].name, class_name) == 0) {
            return primitive_types[i].array_class_name;
        }
    }
    return NULL;
}

const char* primitive_type_get_primitive_name_by_descriptor(const char *descriptor)
{
    assert(descriptor != NULL);

    if (strlen(descriptor) != 1) {
        return NULL; // not primitive type's descriptor
    }

    for (int i = 0; i < PRIMITIVE_TYPE_COUNT; i++) {
        if (primitive_types[i].descriptor == *descriptor) {
            return primitive_types[i].name;
        }
    }
    return NULL;
}