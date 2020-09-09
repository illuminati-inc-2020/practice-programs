package client;

import java.io.IOException;
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
    public static ChatServerIntf server = null; 
	public static String ip;
	public static ClientWindow chatWindow;
    public static void main(String args[]) {
		System.setProperty("java.security.policy", "no.policy");
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new RMISecurityManager());
        }
		try {
			//findReachableIps();
			ip=JOptionPane.showInputDialog(null, "IP", InetAddress.getLocalHost().getHostAddress());
			server=(ChatServerIntf)Naming.lookup("//"+ip+"/ChatServer");
		} catch (UnknownHostException | NotBoundException | MalformedURLException | RemoteException ex) {
			JOptionPane.showMessageDialog(null, ex, "Chat", JOptionPane.ERROR_MESSAGE);
			System.exit(0);
		}
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
	public static void findReachableIps() {
		try {
			/*for(int i=0; i<256; i++)
				for(int j=0; j<256; j++)
					if(InetAddress.getByName("169.254."+i+"."+j).isReachable(1))
						System.out.print("*");
					System.out.println("169.254."+i+"."+j);*/
			if(InetAddress.getByName("169.254.156.109").isReachable(1000))
				System.out.print("*");
		} catch (Exception ex) {
			Logger.getLogger(ChatClient.class.getName()).log(Level.SEVERE, null, ex);
		}
	}
}