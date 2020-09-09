Public Class Note
    Private IsFormBeingDragged As Boolean = False
    Private MouseDownX As Integer
    Private MouseDownY As Integer
    Public filename As String

    Private Sub Note_Activated(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Activated
        On Error Resume Next
        txtNote.LoadFile("notes\" + filename + ".rtf")
        txtNote.Select(Len(txtNote.Text), 0)
        Dim buf As String, num(4) As String
        buf = FileIO.FileSystem.ReadAllText("notes\" + filename + ".txt")
        num = Split(buf)
        Me.SetBounds(Val(num(0)), Val(num(1)), Me.Width, Me.Height)
        txtNote.BackColor = Color.FromArgb(Val(num(2)), Val(num(3)), Val(num(4)))
        SetWindowColor()
    End Sub

    Private Sub Note_Resize(sender As Object, e As EventArgs) Handles Me.Resize
        If Me.WindowState = FormWindowState.Minimized Then
            Me.ShowInTaskbar = True
        Else
            Me.ShowInTaskbar = False
        End If
        txtNote.Focus()
    End Sub

    Private Sub Note_MouseDown(ByVal sender As Object, ByVal e As MouseEventArgs) Handles MyBase.MouseDown
        If e.Button = MouseButtons.Left Then
            IsFormBeingDragged = True
            MouseDownX = e.X
            MouseDownY = e.Y
        End If
    End Sub

    Private Sub Note_MouseUp(ByVal sender As Object, ByVal e As MouseEventArgs) Handles MyBase.MouseUp
        If e.Button = MouseButtons.Left Then
            IsFormBeingDragged = False
        End If
    End Sub

    Private Sub Note_MouseMove(ByVal sender As Object, ByVal e As MouseEventArgs) Handles MyBase.MouseMove
        If IsFormBeingDragged Then
            Dim temp As Point = New Point()
            temp.X = Me.Location.X + (e.X - MouseDownX)
            temp.Y = Me.Location.Y + (e.Y - MouseDownY)
            Me.Location = temp
            temp = Nothing
        End If
    End Sub

    Private Sub Note_LocationChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.LocationChanged
        FileIO.FileSystem.WriteAllText("notes\" + filename + ".txt", CStr(Me.Location.X) + " " + CStr(Me.Location.Y) + " " + CStr(txtNote.BackColor.R) + " " + CStr(txtNote.BackColor.G) + " " + CStr(txtNote.BackColor.B), False)
    End Sub

    Private Sub txtNote_TextChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles txtNote.TextChanged
        On Error Resume Next
        txtNote.SaveFile("notes\" + filename + ".rtf")
    End Sub

    Private Sub btnClose_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnClose.Click
        Me.Close()
    End Sub

    Private Sub FontToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles FontToolStripMenuItem.Click
        dlgFont.Font = txtNote.SelectionFont
        dlgFont.ShowDialog()
        txtNote.SelectionFont = dlgFont.Font
    End Sub

    Private Sub BackColorToolStripMenuItem1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BackColorToolStripMenuItem1.Click
        dlgColor.Color = txtNote.BackColor
        dlgColor.ShowDialog()
        'Me.BackColor = dlgColor.Color
        txtNote.BackColor = dlgColor.Color
        SetWindowColor()
        FileIO.FileSystem.WriteAllText("notes\" + filename + ".txt", CStr(Me.Location.X) + " " + CStr(Me.Location.Y) + " " + CStr(txtNote.BackColor.R) + " " + CStr(txtNote.BackColor.G) + " " + CStr(txtNote.BackColor.B), False)
    End Sub

    Private Sub FontColorToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles FontColorToolStripMenuItem.Click
        dlgColor.Color = txtNote.SelectionColor
        dlgColor.ShowDialog()
        txtNote.SelectionColor = dlgColor.Color
    End Sub

    Private Sub BoldToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BoldToolStripMenuItem.Click
        txtNote.SelectionFont = New Font(Me.txtNote.SelectionFont, txtNote.SelectionFont.Style Xor FontStyle.Bold)
    End Sub

    Private Sub ItalicToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ItalicToolStripMenuItem.Click
        txtNote.SelectionFont = New Font(Me.txtNote.SelectionFont, txtNote.SelectionFont.Style Xor FontStyle.Italic)
    End Sub

    Private Sub UnderlinedToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles UnderlinedToolStripMenuItem.Click
        txtNote.SelectionFont = New Font(Me.txtNote.SelectionFont, txtNote.SelectionFont.Style Xor FontStyle.Underline)
    End Sub

    Private Sub StrikeThroughToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles StrikeThroughToolStripMenuItem.Click
        txtNote.SelectionFont = New Font(Me.txtNote.SelectionFont, txtNote.SelectionFont.Style Xor FontStyle.Strikeout)
    End Sub

    Private Sub SetWindowColor()
        Me.BackColor = txtNote.BackColor
        Dim avg As Long
        avg = Me.BackColor.R / 3 + Me.BackColor.G / 3 + Me.BackColor.B / 3
        Me.BackColor = Color.FromArgb((Me.BackColor.R + avg) / 2, (Me.BackColor.G + avg) / 2, (Me.BackColor.B + avg) / 2)
    End Sub

    Private Sub btnMinimize_Click(sender As Object, e As EventArgs) Handles btnMinimize.Click
        Me.WindowState = FormWindowState.Minimized
    End Sub
End Class
