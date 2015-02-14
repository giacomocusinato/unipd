public class Torre {
    int n_InEntrata = 0;
    int n_InUscita = 0;
    Object tranisto = new Object();
    Thread guardiaEntrata;
    Thread guardiaUscita;

    public Torre(int n) {
        n_InEntrata = n;

        guardiaEntrata = new GuardiaInEntrata();
        guardiaUscita = new GuardiaInUscita();
        guardiaEntrata.start();
        guardiaUscita.start();

        aggiungiVisitatori();
    }

    private void aggiungiVisitatori() {
        for (int i = 0; i < 20; ++i) {
            n_InEntrata += 9;

            synchronized (guardiaEntrata) {
                guardiaEntrata.notifyAll();
            }

            try { Thread.sleep(200); }
            catch (InterruptedException e) { }
        }
    }

    public void salita() {
        synchronized (tranisto) {
            try {
                if (n_InEntrata >= 10) {
                    n_InEntrata -= 10;
                    n_InUscita += 10;
                    System.out.println("10 visitatori sono saliti");
                } else {
                    n_InUscita += n_InEntrata;
                    System.out.println(n_InUscita + " visitatori sono saliti");
                    n_InEntrata = 0;
                }

                synchronized (guardiaUscita) {
                    guardiaUscita.notify();
                }
                Thread.sleep(500);
            } catch (InterruptedException e) { }
        }
    }

    public void discesa() {
        synchronized (tranisto) {
            try {
                if (n_InUscita >= 10) {
                    n_InUscita -= 10;
                    System.out.println("10 visitatori sono scesi");
                } else {
                    System.out.println(n_InUscita + " visitatori sono saliti");
                    n_InUscita = 0;
                }
                Thread.sleep(500);
            } catch (InterruptedException e) { }
        }
    }


    class GuardiaInEntrata extends Thread {
        public void run() {
            synchronized (guardiaEntrata) {
                while (true) {
                    if (n_InEntrata > 0) {
                        salita();
                    } else {
                        try { wait(); }
                        catch (InterruptedException e) { }
                    }
                }
            }
        }
    }

    class GuardiaInUscita extends Thread {
        public void run() {
            synchronized (guardiaUscita) {
                while (true) {
                    if (n_InUscita > 0) {
                        discesa();
                    } else {
                        try { wait(); }
                        catch (InterruptedException e) { }
                    }
                }
            }
        }
    }

    public static void main(String[] args) {
        Torre t = new Torre(30);
    }
}