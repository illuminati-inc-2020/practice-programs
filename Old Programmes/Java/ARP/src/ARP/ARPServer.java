/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ARP;

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
public class ARPServer {
	private HashMap<String, String> mapARP=new HashMap<>(), mapRARP=new HashMap<>();
	private void loadList() {
		InputStreamReader in = new InputStreamReader(getClass().getResourceAsStream("/ARP/name.txt"));
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
				mapARP.put(line.split(" ")[0], line.split(" ")[1]);
				mapRARP.put(line.split(" ")[1], line.split(" ")[0]);
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
		ARPServer arpserver=new ARPServer();
		arpserver.loadList();
		try {
			ServerSocket serversocket=new ServerSocket(4444);
			while (true) {
				try {
					Socket socket = serversocket.accept();
					InputStream in = socket.getInputStream();
					byte[] b = new byte[1000];
					in.read(b);
					String msg = new String(b);
					String res="";
					if(msg.startsWith("A")) {
						msg=msg.substring(1);
						if(arpserver.mapARP.containsKey(msg.trim()))
							res=arpserver.mapARP.get(msg.trim());
						else
							res="Not Found...";
					} else if(msg.startsWith("R")) {
						msg=msg.substring(1);
						if(arpserver.mapRARP.containsKey(msg.trim()))
							res=arpserver.mapRARP.get(msg.trim());
						else
							res="Not Found...";
					} else continue;
					System.out.println(msg.trim()+" -> "+res);
					OutputStream out=socket.getOutputStream();
					out.write(res.getBytes());
					socket.close();
				} catch (UnknownHostException ex) {
					JOptionPane.showMessageDialog(null, ex, "UnknownHostException", JOptionPane.ERROR_MESSAGE);
				}
			}
		} catch (IOException ex) {
			JOptionPane.showMessageDialog(null, ex, "IOException", JOptionPane.ERROR_MESSAGE);
		}
	}
}
