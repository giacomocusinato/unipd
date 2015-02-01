import java.rmi.*;

interface I extends Remote {
    public void f();
    public void g();
}

public class Client1 {
    private static final String HOST = "localhost";

    public void m(String s) {
        for (int i = 0; i < 5; ++i) {
            System.out.println(s);
        }
    }

    public static void main(String[] args) {
        Client1 c1 = new Client1();

        String uri = "rmi://" + HOST + "/server-obj";
        I i = null; try {
            i = (I) Naming.lookup(uri);
        } catch (Exception ex) {
            ex.printStackTrace();
        }

        Thread t1 = new ClientThread(i, c1, true);
        Thread t2 = new ClientThread(i, c1, false);
        t1.start();
        t2.start();
    }
}

class ClientThread extends Thread {
    private I i = null;
    private Client1 c1 = null;
    private boolean b;

    public ClientThread(I in, Client1 client, boolean n) {
        i = in;
        c1 = client;
        b = n;
    }

    public void run() {
        if (b) {
            try {
                c1.m("A");
                i.f();
                c1.m("B");
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        } else {
            try {
                c1.m("UNO");
                i.g();
                c1.m("DUE");
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }
}
