/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bitstuffing;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import javax.swing.JOptionPane;

/**
 *
 * @author Rakesh
 */
public class Sender {
	private static String stuffBit(String msg) {
		return msg.replaceAll("11111", "111110");
	}
	/**
	 * @param args the command line arguments
	 */
	public static void main(String[] args) {
		try {
            Socket socket = new Socket("127.0.0.1", 4444);
            OutputStream out = socket.getOutputStream();
			String msg;
			if(args.length>0)
				msg=args[0];
			else
				msg=JOptionPane.showInputDialog(null, "Enter Message : ", "Bit Stuffing", JOptionPane.PLAIN_MESSAGE);
            String stuffed_msg=stuffBit(msg);
			//JOptionPane.showMessageDialog(null, "Message sent: "+msg+"->"+stuffed_msg, "Data sent", JOptionPane.INFORMATION_MESSAGE);
			System.out.println("Data sent: "+stuffed_msg);
			out.write(stuffed_msg.getBytes());
            socket.close();
        } catch (UnknownHostException ex) {
			JOptionPane.showMessageDialog(null, ex, "UnknownHostException", JOptionPane.ERROR_MESSAGE);
        } catch (IOException ex) {
			JOptionPane.showMessageDialog(null, ex, "IOException", JOptionPane.ERROR_MESSAGE);
        }
	}
}
