VERSION 5.00
Begin VB.Form FindForm 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Find/Replace"
   ClientHeight    =   2010
   ClientLeft      =   11385
   ClientTop       =   4020
   ClientWidth     =   6645
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2010
   ScaleWidth      =   6645
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton btn_Replace 
      Caption         =   "Replace"
      Height          =   375
      Left            =   3960
      TabIndex        =   4
      Top             =   1440
      Width           =   1215
   End
   Begin VB.TextBox text_Replace 
      Height          =   285
      Left            =   1200
      TabIndex        =   2
      Top             =   720
      Width           =   5295
   End
   Begin VB.CheckBox check_NoHighlight 
      Caption         =   "No  Highlight"
      Height          =   195
      Left            =   240
      TabIndex        =   8
      Top             =   1680
      Width           =   1575
   End
   Begin VB.CheckBox check_WholeWord 
      Caption         =   "Whole Word"
      Height          =   195
      Left            =   240
      TabIndex        =   7
      Top             =   1440
      Width           =   1575
   End
   Begin VB.CheckBox check_MatchCase 
      Caption         =   "Match Case"
      Height          =   195
      Left            =   240
      TabIndex        =   6
      Top             =   1200
      Width           =   1575
   End
   Begin VB.CommandButton btn_Close 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   5280
      TabIndex        =   5
      Top             =   1440
      Width           =   1215
   End
   Begin VB.CommandButton btn_Find 
      Caption         =   "Find"
      Height          =   375
      Left            =   2640
      TabIndex        =   3
      Top             =   1440
      Width           =   1215
   End
   Begin VB.TextBox text_search 
      Height          =   285
      Left            =   1200
      TabIndex        =   1
      Top             =   240
      Width           =   5295
   End
   Begin VB.Label Label2 
      Caption         =   "Replace with"
      Height          =   255
      Left            =   120
      TabIndex        =   9
      Top             =   720
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "Find What"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   975
   End
End
Attribute VB_Name = "FindForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub btn_Close_Click()
Me.Hide
End Sub

Private Sub btn_Find_Click()
WordPad.TextBox.SelStart = WordPad.TextBox.SelStart + WordPad.TextBox.SelLength
WordPad.TextBox.SelLength = 0
Dim voption As Integer, result As Long
voption = 0
If check_NoHighlight.Value = 1 Then voption = voption + FindConstants.rtfNoHighlight
If check_MatchCase.Value = 1 Then voption = voption + FindConstants.rtfMatchCase
If check_WholeWord.Value = 1 Then voption = voption + FindConstants.rtfWholeWord
result = WordPad.TextBox.Find(text_search.Text, WordPad.TextBox.SelStart, Len(WordPad.TextBox.Text), voption)
If WordPad.TextBox.SelLength = 0 Then
    WordPad.TextBox.SelStart = 0
    result = WordPad.TextBox.Find(text_search.Text, WordPad.TextBox.SelStart, Len(WordPad.TextBox.Text), voption)
    WordPad.StatusBar.SimpleText = "Search started from beginning"
End If
If check_NoHighlight.Value = 1 Then WordPad.TextBox.SelStart = result
WordPad.TextBox.SetFocus
End Sub

Private Sub btn_Replace_Click()
btn_Find_Click
If WordPad.TextBox.SelLength > 0 Then
    WordPad.TextBox.SelText = text_Replace.Text
    WordPad.TextBox.SelStart = WordPad.TextBox.SelStart - Len(text_Replace.Text)
    WordPad.TextBox.SelLength = Len(text_Replace.Text)
End If
End Sub

Private Sub Form_GotFocus()
FindForm.text_search = WordPad.TextBox.SelText
End Sub
