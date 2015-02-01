import java.util.Random;

public class Distributore {

    private Object acqua = new Object();
    private Object aranciata = new Object();
    private Object vino = new Object();

    private boolean acquaFree = true;
    private boolean arFree = true;
    private boolean vinoFree = true;

    enum Bevanda {
        ACQUA,
        ARANCIATA,
        VINO;

        public String toString() {
            switch(this) {
                case ACQUA: return "acqua";
                case ARANCIATA: return "aranciata";
                case VINO: return "vino";
                default: throw new IllegalArgumentException();
            }
        }
        public static Bevanda fromInteger(int n) {
            switch(n) {
                case 0: return ACQUA;
                case 1: return ARANCIATA;
                case 2: return VINO;
                default: throw new IndexOutOfBoundsException();
            }
        }

    }

    public void riempiBicchiere(Integer num, Bevanda bevanda) {
        System.out.printf("Riempio il bicchiere del cliente %d con %s\n",
            num, bevanda.toString());
        //for (int i = 0; i < 10000; ++i) { }
        /*
        try {
            Thread.sleep(200);
        } catch (InterruptedException e) { }
        */
    }

    public void generaClienti() {
        Cliente[] clienti = new Cliente[100];
        int[] bevandeCount = new int[3];

        for (int i = 0; i < 100; ++i) {
            Random rand = new Random();
            int r = rand.nextInt(3);

            switch (r) {
                case 0: bevandeCount[0]++;
                    break;
                case 1: bevandeCount[1]++;
                    break;
                case 2: bevandeCount[2]++;
                    break;
            }

            clienti[i] = new Cliente(i, Bevanda.fromInteger(r));
            clienti[i].start();
        }

        for (int i = 0; i < 100; ++i) {
            try {
                clienti[i].join();
            } catch (InterruptedException e) { }
        }

        System.out.printf("Numero clienti che hanno preso acqua: %d\n", bevandeCount[0]);
        System.out.printf("Numero clienti che hanno preso aranciata: %d\n", bevandeCount[1]);
        System.out.printf("Numero clienti che hanno preso vino: %d\n", bevandeCount[2]);
    }


    class Cliente extends Thread {
        Integer num;
        Bevanda bevanda;

        public Cliente(Integer n, Bevanda b) {
            num = n;
            bevanda = b;
        }

        public void run() {

            // Prendo i lock per la bevanda in questione
            /*
            Object obj = null;
            boolean b = false;
            switch (bevanda) {
                case ACQUA: obj = acqua; b = acquaFree;
                case ARANCIATA: obj = aranciata; b = arFree;
                case VINO: obj = vino; b = vinoFree;
            }

            System.out.printf("Sono il cliente %d e voglio bere %s\n", num, bevanda.toString());

            synchronized (obj) {
                while (!b)
                try {
                    obj.wait();
                } catch (InterruptedException e) { }

                riempiBicchiere(num, bevanda);

                System.out.printf("Sono il cliente %d e ho bevuto %s\n", num, bevanda.toString());
                obj.notifyAll();
            } */
            System.out.printf("Sono il cliente %d e voglio bere %s\n", num, bevanda.toString());

            if (bevanda == Bevanda.ACQUA) {
                synchronized (acqua) {
                    /*while (!acquaFree)
                    try {
                        acqua.wait();
                    } catch (InterruptedException e) { }*/

                    riempiBicchiere(num, bevanda);

                    //acqua.notify();
                }
            } else if (bevanda == Bevanda.ARANCIATA) {
                synchronized (aranciata) {
                    /*while (!arFree)
                    try {
                        aranciata.wait();
                    } catch (InterruptedException e) { }*/

                    riempiBicchiere(num, bevanda);

                    //aranciata.notify();
                }

            } else {
                synchronized (vino) {
                    /*while (!vinoFree)
                    try {
                        vino.wait();
                    } catch (InterruptedException e) { }*/

                    riempiBicchiere(num, bevanda);

                    //vino.notifyAll();
                }
            }
            
            System.out.printf("Sono il cliente %d e ho bevuto %s\n", num, bevanda.toString());

        }
    }

    public static void main(String[] args) {
        Distributore d = new Distributore();
        d.generaClienti();
    }
}
