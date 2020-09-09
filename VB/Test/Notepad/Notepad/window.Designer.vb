<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class window
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
        Me.textbox = New System.Windows.Forms.TextBox()
        Me.btn_save = New System.Windows.Forms.Button()
        Me.btn_open = New System.Windows.Forms.Button()
        Me.filename = New System.Windows.Forms.TextBox()
        Me.SuspendLayout()
        '
        'textbox
        '
        Me.textbox.Location = New System.Drawing.Point(12, 37)
        Me.textbox.Multiline = True
        Me.textbox.Name = "textbox"
        Me.textbox.Size = New System.Drawing.Size(260, 213)
        Me.textbox.TabIndex = 0
        '
        'btn_save
        '
        Me.btn_save.Location = New System.Drawing.Point(119, 6)
        Me.btn_save.Name = "btn_save"
        Me.btn_save.Size = New System.Drawing.Size(44, 23)
        Me.btn_save.TabIndex = 1
        Me.btn_save.Text = "Save"
        Me.btn_save.UseVisualStyleBackColor = True
        '
        'btn_open
        '
        Me.btn_open.Location = New System.Drawing.Point(169, 5)
        Me.btn_open.Name = "btn_open"
        Me.btn_open.Size = New System.Drawing.Size(44, 23)
        Me.btn_open.TabIndex = 1
        Me.btn_open.Text = "Open"
        Me.btn_open.UseVisualStyleBackColor = True
        '
        'filename
        '
        Me.filename.Location = New System.Drawing.Point(13, 8)
        Me.filename.Name = "filename"
        Me.filename.Size = New System.Drawing.Size(100, 20)
        Me.filename.TabIndex = 2
        '
        'window
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(284, 262)
        Me.Controls.Add(Me.filename)
        Me.Controls.Add(Me.btn_open)
        Me.Controls.Add(Me.btn_save)
        Me.Controls.Add(Me.textbox)
        Me.Name = "window"
        Me.Text = "Form1"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents textbox As System.Windows.Forms.TextBox
    Friend WithEvents btn_save As System.Windows.Forms.Button
    Friend WithEvents btn_open As System.Windows.Forms.Button
    Friend WithEvents filename As System.Windows.Forms.TextBox

End Class
