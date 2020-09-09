VERSION 5.00
Begin VB.Form orders 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Insert on Order Table"
   ClientHeight    =   11085
   ClientLeft      =   45
   ClientTop       =   390
   ClientWidth     =   12225
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   11085
   ScaleWidth      =   12225
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox Text4 
      Height          =   495
      Left            =   3600
      TabIndex        =   16
      Top             =   8640
      Width           =   2295
   End
   Begin VB.TextBox Text3 
      Height          =   495
      Left            =   3600
      TabIndex        =   15
      Top             =   7680
      Width           =   2175
   End
   Begin VB.ComboBox Combo3 
      Height          =   315
      Left            =   3600
      TabIndex        =   14
      Top             =   6720
      Width           =   2175
   End
   Begin VB.ComboBox Combo2 
      Height          =   315
      Left            =   3600
      TabIndex        =   13
      Top             =   5520
      Width           =   2175
   End
   Begin VB.ComboBox Combo1 
      Height          =   315
      Left            =   3600
      TabIndex        =   12
      Top             =   3840
      Width           =   2175
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Back"
      Height          =   615
      Left            =   6360
      TabIndex        =   3
      Top             =   10080
      Width           =   1695
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Insert"
      Height          =   615
      Left            =   2520
      TabIndex        =   2
      Top             =   10080
      Width           =   1815
   End
   Begin VB.TextBox Text2 
      Height          =   495
      Left            =   3600
      TabIndex        =   1
      Top             =   2160
      Width           =   2175
   End
   Begin VB.TextBox Text1 
      Height          =   495
      Left            =   3600
      TabIndex        =   0
      Top             =   960
      Width           =   2175
   End
   Begin VB.Label Label8 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Rupees"
      Height          =   495
      Left            =   1800
      TabIndex        =   11
      Top             =   8640
      Width           =   1215
   End
   Begin VB.Label Label7 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "qty"
      Height          =   495
      Left            =   1800
      TabIndex        =   10
      Top             =   7680
      Width           =   1215
   End
   Begin VB.Label Label6 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "pid"
      Height          =   615
      Left            =   1800
      TabIndex        =   9
      Top             =   6600
      Width           =   1215
   End
   Begin VB.Label Label5 
      Caption         =   "Label5"
      Height          =   375
      Left            =   4560
      TabIndex        =   8
      Top             =   1200
      Width           =   735
   End
   Begin VB.Label Label4 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "aid"
      Height          =   495
      Left            =   1800
      TabIndex        =   7
      Top             =   5400
      Width           =   1215
   End
   Begin VB.Label Label3 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "cid"
      Height          =   495
      Left            =   1800
      TabIndex        =   6
      Top             =   3720
      Width           =   1215
   End
   Begin VB.Label Label2 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "month"
      Height          =   495
      Left            =   1800
      TabIndex        =   5
      Top             =   2160
      Width           =   1215
   End
   Begin VB.Label Label1 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Ordno"
      Height          =   495
      Left            =   1800
      TabIndex        =   4
      Top             =   960
      Width           =   975
   End
End
Attribute VB_Name = "orders"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim cn As New ADODB.Connection, s$, s1$, s2$, s3$, r As New ADODB.Recordset, r1 As New ADODB.Recordset, r2 As New ADODB.Recordset

Private Sub Command1_Click()
s = "insert into orders values('" + Text1.Text + "'," + Text2.Text + ", '" + Combo1.Text + "','" + Combo2.Text + "','" + Combo3.Text + "'," + Text3.Text + "," + Text4.Text + ")"
cn.Execute (s)
MsgBox "Insertion Scuccessful", vbCritical

Text1.Text = ""
Text2.Text = ""
Combo1.Text = ""
Combo2.Text = ""
Combo3.Text = ""
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
s1 = "select cid from customer"
r.Open s1, cn, adOpenStatic, adLockReadOnly
While (Not r.EOF)
Combo1.AddItem r.Fields("cid")
r.MoveNext
Wend
s2 = "select aid from agents"
r1.Open s2, cn, adOpenStatic, adLockReadOnly
While Not r1.EOF
Combo2.AddItem r1.Fields("aid")
r1.MoveNext
Wend
s3 = "select pid from products"
r2.Open s3, cn, adOpenStatic, adLockReadOnly
While Not r2.EOF
Combo3.AddItem r2.Fields("pid")
r2.MoveNext
Wend
End Sub
