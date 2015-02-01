import java.util.Vector;


class Aereo {
    public static int n;
    private int num;
    private String direzione;

    Aereo(String d) {
        num = n++;
        direzione = d;
    }

    // ATTENZIONE: invocare questo metodo quando l'aereo è in pista
    public void stampa() {
        System.out.println("aereo num: " + num + " " + direzione);
    }
}

class GeneraArrivi extends Thread {
    private Controllore contr;

    GeneraArrivi(Controllore c) { contr = c; }

    public void run() {
        while (true) {
            contr.add_arrivi(new Aereo("in arrivo"));
            try {
                sleep(1000);
            } catch (Exception ex) { }
        }
    }
}

class GeneraPartenze extends Thread {
    private Controllore contr;

    GeneraPartenze(Controllore c) { contr = c; }

    public void run() {
        while (true) {
            contr.add_partenze(new Aereo("in partenza"));
            try {
                sleep(1000);
            } catch (Exception ex) { }
        }
    }
}

public class Controllore extends Thread {
    private Vector<Aereo> coda_arrivi = new Vector<Aereo>();
    private Vector<Aereo> coda_partenze = new Vector<Aereo>();
    Object pista = new Object();

    void add_arrivi(Aereo a) { // DA DEFINIRE
        synchronized (coda_arrivi) {
            coda_arrivi.add(a);
            coda_arrivi.notifyAll();
        }
    }

    void add_partenze(Aereo a) { // DA DEFINIRE
        synchronized (coda_partenze) {
            coda_partenze.add(a);
            coda_partenze.notifyAll();
        }
    }

    private char prox_transito() {
        double r = Math.random();
        if (r > 0.5) return 'A';
        return 'P';
    }

    public void run() {
        while (true) {
            char c = prox_transito();
            if (c == 'A') gestisci_arrivo();
            else gestisci_partenza();
        }
    }

    private void gestisci_arrivo() { //DA DEFINIRE
        Aereo a = null;
        synchronized (coda_arrivi) {
            if (coda_arrivi.size() > 0) {
                a = coda_arrivi.remove(0);
            } else {
                new TS(coda_arrivi).start();
                return;
            }
        }
        synchronized(pista) {
            a.stampa();
        }
    }
    private void gestisci_partenza() { // DA DEFINIRE
        Aereo a = null;
        synchronized (coda_partenze) {
            if (coda_partenze.size() > 0) {
                a = coda_partenze.remove(0);
            } else {
                new TS(coda_partenze).start();
                return;
            }
        }
        synchronized(pista) {
            a.stampa();
        }
    }

    private class TS extends Thread {
        Vector<Aereo> coda;

        TS(Vector<Aereo> c) { coda = c; }

        public void run() {
            try {
                Aereo a = null;
                synchronized (coda) {
                    while (coda.isEmpty())
                        coda.wait();
                    a = coda.remove(0);

                }
                synchronized (pista) {
                    a.stampa();
                }
            } catch (Exception ex) { }

        }
    }

    public static void main(String[] args) {
        Controllore contr = new Controllore();
        GeneraArrivi gA = new GeneraArrivi(contr);
        GeneraPartenze gP = new GeneraPartenze(contr);
        gA.start();
        gP.start();
        contr.start();
    }
}
