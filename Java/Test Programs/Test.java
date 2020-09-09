import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.HashMap;
import javax.swing.JFrame;
import javax.swing.JTextArea;

class Test extends JFrame{
	public Test() {
		super("Testing");
		
		pack();
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
	 	Dimension d=getToolkit().getScreenSize();
	 	setLocation((d.width-getWidth())/2,(d.height-getHeight())/2);
		setVisible(true);
	}
	public static void main(String[]arg){
		new Test();
	}
}