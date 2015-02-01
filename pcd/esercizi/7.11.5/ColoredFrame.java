import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ColoredFrame extends JFrame {
    private Thread t = null;
    private boolean pause = false;
    private Object o = new Object();

    public ColoredFrame(String s) {
        super(s);
        setSize(400, 400);
        setLayout(new FlowLayout(FlowLayout.RIGHT, 40, 320));

        JButton buttonAvvia = new JButton("Avvia");
        JButton buttonPausa = new JButton("Pausa");
        JButton buttonStop = new JButton("Stop");

        add(buttonAvvia);
        add(buttonPausa);
        add(buttonStop);

        buttonAvvia.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (t == null) {
                    t = new T();
                    t.start();
                } else if (!t.isInterrupted()) {
                    synchronized(o) {
                        if (pause) {
                            pause = false;
                            o.notifyAll();
                        }
                    }
                }
            }
        });
        buttonPausa.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                pause = true;
            }
        });
        buttonPausa.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                t.interrupt();
            }
        });
    }

    private class T extends Thread {
        public void run() {
            while (true) {
                synchronized(o) {
                    while (!pause) {
                        getContentPane().setBackground(new Color(
                            (int)(Math.random()*255),
                            (int)(Math.random()*255),
                            (int)(Math.random()*255)
                        ));
                        try {
                            Thread.sleep(50);
                        } catch(InterruptedException ex) {
                            System.out.println("Interrupted on sleep()");
                            interrupt();
                            return;
                        }
                    }

                    try {
                        o.wait();
                    } catch (InterruptedException ex) {
                        System.out.println("Interrupted in wait()");
                        interrupt();
                        return;
                    }
                }
            }
        }
    }


    public static void main(String[] args) {
        ColoredFrame frame = new ColoredFrame("Esercizio 7.11.5");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}
