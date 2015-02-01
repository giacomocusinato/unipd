import java.util.Random;

public class Distr{
    private final Object acqua = new Object();
    private final Object vino = new Object();
    private final Object aranciata = new Object();
    private int numCA = 0;
    private int numCV = 0;
    private int numCC = 0;

    public synchronized void setNumCA(){ this.numCA++; }
    public synchronized void setNumCV(){ this.numCV++; }
    public synchronized void setNumCC(){ this.numCC++; }
    public synchronized int getNumCA(){ return this.numCA; }
    public synchronized int getNumCV(){ return this.numCV; }
    public synchronized int getNumCC(){ return this.numCC; }

    public void riempiBicchiere(Cliente c){
        System.out.println("Riempio il bicchiere del cliente numero " + c.numCliente);
    }

    public class Cliente extends Thread{
        private int numCliente;
        private String tipoBevanda;

        public Cliente(int n, String b){
            this.numCliente = n;
            this.tipoBevanda = b;
        }

        public void run(){
            System.out.println("Sono il cliente numero " + this.numCliente + " e voglio bere " + this.tipoBevanda);
            if (this.tipoBevanda.equals("A")){
                synchronized (acqua){
                    setNumCA();
                    riempiBicchiere(this);
                }
            }
            if (this.tipoBevanda.equals("V")){
                synchronized (vino){
                    setNumCV();
                    riempiBicchiere(this);
                }
            }
            if (this.tipoBevanda.equals("C")){
                synchronized (aranciata){
                    setNumCC();
                    riempiBicchiere(this);
                }
            }
            System.out.println("Sono il cliente numero " + this.numCliente + " e ho bevuto " + this.tipoBevanda);
        }
    }

    public static void main( String[] argv){
        Distr distributore = new Distr();
        String[] bibite = {"A","V","C"};
        Random r = new Random();
        Cliente[] allThread = new Cliente[100];
        for (int i = 0; i < 100; i++){
            int idx = r.nextInt(bibite.length);
            String bevanda = bibite[idx];
            Cliente c = distributore.new Cliente(i, bevanda);
            allThread[i] = c;
            c.start();
        }
        for (int i = 0; i < 100; i++){
            try {
                allThread[i].join();
            } catch (InterruptedException e){}
        }
        System.out.println("TERMINATO. I clienti che hanno preso acqua sono: " + distributore.getNumCA()
        + ", quelli che hanno preso vino sono: " + distributore.getNumCV()
        + " e quelli che hanno preso aranciata sono: " + distributore.getNumCC());
    }
}
