package server;

import java.rmi.Naming;
import java.rmi.RMISecurityManager;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;
import javax.swing.JOptionPane;
 
public class RmiServer extends UnicastRemoteObject implements RmiServerIntf {
    public static final String MESSAGE = "Hello world";
 
    public RmiServer() throws RemoteException {
    }
 
	@Override
    public String getMessage() {
        return MESSAGE;
    }
 
 
    public static void main(String args[]) {
        System.out.println("RMI server started");
 
        // Create and install a security manager
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new RMISecurityManager());
            System.out.println("Security manager installed.");
        } else {
            System.out.println("Security manager already exists.");
        }
 
        try { //special exception handler for registry creation
            LocateRegistry.createRegistry(1099); 
            System.out.println("java RMI registry created.");
        } catch (RemoteException e) {
            //do nothing, error means registry already exists
            System.out.println("java RMI registry already exists.");
        }
		
		String ip=JOptionPane.showInputDialog(null, "IP");
        try {
            //Instantiate RmiServer
            RmiServer obj = new RmiServer();
 
            // Bind this object instance to the name "RmiServer"
            Naming.bind("//"+ip+"/RmiServer", obj);
 
            System.out.println("PeerServer bound in registry");
        } catch (Exception e) {
            System.err.println("RMI server exception:" + e);
            e.printStackTrace();
        }
    }
}