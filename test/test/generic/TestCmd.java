package test.generic;

import java.io.File;

public class TestCmd {
	public static void main(String[]args) throws Exception{
		String dir =  "/home/constantinussatrio/ky_log/";
		for(File f : new File(dir).listFiles()){
			touch(f);
		}
	}
	
	public static void touch(File file) {
		file.setLastModified(System.currentTimeMillis());
	}
}
