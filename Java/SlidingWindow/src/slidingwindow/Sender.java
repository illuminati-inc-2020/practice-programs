/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package slidingwindow;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import javax.swing.JOptionPane;

/**
 *
 * @author Rakesh
 */
public class Sender {
	public static int count=1;
	public static Socket socket=null;
	public static int window_size=0;
	public static final int max_window_size=5;
	/**
	 * @param args the command line arguments
	 */
	public static void main(String[] args) {
		SenderWindow win=new SenderWindow("Sender") {
			@Override
			void sendData() {
				if(window_size==max_window_size)
					return;
				try {
					OutputStream out=socket.getOutputStream();
					out.write(new String("Data "+count).getBytes());
					write("Data "+count);
					count++;
					window_size++;
				} catch (IOException ex) {
					JOptionPane.showMessageDialog(null, ex, "IOException", JOptionPane.ERROR_MESSAGE);
					System.exit(0);
				} 
			}
		};
		win.setVisible(true);
		try {
            socket=new Socket("127.0.0.1", 4444);
			while(true) {
				InputStream out = socket.getInputStream();
				byte[] b = new byte[1000];
				out.read(b);
				String msg=new String(b);
				win.addAck();
				window_size--;
			}
        } catch (IOException ex) {
			JOptionPane.showMessageDialog(null, ex, "IOException", JOptionPane.ERROR_MESSAGE);
			System.exit(0);
        }
	}
}
