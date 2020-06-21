package test.generic;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Field;
import java.util.Properties;

public class TestProperties {
	static String instance_prefix = "def";
	static long slack_heart_beat = 0;
	static int daily_report_hour = 0;
	static boolean test = false;

	public static void main(String[] args) throws Exception {
		String filename = "/home/constantinussatrio/java-dev/fbie-kyoe-watcher/fbikyoe-watcher-service/build/libs/config.properties";
		Properties prop = readProperties(filename);
		staticPropertiesMapper(TestProperties.class, prop);
		System.out.println(TestProperties.instance_prefix);
		System.out.println(TestProperties.daily_report_hour);
		System.out.println(TestProperties.slack_heart_beat);
		System.out.println(TestProperties.test);
	}

	/**
	 * <p>	Variable name in Java class must be the same to that in properties file.
	 * All variable name in properties file must be written in lowercase. e.g :</p>
	 * <p> static String INSTANCE_PREFIX => instance_prefix=... </p>
	 * <p><b>Example Usage</b>:<br/>
	 * Properties prop = readProperties(filename);<br/>staticPropertiesMapper(Constant.class, prop);</p>
	 * 
	 * @param cls (class that contain static property).
	 * @param p (java.util.Properties instance parsed from file).
	 * @throws Exception
	 */
	@SuppressWarnings("rawtypes")
	public static void staticPropertiesMapper(Class cls, Properties p) throws Exception {
		for (Field field : cls.getDeclaredFields()) {
			field.setAccessible(true);
			String key = field.getName().toLowerCase();
			String data = p.getProperty(key);
			if (data != null) {
				Class type = field.getType();
				if (type == String.class) {
					field.set(null, data);
				} else if (type == int.class || type == Integer.class) {
					field.set(null, Integer.valueOf(data));
				} else if (type == long.class || type == Long.class) {
					field.set(null, Long.valueOf(data));
				} else if (type == boolean.class || type == Boolean.class) {
					field.set(null, Boolean.valueOf(data));
				}
			}
		}
	}

	/**
	 * <p>Read a file into java.util.Properties instance.<br/> File can be a fullpath or filename.<br/>
	 * <b>Example</b>: "/home/ubuntu/config.properties"
	 * </p>
	 * @param filename
	 * @return java.util.Properties
	 * @throws IOException
	 */
	public static Properties readProperties(String filename) throws IOException {
		Properties prop = new Properties();
		InputStream inputStream = new FileInputStream(filename);
		prop.load(inputStream);
		return prop;
	}
}
