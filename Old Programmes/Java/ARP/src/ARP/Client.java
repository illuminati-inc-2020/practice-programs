/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ARP;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import javax.swing.JOptionPane;

/**
 *
 * @author Rakesh
 */
public class Client {
	/**
	 * @param args the command line arguments
	 */
	public static void main(String[] args) {
		String msg="";
		if(args.length==2 && args[0].equals("ARP"))
			msg="A"+args[1];
		else if(args.length==2 && args[0].equals("RARP"))
			msg="R"+args[1];
		else {
			System.out.println("Format : arp.Client <ARP/RARP> <parameter>");
			System.exit(1);
		}
		try {
            Socket socket = new Socket("127.0.0.1", 4444);
            OutputStream out = socket.getOutputStream();
            out.write(msg.getBytes());
			InputStream in=socket.getInputStream();
			byte[] b = new byte[1000];
			in.read(b);
			msg = new String(b);
			System.out.println((args[0].equals("ARP"))?"MAC: ":"IP "+msg.trim());
            socket.close();
        } catch (UnknownHostException ex) {
			JOptionPane.showMessageDialog(null, ex, "UnknownHostException", JOptionPane.ERROR_MESSAGE);
        } catch (IOException ex) {
			JOptionPane.showMessageDialog(null, ex, "IOException", JOptionPane.ERROR_MESSAGE);
        }
	}
}
