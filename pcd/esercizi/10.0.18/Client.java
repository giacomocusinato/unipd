import java.rmi.*;

interface IObj extends Remote {
    public void stampa() throws RemoteException;
}


public class Client {
    public static final String remoteUri = "rmi://localhost/Obj";

    public Client() {
        new T1().start();
        new T2().start();
    }

    private void stampaC() {
        for (int i = 0; i < 10; ++i) {
            System.out.println("Client");
        }
    }

    class T1 extends Thread {
        public void run() {
            stampaC();
        }
    }

    class T2 extends Thread {
        public void run() {
            IObj remoteObj = null;
            try {
                remoteObj = (IObj) Naming.lookup("rmi://localhost/Obj");
            } catch (Exception e) { e.printStackTrace(); }

            try {
                while (true) remoteObj.stampa();
            } catch (Exception e) { e.printStackTrace(); }
        }

    }


    public static void main(String[] args) {
        Client c = new Client();
    }
}
