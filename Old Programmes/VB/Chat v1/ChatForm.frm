VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Begin VB.Form ChatForm 
   BackColor       =   &H00FFFFFF&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Chat Server"
   ClientHeight    =   3825
   ClientLeft      =   16755
   ClientTop       =   765
   ClientWidth     =   3405
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3825
   ScaleWidth      =   3405
   Begin MSWinsockLib.Winsock Winsock 
      Left            =   720
      Top             =   1080
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin MSWinsockLib.Winsock BroadcastSocket 
      Left            =   720
      Top             =   360
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
      Protocol        =   1
      RemoteHost      =   "255.255.255.255"
   End
   Begin RichTextLib.RichTextBox text_Conversation 
      Height          =   3135
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   3135
      _ExtentX        =   5530
      _ExtentY        =   5530
      _Version        =   393217
      BackColor       =   12648447
      ReadOnly        =   -1  'True
      ScrollBars      =   2
      TextRTF         =   $"ChatForm.frx":0000
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
   Begin VB.CommandButton btn_Send 
      BackColor       =   &H0080EFFF&
      Caption         =   "Send"
      Enabled         =   0   'False
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
      Left            =   2400
      Style           =   1  'Graphical
      TabIndex        =   1
      Top             =   3360
      Width           =   855
   End
   Begin VB.TextBox text_Message 
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
      Left            =   120
      TabIndex        =   0
      Top             =   3440
      Width           =   2175
   End
End
Attribute VB_Name = "ChatForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim UserName As String, RemoteUserName As String

'-----------------------------------------Form events--------------------------
Private Sub CreateBroadcastSocket()
On Error GoTo Client
BroadcastSocket.LocalPort = 4445
BroadcastSocket.RemotePort = 4446
BroadcastSocket.Bind BroadcastSocket.LocalPort
BroadcastSocket.SendData "IP"

Exit Sub
Client:
BroadcastSocket.LocalPort = 4446
BroadcastSocket.RemotePort = 4445
BroadcastSocket.Bind BroadcastSocket.LocalPort
End Sub

Private Sub Form_Load()
CreateBroadcastSocket

Winsock.RemotePort = 4444
Winsock.RemoteHost = LoginForm.txt_IP.Text
Winsock.Connect
End Sub

Private Sub Form_Activate()
UserName = LoginForm.txt_UserName.Text
Me.Caption = UserName
End Sub

Private Sub Form_Unload(Cancel As Integer)
If btn_Send.Enabled Then
    Winsock.SendData "C"
    Cancel = True
Else
    End
End If
End Sub

'----------------------------------------Button Click event--------------------
Private Sub btn_Send_Click()
If btn_Send.Enabled Then
    text_Conversation.SelStart = Len(text_Conversation.TextRTF)
    text_Conversation.SelAlignment = vbLeftJustify
    
    text_Conversation.SelFontSize = 10
    text_Conversation.SelColor = ColorConstants.vbBlue
    text_Conversation.SelBold = True
    text_Conversation.SelText = UserName + " : "
    
    text_Conversation.SelBold = False
    text_Conversation.SelColor = ColorConstants.vbBlack
    text_Conversation.SelText = text_Message.Text + vbCrLf
    
    text_Conversation.SelBold = False
    text_Conversation.SelColor = ColorConstants.vbBlack
    text_Conversation.SelFontSize = 6
    text_Conversation.SelText = CStr(Time) + vbCrLf
    
    text_Conversation.SelStart = Len(text_Conversation.TextRTF)
    
    Winsock.SendData "M" + text_Message.Text
    text_Message.Text = ""
End If
text_Message.SetFocus
End Sub

'-------------------------------------Textbox Events---------------------
Private Sub text_Message_KeyPress(KeyAscii As Integer)
If KeyAscii = Asc(vbCrLf) Then btn_Send_Click
End Sub

Private Sub text_Conversation_Click()
text_Message.SetFocus
End Sub

'-------------------------------Winsock events--------------------------
Private Sub Winsock_ConnectionRequest(ByVal requestID As Long)
If Winsock.State <> sckClosed Then
    Winsock.Close
    Winsock.Accept requestID
    btn_Send.Enabled = True
    Winsock.SendData "U" + UserName
End If
End Sub

Private Sub Winsock_DataArrival(ByVal bytesTotal As Long)
Dim msg As String
Winsock.GetData msg
Select Case Left(msg, 1)
Case "M":
    text_Conversation.SelStart = Len(text_Conversation.TextRTF)
    text_Conversation.SelAlignment = vbRightJustify
    
    text_Conversation.SelFontSize = 10
    text_Conversation.SelColor = ColorConstants.vbBlack
    text_Conversation.SelBold = False
    text_Conversation.SelText = Mid(msg, 2) + " : "
    
    text_Conversation.SelColor = ColorConstants.vbRed
    text_Conversation.SelBold = True
    text_Conversation.SelText = RemoteUserName + vbCrLf
    
    text_Conversation.SelBold = False
    text_Conversation.SelColor = ColorConstants.vbBlack
    text_Conversation.SelFontSize = 6
    text_Conversation.SelText = CStr(Time) + vbCrLf
    
    text_Conversation.SelStart = Len(text_Conversation.TextRTF)
Case "U":
    If text_Conversation.Text = "" Then Winsock.SendData "U" + UserName
    RemoteUserName = Mid(msg, 2)
    Me.Caption = UserName + " -> " + RemoteUserName
    btn_Send.Enabled = True
Case "C":
    btn_Send.Enabled = False
    Winsock.SendData "E"
Case "E":
    End
End Select
End Sub

Private Sub Winsock_Error(ByVal Number As Integer, Description As String, ByVal Scode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
Select Case Number
Case 10061:
    Winsock.Close
    Winsock.LocalPort = 4444
    Winsock.Listen
Case Else:
    MsgBox CStr(Number) + " : " + Description, vbOKOnly, "Winsock Error"
    End
End Select
End Sub

Private Sub BroadcastSocket_DataArrival(ByVal bytesTotal As Long)
Dim msg As String
Winsock.GetData msg
MsgBox msg
End Sub
