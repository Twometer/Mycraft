#include <jni.h>
#include <string>
#include <android/log.h>
#include <GLES3/gl3.h>

#include "VboBuilder.h"
#include "Loader.h"
#include "Renderer.h"

#define  LOG_TAG    "MyCraft_Native"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

Loader loader;
Renderer renderer;

extern "C" JNIEXPORT void JNICALL
Java_de_twometer_mycraft_interop_NativeLib_onPacket(JNIEnv *env, jobject instance, jint id,
                                                    jbyteArray packet_) {
    jbyte *packet = env->GetByteArrayElements(packet_, NULL);


    env->ReleaseByteArrayElements(packet_, packet, 0);
}

extern "C" JNIEXPORT void JNICALL
Java_de_twometer_mycraft_interop_NativeLib_onLoginCompleted(JNIEnv *env, jobject instance) {

    LOGD("Completed login sequence");

}

extern "C"
JNIEXPORT void JNICALL
Java_de_twometer_mycraft_interop_NativeLib_setAssetsFolder(JNIEnv *env, jobject instance,
                                                           jstring folder_) {
    const char *folder = env->GetStringUTFChars(folder_, 0);
    loader.setBasePath(std::string(folder));
    env->ReleaseStringUTFChars(folder_, folder);
}

extern "C" JNIEXPORT void JNICALL
Java_de_twometer_mycraft_interop_NativeLib_onSurfaceCreated(JNIEnv *env, jobject instance) {
    renderer.initialize(loader);
}

extern "C" JNIEXPORT void JNICALL
Java_de_twometer_mycraft_interop_NativeLib_onSurfaceChanged(JNIEnv *env, jobject instance,
                                                            jint width, jint height) {
    renderer.resize(width, height);
}

extern "C" JNIEXPORT void JNICALL
Java_de_twometer_mycraft_interop_NativeLib_onDrawFrame(JNIEnv *env, jobject instance) {
    renderer.drawFrame();
}
extern "C"
JNIEXPORT void JNICALL
Java_de_twometer_mycraft_interop_NativeLib_onRotate(JNIEnv *env, jobject instance, jfloat dx,
                                                    jfloat dy) {

    renderer.rotatePlayer(dx, dy);

}