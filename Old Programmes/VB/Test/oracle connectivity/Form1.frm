VERSION 5.00
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Main Menu"
   ClientHeight    =   8655
   ClientLeft      =   45
   ClientTop       =   390
   ClientWidth     =   11010
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   8655
   ScaleWidth      =   11010
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command5 
      Caption         =   "E&xit"
      Height          =   735
      Left            =   4560
      TabIndex        =   4
      Top             =   6960
      Width           =   1815
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Insert in Or&ders Table"
      Height          =   975
      Left            =   3600
      TabIndex        =   3
      Top             =   5280
      Width           =   3615
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Insert in P&roduct Table"
      Height          =   975
      Left            =   3600
      TabIndex        =   2
      Top             =   3600
      Width           =   3615
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Insert in A&gents Table"
      Height          =   855
      Left            =   3600
      TabIndex        =   1
      Top             =   2040
      Width           =   3615
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Insert in Cu&stomer Table"
      Height          =   855
      Left            =   3600
      TabIndex        =   0
      Top             =   480
      Width           =   3615
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
customer.Show
Me.Hide
End Sub

Private Sub Command2_Click()
Agents.Show
Me.Hide
End Sub

Private Sub Command4_Click()
orders.Show
Me.Hide
End Sub

Private Sub Command5_Click()
End
End Sub
