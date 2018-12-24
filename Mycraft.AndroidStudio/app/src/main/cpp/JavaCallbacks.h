//
// Created by twome on 24/12/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_JAVACALLBACKS_H
#define MYCRAFT_ANDROIDSTUDIO_JAVACALLBACKS_H


#include <jni.h>

class JavaCallbacks {
public:
    static void setPosition(double x, double y, double z);

    static void setRotation(float yaw, float pitch);

    static void setPosAndRot(double x, double y, double z, float yaw, float pitch);

    static void registerCallback(JNIEnv* env, JavaVM *vm, jobject obj);

private:
    static JavaVM *vm;
    static jobject callbackObj;

    static jmethodID setPositionId;
    static jmethodID setRotationId;
    static jmethodID setPosAndRotId;

    static JNIEnv *getEnvironment();

    static void destroyEnvironment(JNIEnv *env);
};


#endif //MYCRAFT_ANDROIDSTUDIO_JAVACALLBACKS_H
