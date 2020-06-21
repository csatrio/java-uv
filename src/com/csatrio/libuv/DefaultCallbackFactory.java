package com.csatrio.libuv;

public class DefaultCallbackFactory extends CallbackFactory {
	@Override
	public CallbackHandle newCallback() {
		return new DefaultCallbackHandle(bridge);
	}
}