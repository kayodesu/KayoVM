#include "../../jni_internal.h"
#include "../../../util/convert.h"

// public static native int floatToRawIntBits(float value);
static jint floatToRawIntBits(jfloat value)
{
    return float_to_raw_int_bits(value);
}

// public static native float intBitsToFloat(int value);
static jfloat intBitsToFloat(jint value)
{
    return int_bits_to_float(value);
}

static JNINativeMethod methods[] = {
        JNINativeMethod_registerNatives,
        { "floatToRawIntBits", "(F)I", TA(floatToRawIntBits) },
        { "intBitsToFloat", "(I)F", TA(intBitsToFloat) },
};

void java_lang_Float_registerNatives()
{
    registerNatives("java/lang/Float", methods, ARRAY_LENGTH(methods));
}