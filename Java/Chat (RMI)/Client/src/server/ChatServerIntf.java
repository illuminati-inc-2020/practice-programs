package server;

import java.rmi.Remote;
import java.rmi.RemoteException;
 
public interface ChatServerIntf extends Remote {
    public void sendMessage(String sender, String msg) throws RemoteException;
	public String getMessageLog(int offset) throws RemoteException;
}