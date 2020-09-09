/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package udp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import javax.swing.JOptionPane;

/**
 *
 * @author Rakesh
 */
public class Receiver {
	/**
	 * @param args the command line arguments
	 */
	public static void main(String[] args) {
		//Console console=new Console("UDP Server");
		//console.setVisible(true);
		try {
			DatagramSocket socket=new DatagramSocket(4444);
			try {
				while (true) {
					byte b[]=new byte[1000];
					DatagramPacket packet=new DatagramPacket(b, b.length);
					socket.receive(packet);
					System.out.println(new String(packet.getData()));
					System.out.println(packet.getPort());
					DatagramPacket packet2=new DatagramPacket("Rakesh".getBytes(), "Rakesh".length(), InetAddress.getByName("127.0.0.1"), packet.getPort());
					socket.send(packet2);
					//console.write(new String(packet.getData()));
				}
			}  catch (IOException ex) {
				JOptionPane.showMessageDialog(null, ex, "IOException", JOptionPane.ERROR_MESSAGE);
			}
			socket.close();
		} catch (SocketException ex) {
			JOptionPane.showMessageDialog(null, ex, "SocketException", JOptionPane.ERROR_MESSAGE);
		}
	}
}
