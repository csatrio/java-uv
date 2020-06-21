package com.csatrio.libuv;

import java.lang.ref.WeakReference;
import java.lang.reflect.Field;
import java.nio.ByteBuffer;
import java.util.Arrays;

public class DefaultCallbackHandle extends CallbackHandle{

	private final byte[] buf = new byte[65536];
	private final String dataStr = new String(buf);
	private static Field field;
	
	static {
		try {
			field = String.class.getDeclaredField("value");
			field.setAccessible(true);
		} catch (NoSuchFieldException | SecurityException e) {
			e.printStackTrace();
		}
	}
	
	public DefaultCallbackHandle(WeakReference<UvBridge> bridge) {
		super(bridge);
	}
	
	@Override
	public void onRead(ByteBuffer data) {
		int pos = data.position();
		data.flip();
		data.get(buf, 0, pos);
		try {
			char[] str = (char[]) field.get(dataStr);
			Arrays.fill(str, Character.MIN_VALUE);
			for(int i=0; i<pos; i++) {
				str[i] = (char) (buf[i] & 0xff);
			}
			System.out.println(dataStr);
			if(dataStr.contains("dc")) {
				System.out.println("disconnecting");
				disconnect();
			}
		} catch (IllegalArgumentException | IllegalAccessException e) {
			e.printStackTrace();
		}
		write(data);
	}

}
