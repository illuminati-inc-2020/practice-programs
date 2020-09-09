/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ping;

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
public class PingServer {
	/**
	 * @param args the command line arguments
	 */
	public static void main(String[] args) {
		//Console console=new Console("Ping Server");
		//console.setVisible(true);
		try {
			ServerSocket server=new ServerSocket(4444);
			while (true) {
				try {
					Socket socket = server.accept();
					byte[] b=new byte[1];
					socket.getInputStream().read(b);
					if(b[0]==0x00) {
						//console.write(socket.getInetAddress()+" Pinging with 8 bytes of data");
						System.out.println(socket.getInetAddress()+" Pinging with 8 bytes of data");
						socket.getOutputStream().write(new byte[] {0x00});
					}
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
