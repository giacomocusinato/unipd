import java.util.HashSet;
import java.lang.String;

class Auto extends Thread {
    private Integer distanza;
    private Rotatoria rotatoria;
    private Integer direzione; // Nord=0 Est=1 Sud=2 Ovest=3

    Auto(Integer d, Rotatoria r, Integer dir) {
        distanza = d;
        rotatoria = r;
        direzione = dir;
    }

    public void run() {
        try {
            while(distanza > 0) {
                distanza--;
                sleep(((int)Math.random())*50);
            }
            // ora auto è all'imbocco della rotatoria
            rotatoria.entraRotatoria(direzione);
            sleep(((int)Math.random())*50); // auto resta nella rotatoria
            rotatoria.esciRotatoria(direzione);
        } catch (InterruptedException ex) { ex.printStackTrace(); }
    }
}


public class Rotatoria {
    HashSet<Integer> nellaRotatoria = new HashSet<>();

    public Rotatoria() { }

    public void entraRotatoria(Integer dir) {
        synchronized(this) {
            while(nellaRotatoria.contains(leftDirection(dir))) {
                try {
                    wait();
                } catch (Exception ex) { ex.printStackTrace(); }
            }
            nellaRotatoria.add(dir);
            System.out.println("Macchina " + dir + " entrata in rotatoria");
        }

    }

    public void esciRotatoria(Integer dir) {
        synchronized(this) {
            if (nellaRotatoria.contains(dir)) {
                nellaRotatoria.remove(dir);
            }
            try {
                notifyAll();
            } catch (Exception ex) { ex.printStackTrace(); }

            System.out.println("Macchina " + dir + " uscita dalla rotatoria");
        }
    }

    private Integer leftDirection(Integer dir) {
        if (dir == 3) {
            return 0;
        }
        return dir + 1;
    }
}


class QuattroAuto {
    public static void main(String[] args) {
        Rotatoria r = new Rotatoria();

        Auto[] a = new Auto[4];
        for (Integer i = 0; i < 4; ++i) {
            a[i] = new Auto(10, r, i);
            a[i].start();
        }
    }
}
