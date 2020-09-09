<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Note
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Note))
        Me.mnuNote = New System.Windows.Forms.ContextMenuStrip(Me.components)
        Me.FontToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.FontColorToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.BoldToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ItalicToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.UnderlinedToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.StrikeThroughToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripMenuItem2 = New System.Windows.Forms.ToolStripSeparator()
        Me.BackColorToolStripMenuItem1 = New System.Windows.Forms.ToolStripMenuItem()
        Me.BackColorToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.dlgFont = New System.Windows.Forms.FontDialog()
        Me.dlgColor = New System.Windows.Forms.ColorDialog()
        Me.btnClose = New System.Windows.Forms.Button()
        Me.ToolStripMenuItem1 = New System.Windows.Forms.ToolStripSeparator()
        Me.mnuStrikeThrough = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuUnderlined = New System.Windows.Forms.ToolStripMenuItem()
        Me.mniItalic = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuBold = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFontStyle = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFontColor = New System.Windows.Forms.ToolStripMenuItem()
        Me.ColorToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.txtNote = New System.Windows.Forms.RichTextBox()
        Me.btnMinimize = New System.Windows.Forms.Button()
        Me.mnuNote.SuspendLayout()
        Me.SuspendLayout()
        '
        'mnuNote
        '
        Me.mnuNote.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.FontToolStripMenuItem, Me.FontColorToolStripMenuItem, Me.BoldToolStripMenuItem, Me.ItalicToolStripMenuItem, Me.UnderlinedToolStripMenuItem, Me.StrikeThroughToolStripMenuItem, Me.ToolStripMenuItem2, Me.BackColorToolStripMenuItem1})
        Me.mnuNote.Name = "ContextMenuStrip1"
        Me.mnuNote.Size = New System.Drawing.Size(193, 164)
        '
        'FontToolStripMenuItem
        '
        Me.FontToolStripMenuItem.Name = "FontToolStripMenuItem"
        Me.FontToolStripMenuItem.Size = New System.Drawing.Size(192, 22)
        Me.FontToolStripMenuItem.Text = "Font Style"
        '
        'FontColorToolStripMenuItem
        '
        Me.FontColorToolStripMenuItem.Name = "FontColorToolStripMenuItem"
        Me.FontColorToolStripMenuItem.Size = New System.Drawing.Size(192, 22)
        Me.FontColorToolStripMenuItem.Text = "Font Color"
        '
        'BoldToolStripMenuItem
        '
        Me.BoldToolStripMenuItem.Name = "BoldToolStripMenuItem"
        Me.BoldToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.B), System.Windows.Forms.Keys)
        Me.BoldToolStripMenuItem.Size = New System.Drawing.Size(192, 22)
        Me.BoldToolStripMenuItem.Text = "Bold"
        '
        'ItalicToolStripMenuItem
        '
        Me.ItalicToolStripMenuItem.Name = "ItalicToolStripMenuItem"
        Me.ItalicToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.I), System.Windows.Forms.Keys)
        Me.ItalicToolStripMenuItem.Size = New System.Drawing.Size(192, 22)
        Me.ItalicToolStripMenuItem.Text = "Italic"
        '
        'UnderlinedToolStripMenuItem
        '
        Me.UnderlinedToolStripMenuItem.Name = "UnderlinedToolStripMenuItem"
        Me.UnderlinedToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.U), System.Windows.Forms.Keys)
        Me.UnderlinedToolStripMenuItem.Size = New System.Drawing.Size(192, 22)
        Me.UnderlinedToolStripMenuItem.Text = "Underlined"
        '
        'StrikeThroughToolStripMenuItem
        '
        Me.StrikeThroughToolStripMenuItem.Name = "StrikeThroughToolStripMenuItem"
        Me.StrikeThroughToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.S), System.Windows.Forms.Keys)
        Me.StrikeThroughToolStripMenuItem.Size = New System.Drawing.Size(192, 22)
        Me.StrikeThroughToolStripMenuItem.Text = "Strike Through"
        '
        'ToolStripMenuItem2
        '
        Me.ToolStripMenuItem2.Name = "ToolStripMenuItem2"
        Me.ToolStripMenuItem2.Size = New System.Drawing.Size(189, 6)
        '
        'BackColorToolStripMenuItem1
        '
        Me.BackColorToolStripMenuItem1.Name = "BackColorToolStripMenuItem1"
        Me.BackColorToolStripMenuItem1.Size = New System.Drawing.Size(192, 22)
        Me.BackColorToolStripMenuItem1.Text = "Back Color"
        '
        'BackColorToolStripMenuItem
        '
        Me.BackColorToolStripMenuItem.Name = "BackColorToolStripMenuItem"
        Me.BackColorToolStripMenuItem.Size = New System.Drawing.Size(192, 22)
        Me.BackColorToolStripMenuItem.Text = "Back Color"
        '
        'dlgFont
        '
        Me.dlgFont.Color = System.Drawing.SystemColors.ControlText
        '
        'btnClose
        '
        Me.btnClose.Anchor = System.Windows.Forms.AnchorStyles.Right
        Me.btnClose.BackColor = System.Drawing.Color.Transparent
        Me.btnClose.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch
        Me.btnClose.Cursor = System.Windows.Forms.Cursors.Hand
        Me.btnClose.FlatAppearance.BorderSize = 0
        Me.btnClose.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent
        Me.btnClose.FlatAppearance.MouseOverBackColor = System.Drawing.Color.LightGray
        Me.btnClose.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.btnClose.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btnClose.ForeColor = System.Drawing.Color.Black
        Me.btnClose.Location = New System.Drawing.Point(200, 3)
        Me.btnClose.Name = "btnClose"
        Me.btnClose.Size = New System.Drawing.Size(20, 20)
        Me.btnClose.TabIndex = 0
        Me.btnClose.TabStop = False
        Me.btnClose.Text = "X"
        Me.btnClose.UseVisualStyleBackColor = False
        '
        'ToolStripMenuItem1
        '
        Me.ToolStripMenuItem1.Name = "ToolStripMenuItem1"
        Me.ToolStripMenuItem1.Size = New System.Drawing.Size(189, 6)
        '
        'mnuStrikeThrough
        '
        Me.mnuStrikeThrough.Name = "mnuStrikeThrough"
        Me.mnuStrikeThrough.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.S), System.Windows.Forms.Keys)
        Me.mnuStrikeThrough.Size = New System.Drawing.Size(192, 22)
        Me.mnuStrikeThrough.Text = "Strike Through"
        '
        'mnuUnderlined
        '
        Me.mnuUnderlined.Name = "mnuUnderlined"
        Me.mnuUnderlined.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.U), System.Windows.Forms.Keys)
        Me.mnuUnderlined.Size = New System.Drawing.Size(192, 22)
        Me.mnuUnderlined.Text = "Underlined"
        '
        'mniItalic
        '
        Me.mniItalic.Name = "mniItalic"
        Me.mniItalic.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.I), System.Windows.Forms.Keys)
        Me.mniItalic.Size = New System.Drawing.Size(192, 22)
        Me.mniItalic.Text = "Italic"
        '
        'mnuBold
        '
        Me.mnuBold.Name = "mnuBold"
        Me.mnuBold.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.B), System.Windows.Forms.Keys)
        Me.mnuBold.Size = New System.Drawing.Size(192, 22)
        Me.mnuBold.Text = "Bold"
        '
        'mnuFontStyle
        '
        Me.mnuFontStyle.Name = "mnuFontStyle"
        Me.mnuFontStyle.Size = New System.Drawing.Size(192, 22)
        Me.mnuFontStyle.Text = "Font Style"
        '
        'mnuFontColor
        '
        Me.mnuFontColor.Name = "mnuFontColor"
        Me.mnuFontColor.Size = New System.Drawing.Size(192, 22)
        Me.mnuFontColor.Text = "Font Color"
        '
        'ColorToolStripMenuItem
        '
        Me.ColorToolStripMenuItem.Name = "ColorToolStripMenuItem"
        Me.ColorToolStripMenuItem.Size = New System.Drawing.Size(192, 22)
        Me.ColorToolStripMenuItem.Text = "Font Color"
        '
        'txtNote
        '
        Me.txtNote.BackColor = System.Drawing.Color.GreenYellow
        Me.txtNote.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.txtNote.ContextMenuStrip = Me.mnuNote
        Me.txtNote.Dock = System.Windows.Forms.DockStyle.Bottom
        Me.txtNote.Font = New System.Drawing.Font("Lucida Handwriting", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtNote.ForeColor = System.Drawing.Color.Black
        Me.txtNote.Location = New System.Drawing.Point(0, 25)
        Me.txtNote.Name = "txtNote"
        Me.txtNote.Size = New System.Drawing.Size(227, 213)
        Me.txtNote.TabIndex = 0
        Me.txtNote.TabStop = False
        Me.txtNote.Text = ""
        '
        'btnMinimize
        '
        Me.btnMinimize.Anchor = System.Windows.Forms.AnchorStyles.Right
        Me.btnMinimize.BackColor = System.Drawing.Color.Transparent
        Me.btnMinimize.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch
        Me.btnMinimize.Cursor = System.Windows.Forms.Cursors.Hand
        Me.btnMinimize.FlatAppearance.BorderSize = 0
        Me.btnMinimize.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent
        Me.btnMinimize.FlatAppearance.MouseOverBackColor = System.Drawing.Color.LightGray
        Me.btnMinimize.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.btnMinimize.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btnMinimize.ForeColor = System.Drawing.Color.Black
        Me.btnMinimize.Location = New System.Drawing.Point(176, 3)
        Me.btnMinimize.Name = "btnMinimize"
        Me.btnMinimize.Size = New System.Drawing.Size(20, 20)
        Me.btnMinimize.TabIndex = 1
        Me.btnMinimize.TabStop = False
        Me.btnMinimize.Text = "‒"
        Me.btnMinimize.UseVisualStyleBackColor = False
        '
        'Note
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.Color.Lime
        Me.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch
        Me.ClientSize = New System.Drawing.Size(227, 238)
        Me.ContextMenuStrip = Me.mnuNote
        Me.ControlBox = False
        Me.Controls.Add(Me.btnMinimize)
        Me.Controls.Add(Me.btnClose)
        Me.Controls.Add(Me.txtNote)
        Me.DoubleBuffered = True
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Name = "Note"
        Me.Opacity = 0.7R
        Me.ShowInTaskbar = False
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.mnuNote.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents mnuNote As System.Windows.Forms.ContextMenuStrip
    Friend WithEvents dlgFont As System.Windows.Forms.FontDialog
    Friend WithEvents dlgColor As System.Windows.Forms.ColorDialog
    Friend WithEvents BackColorToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents btnClose As System.Windows.Forms.Button
    Friend WithEvents mnuUnderlined As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuStrikeThrough As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ToolStripMenuItem1 As System.Windows.Forms.ToolStripSeparator
    Friend WithEvents mniItalic As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuBold As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuFontStyle As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuFontColor As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ColorToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents FontToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents FontColorToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents BoldToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ItalicToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents UnderlinedToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents StrikeThroughToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ToolStripMenuItem2 As System.Windows.Forms.ToolStripSeparator
    Friend WithEvents BackColorToolStripMenuItem1 As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents txtNote As System.Windows.Forms.RichTextBox
    Friend WithEvents btnMinimize As System.Windows.Forms.Button

End Class
