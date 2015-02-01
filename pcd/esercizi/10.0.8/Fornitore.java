public class Fornitore {
    public Fornitore() { }

    public synchronized Risorsa riproduci() throws InterruptedException {
        Thread.sleep(1000);
        return new Risorsa("mobile");
    }
}
