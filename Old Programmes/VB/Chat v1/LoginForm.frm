VERSION 5.00
Begin VB.Form LoginForm 
   BackColor       =   &H00FFFFFF&
   Caption         =   "Connect"
   ClientHeight    =   3480
   ClientLeft      =   17025
   ClientTop       =   1035
   ClientWidth     =   2985
   LinkTopic       =   "Form1"
   ScaleHeight     =   3480
   ScaleWidth      =   2985
   Begin VB.CommandButton btn_Connect 
      BackColor       =   &H0080EFFF&
      Caption         =   "Connect"
      BeginProperty Font 
         Name            =   "Calibri"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   840
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   2280
      Width           =   1215
   End
   Begin VB.TextBox txt_IP 
      Alignment       =   2  'Center
      BackColor       =   &H00C0FFFF&
      BeginProperty Font 
         Name            =   "Calibri"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   360
      TabIndex        =   1
      Text            =   "127.0.0.1"
      Top             =   1800
      Width           =   2175
   End
   Begin VB.TextBox txt_UserName 
      Alignment       =   2  'Center
      BackColor       =   &H00C0FFFF&
      BeginProperty Font 
         Name            =   "Calibri"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   360
      TabIndex        =   0
      Text            =   "NoName"
      Top             =   840
      Width           =   2175
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      BackColor       =   &H00FFFFFF&
      Caption         =   "User Name"
      BeginProperty Font 
         Name            =   "Calibri"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   360
      TabIndex        =   4
      Top             =   480
      Width           =   2175
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackColor       =   &H00FFFFFF&
      Caption         =   "Connect to IP"
      BeginProperty Font 
         Name            =   "Calibri"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   360
      TabIndex        =   3
      Top             =   1440
      Width           =   2175
   End
End
Attribute VB_Name = "LoginForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
txt_UserName.Text = Environ("username")
txt_UserName.SelStart = 0
txt_UserName.SelLength = Len(txt_UserName.Text)
End Sub

Private Sub btn_Connect_Click()
If txt_UserName.Text <> "" Then
    ChatForm.Show
    Me.Hide
End If
End Sub

Private Sub txt_IP_GotFocus()
txt_IP.SelStart = 0
txt_IP.SelLength = Len(txt_IP.Text)
End Sub

Private Sub txt_IP_KeyPress(KeyAscii As Integer)
If KeyAscii = Asc(vbCrLf) Then btn_Connect_Click
End Sub

Private Sub txt_UserName_GotFocus()
txt_UserName.SelStart = 0
txt_UserName.SelLength = Len(txt_UserName.Text)
End Sub

Private Sub txt_UserName_KeyPress(KeyAscii As Integer)
If KeyAscii = Asc(vbCrLf) Then
    txt_IP.SetFocus
    txt_IP.SelStart = 0
    txt_IP.SelLength = Len(txt_IP.Text)
End If
End Sub
