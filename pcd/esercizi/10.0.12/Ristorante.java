import java.lang.*;
import java.util.*;

public class Ristorante {
    private int nPrenotati = 0;
    private final int maxPrenotazioni = 30;
    private int nOverbooked = 0;
    private Vector<Cliente> overbooked = new Vector<Cliente>();
    private boolean stopPrenotazioni = false;

    public synchronized Risposta prenota(Cliente c) {
        if (stopPrenotazioni == true) {
            return new Risposta(0, false, false);
        }

        if (nPrenotati < maxPrenotazioni) {
            nPrenotati++;
            return new Risposta(nPrenotati, true, false);
        }

        // Non c'è posto ma le prenotazioni sono ancora aperte
        nOverbooked++;
        overbooked.add(c);
        return new Risposta(0, false, true);
    }

    public synchronized void disdici() {
        nPrenotati--;
        if (nOverbooked > 0) {
            Cliente c = overbooked.remove(0);
            nOverbooked--;
            nPrenotati++;
            c.avvisa(new Risposta(nPrenotati, true, false));
        }
    }

    public synchronized void stopPrenotazioni() {
        stopPrenotazioni = true;
        System.out.println("CHIUDONO LE PRENOTAZIONI, tot prenotati " + nPrenotati);
        System.out.println("CHIUDONO LE PRENOTAZIONI, tot respinti " + nOverbooked);
        for (int i = 0; i < nOverbooked; ++i) {
            Cliente c = overbooked.remove(0);
            c.avvisa(new Risposta(0, false, false));
        }
    }

    public static void main(String[] args) {
        Ristorante r = new Ristorante();
        Thread tempo = new Tempo(r);
        tempo.start();

        Cliente[] clienti = new Cliente[50];
        for (int i = 0; i < clienti.length; ++i) {
            clienti[i] = new Cliente(r, i);
            clienti[i].start();
        }

        for (Cliente c : clienti) {
            try { c.join(); } catch (InterruptedException e) { }
        }

        try { tempo.join(); } catch (InterruptedException e) { }

        System.out.println("MANCANO DUE GIORNI A CAPODANNO!");
    }
}


class Cliente extends Thread {
    private Ristorante r;
    private boolean prenotato = false;
    private boolean overbooking = false;
    private int id = 0;

    public Cliente(Ristorante rist, int i) { r = rist; id = i; }

    public synchronized void avvisa(Risposta risp) {
        prenotato = risp.prenotato();
        overbooking = risp.overbooking();
        notifyAll();
    }

    public void run() {
        Risposta risposta = r.prenota(this);
        prenotato = risposta.prenotato();
        overbooking = risposta.overbooking();

        synchronized (r) {
            while (overbooking) {
                try { wait(); } catch (InterruptedException e) {}
            }
        }

        if (prenotato) {
            //System.out.println("Prenotazione effettuata, num: " + risposta.nPrenotazione());
            System.out.println("Prenotazione effettuata, cliente: " + id);
        }

        int rand = (int) Math.random() * 10;
        if (prenotato && (rand % 3 == 0)) {
            r.disdici();
            //System.out.println("Disdetto prenotazione, num " + risposta.nPrenotazione());
            System.out.println("Disdetto prenotazione, cliente " + id);
        }
    }
}


class Tempo extends Thread {
    private Ristorante r;

    Tempo(Ristorante rist) { r = rist; }

    public void run() {
        for (int i = 1; i< 29; i++) {
            try { sleep(200); } catch (InterruptedException e) { }
        }
        r.stopPrenotazioni();
    }
}


class Risposta {
    public int nPrenotazione;
    public boolean prenotato;
    public boolean overbooking;

    Risposta(int n, boolean p, boolean o) {
        nPrenotazione = n;
        prenotato = p;
        overbooking = o;
    }

    public boolean prenotato() { return prenotato; }
    public boolean overbooking() { return overbooking; }
    public int nPrenotazione() { return nPrenotazione; }
}