import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Graphics;

import javax.swing.JFrame;
import javax.swing.JPanel;

class TestWindow extends JFrame {
	private GraphicsPanel graph=new GraphicsPanel();
	public TestWindow() {
		super("TestWindow");
		initComponent();
		pack();
		setLocation((getToolkit().getScreenSize().width-WIDTH)/2, (getToolkit().getScreenSize().height-HEIGHT)/2);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);
	}
	private void initComponent(){
		setLayout(new FlowLayout());
		add(graph);
	}
	public static void main(String[] arg) {
		new TestWindow();
	}
}

class GraphicsPanel extends JPanel {
	public GraphicsPanel() {
		super();
	}
	protected void paintComponent(Graphics g) {
		g.create();
		g.setColor(Color.red);
		g.fillOval(0, 0, 100, 100);
	}
}