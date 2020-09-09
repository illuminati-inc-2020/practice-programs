package client;

import java.net.InetAddress;
import java.net.MalformedURLException;
import java.net.UnknownHostException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RMISecurityManager;
import java.rmi.RemoteException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
import server.ChatServerIntf;
 
public class ChatClient {
    private static ChatServerIntf server = null; 
	private static String ip = "";
	private static boolean connected=false;
	private static ClientWindow chatWindow;
    public static void main(String args[]) {
		System.setProperty("java.security.policy", "no.policy");
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new RMISecurityManager());
        }
		connect();
		chatWindow=new ClientWindow() {
			@Override
			public void onSendMessage(String msg) {
				try {
					server.sendMessage(chatWindow.getSenderName(), msg);
				} catch (RemoteException ex) {
					JOptionPane.showMessageDialog(null, ex.getMessage(), "Chat Client", JOptionPane.ERROR_MESSAGE);
				}
			}
		};
		new Thread(){
			@Override
			public void run() {
				while(chatWindow.isVisible()) {
					try {
						Thread.sleep(100);
						chatWindow.setMessageLog(chatWindow.getMessageLog()+server.getMessageLog(chatWindow.getMessageLog().length()));
					} catch (InterruptedException | RemoteException ex) {
						JOptionPane.showMessageDialog(null, ex, "Chat Client", JOptionPane.ERROR_MESSAGE);
						System.exit(0);
					}
				}
			}
		}.start();
    }
	private static void connect() {
		if(!connected) {
			try {
				ip=JOptionPane.showInputDialog(null, "Ip", InetAddress.getLocalHost().getHostAddress());
				server=(ChatServerIntf)Naming.lookup("//"+ip+"/ChatServer");
				connected=true;
			} catch (UnknownHostException | NotBoundException | MalformedURLException | RemoteException ex) {
				JOptionPane.showMessageDialog(null, ex, "Chat", JOptionPane.ERROR_MESSAGE);
				System.exit(0);
			}
		}
	}
}