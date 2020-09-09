Public Class Main
    Private Sub Timer_Tick(sender As Object, e As EventArgs) Handles Timer.Tick
        Timer.Stop()
        Dim buf As String, filename() As String
        buf = FileIO.FileSystem.ReadAllText("common.txt")
        filename = buf.Split(vbCrLf)
        Dim nt(filename.Length) As Note
        For i = 0 To filename.Length - 2
            nt(i) = New Note
            nt(i).filename = filename(i)
            nt(i).Show()
        Next
        Me.Close()
    End Sub
End Class