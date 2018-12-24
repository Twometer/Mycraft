#include <jni.h>
#include <string>
#include <GLES3/gl3.h>

#include "gui/GuiRenderer.h"
#include "Loader.h"
#include "Renderer.h"
#include "Logger.h"
#include "gui/FontRenderer.h"
#include "JavaCallbacks.h"

Loader loader;
Renderer renderer;

extern "C" JNIEXPORT void JNICALL
Java_de_twometer_mycraft_interop_NativeLib_onPacket(JNIEnv *env, jobject instance, jint id,
                                                    jbyteArray packet_) {
    jbyte *packet = env->GetByteArrayElements(packet_, NULL);
    int packetLen = env->GetArrayLength(packet_);
    renderer.getPacketHandler()->onPacket(id, reinterpret_cast<unsigned char *>(packet), packetLen);
    env->ReleaseByteArrayElements(packet_, packet, 0);
}

extern "C" JNIEXPORT void JNICALL
Java_de_twometer_mycraft_interop_NativeLib_onLoginCompleted(JNIEnv *env, jobject instance) {

    LOGD("Completed login sequence");
    Renderer::getPlayer()->startPhysics();
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

extern "C"
JNIEXPORT void JNICALL
Java_de_twometer_mycraft_interop_NativeLib_onPadTouch(JNIEnv *env, jobject instance, jboolean down,
                                                      jfloat x, jfloat y) {

    renderer.onPadTouch(down, x, y);

}

extern "C"
JNIEXPORT void JNICALL
Java_de_twometer_mycraft_interop_NativeLib_uploadFontWidths(JNIEnv *env, jobject instance,
                                                            jbyteArray widths_) {
    jbyte *widths = env->GetByteArrayElements(widths_, NULL);

    FontRenderer::setFontWidths((unsigned char *) (widths));

    env->ReleaseByteArrayElements(widths_, widths, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_de_twometer_mycraft_interop_NativeLib_register(JNIEnv *env, jobject instance,
                                                    jobject callback) {
    JavaVM* vm;
    env->GetJavaVM(&vm);
    JavaCallbacks::registerCallback(env, vm, env->NewGlobalRef(callback));
}