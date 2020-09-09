/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package DNS;

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
		try {
            Socket socket = new Socket("127.0.0.1", 4444);
            OutputStream out = socket.getOutputStream();
			String msg;
			if(args.length>1)
				msg=args[1];
			else
				msg=JOptionPane.showInputDialog(null, "Enter Domain Name : ", "DNS Client", JOptionPane.PLAIN_MESSAGE);
            out.write(msg.getBytes());
			InputStream in=socket.getInputStream();
			byte[] b = new byte[1000];
			in.read(b);
			msg = new String(b);
			System.out.println("IP: "+msg);
            socket.close();
        } catch (UnknownHostException ex) {
			JOptionPane.showMessageDialog(null, ex, "UnknownHostException", JOptionPane.ERROR_MESSAGE);
        } catch (IOException ex) {
			JOptionPane.showMessageDialog(null, ex, "IOException", JOptionPane.ERROR_MESSAGE);
        }
	}
}
