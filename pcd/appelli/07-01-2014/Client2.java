import java.rmi.*;

interface I extends Remote {
    public void f();
    public void g();
}

public class Client2 {
    private static final String HOST = "localhost";
    public void m(String s) {
        for (int i = 0; i < 5; ++i) {
            System.out.println(s);
        }
    }

    public static void main(String[] args) {
        Client2 c2 = new Client2();

        String uri = "rmi://" + HOST + "/server-obj";
        I i = null; try {
            i = (I) Naming.lookup(uri);
        } catch (Exception ex) {
            ex.printStackTrace();
        }

        i.f();
    }
}
