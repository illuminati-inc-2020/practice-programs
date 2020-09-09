Public Class window

    Private Sub TextBox1_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles textbox.TextChanged

    End Sub

    Private Sub btn_save_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btn_save.Click
        FileIO.FileSystem.WriteAllText(filename.Text, textbox.Text, False)
    End Sub

    Private Sub btn_open_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btn_open.Click
        If FileIO.FileSystem.FileExists(filename.Text) Then
            textbox.Text = FileIO.FileSystem.ReadAllText(filename.Text)
        Else
            FileIO.FileSystem.WriteAllText(filename.Text, "", False)
        End If
    End Sub

    Private Sub OpenFileDialog1_FileOk(ByVal sender As System.Object, ByVal e As System.ComponentModel.CancelEventArgs)

    End Sub


End Class
