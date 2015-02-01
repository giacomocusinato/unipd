import java.rmi.*;
import java.rmi.server.*;

interface IObj extends Remote {
    public void stampa() throws RemoteException;
}

public class Server extends UnicastRemoteObject implements IObj {
    Object lock = new Object();

    public Server() throws RemoteException {
        //stampaN();
    }

    public void stampa() throws RemoteException {
        for (int i = 0; i < 10; ++i) {
            synchronized (lock) {
                System.out.println("Remote");
            }
            //try { Thread.sleep(1); } catch (Exception e) { }
        }
    }

    private void stampaN() {
        synchronized(lock) {
            while (true) {
                for (int i = 0; i < 10; ++i) {
                    System.out.println(i + "");
                    //try { Thread.sleep(500); } catch (Exception e) { }
                }
            }
        }
    }

    public static void main(String[] args) {
        try {
            Server s = new Server();
            Naming.rebind("rmi://localhost/Obj", s);
        } catch (Exception e) { }

        System.out.println("Server pronto");
    }
}
