public class Artigiano extends Thread {
    private boolean pronta = false;
    private Fornitore fornitore;
    private String nome;

    public Artigiano(String n, Fornitore f) {
        nome = n; fornitore = f;
    }

    class Lavora extends Thread {
        public void run() {
            for (int i = 0; i < 100; ++i) {
                System.out.println("L'artigiano " + nome + " procede con il lavoro");
            }
            synchronized(fornitore) {
                while (pronta == false) {
                    try {
                        fornitore.wait();
                    } catch (Exception ex) { ex.printStackTrace(); }
                }
                System.out.println("L'artigiano " + nome + " ha completo il lavoro iniziato");
            }
        }
    }

    class Attendi extends Thread {
        public void run() {
            try {
                Risorsa r = fornitore.riproduci();
                pronta = true;
                System.out.println("L'artigiano " + nome + " ha ricevuto: " + r.getNome());
                synchronized(fornitore) {
                    fornitore.notifyAll();
                }
            } catch (InterruptedException ex) { ex.printStackTrace(); }
        }


    }

    public void run() {
        Thread lavora = new Lavora();
        Thread attendi = new Attendi();

        attendi.start(); lavora.start();
    }

    public static void main(String[] args) {
        Fornitore fornitore = new Fornitore();

        Thread art1 = new Artigiano("Tizio", fornitore);
        Thread art2 = new Artigiano("Caio", fornitore);
        Thread art3 = new Artigiano("Sempronio", fornitore);

        art1.start();
        art2.start();
        art3.start();
    }
}
