import java.rmi.*;
import java.rmi.server.*;


interface I extends Remote {
    public void f() throws RemoteException;
    public void g() throws RemoteException;
}


public class ServerObj extends UnicastRemoteObject implements I {
    private static final String HOST = "localhost";
    Object obj = new Object();

    public ServerObj() throws RemoteException { }

    public void f() throws RemoteException {
        synchronized (obj) {
            for (int i = 0; i < 5; ++i) {
                System.out.println("FF");
            }
        }
    }

    public void g() throws RemoteException {
        for (int i = 0; i < 5; ++i) {
            System.out.println("GG");
        }
    }

    public static void main(String[] args) {
        ServerObj server = null;
        try {
            server = new ServerObj();
        } catch (Exception ex) {
            System.out.println("Server Error!");
            //ex.printStackTrace();
        }

        String uri = "rmi://" + HOST + "/server-obj";
        try {
            Naming.rebind(uri, server);
        } catch(Exception ex) {
            ex.printStackTrace();
        }

        System.out.println("Server pronto");
    }
}
