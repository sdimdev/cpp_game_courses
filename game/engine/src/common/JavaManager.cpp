//
// Created by dzmitry on 24.01.2022.
//

#include "JavaManager.hpp"
#include <jni.h>

namespace {
    JNIEnv *jniEnv = nullptr;
    jobject jniManager = nullptr;
}

const JavaManager &JavaManager::instance()
{
    static JavaManager javaManager;
    return javaManager;
}

bool JavaManager::openBrowser(std::string url) const{
    auto clazz = jniEnv->GetObjectClass(jniManager);
    auto method = jniEnv->GetMethodID(clazz, "openUrl", "(Ljava/lang/String;)Z");
    jobject jurl = jniEnv->NewStringUTF(url.c_str());
    auto result = jniEnv->CallBooleanMethod(jniManager, method, jurl);
    return result;
}

#include <iostream>

/*JNIEXPORT jobject JNICALL
Java_sdim_game_example_MainActivity_initJni(JNIEnv *env, jobject this, jstring name, jint version){

}*/
extern "C"
JNIEXPORT jboolean JNICALL
Java_sdim_game_example_JniManager_initJni(JNIEnv *env, jobject thiz, jstring name, jint version) {
    std::string nameStr = env->GetStringUTFChars(name, nullptr);
    std::cout << nameStr << " ; " << version;
    jniEnv = env;
    jniManager = env->NewGlobalRef(thiz);

    return JNI_TRUE;
}