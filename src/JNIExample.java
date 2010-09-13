public class JNIExample
{
	static {
		//System.out.println(System.getProperty("java.library.path"));
		//System.load("/Users/bradleymeck/documents/server/jni/libJNIExample.so");
		System.loadLibrary("JNIExample");
	}
	public native String sayHello(String s);
	public static void main(String[] argv)
	{
		System.out.println("TEST");
		String retval = null;
		JNIExample nt = new JNIExample();
		retval = nt.sayHello("Beavis");
		System.out.println("Invocation returned " + retval);
	}
}