
import java.awt.FlowLayout;
import java.awt.LayoutManager;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

class WinTest extends JFrame implements ActionListener{
	JButton btn;
	JLabel lbl;
	JTextField txt;
	private void initComp(){

		this.setLayout(new FlowLayout());
		
		this.lbl=new JLabel("Give some text:");
		this.lbl.setLabelFor(txt);
		this.add(lbl);

		this.txt=new JTextField(20);
		this.add(txt);
		
		this.btn=new JButton("Hello");
		this.btn.addActionListener(this);
		this.add(btn);
		
		this.pack();
	}
	public WinTest() {
		super("Test window");
		initComp();
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		setVisible(true);
	}
	public void actionPerformed(ActionEvent e){
		System.out.println(txt.getText());
		txt.setText("");
		txt.grabFocus();
	}
	public static void main(String[]a){
		new WinTest();
	}
}