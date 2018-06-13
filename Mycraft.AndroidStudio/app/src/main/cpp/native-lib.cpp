#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring

JNICALL
Java_de_twometer_mycraft_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */,
        jstring test) {
    std::string hello = "Hello from C++ // ";
    const char* chr = env->GetStringUTFChars(test, false);
    hello += std::string(chr);
    return env->NewStringUTF(hello.c_str());
}
