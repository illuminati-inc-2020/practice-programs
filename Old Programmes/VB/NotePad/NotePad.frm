VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.Form NotePad 
   Caption         =   "NotePad : New File"
   ClientHeight    =   6210
   ClientLeft      =   225
   ClientTop       =   855
   ClientWidth     =   9045
   LinkTopic       =   "Form1"
   ScaleHeight     =   6210
   ScaleWidth      =   9045
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox TextBox 
      BeginProperty Font 
         Name            =   "Calibri"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3975
      Left            =   0
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Top             =   0
      Width           =   6015
   End
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   6240
      Top             =   4440
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFile_New 
         Caption         =   "&New"
         Shortcut        =   ^N
      End
      Begin VB.Menu mnuFile_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile_Open 
         Caption         =   "&Open"
         Shortcut        =   ^O
      End
      Begin VB.Menu mnuFile_Sep2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile_Save 
         Caption         =   "&Save"
         Shortcut        =   ^S
      End
      Begin VB.Menu mnuFile_SaveAs 
         Caption         =   "Save &As..."
      End
      Begin VB.Menu mnuFile_Sep3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile_Exit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "&Edit"
      Begin VB.Menu mnuEdit_Cut 
         Caption         =   "C&ut"
         Shortcut        =   ^X
      End
      Begin VB.Menu mnuEdit_Copy 
         Caption         =   "&Copy"
         Shortcut        =   ^C
      End
      Begin VB.Menu mnuEdit_Paste 
         Caption         =   "&Paste"
         Shortcut        =   ^V
      End
      Begin VB.Menu mnuEdit_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEdit_SelectAll 
         Caption         =   "Select &All"
         Shortcut        =   ^A
      End
   End
   Begin VB.Menu mnuFormat 
      Caption         =   "F&ormat"
      Begin VB.Menu mnuFormat_Font 
         Caption         =   "Font"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuHelp_About 
         Caption         =   "&About"
         Shortcut        =   {F1}
      End
   End
End
Attribute VB_Name = "NotePad"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim FileName As String

Private Sub Form_Resize()
TextBox.Width = Me.Width - 250
TextBox.Height = Me.Height - 900
End Sub

Private Sub Form_Unload(Cancel As Integer)
If Right(Me.Caption, 2) = " #" Then
    Select Case MsgBox("Do you Want to Save the Document?", vbYesNoCancel, "Save")
    Case vbYes
        mnuFile_Save_Click
    Case vbCancel
        Cancel = True
    End Select
End If
End Sub

Private Sub mnuEdit_Copy_Click()
Clipboard.SetText TextBox.SelText
End Sub

Private Sub mnuEdit_Cut_Click()
Clipboard.SetText TextBox.SelText
TextBox.SelText = ""
End Sub

Private Sub mnuEdit_Paste_Click()
TextBox.SelText = Clipboard.GetText
End Sub

Private Sub mnuEdit_SelectAll_Click()
TextBox.SelStart = 0
TextBox.SelLength = Len(TextBox.Text)
End Sub

Private Sub mnuFile_Exit_Click()
Unload Me
End Sub

Private Sub mnuFile_New_Click()
TextBox.Text = ""
FileName = ""
Me.Caption = "Notepad : New File"
End Sub

Private Sub mnuFile_Open_Click()
CommonDialog.FileName = ""
CommonDialog.Filter = "Text (*.txt)|*.txt|All Files|*.*"
CommonDialog.ShowOpen
If CommonDialog.FileName <> "" Then
    FileName = CommonDialog.FileName
    Dim tmp As String, contents As String
    Open FileName For Input As #1
    While EOF(1) = 0
          Line Input #1, tmp
          If contents = "" Then contents = contents + tmp Else contents = contents + vbCrLf + tmp
    Wend
    Close #1
    TextBox.Text = contents
    Me.Caption = "Notepad : " + FileName
End If
End Sub

Private Sub mnuFile_Save_Click()
CommonDialog.FileName = ""
CommonDialog.Filter = "Text (*.txt)|*.txt"
Dim tmp As String, contents As String
If FileName = "" Then
    CommonDialog.ShowSave
    If CommonDialog.CancelError Then
        FileName = CommonDialog.FileName
        Open FileName For Output As #1
        Print #1, TextBox.Text
        Close #1
        Me.Caption = "Notepad : " + FileName
    End If
Else
    FileName = CommonDialog.FileName
    Open FileName For Output As #1
    Print #1, TextBox.Text
    Close #1
    Me.Caption = "Notepad : " + FileName
End If
End Sub

Private Sub mnuFile_SaveAs_Click()
CommonDialog.FileName = ""
CommonDialog.Filter = "Text (*.txt)|*.txt"
CommonDialog.ShowSave
If CommonDialog.CancelError Then
MsgBox CommonDialog.FileName
    FileName = CommonDialog.FileName
    Dim tmp As String, contents As String
    Open FileName For Output As #1
    Print #1, TextBox.Text
    Close #1
    Me.Caption = "Notepad : " + FileName
End If
End Sub

Private Sub mnuFormat_Font_Click()
CommonDialog.ShowFont
TextBox.Font.Name = CommonDialog.FontName
TextBox.Font.Size = CommonDialog.FontSize
TextBox.Font.Bold = CommonDialog.FontBold
TextBox.Font.Italic = CommonDialog.FontItalic
TextBox.Font.Underline = CommonDialog.FontUnderline
TextBox.Font.Strikethrough = CommonDialog.FontStrikethru
End Sub

Private Sub mnuHelp_About_Click()
MsgBox "Notepad" + vbCrLf + "     by Rakesh Malik" + vbCrLf + "     07-10-2012", vbOKOnly, "About"
End Sub

Private Sub TextBox_Change()
If Right(Me.Caption, 2) <> " #" Then Me.Caption = Me.Caption + " #"
End Sub
