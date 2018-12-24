//
// Created by twome on 24/12/2018.
//

#include <iostream>
#include "JavaCallbacks.h"

JavaVM *JavaCallbacks::vm;
jobject JavaCallbacks::callbackObj;

jmethodID JavaCallbacks::setPositionId;
jmethodID JavaCallbacks::setRotationId;
jmethodID JavaCallbacks::setPosAndRotId;

bool needsDetach;

void JavaCallbacks::setPosition(double x, double y, double z) {
    JNIEnv *env = getEnvironment();
    env->CallVoidMethod(callbackObj, setPositionId, x, y, z);
    destroyEnvironment(env);
}

void JavaCallbacks::setRotation(float yaw, float pitch) {
    JNIEnv *env = getEnvironment();
    env->CallVoidMethod(callbackObj, setPositionId, yaw, pitch);
    destroyEnvironment(env);
}

void JavaCallbacks::setPosAndRot(double x, double y, double z, float yaw, float pitch) {
    JNIEnv *env = getEnvironment();
    env->CallVoidMethod(callbackObj, setPositionId, x, y, z, yaw, pitch);
    destroyEnvironment(env);
}

JNIEnv *JavaCallbacks::getEnvironment() {
    JNIEnv *env;
    int result = vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);
    if(result == JNI_EDETACHED){
        result = vm->AttachCurrentThread(&env, NULL);
        needsDetach = result == JNI_OK;
    }
    return env;
}

void JavaCallbacks::destroyEnvironment(JNIEnv *env) {
    if (env->ExceptionCheck())
        env->ExceptionDescribe();
    if (needsDetach)
        vm->DetachCurrentThread();
}

void JavaCallbacks::registerCallback(JNIEnv *env, JavaVM *vm, jobject obj) {
    JavaCallbacks::vm = vm;
    JavaCallbacks::callbackObj = obj;

    jclass callbackClass = env->GetObjectClass(obj);

    JavaCallbacks::setPositionId = env->GetMethodID(callbackClass, "setPosition", "(DDD)V");
    JavaCallbacks::setRotationId = env->GetMethodID(callbackClass, "setRotation", "(FF)V");
    JavaCallbacks::setPosAndRotId = env->GetMethodID(callbackClass, "setPosAndRot", "(DDDFF)V");
}
