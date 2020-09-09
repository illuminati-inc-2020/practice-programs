VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form WordPad 
   Caption         =   "WordPad : New File"
   ClientHeight    =   7125
   ClientLeft      =   870
   ClientTop       =   1320
   ClientWidth     =   11760
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   18
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H00000000&
   LinkTopic       =   "Form1"
   ScaleHeight     =   7125
   ScaleWidth      =   11760
   Begin ComctlLib.StatusBar StatusBar 
      Align           =   2  'Align Bottom
      Height          =   375
      Left            =   0
      TabIndex        =   21
      Top             =   6750
      Width           =   11760
      _ExtentX        =   20743
      _ExtentY        =   661
      Style           =   1
      SimpleText      =   "New File"
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   1
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Calibri"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.CommandButton btn_Find 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   9000
      Picture         =   "WordPad.frx":0000
      Style           =   1  'Graphical
      TabIndex        =   20
      TabStop         =   0   'False
      ToolTipText     =   "Insert Image"
      Top             =   240
      Width           =   500
   End
   Begin VB.CommandButton btn_Underlined 
      Caption         =   "U"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   -1  'True
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   7200
      Style           =   1  'Graphical
      TabIndex        =   13
      TabStop         =   0   'False
      ToolTipText     =   "Underlined"
      Top             =   480
      Width           =   375
   End
   Begin VB.CommandButton btn_Italic 
      Caption         =   "I"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   6840
      Style           =   1  'Graphical
      TabIndex        =   12
      TabStop         =   0   'False
      ToolTipText     =   "Italic"
      Top             =   480
      Width           =   375
   End
   Begin VB.CommandButton btn_Bold 
      Caption         =   "B"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   6480
      Style           =   1  'Graphical
      TabIndex        =   11
      TabStop         =   0   'False
      ToolTipText     =   "Bold"
      Top             =   480
      Width           =   375
   End
   Begin VB.CommandButton btn_Copy 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2880
      Picture         =   "WordPad.frx":05CD
      Style           =   1  'Graphical
      TabIndex        =   6
      TabStop         =   0   'False
      ToolTipText     =   "Copy"
      Top             =   480
      Width           =   375
   End
   Begin VB.CommandButton btn_Cut 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2880
      Picture         =   "WordPad.frx":0974
      Style           =   1  'Graphical
      TabIndex        =   5
      TabStop         =   0   'False
      ToolTipText     =   "Cut"
      Top             =   120
      Width           =   375
   End
   Begin VB.CommandButton btn_Save 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   1080
      Picture         =   "WordPad.frx":0D0A
      Style           =   1  'Graphical
      TabIndex        =   3
      TabStop         =   0   'False
      ToolTipText     =   "Save"
      Top             =   240
      Width           =   500
   End
   Begin VB.CommandButton btn_Open 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   600
      Picture         =   "WordPad.frx":1213
      Style           =   1  'Graphical
      TabIndex        =   2
      TabStop         =   0   'False
      ToolTipText     =   "Open"
      Top             =   240
      Width           =   500
   End
   Begin VB.CommandButton btn_RightAlignment 
      BeginProperty Font 
         Name            =   "Calibri"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   5640
      Picture         =   "WordPad.frx":16BC
      Style           =   1  'Graphical
      TabIndex        =   18
      TabStop         =   0   'False
      ToolTipText     =   "Right Justify"
      Top             =   480
      Width           =   375
   End
   Begin VB.CommandButton btn_Undo 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   1800
      Picture         =   "WordPad.frx":1A4A
      Style           =   1  'Graphical
      TabIndex        =   19
      TabStop         =   0   'False
      ToolTipText     =   "Undo"
      Top             =   240
      Width           =   500
   End
   Begin VB.CommandButton btn_CentreAlignment 
      BeginProperty Font 
         Name            =   "Calibri"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   5280
      Picture         =   "WordPad.frx":1E94
      Style           =   1  'Graphical
      TabIndex        =   17
      TabStop         =   0   'False
      ToolTipText     =   "Centre"
      Top             =   480
      Width           =   375
   End
   Begin VB.CommandButton btn_LeftAlignment 
      BeginProperty Font 
         Name            =   "Calibri"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4920
      Picture         =   "WordPad.frx":2228
      Style           =   1  'Graphical
      TabIndex        =   16
      TabStop         =   0   'False
      ToolTipText     =   "Left Justify"
      Top             =   480
      Width           =   375
   End
   Begin VB.CommandButton btn_Image 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   8280
      Picture         =   "WordPad.frx":25BD
      Style           =   1  'Graphical
      TabIndex        =   15
      TabStop         =   0   'False
      ToolTipText     =   "Insert Image"
      Top             =   240
      Width           =   500
   End
   Begin VB.CommandButton btn_Bullet 
      BeginProperty Font 
         Name            =   "Calibri"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4440
      Picture         =   "WordPad.frx":2AF2
      Style           =   1  'Graphical
      TabIndex        =   9
      TabStop         =   0   'False
      ToolTipText     =   "Bullet"
      Top             =   480
      Width           =   375
   End
   Begin VB.CommandButton btn_StrikeTrouugh 
      Caption         =   "S"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   -1  'True
      EndProperty
      Height          =   375
      Left            =   6120
      Style           =   1  'Graphical
      TabIndex        =   10
      TabStop         =   0   'False
      ToolTipText     =   "Strike Strough"
      Top             =   480
      Width           =   375
   End
   Begin VB.ComboBox combo_fontsize 
      BeginProperty DataFormat 
         Type            =   1
         Format          =   "0"
         HaveTrueFalseNull=   0
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
         LCID            =   16393
         SubFormatType   =   1
      EndProperty
      BeginProperty Font 
         Name            =   "Calibri"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      ItemData        =   "WordPad.frx":2EDB
      Left            =   3480
      List            =   "WordPad.frx":2F0F
      TabIndex        =   8
      TabStop         =   0   'False
      Text            =   "size"
      ToolTipText     =   "Font Size"
      Top             =   480
      Width           =   855
   End
   Begin VB.ComboBox combo_fontstyle 
      BeginProperty Font 
         Name            =   "Calibri"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   3480
      Sorted          =   -1  'True
      TabIndex        =   7
      TabStop         =   0   'False
      Text            =   "style"
      ToolTipText     =   "Font Style"
      Top             =   120
      Width           =   4575
   End
   Begin VB.CommandButton btn_New 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   120
      Picture         =   "WordPad.frx":2F52
      Style           =   1  'Graphical
      TabIndex        =   1
      TabStop         =   0   'False
      ToolTipText     =   "New"
      Top             =   240
      Width           =   500
   End
   Begin VB.CommandButton btn_Paste 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   2400
      Picture         =   "WordPad.frx":3337
      Style           =   1  'Graphical
      TabIndex        =   4
      TabStop         =   0   'False
      ToolTipText     =   "Paste"
      Top             =   240
      Width           =   500
   End
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   11160
      Top             =   120
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin RichTextLib.RichTextBox TextBox 
      Height          =   5775
      Left            =   0
      TabIndex        =   0
      TabStop         =   0   'False
      Top             =   960
      Width           =   11775
      _ExtentX        =   20770
      _ExtentY        =   10186
      _Version        =   393217
      ScrollBars      =   2
      TextRTF         =   $"WordPad.frx":37EF
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Calibri"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.CommandButton btn_Color 
      Caption         =   "A"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   300
      Left            =   7680
      MaskColor       =   &H00FFFFFF&
      Style           =   1  'Graphical
      TabIndex        =   14
      TabStop         =   0   'False
      ToolTipText     =   "Text Colour"
      Top             =   480
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.Shape ColorRect 
      BorderStyle     =   6  'Inside Solid
      FillStyle       =   0  'Solid
      Height          =   135
      Left            =   7680
      Top             =   720
      Width           =   375
   End
   Begin VB.Shape Shape1 
      FillStyle       =   0  'Solid
      Height          =   135
      Left            =   7800
      Top             =   600
      Width           =   135
   End
   Begin VB.Line Line5 
      BorderColor     =   &H80000000&
      X1              =   9600
      X2              =   9600
      Y1              =   0
      Y2              =   960
   End
   Begin VB.Line Line4 
      BorderColor     =   &H80000000&
      X1              =   8880
      X2              =   8880
      Y1              =   0
      Y2              =   960
   End
   Begin VB.Line Line3 
      BorderColor     =   &H80000000&
      X1              =   8160
      X2              =   8160
      Y1              =   0
      Y2              =   960
   End
   Begin VB.Line Line2 
      BorderColor     =   &H80000000&
      X1              =   3360
      X2              =   3360
      Y1              =   0
      Y2              =   960
   End
   Begin VB.Line Line1 
      BorderColor     =   &H80000000&
      X1              =   1680
      X2              =   1680
      Y1              =   0
      Y2              =   960
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
      Begin VB.Menu mnuFile_Sep4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile_Exit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "&Edit"
      Begin VB.Menu mnuEdit_Undo 
         Caption         =   "&Undo"
      End
      Begin VB.Menu mnuEdit_Sep1 
         Caption         =   "-"
      End
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
      End
      Begin VB.Menu mnuEdit_Clear 
         Caption         =   "Clea&r"
      End
      Begin VB.Menu mnuEdit_Sep2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEdit_SelectAll 
         Caption         =   "Select &All"
         Shortcut        =   ^A
      End
      Begin VB.Menu mnuEdit_Sep3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEdit_Find 
         Caption         =   "Find"
         Shortcut        =   ^F
      End
   End
   Begin VB.Menu mnuInsert 
      Caption         =   "&Insert"
      Begin VB.Menu mnuInsert_Image 
         Caption         =   "Image"
         Shortcut        =   {F2}
      End
      Begin VB.Menu mnuInsert_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuInsert_Date 
         Caption         =   "Date"
         Shortcut        =   ^D
      End
      Begin VB.Menu mnuInsert_Time 
         Caption         =   "Time"
         Shortcut        =   ^T
      End
   End
   Begin VB.Menu mnuFormat 
      Caption         =   "F&ormat"
      Begin VB.Menu mnuFormat_Font 
         Caption         =   "Font"
      End
      Begin VB.Menu mnuFormat_Color 
         Caption         =   "Text Colour"
      End
      Begin VB.Menu mnuFormat_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFormat_StrikeThrough 
         Caption         =   "Strike Through"
      End
      Begin VB.Menu mnuFormat_Bold 
         Caption         =   "Bold"
         Shortcut        =   ^B
      End
      Begin VB.Menu mnuFormat_Italic 
         Caption         =   "Italic"
         Shortcut        =   ^I
      End
      Begin VB.Menu mnuFormat_Underlined 
         Caption         =   "Underlined"
         Shortcut        =   ^U
      End
      Begin VB.Menu mnuFormat_Sep2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFormat_LeftJustify 
         Caption         =   "Left Justify"
         Shortcut        =   ^L
      End
      Begin VB.Menu mnuFormat_Centre 
         Caption         =   "Centre"
         Shortcut        =   ^E
      End
      Begin VB.Menu mnuFormat_RightJustify 
         Caption         =   "Right Justify"
         Shortcut        =   ^R
      End
      Begin VB.Menu mnuFormat_Sep3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFormat_Bullet 
         Caption         =   "Bullet"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuHelp_Help 
         Caption         =   "Help"
      End
      Begin VB.Menu mnuHelp_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuHelp_About 
         Caption         =   "&About"
         Shortcut        =   {F1}
      End
   End
End
Attribute VB_Name = "WordPad"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim FileName As String
Dim Form_initLeft As Integer, Form_initTop As Integer

'-------------------------------------------API--------------------------------------
Private Const WM_CUT = &H300
Private Const WM_COPY = &H301
Private Const WM_PASTE = &H302
Private Const WM_CLEAR = &H303
Private Const EM_UNDO = &HC7
Private Declare Function SendMessage Lib "user32" Alias "SendMessageA" (ByVal _
    hWnd As Long, ByVal wMsg As Long, ByVal wParam As Long, _
    lParam As Any) As Long
    
'----------------------------------------SubProcedures--------------------------------
Public Sub NewFile()
TextBox.Text = ""
FileName = ""
Me.Caption = "Wordpad : New File"
End Sub

Public Sub OpenFile()
CommonDialog.FileName = ""
CommonDialog.Filter = "Rich Text Format(*.rtf)|*.rtf|Text (*.txt)|*.txt|All Files|*.*"
CommonDialog.ShowOpen
If CommonDialog.FileName <> "" Then
    FileName = CommonDialog.FileName
    TextBox.LoadFile (FileName)
    Me.Caption = "Wordpad : " + FileName
    StatusBar.SimpleText = "Opened File: " + FileName
End If
End Sub

Private Function LineNumber() As Integer
Dim i As Integer
LineNumber = 0
For i = 1 To TextBox.SelStart - 1
    If Mid(TextBox.Text, i, 2) = vbCrLf Then LineNumber = LineNumber + 1
Next
End Function

Private Function ColNumber() As Integer
Dim i As Integer
ColNumber = 0
For i = 1 To TextBox.SelStart - 1
    If Mid(TextBox.Text, i, 2) = vbCrLf Then ColNumber = -1
    ColNumber = ColNumber + 1
Next
End Function

Private Sub ComponentUpdate()
StatusBar.SimpleText = "Line: " + CStr(LineNumber) + "     Col: " + CStr(ColNumber) + "         Char: " + CStr(TextBox.SelStart) + "     Sel: " + CStr(TextBox.SelLength)
On Error GoTo DumpError
ColorRect.FillColor = TextBox.SelColor
btn_Bold.FontBold = Not TextBox.SelBold
btn_Italic.FontItalic = Not TextBox.SelItalic
btn_Underlined.FontUnderline = Not TextBox.SelUnderline
btn_StrikeTrouugh.FontStrikethru = Not TextBox.SelStrikeThru
combo_fontsize.Text = CStr(TextBox.SelFontSize)
combo_fontstyle.Text = TextBox.SelFontName
combo_fontstyle.FontName = TextBox.SelFontName
combo_fontstyle.SelLength = 0
DumpError:
End Sub

Public Sub LoadFontNames()
Dim i As Integer
For i = 1 To Screen.FontCount - 1
    combo_fontstyle.AddItem (Screen.Fonts(i))
Next
combo_fontstyle.Text = TextBox.Font.Name
End Sub

'---------------------------------------Form Events------------------------------
Private Sub Form_Load()
Form_initLeft = TextBox.Left
Form_initTop = TextBox.Top
LoadFontNames
combo_fontsize.Text = CStr(TextBox.Font.Size)
Form_Resize
End Sub

Private Sub Form_Resize()
On Error GoTo DumpError
TextBox.Width = Me.Width - 250 - Form_initLeft
TextBox.Height = Me.Height - 900 - Form_initTop - StatusBar.Height
DumpError:
End Sub

Private Sub Form_Unload(Cancel As Integer)
If Right(Me.Caption, 2) = " #" Then
    Select Case MsgBox("Do you Want to Save the Document?", vbYesNoCancel, "Save")
    Case vbYes
        mnuFile_Save_Click
        End
    Case vbCancel
        Cancel = True
    Case vbNo
        End
    End Select
Else
    End
End If
End Sub

Private Sub mnuHelp_Help_Click()
CommonDialog.ShowHelp
End Sub

'----------------------------------------TextBox Events-----------------------------
Private Sub TextBox_KeyPress(KeyAscii As Integer)
End Sub

Private Sub TextBox_Change()
If Right(Me.Caption, 2) <> " #" Then Me.Caption = Me.Caption + " #"
End Sub

Private Sub TextBox_SelChange()
ComponentUpdate
End Sub

'-----------------------------------Menu Events-----------------------
Private Sub mnuFile_New_Click()
If Right(Me.Caption, 2) = " #" Then
    Select Case MsgBox("Do you Want to Save the Document?", vbYesNoCancel, "Save")
    Case vbYes
        mnuFile_Save_Click
        NewFile
    Case vbNo
        NewFile
    End Select
Else
    NewFile
End If
End Sub

Private Sub mnuFile_Open_Click()
If Right(Me.Caption, 2) = " #" Then
    Select Case MsgBox("Do you Want to Save the Document?", vbYesNoCancel, "Save")
    Case vbYes
        mnuFile_Save_Click
        OpenFile
    Case vbNo
        OpenFile
    End Select
Else
    OpenFile
End If
End Sub

Private Sub mnuFile_Save_Click()
Dim tmp As String, contents As String
CommonDialog.FileName = ""
CommonDialog.Filter = "Rich Text Format(*.rtf)|*.rtf"
If FileName = "" Then
    CommonDialog.ShowSave
    If CommonDialog.FileName <> "" Then
        FileName = CommonDialog.FileName
        TextBox.SaveFile (FileName)
        Me.Caption = "Notepad : " + FileName
        StatusBar.SimpleText = "Saved file: " + FileName
    End If
Else
    TextBox.SaveFile (FileName)
    Me.Caption = "Wordpad : " + FileName
    StatusBar.SimpleText = "Saved file: " + FileName
End If
End Sub

Private Sub mnuFile_SaveAs_Click()
CommonDialog.FileName = ""
CommonDialog.Filter = "Rich Text Format(*.rtf)|*.rtf"
CommonDialog.ShowSave
If CommonDialog.FileName <> "" Then
    FileName = CommonDialog.FileName
    TextBox.SaveFile (FileName)
    Me.Caption = "Wordpad : " + FileName
    StatusBar.SimpleText = "Saved file: " + FileName
End If
End Sub

Private Sub mnuFile_Exit_Click()
Unload Me
End Sub

Private Sub mnuEdit_Cut_Click()
SendMessage TextBox.hWnd, WM_CUT, 0, 0
TextBox.SelText = ""
End Sub

Private Sub mnuEdit_Copy_Click()
SendMessage TextBox.hWnd, WM_COPY, 0, 0
End Sub

Private Sub mnuEdit_Paste_Click()
SendMessage TextBox.hWnd, WM_PASTE, 0, 0
End Sub

Private Sub mnuEdit_Undo_Click()
SendMessage TextBox.hWnd, EM_UNDO, 0, 0
End Sub

Private Sub mnuEdit_Clear_Click()
SendMessage TextBox.hWnd, WM_CLEAR, 0, 0
End Sub

Private Sub mnuEdit_SelectAll_Click()
TextBox.SelStart = 0
TextBox.SelLength = Len(TextBox.Text)
End Sub

Private Sub mnuEdit_Find_Click()
FindForm.Show vbModeless, Me
End Sub

Private Sub mnuFormat_Font_Click()
CommonDialog.ShowFont
TextBox.SelFontName = CommonDialog.FontName
TextBox.SelFontSize = CommonDialog.FontSize
TextBox.SelBold = CommonDialog.FontBold
TextBox.SelItalic = CommonDialog.FontItalic
TextBox.SelUnderline = CommonDialog.FontUnderline
TextBox.Font.Strikethrough = CommonDialog.FontStrikethru
End Sub

Private Sub mnuFormat_StrikeThrough_Click()
TextBox.SelStrikeThru = Not TextBox.SelStrikeThru
End Sub

Private Sub mnuFormat_Bold_Click()
TextBox.SelBold = Not TextBox.SelBold
End Sub

Private Sub mnuFormat_Italic_Click()
TextBox.SelItalic = Not TextBox.SelItalic
End Sub

Private Sub mnuFormat_Underlined_Click()
TextBox.SelUnderline = Not TextBox.SelUnderline
End Sub

Private Sub mnuFormat_Centre_Click()
TextBox.SelAlignment = vbCenter
End Sub

Private Sub mnuFormat_LeftJustify_Click()
TextBox.SelAlignment = vbLeftJustify
End Sub

Private Sub mnuFormat_RightJustify_Click()
TextBox.SelAlignment = vbRightJustify
End Sub

Private Sub mnuFormat_Color_Click()
CommonDialog.ShowColor
TextBox.SelColor = CommonDialog.Color
ColorRect.FillColor = TextBox.SelColor
End Sub

Private Sub mnuFormat_Bullet_Click()
TextBox.SelBullet = Not TextBox.SelBullet
End Sub

Private Sub mnuInsert_Date_Click()
TextBox.SelText = Date
End Sub

Private Sub mnuInsert_Time_Click()
TextBox.SelText = Time
End Sub

Private Sub mnuHelp_About_Click()
MsgBox "Wordpad" + vbCrLf + "     by Rakesh Malik" + vbCrLf + "     October 2012", vbOKOnly, "About WordPad"
End Sub

Private Sub mnuInsert_Image_Click()
CommonDialog.FileName = ""
CommonDialog.Filter = "Image File(*.jpg;*.bmp;*.gif)|*.jpg;*.jpeg;*.bmp;*.gif|JPEG Image(*.jpg)|*.jpg;*.jpeg|Bitmap Image(*.bmp)|*.bmp|GIF Image(*.gif)|*.gif|All Files|*.*"
Clipboard.Clear
CommonDialog.ShowOpen
If CommonDialog.FileName <> "" Then
    Clipboard.SetData LoadPicture(CommonDialog.FileName)
    SendMessage TextBox.hWnd, WM_PASTE, 0, 0
End If
End Sub

'-----------------------------------Toolbar Events-----------------------
Private Sub btn_New_Click()
mnuFile_New_Click
TextBox.SetFocus
End Sub

Private Sub btn_Open_Click()
mnuFile_Open_Click
TextBox.SetFocus
End Sub

Private Sub btn_Save_Click()
mnuFile_Save_Click
TextBox.SetFocus
End Sub

Private Sub btn_Cut_Click()
mnuEdit_Cut_Click
TextBox.SetFocus
End Sub

Private Sub btn_Copy_Click()
mnuEdit_Copy_Click
TextBox.SetFocus
End Sub

Private Sub btn_Paste_Click()
mnuEdit_Paste_Click
TextBox.SetFocus
End Sub

Private Sub btn_Undo_Click()
mnuEdit_Undo_Click
TextBox.SetFocus
End Sub

Private Sub btn_StrikeTrouugh_Click()
mnuFormat_StrikeThrough_Click
ComponentUpdate
TextBox.SetFocus
End Sub

Private Sub btn_Bold_Click()
mnuFormat_Bold_Click
ComponentUpdate
TextBox.SetFocus
End Sub

Private Sub btn_Italic_Click()
mnuFormat_Italic_Click
ComponentUpdate
TextBox.SetFocus
End Sub

Private Sub btn_Underlined_Click()
mnuFormat_Underlined_Click
ComponentUpdate
TextBox.SetFocus
End Sub

Private Sub combo_fontstyle_Click()
TextBox.SelFontName = combo_fontstyle.Text
combo_fontstyle.Font.Name = combo_fontstyle.Text
TextBox.SetFocus
End Sub

Private Sub combo_fontstyle_DropDown()
combo_fontstyle.Font.Name = "Calibri"
End Sub

Private Sub combo_fontsize_Click()
TextBox.SelFontSize = Val(combo_fontsize.Text)
TextBox.SetFocus
End Sub

Private Sub combo_fontsize_KeyDown(KeyCode As Integer, Shift As Integer)
If KeyCode = Asc(vbCrLf) And IsNumeric(combo_fontsize.Text) Then
    TextBox.SelFontSize = Val(combo_fontsize.Text)
    TextBox.SetFocus
End If
End Sub

Private Sub btn_Color_Click()
mnuFormat_Color_Click
TextBox.SetFocus
End Sub

Private Sub btn_Bullet_Click()
mnuFormat_Bullet_Click
TextBox.SetFocus
End Sub

Private Sub btn_CentreAlignment_Click()
mnuFormat_Centre_Click
TextBox.SetFocus
End Sub

Private Sub btn_LeftAlignment_Click()
mnuFormat_LeftJustify_Click
TextBox.SetFocus
End Sub

Private Sub btn_RightAlignment_Click()
mnuFormat_RightJustify_Click
TextBox.SetFocus
End Sub

Private Sub btn_Image_Click()
mnuInsert_Image_Click
TextBox.SetFocus
End Sub

Private Sub btn_Find_Click()
mnuEdit_Find_Click
End Sub
