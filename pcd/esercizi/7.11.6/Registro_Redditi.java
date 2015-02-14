import java.util.*;

public class Registro_Redditi {
    private int dim_famiglia;
    private List<Integer> registro = new ArrayList<Integer>();
    private boolean sconto_usato = false;
    private int figli_reg = 0;

    public Registro_Redditi(int dim) {
        dim_famiglia = dim;
    }

    public int riassunto() {
        int somma = 0;
        for (int n : registro) {
            System.out.println("Reddito persona: " + n);
            somma = somma + n;
        }
        return somma;
    }

    public void aggiungiReddito(int r) {
        registro.add(r);
    }

    public void contaFiglioRegistrato() {
        figli_reg++;
    }

    public int figliRegistrati() {
        return figli_reg;
    }

    public boolean scontoUsato() {
        return sconto_usato;
    }
    public void usaSconto() {
        sconto_usato = true;
    }

    public int redditoFigli(int nFigli) {
        int somma = 0;
        for (int i = 0; i < nFigli; ++i) {
            somma = somma + registro.get(i);
        }
        return somma;
    }

    public static void main(String[] args) {
        Registro_Redditi r = new Registro_Redditi(6);
        Thread f1 = new Figlio(r);
        Thread f2 = new Figlio(r);
        Thread f3 = new Figlio(r);
        Thread f4 = new Figlio(r);
        Thread g1 = new Genitore(r, 4);
        Thread g2 = new Genitore(r, 4);

        f1.start(); f2.start(); f3.start(); f4.start();
        g1.start(); g2.start();

        try {
            g1.join(); g2.join();
        } catch (InterruptedException e) { System.out.println("HELLO"); }

        System.out.println("Somma redditi: " + r.riassunto());
    }
}


class Membro_Famiglia extends Thread {
    protected Registro_Redditi registro;

    public Membro_Famiglia(Registro_Redditi r) {
        registro = r;
    }
}

class Figlio extends Membro_Famiglia {
    public Figlio(Registro_Redditi r) {
        super(r);
    }
    public void run() {
        int reddito = 6; //(int)Math.random()*10000;
        try {
            sleep(400);
        } catch(InterruptedException e) { }
        synchronized (registro) {
            registro.aggiungiReddito(reddito);
            registro.contaFiglioRegistrato();
            registro.notifyAll();
        }
    }
}

class Genitore extends Membro_Famiglia {
    private int nFigli;

    public Genitore(Registro_Redditi r, int n) {
        super(r);
        nFigli = n;
    }

    public void run() {
        int reddito = 14; //(int)Math.random()*10000;
        try {
            sleep(400);
        } catch(InterruptedException e) { }
        synchronized (registro) {
            while (registro.figliRegistrati() < nFigli) {
                try { registro.wait(); }
                catch (InterruptedException e) { }
            }

            if (!registro.scontoUsato()) {
                reddito = (int) (reddito - (registro.redditoFigli(nFigli) * 0.05));
                registro.usaSconto();
            }

            registro.aggiungiReddito(reddito);
        }
    }
}