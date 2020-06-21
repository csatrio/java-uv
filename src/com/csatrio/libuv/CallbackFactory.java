package com.csatrio.libuv;

import java.lang.ref.WeakReference;

public abstract class CallbackFactory {
	protected WeakReference<UvBridge> bridge;
	
	public abstract CallbackHandle newCallback();
	
	public void setBridge(UvBridge bridge) {
		this.bridge = new WeakReference<UvBridge>(bridge);
	}
}
