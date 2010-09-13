pushd src
echo "JAVAC"
javac JNIExample.java
echo "JAVAH"
javah JNIExample
mv JNIExample.class ../lib/
popd

#has to be a jnilib, is this documented somewhere!?
echo "GCC"
gcc -o ./lib/libJNIExample.jnilib -dynamic -shared -I/System/Library/Frameworks/JavaVM.framework/Headers ./src/JNIExample.cc -lc
echo "NODE-WAF"
node-waf clean configure build || node-waf configure build
cp -f build/default/*.node ./lib
