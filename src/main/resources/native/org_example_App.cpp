#include <iostream>
#include <jni.h>
#include "org_example_App.h"

std::string jstring2string(JNIEnv *env, jstring jStr) {
  if (!jStr)
    return "";

  const jclass stringClass = env->GetObjectClass(jStr);
  const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
  const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

  size_t length = (size_t) env->GetArrayLength(stringJbytes);
  jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

  std::string ret = std::string((char *)pBytes, length);
  env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

  env->DeleteLocalRef(stringJbytes);
  env->DeleteLocalRef(stringClass);
  return ret;
}

JNIEXPORT jstring JNICALL Java_org_example_App_sayHello(JNIEnv *env, jobject, jstring input) {
  std::string result = "Hello from C++ " + jstring2string(env, input);
  std::cout << result << std::endl;
  return env->NewStringUTF(result.c_str());
}