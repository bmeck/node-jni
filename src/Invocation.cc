#include <jni.h>       /* where everything is defined */
#include <v8.h>
#include <stdio.h>
using namespace v8;

//JNI GUIDE
//http://download-llnw.oracle.com/javase/1.3/docs/guide/jni/spec/jniTOC.doc.html

//USEFUL PARTS OF GUIDE
//http://download.oracle.com/javase/1.4.2/docs/guide/jni/spec/functions.html#wp5256
//http://download-llnw.oracle.com/javase/1.3/docs/guide/jni/spec/types.doc.html
//http://download.oracle.com/javase/6/docs/technotes/guides/jni/spec/functions.html#weak

Handle<Value> JavaMethodWrapper() {return Undefined();}
Handle<Value> JavaClassWrapper() {return Undefined();}
Handle<Value> JavaObjectWrapper() {return Undefined();}

jstring JSToJavaString(JNIEnv* env, Handle<Value> js) {
	return env->NewStringUTF(*String::Utf8Value(js));
}
jboolean JSToJavaBoolean(Handle<Value> js) {return js->IsTrue();}
jbyte JSToJavaByte(Handle<Value> js) {return (char)js->IntegerValue();}
jchar JSToJavaCharacter(Handle<Value> js) {return (short)js->IntegerValue();}
jshort JSToJavaShort(Handle<Value> js) {return (short)js->IntegerValue();}
jint JSToJavaInteger(Handle<Value> js) {return (int)js->IntegerValue();}
jlong JSToJavaLong(Handle<Value> js) {return (long)js->IntegerValue();}
jfloat JSToJavaFloat(Handle<Value> js) {return (float)js->NumberValue();}
jdouble JSToJavaDouble(Handle<Value> js) {return (double)js->NumberValue();}

Handle<Value> JavaByteToJSNumber(jbyte v) {return Number::New(v);}
Handle<Value> JavaShortToJSNumber(jshort v) {return Number::New(v);}
Handle<Value> JavaIntegerToJSNumber(jint v) {return Number::New(v);}
Handle<Value> JavaLongToJSNumber(jlong v) {return Number::New(v);}
Handle<Value> JavaFloatToJSNumber(jfloat v) {return Number::New(v);}
Handle<Value> JavaDoubleToJSNumber(jdouble v) {return Number::New(v);}
Handle<Value> JavaStringToJSString(JNIEnv* env, jstring v) {
	char* chrs = env->GetStringUTFChars(v,NULL);
	Handle<String> str = String::New(chrs);
	env->ReleaseStringUTFChars(v,chrs);
	return str;
}

extern "C" void init (Handle<Object> target) {
	JavaVM *jvm;       /* denotes a Java VM */
	printf("%p jvm\n",jvm);
	JNIEnv *env;       /* pointer to native method interface */
	printf("%p env\n",env);
	JavaVMInitArgs vm_args; /* JDK 1.1 VM initialization arguments */
	vm_args.version = JNI_VERSION_1_4; /* New in 1.1.2: VM version */
	/* Get the default initialization arguments and set the class
	 * path */
	JNI_GetDefaultJavaVMInitArgs(&vm_args);
	/* load and initialize a Java VM, return a JNI interface
	 * pointer in env */
	JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
	/* invoke the Main.test method using the JNI */
	jclass cls = env->FindClass("JNIExample");
	jmethodID constructor_id = env->GetMethodID(cls,"<init>","()V");
	jobject loader = env->NewGlobalRef(env->NewObject(cls,constructor_id));
	jclass string_cls = env->FindClass("java/lang/ClassLoader");
	jmethodID package_id = env->GetMethodID(cls,"getPackage","(Ljava/lang/String;)Ljava/lang/Package;");
	/* We are done. */
	env->DeleteGlobalRef(loader);
	jvm->DestroyJavaVM();
}