#include "../../jni_internal.h"

/*
 * Notify the VM that it's time to halt.
 *
 * static native void beforeHalt();
 */
static void beforeHalt()
{
    JVM_PANIC("beforeHalt");
}

/*
 * The halt method is synchronized on the halt lock
 * to avoid corruption of the delete-on-shutdown file list.
 * It invokes the true native halt method.
 *
 * static native void halt0(int status);
 */
static void halt0(jint status)
{
    JVM_PANIC("halt0");
}

static JNINativeMethod methods[] = {
        JNINativeMethod_registerNatives,
        { "beforeHalt", "()V", TA(beforeHalt) },
        { "halt0", "(I)V", TA(halt0) },
};

void java_lang_Shutdown_registerNatives()
{
    registerNatives("java/lang/Shutdown", methods, ARRAY_LENGTH(methods));
}
