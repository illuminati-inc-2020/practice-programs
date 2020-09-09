package server;

import java.rmi.Remote;
import java.rmi.RemoteException;
 
public interface DNSServerInterface extends Remote {
    public String getIP(String name) throws RemoteException;
}