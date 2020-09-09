package server;

import java.rmi.Remote;
import java.rmi.RemoteException;
 
public interface ARPServerInterface extends Remote {
    public String getMAC(String name) throws RemoteException;
    public String getIP(String name) throws RemoteException;
}