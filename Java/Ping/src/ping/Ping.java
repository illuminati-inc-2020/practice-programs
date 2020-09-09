/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ping;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.sql.Time;
import javax.swing.JOptionPane;

/**
 *
 * @author Rakesh
 */
public class Ping {
	public static boolean pinged=false, hostNotFound=false;
	/**
	 * @param args the command line arguments
	 */
	public static void main(String[] args) {
		//final Console console=new Console("Ping");
		//console.setVisible(true);
		final String ip;
		if(args.length>0)
			ip=args[0];
		else
			ip=JOptionPane.showInputDialog(null, "Enter Host : ", "IP", JOptionPane.PLAIN_MESSAGE);
		for(int i=0; i<10; i++) {
			Thread t = null;
			t=new Thread() {
				@Override
				public void run() {
					try {
						Socket socket = new Socket(ip, 4444);
						socket.getOutputStream().write(new byte[] {0x00});
						long startTime = System.currentTimeMillis();
						super.run();
						byte[] b=new byte[1];
						socket.getInputStream().read(b);
						if(b[0]==0x00) {
							pinged=true;
							//console.write("Pinging "+socket.getInetAddress()+" with 8 bytes of data, time: "+(System.currentTimeMillis()-startTime)+" ms");
							System.out.println("Pinging "+socket.getInetAddress()+" with 8 bytes of data, time: "+(System.currentTimeMillis()-startTime)+" ms");
						}
						socket.close();
					} catch (IOException ex) {
						//console.write("Host not found");
						System.out.println("Host not found");
						hostNotFound=true;
					}
				}
			};
			t.start();
			try {
				Thread.sleep(1000);
			} catch (InterruptedException ex) {
				JOptionPane.showMessageDialog(null, ex, "InterruptedException", JOptionPane.ERROR_MESSAGE);
			}
			if(t!=null && !pinged && !hostNotFound) {
				t.interrupt();
				//console.write("Connection timed out");
				System.out.println("Connection timed out");
			}
		}
	}
}
