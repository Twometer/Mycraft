#include <jni.h>
#include <string>
#include <android/log.h>
#include <GLES3/gl3.h>

#include "VboBuilder.h"
#include "Loader.h"

#define  LOG_TAG    "MyCraft_Native"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

GLuint shader;
Loader loader;

int viewport_width;
int viewport_height;

VboBuilder* builder = new VboBuilder(2);

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



extern "C" JNIEXPORT void JNICALL
Java_de_twometer_mycraft_interop_NativeLib_onSurfaceCreated(JNIEnv *env, jobject instance) {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    const char *vertexShader =
            "#version 300 es\n"
                    "layout(location = 0) in vec2 position;\n"
                    "layout(location = 1) in vec4 vertexColor;\n"
                    "out vec4 fragmentColor;\n"
                    "void main(void) {\n"
                    "gl_Position = vec4(position, 0.0, 1.0);\n"
                    "fragmentColor = vertexColor;\n"
                    "}";
    const char *fragmentShader =
            "#version 300 es\n"
                    "precision mediump float;\n"
                    "in vec4 fragmentColor;\n"
                    "out vec4 out_Colour;\n"
                    "void main(void) {\n"
                    "out_Colour = fragmentColor;\n"
                    "}";
    shader = loader.loadShader(vertexShader, fragmentShader);
    builder->drawRect(-1, -1, 1, 1, COLORDATA(255, 255, 255, 255));
    builder->build();
    LOGD("Shader loaded: %d!", shader);

}
extern "C" JNIEXPORT void JNICALL
Java_de_twometer_mycraft_interop_NativeLib_onSurfaceChanged(JNIEnv *env, jobject instance,
                                                            jint width, jint height) {
    viewport_width = width;
    viewport_height = height;
}
extern "C" JNIEXPORT void JNICALL
Java_de_twometer_mycraft_interop_NativeLib_onDrawFrame(JNIEnv *env, jobject instance) {
    glViewport(0, 0, viewport_width, viewport_height);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader);
    builder->render();

}