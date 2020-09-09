/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bitstuffing;

import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import javax.swing.JOptionPane;

/**
 *
 * @author Rakesh
 */
public class Receiver {
	private static String unstuffBit(String msg) {
		return msg.replaceAll("111110", "11111");
	}
	/**
	 * @param args the command line arguments
	 */
	public static void main(String[] args) {
		//Console console=new Console("TCP Server");
		//console.setVisible(true);
		try {
			ServerSocket server=new ServerSocket(4444);
			while (true) {
				try {
					Socket socket = server.accept();
					InputStream out = socket.getInputStream();
					byte[] b = new byte[1000];
					out.read(b);
					String msg=new String(b).trim();
					String unstuffed_msg=unstuffBit(msg);
					//console.write(msg+"\n\t->"+unstuffed_msg);
					System.out.println("Received Message: "+msg);
					System.out.println("After unstuffing Message: "+unstuffed_msg);
					socket.close();
				} catch (UnknownHostException ex) {
					JOptionPane.showMessageDialog(null, ex, "IOException", JOptionPane.ERROR_MESSAGE);
				}
			}
		} catch (IOException ex) {
			JOptionPane.showMessageDialog(null, ex, "IOException", JOptionPane.ERROR_MESSAGE);
		}
	}
}
