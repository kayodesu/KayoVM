#include "../../jni_internal.h"

// static native void copyFromShortArray(Object src, long srcPos, long dstAddr, long length);
static void copyFromShortArray(jobject _this, jobject src, jlong srcPos, jlong dstAddr, jlong length)
{
    JVM_PANIC("copyFromShortArray"); // todo
}

// static native void copyToShortArray(long srcAddr, Object dst, long dstPos, long length);
static void copyToShortArray(jobject _this, jlong srcAddr, jobject dst, jlong dstPos, jlong length)
{
    JVM_PANIC("copyToShortArray"); // todo
}

// static native void copyFromIntArray(Object src, long srcPos, long dstAddr, long length);
static void copyFromIntArray(jobject _this, jobject src, jlong srcPos, jlong dstAddr, jlong length)
{
    JVM_PANIC("copyFromIntArray"); // todo
}


// static native void copyToIntArray(long srcAddr, Object dst, long dstPos, long length);
static void copyToIntArray(jobject _this, jlong srcAddr, jobject dst, jlong dstPos, jlong length)
{
    JVM_PANIC("copyToIntArray"); // todo
}

// static native void copyFromLongArray(Object src, long srcPos, long dstAddr, long length);
static void copyFromLongArray(jobject _this, jobject src, jlong srcPos, jlong dstAddr, jlong length)
{
    JVM_PANIC("copyFromLongArray"); // todo
}

// static native void copyToLongArray(long srcAddr, Object dst, long dstPos, long length);
static void copyToLongArray(jobject _this, jlong srcAddr, jobject dst, jlong dstPos, jlong length)
{
    JVM_PANIC("copyToLongArray"); // todo
}

static JNINativeMethod methods[] = {
        JNINativeMethod_registerNatives,
        { "copyFromShortArray", "(Ljava/lang/Object;JJJ)V", TA(copyFromShortArray) },
        { "copyToShortArray", "(JLjava/lang/Object;JJ)V", TA(copyToShortArray) },
        { "copyFromIntArray", "(Ljava/lang/Object;JJJ)V", TA(copyFromIntArray) },
        { "copyToIntArray", "(JLjava/lang/Object;JJ)V", TA(copyToIntArray) },
        { "copyFromLongArray", "(Ljava/lang/Object;JJJ)V", TA(copyFromLongArray) },
        { "copyToLongArray", "(JLjava/lang/Object;JJ)V", TA(copyToLongArray) },
};

void java_nio_Bits_registerNatives()
{
    registerNatives("java/nio/Bits", methods, ARRAY_LENGTH(methods));
}
