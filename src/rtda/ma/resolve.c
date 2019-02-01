/*
 * Author: Jia Yang
 */

#include "resolve.h"
#include "field.h"
#include "class.h"
#include "../../classfile/constant.h"
#include "../heap/strpool.h"

struct class* resolve_class(struct class *visitor, int cp_index)
{
    struct constant_pool *cp = &visitor->constant_pool;
    if (CP_TYPE(cp, cp_index) == CONSTANT_ResolvedClass) {
        return (struct class *) CP_INFO(cp, cp_index);
    }

    struct class *c = load_class(visitor->loader, CP_CLASS_NAME(cp, cp_index));
    if (!class_is_accessible_to(c, visitor)) {
        // todo  java.lang.IllegalAccessError
        jvm_abort("java.lang.IllegalAccessError\n");
    }

    CP_TYPE(cp, cp_index) = CONSTANT_ResolvedClass;
    CP_INFO(cp, cp_index) = (uintptr_t) c;
    return c;
}

struct method* resolve_method(struct class *visitor, int cp_index)
{
    struct constant_pool *cp = &visitor->constant_pool;
    u1 type = CP_TYPE(cp, cp_index);

    if (type == CONSTANT_ResolvedMethod) {
        return (struct method *) CP_INFO(cp, cp_index);
    }

    struct class *resolved_class = resolve_class(visitor, CP_METHOD_CLASS(cp, cp_index));
    struct method *m = class_lookup_method(resolved_class, CP_METHOD_NAME(cp, cp_index), CP_METHOD_TYPE(cp, cp_index));
    if (!method_is_accessible_to(m, visitor)) {
        // todo  java.lang.IllegalAccessError
        jvm_abort("java.lang.IllegalAccessError\n");
    }

    CP_TYPE(cp, cp_index) = CONSTANT_ResolvedMethod;
    CP_INFO(cp, cp_index) = (uintptr_t) m;
    return m;
}

struct field* resolve_field(struct class *visitor, int cp_index)
{
    struct constant_pool *cp = &visitor->constant_pool;
    u1 type = CP_TYPE(cp, cp_index);

    if (type == CONSTANT_ResolvedField) {
        return (struct field *) CP_INFO(cp, cp_index);
    }

    struct class *resolved_class = resolve_class(visitor, CP_FIELD_CLASS(cp, cp_index));
    struct field *f = class_lookup_field(resolved_class, CP_FIELD_NAME(cp, cp_index), CP_FIELD_TYPE(cp, cp_index));
    if (!field_is_accessible_to(f, visitor)) {
        // todo  java.lang.IllegalAccessError
        jvm_abort("java.lang.IllegalAccessError\n");
    }

    CP_TYPE(cp, cp_index) = CONSTANT_ResolvedField;
    CP_INFO(cp, cp_index) = (uintptr_t) f;
    return f;
}

struct object* resolve_string(struct class *c, int cp_index)
{
    struct constant_pool *cp = &c->constant_pool;
    if (CP_TYPE(cp, cp_index) == CONSTANT_ResolvedString) {
        return (struct object *) CP_INFO(cp, cp_index);
    }

    const char *str = CP_STRING(cp, cp_index);
    struct object *so = get_str_from_pool(c->loader, str);
    CP_INFO(cp, cp_index) = (uintptr_t) so;
    CP_TYPE(cp, cp_index) = CONSTANT_ResolvedString;

    return so;
}

uintptr_t resolve_single_constant(struct class *c, int cp_index)
{
    struct constant_pool *cp = &c->constant_pool;

    switch(CP_TYPE(cp, cp_index)) {
        case CONSTANT_Class: return (uintptr_t) resolve_class(c, cp_index);
        case CONSTANT_String: return (uintptr_t) resolve_string(c, cp_index);
        default: return CP_INFO(cp, cp_index);
    }
}