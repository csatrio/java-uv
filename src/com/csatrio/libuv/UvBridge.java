package com.csatrio.libuv;

import java.nio.ByteBuffer;

public class UvBridge {
	static {
		System.loadLibrary("tcpnative"); // libtcpnative.dll (Windows) or libtcpnative.so (Unix)
	}

	public UvBridge(CallbackFactory factory) {
		factory.setBridge(this);
		this.factory = factory;
	}

	private final CallbackFactory factory;

	// Native method declaration
	public native void runServer(String ip, int port, CallbackFactory factory, Class<CallbackHandle> callbackClass);

	public native void write(ByteBuffer data, CallbackHandle callback);

	public native void disconnect(CallbackHandle callback);

	// Facade Method
	public void runServer(String ip, int port) {
		runServer(ip, port, factory, CallbackHandle.class);
	}

	// Test Driver
	public static void main(String[] args) {
		CallbackFactory factory = new DefaultCallbackFactory();
		UvBridge bridge = new UvBridge(factory);
		bridge.runServer("0.0.0.0", 8000);
	}
}