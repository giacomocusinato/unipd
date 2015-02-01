class Ex {
    private Stato stato;
    private int threadCount = 0;

    public Ex(int n) {
        stato = new Stato(n);

        new T("essere").start();
        new T(" o ").start();
        new T("non essere?\n").start();
    }

    class Stato {
        private int current = 0;
        private final int range;

        public Stato(int thread_range) { range = thread_range; }
        public synchronized int get() { return current; }
        public synchronized void next() { current = (current + 1) % range; }
    }

    class T extends Thread {
        private int num;
        private String word;

        public T(String s) {
            word = s;
            num = threadCount++;
        }

        public void run() {
            System.out.println("Avvio thread numero " + num);
            while (true) {
                synchronized (stato) {
                    try {
                        while (stato.get() != num) {
                            stato.wait();
                        }
                    } catch (Exception ex) { }
                    System.out.print(word);
                    stato.next();
                    stato.notifyAll();
                } try {Thread.sleep(500);}catch(Exception ex) {}
            }
        }
    }

    public static void main(String[] args) {
        Ex e = new Ex(3);
        //Ex.T t1 = e.new T("essere");
        //Ex.T t2 = e.new T(" o ");
        //Ex.T t3 = e.new T("non essere?\n");

        /*
        Ex f = new Ex(2);
        Ex.T r1 = f.new T("ciao");
        Ex.T r2 = f.new T(" pippo\n");
        */

        //t1.start(); t2.start(); t2.start();
        //r1.start(); r2.start();
    }


}
