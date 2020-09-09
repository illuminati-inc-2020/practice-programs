package client;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RMISecurityManager;
import java.rmi.RemoteException;
import javax.swing.JOptionPane;
import server.DNSServerInterface;
 
public class Client {
	private static DNSServerInterface dnsServer; 
    public static void main(String args[]) {
		System.setProperty("java.security.policy", "no.policy");
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new RMISecurityManager());
        }
		String ip=JOptionPane.showInputDialog(null, "IP", "localhost");
        try { 
            dnsServer = (DNSServerInterface)Naming.lookup("//"+ip+"/DNSServer");
        } catch (NotBoundException | MalformedURLException | RemoteException e) { 
			JOptionPane.showMessageDialog(null, e, "Server Look Up Error", JOptionPane.ERROR_MESSAGE);
			System.exit(0);
        }
		ClientWindow clientWindow=new ClientWindow() {
			@Override
			public String onFind() {
				super.onFind();
				try {
					return dnsServer.getIP(getName());
				} catch (RemoteException e) {
					JOptionPane.showMessageDialog(null, e, "Server Error", JOptionPane.ERROR_MESSAGE);
					System.exit(0);
					return "";
				}
			}
		};
    }
}