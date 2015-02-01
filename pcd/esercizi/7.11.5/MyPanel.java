import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

import javax.swing.*;

public class MyPanel extends JFrame {
    private JButton avvia;
    private JButton pausa;
    private JButton stop;
    public Object o = new Object();
    avvioThread t1;

    private boolean attesa = false;


    public MyPanel() {
        super("Esercizio 7.9.3");
        setSize(200,200);
        avvia = new JButton("Avvia");
        pausa = new JButton("Pausa");
        stop = new JButton("Stop");

        avvia.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (t1 == null) {
                    t1 = new avvioThread();
                    t1.start();
                }
                else if (!t1.isInterrupted()){
                    if (attesa == true)
                    synchronized(o) {
                        attesa = false;
                        o.notify();
                    }
                }
            }
        });

        pausa.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                attesa = true;
            }
        });

        stop.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                t1.interrupt();
            }
        });

        setLayout(new FlowLayout());
        add(avvia); add(pausa); add(stop);
    }

    public static void main(String[] args) {
        MyPanel p = new MyPanel();
        p.setVisible(true);
        p.setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    private class avvioThread extends Thread {
        public void run() {
            while(true) {
                synchronized(o) {
                    while(attesa == false) {
                        Random r = new Random();
                        getContentPane().setBackground(new Color(r.nextInt(255),r.nextInt(255),r.nextInt(255)));
                        try {
                            this.sleep(30);
                        } catch (InterruptedException e) {
                            interrupt();
                            System.out.println(isInterrupted() + "- Thread interrotto durante lo sleep");
                            return;
                        }
                    }
                    try {
                        o.wait();
                    } catch (InterruptedException e) {
                        interrupt();
                        System.out.println(isInterrupted() + "- Thread interrotto durante il wait");
                        return;
                    }
                }
            }
        }
    }
}
