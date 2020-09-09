import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.HashMap;


import javax.swing.JFrame;
import javax.swing.JTextArea;


class TestWindow extends JFrame{
	JTextArea txt;
	public TestWindow() {
		super("Testing");
		initComp();
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
	 	Dimension d=getToolkit().getScreenSize();
	 	setLocation((d.width-getWidth())/2,(d.height-getHeight())/2);
		setVisible(true);
	}
	private void initComp(){
		
		setLayout(new FlowLayout());
		
		txt=new JTextArea(20,50);
		txt.setFont(Font.decode("Bangla Akademi 20"));
		String str="\u0986\u09AE\u09BE\u09B0 \u09A8\u09BE\u09AE "
				+ "\u09B8\u0982\u0995\u09B0\u09CD\u09B7\u09A3 "
				+ "\u0995\u09C1\u09A8\u09CD\u09A1\u09C1\u09F7\n"
				+ "\u09A4\u09CB\u09AE\u09BE\u09B0 \u09A8\u09BE\u09AE "
				+ "\u0995\u09BF?\n";
		txt.setText(str);
		txt.addKeyListener(new KeyAdapter() {
			public void keyTyped(KeyEvent e){
				
				HashMap<Character,String> hm=new HashMap<Character,String>();
				hm.put('a', "\u0985");
				hm.put('A', "\u09BE");
				hm.put('m', "\u09AE");
				hm.put('r', "\u09B0");
				hm.put('i', "\u09BF");
				
				char key=e.getKeyChar();
				if(hm.containsKey(key))
				{
					txt.insert(hm.get(key), txt.getCaretPosition());
					e.setKeyChar('\0');
				}
			}
		});
		txt.setCaretPosition(str.length());
		add(txt);
		pack();
	}

	public static void main(String[]arg){
		new TestWindow();
	}
}