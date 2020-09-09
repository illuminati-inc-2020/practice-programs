VERSION 5.00
Begin VB.Form Agents 
   Caption         =   "Agents"
   ClientHeight    =   6570
   ClientLeft      =   60
   ClientTop       =   405
   ClientWidth     =   10530
   LinkTopic       =   "Form2"
   ScaleHeight     =   6570
   ScaleWidth      =   10530
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox Text1 
      Height          =   495
      Left            =   2880
      TabIndex        =   5
      Top             =   720
      Width           =   2175
   End
   Begin VB.TextBox Text2 
      Height          =   495
      Left            =   2880
      TabIndex        =   4
      Top             =   1920
      Width           =   2175
   End
   Begin VB.TextBox Text3 
      Height          =   495
      Left            =   2880
      TabIndex        =   3
      Top             =   3120
      Width           =   2175
   End
   Begin VB.TextBox Text4 
      Height          =   495
      Left            =   2880
      TabIndex        =   2
      Top             =   4320
      Width           =   2175
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Insert"
      Height          =   615
      Left            =   2760
      TabIndex        =   1
      Top             =   5400
      Width           =   1815
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Back"
      Height          =   615
      Left            =   6120
      TabIndex        =   0
      Top             =   5400
      Width           =   1695
   End
   Begin VB.Label Label1 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "       aid"
      Height          =   495
      Left            =   1080
      TabIndex        =   9
      Top             =   720
      Width           =   975
   End
   Begin VB.Label Label2 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "aname"
      Height          =   495
      Left            =   1080
      TabIndex        =   8
      Top             =   1920
      Width           =   1215
   End
   Begin VB.Label Label3 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "city"
      Height          =   495
      Left            =   1080
      TabIndex        =   7
      Top             =   3120
      Width           =   1215
   End
   Begin VB.Label Label4 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "percent commission"
      Height          =   495
      Left            =   1080
      TabIndex        =   6
      Top             =   4320
      Width           =   1215
   End
End
Attribute VB_Name = "Agents"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim cn As New ADODB.Connection, s As String

Private Sub Command1_Click()
s = "insert into agents values('" + Text1.Text + "','" + Text2.Text + "','" + Text3.Text + "', " + Text4.Text + ");"
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
cn.Open "dsn=dat;pwd=tiger;"
End Sub

