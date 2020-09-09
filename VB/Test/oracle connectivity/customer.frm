VERSION 5.00
Begin VB.Form customer 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Customer"
   ClientHeight    =   6900
   ClientLeft      =   45
   ClientTop       =   390
   ClientWidth     =   10845
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6900
   ScaleWidth      =   10845
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command2 
      Caption         =   "Back"
      Height          =   615
      Left            =   5880
      TabIndex        =   9
      Top             =   5640
      Width           =   1695
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Insert"
      Height          =   615
      Left            =   2520
      TabIndex        =   8
      Top             =   5640
      Width           =   1815
   End
   Begin VB.TextBox Text4 
      Height          =   495
      Left            =   2400
      TabIndex        =   7
      Top             =   4440
      Width           =   2175
   End
   Begin VB.TextBox Text3 
      Height          =   495
      Left            =   2400
      TabIndex        =   5
      Top             =   3240
      Width           =   2175
   End
   Begin VB.TextBox Text2 
      Height          =   495
      Left            =   2400
      TabIndex        =   3
      Top             =   2040
      Width           =   2175
   End
   Begin VB.TextBox Text1 
      Height          =   495
      Left            =   2400
      TabIndex        =   1
      Top             =   840
      Width           =   2175
   End
   Begin VB.Label Label4 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "discount"
      Height          =   495
      Left            =   600
      TabIndex        =   6
      Top             =   4440
      Width           =   1215
   End
   Begin VB.Label Label3 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "city"
      Height          =   495
      Left            =   600
      TabIndex        =   4
      Top             =   3240
      Width           =   1215
   End
   Begin VB.Label Label2 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "cname"
      Height          =   495
      Left            =   600
      TabIndex        =   2
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Label Label1 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "       CID"
      Height          =   495
      Left            =   600
      TabIndex        =   0
      Top             =   840
      Width           =   975
   End
End
Attribute VB_Name = "customer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim cn As New ADODB.Connection, s As String

Private Sub Command1_Click()
s = "insert into customer values('" + Text1.Text + "','" + Text2.Text + "','" + Text3.Text + "', " + Text4.Text + ");"
cn.Execute (s)
MsgBox "Insertion Successful", 64
Text1.Text = ""
Text2.Text = ""
Text3.Text = ""
Text4.Text = ""
Text1.SetFocus
End Sub

Private Sub Command2_Click()
cn.Close
Form1.Show
Me.Hide
End Sub

Private Sub Form_Load()
cn.Open "dsn=dat;pwd=product;"
End Sub
