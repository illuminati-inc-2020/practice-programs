/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package tcp;

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
public class Server {
	private static String msg;

	/**
	 * @param args the command line arguments
	 */
	public static void main(String[] args) {
		try {
			ServerSocket server=new ServerSocket(4444);
			while (true) {
				try {
					Socket socket = server.accept();
					InputStream out = socket.getInputStream();
					byte[] b = new byte[1000];
					out.read(b);
					msg = new String(b);
					//console.write(msg.trim());
					System.out.println(msg.trim());
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
