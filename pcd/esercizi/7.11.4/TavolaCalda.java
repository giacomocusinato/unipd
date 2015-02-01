class Cliente extends Thread {
    private TavolaCalda mensa;
    private static int nC;
    private int numero;

    // l'ordine di arrivo dei clienti corrisponde al numero assegnato da costruttore
    Cliente(TavolaCalda m) {
        mensa = m;
        numero = nC++;
    }

    public void run() {
        mensa.prendi_primo(numero);
        mensa.prendi_secondo(numero);
        mensa.paga(this);
    }

    // metodo invocato dal cassiere della tavola calda
    public void pagamento() {
        System.out.println(numero + " ha pagato");
    }
}


public class TavolaCalda {
    private int prox_primo_da_servire = 0;
    private int prox_secondo_da_servire = 0;
    private int tot_pagamenti = 0;
    private Object primo = new Object();
    private Object secondo = new Object();
    private Object cassa = new Object();

    void prendi_primo(int i) { // DA DEFINIRE
        try {
            synchronized (primo) {
                while (i != prox_primo_da_servire) {
                    primo.wait();
                }
                System.out.println(i + "ha ricevuto il primo");
                if (i==5) try { Thread.sleep(14); } catch(InterruptedException e){}
                prox_primo_da_servire++;
                primo.notifyAll();
            }
        } catch (Exception ex) { ex.printStackTrace(); }
    }

    void prendi_secondo(int i) { // DA DEFINIRE
        try {
            synchronized (secondo) {
                while (i != prox_secondo_da_servire) {
                    secondo.wait();
                }
                System.out.println(i + " ha ricevuto il secondo");
                prox_secondo_da_servire++;
                secondo.notifyAll();
            }
        } catch (Exception ex) { ex.printStackTrace(); }
    }

    void paga(Cliente c) { // DA DEFINIRE
        synchronized (cassa) {
            c.pagamento();
            tot_pagamenti++;
            cassa.notifyAll();
        }
    }

    private void genera_clienti(final int n) { // DA DEFINIRE
        Thread t = new Thread()
        {
            public void run() {
                for (int i = 0; i < n; ++i) {
                    new Cliente(TavolaCalda.this).start();
                }
            }
        };
        t.start();
    }

    private void attendi_clienti(final int n) { // DA DEFINIRE
        synchronized (cassa) {
            while(tot_pagamenti != n) {
                try {
                    cassa.wait();
                } catch (Exception ex) { ex.printStackTrace(); }
            }
        }
    }


    public static void main(String[] args) {
        TavolaCalda m = new TavolaCalda();
        m.genera_clienti(100);
        m.attendi_clienti(100);
    }
}
