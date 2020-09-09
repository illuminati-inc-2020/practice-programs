VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form LoginForm 
   BackColor       =   &H00FFFFFF&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Connect"
   ClientHeight    =   3480
   ClientLeft      =   16950
   ClientTop       =   960
   ClientWidth     =   2985
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3480
   ScaleWidth      =   2985
   Begin VB.ComboBox txt_IP 
      BackColor       =   &H00C0FFFF&
      Height          =   315
      Left            =   360
      TabIndex        =   4
      Top             =   1920
      Width           =   2175
   End
   Begin VB.Timer Timer 
      Interval        =   500
      Left            =   1560
      Top             =   2880
   End
   Begin MSWinsockLib.Winsock Winsock 
      Left            =   960
      Top             =   2880
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
      Protocol        =   1
      RemoteHost      =   "255.255.255.255"
   End
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
      TabIndex        =   1
      Top             =   2280
      Width           =   1215
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
      TabIndex        =   3
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
      TabIndex        =   2
      Top             =   1440
      Width           =   2175
   End
End
Attribute VB_Name = "LoginForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub CreateBroadcastSocket()
On Error GoTo Client
Winsock.Close
Winsock.LocalPort = 4445
Winsock.RemotePort = 4446
Winsock.Bind Winsock.LocalPort
Exit Sub
Client:
Winsock.Close
Winsock.LocalPort = 4446
Winsock.RemotePort = 4445
Winsock.Bind Winsock.LocalPort
End Sub

Private Sub Form_Load()
txt_UserName.Text = Environ("username")
txt_UserName.SelStart = 0
txt_UserName.SelLength = Len(txt_UserName.Text)

CreateBroadcastSocket
End Sub

Private Sub Winsock_DataArrival(ByVal bytesTotal As Long)
Dim msg As String
Winsock.GetData msg
Dim new_server As Boolean, i As Integer
new_server = True
For i = 0 To txt_IP.ListCount
    If txt_IP.List(i) = msg Then new_server = False
Next
If new_server Then
    txt_IP.Text = msg
    txt_IP.AddItem msg
End If
End Sub

Private Sub Timer_Timer()
If txt_IP.Text = "" Then Winsock.SendData Winsock.LocalIP
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

