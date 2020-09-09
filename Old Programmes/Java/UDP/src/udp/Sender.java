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
import java.net.UnknownHostException;
import javax.swing.JOptionPane;

/**
 *
 * @author Rakesh
 */
public class Sender {
	/**
	 * @param args the command line arguments
	 */
	public static void main(String[] args) {
		try {
			String msg;
			if(args.length>0)
				msg=args[0];
			else
				msg=JOptionPane.showInputDialog(null, "Enter Message : ", "UDP Client", JOptionPane.PLAIN_MESSAGE);
			byte b[]=msg.getBytes();
			DatagramPacket packet=new DatagramPacket(b, b.length, InetAddress.getByName("127.0.0.1"), 4444);
			DatagramSocket socket=new DatagramSocket();
			socket.send(packet);
			
			byte b2[]=new byte[1000];
			DatagramPacket packet2=new DatagramPacket(b2, b2.length);
			socket.receive(packet2);
			System.out.println(new String(packet2.getData()));
			socket.close();
		} catch (UnknownHostException ex) {
			JOptionPane.showMessageDialog(null, ex, "UnknownHostException", JOptionPane.ERROR_MESSAGE);
		} catch (SocketException ex) {
			JOptionPane.showMessageDialog(null, ex, "SocketException", JOptionPane.ERROR_MESSAGE);
		} catch (IOException ex) {
			JOptionPane.showMessageDialog(null, ex, "IOException", JOptionPane.ERROR_MESSAGE);
		}
	}
}
