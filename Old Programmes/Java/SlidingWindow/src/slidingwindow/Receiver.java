/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package slidingwindow;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import javax.swing.JOptionPane;

/**
 *
 * @author Rakesh
 */
public class Receiver {
	public static Socket socket=null;
	public static int n_data=0;
	public static int n_ack=0;
	/**
	 * @param args the command line arguments
	 */
	public static void main(String[] args) {
		ReceiverWindow win=new ReceiverWindow("Receiver") {
			@Override
			void ack() {
				if(n_ack==n_data)
					return;
				try {
					OutputStream out=socket.getOutputStream();
					out.write(new String("ACK").getBytes());
					addAck();
					n_ack++;
				} catch (IOException ex) {
					JOptionPane.showMessageDialog(null, ex, "IOException", JOptionPane.ERROR_MESSAGE);
					System.exit(1);
				} 
			}
		};
		win.setVisible(true);
		try {
			ServerSocket server=new ServerSocket(4444);
			try {
				socket = server.accept();
				while(true) {
					InputStream out = socket.getInputStream();
					byte[] b = new byte[1000];
					out.read(b);
					String msg=new String(b);
					win.write(msg.trim());
					n_data++;
				}
			} catch (UnknownHostException ex) {
				JOptionPane.showMessageDialog(null, ex, "IOException", JOptionPane.ERROR_MESSAGE);
				System.exit(1);
			}
		} catch (IOException ex) {
			JOptionPane.showMessageDialog(null, ex, "IOException", JOptionPane.ERROR_MESSAGE);
			System.exit(1);
		}
	}
}
