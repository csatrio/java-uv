package test.generic;

import java.util.Queue;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.ConcurrentLinkedDeque;

public class TestQueue {
	
	static class RateLimitter<T> extends TimerTask{
		Queue<T> q = new ConcurrentLinkedDeque<>();

		public void send(T data) {
			q.add(data);
		}
		
		@Override
		public void run() {
			StringBuilder sb = new StringBuilder();
			sb.append("limitter send: " + System.currentTimeMillis()).append("\n");
			while(!q.isEmpty()) {
				sb.append(q.poll()).append("\n");
			}
			System.out.println(sb.toString());
		}
	}

	public static void main(String[] args) throws InterruptedException {
		Timer t = new Timer();
		RateLimitter<String> limiter = new RateLimitter<String>();
		t.scheduleAtFixedRate(limiter, 0, 2500);
		
		for(long i=0;i<Long.MAX_VALUE;i++) {
			limiter.send("data:"+i);
			Thread.sleep(100);
		}
	}

}
