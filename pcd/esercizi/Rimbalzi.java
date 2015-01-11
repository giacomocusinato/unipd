import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import java.util.*;
import javax.swing.*;

public class Rimbalzi {
	public static void main(String[] args) {
		JFrame frame = new RimbalziFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}

class RimbalziFrame extends JFrame {
	private JBallPanel panel;

	public RimbalziFrame() {
		setSize(450, 350);
		setTitle("Rimbalzi");
		panel = new JBallPanel();
		add(panel, BorderLayout.CENTER); // aggiunto pannello di sfondo

		// costruisco pannello con due bottoni
		JPanel p = new JPanel();
		JButton b1 = new JButton("Start");
		p.add(b1);
		b1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				addBall();
			}
		});
		JButton b2 = new JButton("Close");
		p.add(b2);
		b2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
		add(p, BorderLayout.SOUTH);
	}

	public void addBall() {
		try {
			Ball ball = new Ball();
			panel.add(ball);

			for (int i = 1; i <= 1000; ++i) {
				ball.move(panel.getBounds());
				panel.paint(panel.getGraphics());
				Thread.sleep(3);
			}
		} catch (InterruptedException e) {}
	}
} 

class JBallPanel extends JPanel {
	private ArrayList<Ball> balls = new ArrayList<Ball>();

	public void add(Ball b) {
		balls.add(b);
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		Graphics2D g2 = (Graphics2D)g;
		for (Ball b : balls) {
			g2.fill(b.getShape());
		}
	}
}

class Ball {
	private static final int XSIZE = 15;
	private static final int YSIZE = 15;
	private double x = 0; 
	private double y = 0; 
	private double dx = 2; 
	private double dy = 2; 

	public Ellipse2D getShape() {
		return new Ellipse2D.Double(x, y, XSIZE, YSIZE);
	}

	/* sposta la pallin nella posizione successiva,
	   invertendo la direzione se incontra uno dei bordi */
	public void move(Rectangle2D bounds) {
		x += dx; 
		y += dy;

		if (x < bounds.getMinX()) {
			x = bounds.getMinX();
			dx = -dx;
		}
		if (x + XSIZE > bounds.getMaxX()) {
			x = bounds.getMaxX() - XSIZE;
			dx = -dx;
		}
		if (y < bounds.getMinY()) {
			y = bounds.getMinY();
			dy = -dy;
		}
		if (y + XSIZE > bounds.getMaxY()) {
			y = bounds.getMaxY() - YSIZE;
			dy = -dy;
		}
	}
}