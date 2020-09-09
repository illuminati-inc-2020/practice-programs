import java.lang.*;

class th{
	public static void main(String[] argv){
		new RunnableThread("Fast",3000);
		new RunnableThread("Slow",5000);
	}
}

class RunnableThread implements Runnable{
	private Thread t;
	private String name;
	private long delay;
	public RunnableThread(String name,long delay){
		this.name=name;
		this.delay=delay;
		t=new Thread(this,name);
		System.out.println(t+" started");
		t.start();
	}
	public void run(){
		try{
			for(int i=5;i>0;i--){
				System.out.println(t+" counts "+i);
				Thread.sleep(this.delay);
			}
		}catch(InterruptedException e){
			System.out.println(t+" interrupted");
		}
		System.out.println(t+" exited");
	}
}