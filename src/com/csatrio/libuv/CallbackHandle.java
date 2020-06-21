package com.csatrio.libuv;

import java.lang.ref.WeakReference;
import java.nio.ByteBuffer;

public abstract class CallbackHandle{
	protected final WeakReference<UvBridge> bridge;
	protected long wrapperAddress = 0;
	
	public CallbackHandle(WeakReference<UvBridge> bridge) {
		this.bridge = bridge;
	}
	
	public abstract void onRead(ByteBuffer data);
	
	public void write(ByteBuffer data) {
		bridge.get().write(data, this);
	}
	
	public void disconnect() {
		bridge.get().disconnect(this);
	}
}