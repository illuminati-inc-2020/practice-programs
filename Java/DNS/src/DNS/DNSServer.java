/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package DNS;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.HashMap;
import javax.swing.JOptionPane;

/**
 *
 * @author Rakesh
 */
public class DNSServer {
	private HashMap<String, String> map=new HashMap<>();
	private void loadDomainNames() {
		InputStreamReader in = new InputStreamReader(getClass().getResourceAsStream("/DNS/name.txt"));
		int length=1;
		String sbuf="";
		try {
			while(length>0){
				char cbuf[]=new char[10000];
				length=in.read(cbuf);
				try{
					sbuf=sbuf+String.valueOf(cbuf, 0, length);
				}catch(StringIndexOutOfBoundsException ex){}
			}
			String[] str=sbuf.split("\n");
			for(String line : str) {
				map.put(line.split(" ")[0], line.split(" ")[1]);
			}
			in.close();
		} catch (IOException ex) {
			JOptionPane.showMessageDialog(null, ex, "File Load Error", JOptionPane.ERROR_MESSAGE);
			System.exit(0);
		}
	}
	/**
	 * @param args the command line arguments
	 */
	public static void main(String[] args) {
		DNSServer dnsserver=new DNSServer();
		dnsserver.loadDomainNames();
		try {
			ServerSocket serversocket=new ServerSocket(4444);
			while (true) {
				try {
					Socket socket = serversocket.accept();
					InputStream in = socket.getInputStream();
					byte[] b = new byte[1000];
					in.read(b);
					String msg = new String(b);
					System.out.println(msg.trim()+" -> "+dnsserver.map.get(msg.trim()));
					OutputStream out=socket.getOutputStream();
					if(dnsserver.map.containsKey(msg.trim()))
						out.write(dnsserver.map.get(msg.trim()).getBytes());
					else
						out.write("Not Found...".getBytes());
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
