package server;

import java.net.InetAddress;
import java.net.MalformedURLException;
import java.net.UnknownHostException;
import java.rmi.AlreadyBoundException;
import java.rmi.Naming;
import java.rmi.RMISecurityManager;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
 
public class ChatServer extends UnicastRemoteObject implements ChatServerIntf {
	private static ServerWindow chatWindow;
	public ChatServer() throws RemoteException {}
	public static void main(String args[]) {
		System.setProperty("java.security.policy", "no.policy");
		try {
		System.out.print(InetAddress.getLocalHost().getHostAddress());
		} catch (UnknownHostException ex) {
			JOptionPane.showMessageDialog(null, ex, "Chat Server", JOptionPane.ERROR_MESSAGE);
		}
        System.out.println("RMI server started");
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new RMISecurityManager());
            System.out.println("Security manager installed.");
        } else {
			JOptionPane.showMessageDialog(null, "Security manager already exists.", "Chat Server", JOptionPane.ERROR_MESSAGE);
			System.exit(0);
        }
        try {
            LocateRegistry.createRegistry(1099); 
            System.out.println("java RMI registry created.");
        } catch (Exception e) {
			JOptionPane.showMessageDialog(null, "java RMI registry already exists.", "Chat Server", JOptionPane.ERROR_MESSAGE);
			System.exit(0);
        }
        try {
			String ip=InetAddress.getLocalHost().getHostAddress();
            ChatServer obj = new ChatServer();
            Naming.bind("//"+ip+"/ChatServer", obj);
            System.out.println("PeerServer bound in registry");
			chatWindow=new ServerWindow(ip);
			chatWindow.setVisible(true);
        } catch (UnknownHostException | RemoteException | AlreadyBoundException | MalformedURLException e) {
			JOptionPane.showMessageDialog(null, e.getMessage(), "Chat Server", JOptionPane.ERROR_MESSAGE);
        }
    }
	@Override
	public void sendMessage(String sender, String msg) throws RemoteException {
		chatWindow.addMessage(sender, msg);
	}
	@Override
	public String getMessageLog(int offset) throws RemoteException {
		try{
			return chatWindow.getMessageLog().substring(offset);
		} catch(ArrayIndexOutOfBoundsException ex) {}
		return "";
	}
}