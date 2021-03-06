/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lexicalanalyzer;

import java.util.ArrayList;
import java.util.Arrays;

/**
 *
 * @author Rakesh
 */
public class LexicalAnalyzer extends javax.swing.JFrame {
	private String[] operator={
			"+", "-", "*", "/", "%", "=", 
			"(", ")", "{", "}", 
			"+=", "-=", "/=", "+=", "%=", "&=", "|=", "++", "--", 
			"&&", "||", "&", "|", "~", "!", "^",
			"==", ">=", "<=", "!=", "<", ">",
			":", "?", ".", "->", ",",
			"\"", "\'", "#", "//", "/*", "*/"};
	private String[] keyword={
			"int", "float", "char", "void",
			"for", "if", "while", "do"};
	private ArrayList<String> tokens=new ArrayList<>();
		
	/**
	 * Creates new form LexicalAnalyzer
	 */
	public LexicalAnalyzer() {
		initComponents();
	}

	/**
	 * This method is called from within the constructor to initialize the form.
	 * WARNING: Do NOT modify this code. The content of this method is always
	 * regenerated by the Form Editor.
	 */
	@SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jScrollPane1 = new javax.swing.JScrollPane();
        list = new javax.swing.JList();
        jScrollPane2 = new javax.swing.JScrollPane();
        txt = new javax.swing.JTextArea();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Lex");

        list.setFont(new java.awt.Font("Monospaced", 0, 10)); // NOI18N
        jScrollPane1.setViewportView(list);

        txt.setColumns(20);
        txt.setRows(5);
        txt.setText("int main() {\n\tchar* s=\"Hello\";\n\tint a, b=1, c='a';\n\ta=b+c;\n}");
        txt.addCaretListener(new javax.swing.event.CaretListener() {
            public void caretUpdate(javax.swing.event.CaretEvent evt) {
                txtCaretUpdate(evt);
            }
        });
        jScrollPane2.setViewportView(txt);

        jLabel1.setText("Input string :");

        jLabel2.setText("Tokens :");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 380, Short.MAX_VALUE)
                    .addComponent(jScrollPane2)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jLabel1)
                            .addComponent(jLabel2))
                        .addGap(0, 0, Short.MAX_VALUE)))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 76, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jLabel2)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 451, Short.MAX_VALUE)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents
	private boolean contains(String []array, String s) {
		for(String e : array) {
			if(e.equals(s))
				return true;
		}
		return false;
	}
	
	private void addToken(String token) {
		if(token.trim().isEmpty())
			return;
		if(token.charAt(0)=='\"') 
			tokens.add("String     : "+token);
		else if(Character.isDigit(token.charAt(0)) || token.charAt(0)=='\'')
			tokens.add("Constants  : "+token);
		else if(contains(operator, token))
			tokens.add("Operator   : "+token);
		else if(contains(keyword, token))
			tokens.add("Keyword    : "+token);
		else
			tokens.add("Identifier : "+token);
	}
	
	public void tokenize() {
		//list.setListData(s.split("[ \t\n]*\\b"));
        //list.setListData(s.split("!(([a-zA-Z_][a-zA-Z_0-9]*)|([0-9])|([=+-]))"));
		
		list.removeAll();
		tokens.clear();
        String s=txt.getText();
		String token="";
		boolean isOperator=false, isString=false, escape=false;
		for(int i=0; i<s.length(); i++) {
			char c=s.charAt(i);
			if(c=='\"' || c=='\'') {
				if(token.charAt(token.length()-1)=='\\')
					escape=!escape;
				if(isString) {
					if(escape) {
						token+=c;
						escape=false;
					} else {
						isString=false;
						token+=c;
						addToken(token);
						token="";
					}
				} else {
					addToken(token);
					token=""+c;
					isString=true;
				}
			} else if(isString) {
				token+=c;
			} else {
				if(Character.isAlphabetic(c) || Character.isDigit(c)) {
					if(isOperator!=false) {
						addToken(token);
						token="";
					}
					token+=c;
					isOperator=false;
				} else if("=+-*/%(){}[],;.~!|&<>!#^-\"\'".contains(""+c)) {
					if(isOperator!=true || !contains(operator, token+c)) {
						addToken(token);
						token="";
					}
					token+=c;
					isOperator=true;
				} else {
					addToken(token);
					token="";
					isOperator=false;
				}
			}
		}
		addToken(token);
		list.setListData(tokens.toArray());
	}
	
    private void txtCaretUpdate(javax.swing.event.CaretEvent evt) {//GEN-FIRST:event_txtCaretUpdate
        tokenize();
    }//GEN-LAST:event_txtCaretUpdate

	/**
	 * @param args the command line arguments
	 */
	public static void main(String args[]) {
		/* Set the Nimbus look and feel */
		//<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
		 * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
		 */
		try {
			for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
				if ("Nimbus".equals(info.getName())) {
					javax.swing.UIManager.setLookAndFeel(info.getClassName());
					break;
				}
			}
		} catch (ClassNotFoundException ex) {
			java.util.logging.Logger.getLogger(LexicalAnalyzer.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		} catch (InstantiationException ex) {
			java.util.logging.Logger.getLogger(LexicalAnalyzer.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		} catch (IllegalAccessException ex) {
			java.util.logging.Logger.getLogger(LexicalAnalyzer.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		} catch (javax.swing.UnsupportedLookAndFeelException ex) {
			java.util.logging.Logger.getLogger(LexicalAnalyzer.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		}
		//</editor-fold>

		/* Create and display the form */
		java.awt.EventQueue.invokeLater(new Runnable() {
			public void run() {
				LexicalAnalyzer lexWindow=new LexicalAnalyzer();
				lexWindow.setVisible(true);
				lexWindow.tokenize();
			}
		});
	}
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JList list;
    private javax.swing.JTextArea txt;
    // End of variables declaration//GEN-END:variables
}
