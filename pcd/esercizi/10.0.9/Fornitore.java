public class Fornitore {
    public Risorsa riproduci() {
        try {
            System.out.println("Produco la risorsa...");
            sleep(400);
        } catch (Exception e) { }
        return new Risorsa("1");
    }
}

class Risorsa {
    public String nome;
    public Risorsa(String n) { nome = n; }
}

class Artigiano extends Thread {
    Fornitore fornitore;
    String id;

    public Artigiano(Fornitore f, String s) {
        fornitore = f;
        id = s;
    }

    public void run() {
        Risorsa r = fornitore.riproduci();

        while ()
    }

    private void lavora() {
        for (int i = 0; i < 100; ++i) {
            System.out.println(id + " procede con il lavoro");
        }
    }
}