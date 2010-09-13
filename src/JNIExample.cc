#include <stdio.h>
#include <jni.h>

#include "JNIExample.h"


JNIEXPORT jstring JNICALL Java_JNIExample_sayHello
  (JNIEnv *env, jobject thisobject, jstring js)

{
	//printf("%p jni env\n",env);
	return js;
}