package com.csatrio.libuv;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.net.UnknownHostException;

public class UvBridgeTester {

	public static void main(String[] args) throws UnknownHostException, IOException {
		Socket s = new Socket();
		SocketAddress address = new InetSocketAddress("localhost", 8000);
		s.connect(address);
		OutputStream out = s.getOutputStream();
		for(int i=0; i<1000; i++) {
			byte[] data = String.format("data%d\n", i).getBytes();
			out.write(data);
		}
		s.close();
	}

}
