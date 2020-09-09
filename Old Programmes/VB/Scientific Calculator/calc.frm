VERSION 5.00
Begin VB.Form Calc_form 
   BackColor       =   &H00E0E0E0&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Scientific Calculator"
   ClientHeight    =   5355
   ClientLeft      =   1035
   ClientTop       =   1350
   ClientWidth     =   6915
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5355
   ScaleWidth      =   6915
   Begin VB.CommandButton btn_exp 
      BackColor       =   &H00FFC0C0&
      Caption         =   "Exp"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   1
      Left            =   3960
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   50
      Top             =   4320
      Width           =   855
   End
   Begin VB.CommandButton btn_ans 
      BackColor       =   &H00FFC0C0&
      Caption         =   "Ans"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   5880
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   49
      Top             =   4320
      Width           =   855
   End
   Begin VB.CommandButton btn_log 
      BackColor       =   &H00FFC0C0&
      Caption         =   "log x"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4920
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   48
      Top             =   4320
      Width           =   855
   End
   Begin VB.CommandButton btn_rnd 
      BackColor       =   &H00FFC0C0&
      Caption         =   "Rand"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3000
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   47
      Top             =   4800
      Width           =   855
   End
   Begin VB.CommandButton btn_pi 
      BackColor       =   &H00C0FFC0&
      Caption         =   "p"
      BeginProperty Font 
         Name            =   "Symbol"
         Size            =   11.25
         Charset         =   2
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   46
      Top             =   4800
      Width           =   855
   End
   Begin VB.CommandButton btn_e 
      BackColor       =   &H00C0FFC0&
      Caption         =   "e"
      Height          =   375
      Index           =   0
      Left            =   1080
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   45
      Top             =   4800
      Width           =   855
   End
   Begin VB.TextBox tb_mem 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FFFFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Lucida Console"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   405
      Left            =   5280
      ScrollBars      =   1  'Horizontal
      TabIndex        =   44
      Text            =   "0"
      Top             =   1320
      Width           =   1455
   End
   Begin VB.CommandButton btn_inverse 
      BackColor       =   &H00FFC0C0&
      Caption         =   "x^-1"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3960
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   42
      Top             =   2400
      Width           =   855
   End
   Begin VB.CommandButton btn_equal 
      BackColor       =   &H00FFC0C0&
      Caption         =   "="
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4920
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   41
      Top             =   4800
      Width           =   1815
   End
   Begin VB.CommandButton btn_bksp 
      BackColor       =   &H00C0C0FF&
      Caption         =   "Back Space"
      Height          =   375
      Left            =   4920
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   40
      Top             =   2400
      Width           =   1815
   End
   Begin VB.CommandButton btn_ln 
      BackColor       =   &H00FFC0C0&
      Caption         =   "ln x"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3960
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   39
      Top             =   4800
      Width           =   855
   End
   Begin VB.CommandButton btn_mod 
      BackColor       =   &H00FFC0C0&
      Caption         =   "mod"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2040
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   38
      Top             =   4320
      Width           =   855
   End
   Begin VB.CommandButton btn_cbrkt 
      BackColor       =   &H00FFC0C0&
      Caption         =   ")"
      Height          =   375
      Left            =   1080
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   37
      Top             =   4320
      Width           =   855
   End
   Begin VB.CommandButton btn_obrkt 
      BackColor       =   &H00FFC0C0&
      Caption         =   "("
      Height          =   375
      Left            =   120
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   36
      Top             =   4320
      Width           =   855
   End
   Begin VB.CommandButton btn_cot 
      BackColor       =   &H00FFC0C0&
      Caption         =   "cot x"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   5880
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   35
      Top             =   3840
      Width           =   855
   End
   Begin VB.CommandButton btn_sec 
      BackColor       =   &H00FFC0C0&
      Caption         =   "sec x"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4920
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   34
      Top             =   3840
      Width           =   855
   End
   Begin VB.CommandButton btn_cosec 
      BackColor       =   &H00FFC0C0&
      Caption         =   "cosec x"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   5880
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   33
      Top             =   3360
      Width           =   855
   End
   Begin VB.CommandButton btn_tan 
      BackColor       =   &H00FFC0C0&
      Caption         =   "tan x"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4920
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   32
      Top             =   3360
      Width           =   855
   End
   Begin VB.CommandButton btn_cos 
      BackColor       =   &H00FFC0C0&
      Caption         =   "cos x"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   5880
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   31
      Top             =   2880
      Width           =   855
   End
   Begin VB.CommandButton btn_sin 
      BackColor       =   &H00FFC0C0&
      Caption         =   "sin x"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4920
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   30
      Top             =   2880
      Width           =   855
   End
   Begin VB.CommandButton btn_sqrt 
      BackColor       =   &H00FFC0C0&
      Caption         =   "x^0.5"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3960
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   29
      Top             =   3840
      Width           =   855
   End
   Begin VB.CommandButton btn_sqr 
      BackColor       =   &H00FFC0C0&
      Caption         =   "x^2"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3960
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   28
      Top             =   3360
      Width           =   855
   End
   Begin VB.CommandButton btn_pow 
      BackColor       =   &H00FFC0C0&
      Caption         =   "x^y"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3960
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   27
      Top             =   2880
      Width           =   855
   End
   Begin VB.CommandButton btn_fact 
      BackColor       =   &H00FFC0C0&
      Caption         =   "x!"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2040
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   26
      Top             =   4800
      Width           =   855
   End
   Begin VB.CommandButton btn_div 
      BackColor       =   &H00FFC0C0&
      Caption         =   "÷"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3000
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   25
      Top             =   4320
      Width           =   855
   End
   Begin VB.CommandButton btn_mul 
      BackColor       =   &H00FFC0C0&
      Caption         =   "×"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3000
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   24
      Top             =   3840
      Width           =   855
   End
   Begin VB.CommandButton btn_sub 
      BackColor       =   &H00FFC0C0&
      Caption         =   "-"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3000
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   23
      Top             =   3360
      Width           =   855
   End
   Begin VB.CommandButton btn_add 
      BackColor       =   &H00FFC0C0&
      Caption         =   "+"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   3000
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   22
      Top             =   2400
      Width           =   855
   End
   Begin VB.OptionButton op_radians 
      BackColor       =   &H00E0E0E0&
      Caption         =   "Radians"
      Height          =   255
      Left            =   1080
      TabIndex        =   21
      Top             =   1440
      Value           =   -1  'True
      Width           =   975
   End
   Begin VB.OptionButton op_degrees 
      BackColor       =   &H00E0E0E0&
      Caption         =   "Degrees"
      Height          =   255
      Left            =   120
      TabIndex        =   20
      Top             =   1440
      Width           =   975
   End
   Begin VB.CommandButton btn_C 
      BackColor       =   &H00C0C0FF&
      Caption         =   "C"
      Height          =   375
      Left            =   120
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   1920
      Width           =   1815
   End
   Begin VB.OptionButton op_grads 
      BackColor       =   &H00E0E0E0&
      Caption         =   "Grads"
      Height          =   255
      Left            =   2040
      TabIndex        =   19
      Top             =   1440
      Width           =   855
   End
   Begin VB.CommandButton btn_MMinus 
      BackColor       =   &H00C0E0FF&
      Caption         =   "M-"
      Height          =   375
      Left            =   5880
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   18
      Top             =   1920
      Width           =   855
   End
   Begin VB.CommandButton btn_MPlus 
      BackColor       =   &H00C0E0FF&
      Caption         =   "M+"
      Height          =   375
      Left            =   4920
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   17
      Top             =   1920
      Width           =   855
   End
   Begin VB.CommandButton btn_MR 
      BackColor       =   &H00C0E0FF&
      Caption         =   "MR"
      Height          =   375
      Left            =   3000
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   16
      Top             =   1920
      Width           =   855
   End
   Begin VB.CommandButton btn_MC 
      BackColor       =   &H00C0E0FF&
      Caption         =   "MC"
      Height          =   375
      Left            =   3960
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   15
      Top             =   1920
      Width           =   855
   End
   Begin VB.CommandButton btn_point 
      BackColor       =   &H00C0C0C0&
      Caption         =   "·"
      BeginProperty Font 
         Name            =   "Symbol"
         Size            =   8.25
         Charset         =   2
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2040
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   14
      Top             =   3840
      Width           =   855
   End
   Begin VB.CommandButton btn_0 
      BackColor       =   &H00C0C0C0&
      Caption         =   "0"
      Height          =   375
      Left            =   120
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   13
      Top             =   3840
      Width           =   1815
   End
   Begin VB.CommandButton btn_9 
      BackColor       =   &H00C0C0C0&
      Caption         =   "9"
      Height          =   375
      Left            =   2040
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   12
      Top             =   2400
      Width           =   855
   End
   Begin VB.CommandButton btn_8 
      BackColor       =   &H00C0C0C0&
      Caption         =   "8"
      Height          =   375
      Left            =   1080
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   11
      Top             =   2400
      Width           =   855
   End
   Begin VB.CommandButton btn_7 
      BackColor       =   &H00C0C0C0&
      Caption         =   "7"
      Height          =   375
      Left            =   120
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   10
      Top             =   2400
      Width           =   855
   End
   Begin VB.CommandButton btn_6 
      BackColor       =   &H00C0C0C0&
      Caption         =   "6"
      Height          =   375
      Left            =   2040
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   9
      Top             =   2880
      Width           =   855
   End
   Begin VB.CommandButton btn_5 
      BackColor       =   &H00C0C0C0&
      Caption         =   "5"
      Height          =   375
      Left            =   1080
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   8
      Top             =   2880
      Width           =   855
   End
   Begin VB.CommandButton btn_4 
      BackColor       =   &H00C0C0C0&
      Caption         =   "4"
      Height          =   375
      Left            =   120
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   7
      Top             =   2880
      Width           =   855
   End
   Begin VB.CommandButton btn_3 
      BackColor       =   &H00C0C0C0&
      Caption         =   "3"
      Height          =   375
      Left            =   2040
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   6
      Top             =   3360
      Width           =   855
   End
   Begin VB.CommandButton btn_2 
      BackColor       =   &H00C0C0C0&
      Caption         =   "2"
      Height          =   375
      Left            =   1080
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   5
      Top             =   3360
      Width           =   855
   End
   Begin VB.CommandButton btn_1 
      BackColor       =   &H00C0C0C0&
      Caption         =   "1"
      Height          =   375
      Left            =   120
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   3360
      Width           =   855
   End
   Begin VB.CommandButton btn_CE 
      BackColor       =   &H00C0C0FF&
      Caption         =   "CE"
      Height          =   375
      Left            =   2040
      MaskColor       =   &H00E0E0E0&
      Style           =   1  'Graphical
      TabIndex        =   3
      Top             =   1920
      Width           =   855
   End
   Begin VB.TextBox Sol 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FFFFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Lucida Console"
         Size            =   21.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   120
      TabIndex        =   1
      Text            =   "0"
      Top             =   600
      Width           =   6615
   End
   Begin VB.TextBox Eq 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00FFFFFF&
      CausesValidation=   0   'False
      BeginProperty Font 
         Name            =   "Lucida Console"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   405
      Left            =   120
      Locked          =   -1  'True
      ScrollBars      =   1  'Horizontal
      TabIndex        =   0
      Top             =   120
      Width           =   6615
   End
   Begin VB.Label Label1 
      BackColor       =   &H00E0E0E0&
      Caption         =   "M ="
      Height          =   255
      Left            =   4920
      TabIndex        =   43
      Top             =   1440
      Width           =   375
   End
End
Attribute VB_Name = "Calc_form"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim Mem As Double, AngleUnit As Double
Dim Edit As Boolean

Private Sub Form_Load()
Edit = True
AngleUnit = 1
End Sub

Private Sub Form_KeyPress(KeyAscii As Integer)
MsgBox (Chr(KeyAscii))
End Sub

Public Sub WriteEq(s As String)
Dim Cursor As Integer
Cursor = Eq.SelStart
Eq.Text = Left(Eq.Text, Cursor) + s + Right(Eq.Text, Len(Eq.Text) - Cursor)
Eq.SetFocus
Cursor = Cursor + Len(s)
Eq.SelStart = Cursor
End Sub

Public Function IsSmallCharacter(c As String) As Boolean
If (Asc(c) >= Asc("a") And Asc(c) <= Asc("z")) Then IsSmallCharacter = True Else IsSmallCharacter = False
End Function

Public Function IsAlphabetic(c As String) As Boolean
If (Asc(c) >= Asc("a") And Asc(c) <= Asc("z") Or Asc(c) >= Asc("A") And Asc(c) <= Asc("Z")) Then IsAlphabetic = True Else IsAlphabetic = False
End Function

Public Function IsDigit(c As String) As Boolean
If (Asc(c) >= Asc("0") And Asc(c) <= Asc("9")) Then IsDigit = True Else IsDigit = False
End Function

Public Function IsSpecial(c As String) As Boolean
If (Asc(c) >= Asc("!") And Asc(c) <= Asc("/") Or Asc(c) >= Asc(":") And Asc(c) <= Asc("@") Or Asc(c) >= Asc("[") And Asc(c) <= Asc("`") Or Asc(c) >= Asc("{") And Asc(c) <= Asc("~")) Then IsSpecial = True Else IsSpecial = False
End Function

Public Function Fact(n As Integer) As Double
Fact = 1
Dim i As Double
For i = 2 To n
    Fact = Fact * i
Next i
End Function

Public Function Execute() As String
If Eq.Text = "" Then Exit Function

Dim eqn As String, token(1000) As String, n As Integer, i As Integer, error As String, bracket As Integer
eqn = Eq.Text
n = 0
bracket = 0
While (eqn <> "")
    If IsSmallCharacter(Left(eqn, 1)) Then
        Do
            token(n) = token(n) + Left(eqn, 1)
            eqn = Right(eqn, Len(eqn) - 1)
            If eqn = "" Then Exit Do
        Loop While IsSmallCharacter(Left(eqn, 1))
        Select Case token(n)
        Case "sin", "cos", "tan", "cosec", "sec", "cot", "log", "ln", "e", "pi", "ans", "m", "rand", "mod"
        Case Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End Select
    Else
        If InStr("+-×÷^()!", Left(eqn, 1)) Then
            If Left(eqn, 1) = "-" Then
                If n = 0 Then
                    token(n) = "~"
                Else
                    If IsNumeric(token(n - 1)) Or IsAlphabetic(token(n - 1)) Then token(n) = "-" Else token(n) = "~"
                End If
            Else
                token(n) = Left(eqn, 1)
            End If
            eqn = Right(eqn, Len(eqn) - Len(token(n)))
            If token(n) = "(" Then bracket = bracket + 1
            If token(n) = ")" Then bracket = bracket - 1
        Else
            Do
                If IsDigit(Left(eqn, 1)) Then
                    token(n) = token(n) + Left(eqn, 1)
                    eqn = Right(eqn, Len(eqn) - 1)
                Else
                    Exit Do
                End If
            Loop While eqn <> ""
            If Left(eqn, 1) = "." Then
                token(n) = token(n) + Left(eqn, 1)
                eqn = Right(eqn, Len(eqn) - 1)
            End If
            Do
                If eqn = "" Then Exit Do
                If IsDigit(Left(eqn, 1)) Then
                    token(n) = token(n) + Left(eqn, 1)
                    eqn = Right(eqn, Len(eqn) - 1)
                Else
                    Exit Do
                End If
            Loop
            If Left(eqn, 1) = "." Then
                Execute = "Syntax Error"
                Edit = False
                Exit Function
            End If
        End If
    End If
    n = n + 1
Wend
If bracket <> 0 Then
    Execute = "Syntax Error"
    Edit = False
    Exit Function
End If

'Sol.Text = ""
'For i = 0 To n - 1
'    Sol.Text = Sol.Text + " " + token(i)
'Next i

Dim postfix(1000) As String, stack(1000) As String, top As Integer, j As Integer
j = 0
top = -1
For i = 0 To n - 1
    Select Case token(i)
    Case "+", "-"
        Do
            If top = -1 Then Exit Do
            If stack(top) = "(" Then Exit Do
            postfix(j) = stack(top)
            j = j + 1
            top = top - 1
        Loop
        top = top + 1
        stack(top) = token(i)
    Case "×", "÷", "mod"
        Do
            If top = -1 Then Exit Do
            If stack(top) = "(" Then Exit Do
            If InStr("+-*/", stack(top)) Then Exit Do
            postfix(j) = stack(top)
            j = j + 1
            top = top - 1
        Loop
        top = top + 1
        stack(top) = token(i)
    Case "^"
        Do
            If top = -1 Then Exit Do
            If stack(top) = "(" Then Exit Do
            If InStr("+-*/^", stack(top)) Then Exit Do
            postfix(j) = stack(top)
            j = j + 1
            top = top - 1
        Loop
        top = top + 1
        stack(top) = token(i)
    Case "sin", "cos", "tan", "cosec", "sec", "cot", "log", "ln", "~"
        top = top + 1
        stack(top) = token(i)
    Case "!"
        postfix(j) = token(i)
        j = j + 1
    Case "("
        top = top + 1
        stack(top) = token(i)
    Case ")"
        Do
            If top = -1 Then Exit Do
            If stack(top) = "(" Then Exit Do
            postfix(j) = stack(top)
            j = j + 1
            top = top - 1
        Loop
        top = top - 1
    Case Else
        postfix(j) = token(i)
        j = j + 1
    End Select
Next i
While (top > -1)
    postfix(j) = stack(top)
    j = j + 1
    top = top - 1
Wend
n = j

'Sol.Text = ""
'For i = 0 To n - 1
'    Sol.Text = Sol.Text + " " + postfix(i)
'Next i

For i = 0 To n - 1
    Select Case postfix(i)
    Case "+"
        If top >= 1 Then
            If IsNumeric(stack(top - 1)) Or IsNumeric(stack(top)) Then
                stack(top - 1) = CStr(Val(stack(top - 1)) + Val(stack(top)))
                top = top - 1
            End If
        Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End If
    Case "-"
        If top >= 1 Then
            If IsNumeric(stack(top - 1)) Or IsNumeric(stack(top)) Then
                stack(top - 1) = CStr(Val(stack(top - 1)) - Val(stack(top)))
                top = top - 1
            End If
        Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End If
    Case "×"
        If top >= 1 Then
            If IsNumeric(stack(top - 1)) Or IsNumeric(stack(top)) Then
                stack(top - 1) = CStr(Val(stack(top - 1)) * Val(stack(top)))
                top = top - 1
            End If
        Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End If
    Case "÷"
        If top >= 1 Then
            If IsNumeric(stack(top - 1)) Or IsNumeric(stack(top)) Then
                If Val(stack(top)) = 0 Then
                    Execute = "Math Error"
                    Edit = False
                    Exit Function
                End If
                stack(top - 1) = CStr(Val(stack(top - 1)) / Val(stack(top)))
                top = top - 1
            End If
        Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End If
    Case "mod"
        If top >= 1 Then
            If IsNumeric(stack(top - 1)) Or IsNumeric(stack(top)) Then
                If Val(stack(top)) = 0 Then
                    Execute = "Math Error"
                    Edit = False
                    Exit Function
                End If
                stack(top - 1) = CStr(Val(stack(top - 1)) Mod Val(stack(top)))
                top = top - 1
            End If
        Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End If
    Case "^"
        If top >= 1 Then
            If IsNumeric(stack(top - 1)) Or IsNumeric(stack(top)) Then
                If stack(top - 1) = Exp(1) Then
                    stack(top - 1) = Exp(Val(stack(top)))
                Else
                    If Val(stack(top - 1)) = 0 And Val(stack(top)) < 0 Then
                        Execute = "Math Error"
                        Edit = False
                        Exit Function
                    End If
                    stack(top - 1) = CStr(Val(stack(top - 1)) ^ Val(stack(top)))
                End If
                top = top - 1
            End If
        Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End If
    Case "sin"
        If top >= 0 Then
            If IsNumeric(stack(top)) Then
                stack(top) = Sin(Val(stack(top)) * AngleUnit)
            End If
        Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End If
    Case "cos"
        If top >= 0 Then
            If IsNumeric(stack(top)) Then
                stack(top) = Cos(Val(stack(top)) * AngleUnit)
            End If
        Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End If
    Case "tan"
        If top >= 0 Then
            If IsNumeric(stack(top)) Then
                If (Val(stack(top)) * AngleUnit - 3.14159265358979 / 2) Mod 3.14159265358979 = 0 Then
                    Execute = "Math Error"
                    Edit = False
                    Exit Function
                End If
                stack(top) = Tan(Val(stack(top)) * AngleUnit)
            End If
        Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End If
    Case "cosec"
        If top >= 0 Then
            If IsNumeric(stack(top)) Then
                stack(top) = 1 / Sin(Val(stack(top)) * AngleUnit)
            End If
        Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End If
    Case "sec"
        If top >= 0 Then
            If IsNumeric(stack(top)) Then
                stack(top) = 1 / Cos(Val(stack(top)) * AngleUnit)
            End If
        Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End If
    Case "cot"
        If top >= 0 Then
            If IsNumeric(stack(top)) Then
                If (Val(stack(top)) * AngleUnit) Mod 3.14159265358979 = 0 Then
                    Execute = "Math Error"
                    Edit = False
                    Exit Function
                End If
                stack(top) = 1 / Tan(Val(stack(top)) * AngleUnit)
            End If
        Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End If
    Case "log"
        If top >= 0 Then
            If IsNumeric(stack(top)) Then
                If Val(stack(top)) = 0 Then
                    Execute = "Math Error"
                    Edit = False
                    Exit Function
                End If
                stack(top) = Log(Val(stack(top))) / Log(10)
            End If
        Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End If
    Case "ln"
        If top >= 0 Then
            If IsNumeric(stack(top)) Then
                If Val(stack(top)) = 0 Then
                    Execute = "Math Error"
                    Edit = False
                    Exit Function
                End If
                stack(top) = Log(Val(stack(top)))
            End If
        Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End If
    Case "!"
        If top >= 0 Then
            If IsNumeric(stack(top)) Then
                stack(top) = Fact(Val(stack(top)))
            End If
        Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End If
    Case "~"
        If top >= 0 Then
            If IsNumeric(stack(top)) Then
                stack(top) = -Val(stack(top))
            End If
        Else
            Execute = "Syntax Error"
            Edit = False
            Exit Function
        End If
    Case "e"
        top = top + 1
        stack(top) = Exp(1)
    Case "pi"
        top = top + 1
        stack(top) = "3.14159265358979"
    Case "rand"
        top = top + 1
        stack(top) = CStr(Rnd())
    Case "m"
        top = top + 1
        stack(top) = CStr(Mem)
    Case "ans"
        top = top + 1
        stack(top) = Sol.Text
    Case Else
        top = top + 1
        stack(top) = postfix(i)
    End Select
Next i
If top = 0 And IsNumeric(stack(top)) Then
    Execute = stack(top)
Else
    Execute = "Syntax Error"
End If
Edit = False
End Function

Public Sub NewEq()
If Edit = True Or Eq.Text = "" Then Exit Sub
If Not (Eq.Text = "." Or (Asc(Eq.Text) >= "0" And Asc(Eq.Text) <= "9")) Then Eq.Text = ""
Edit = True
End Sub

Private Sub btn_equal_Click()
Sol.Text = Execute
End Sub

Private Sub btn_0_Click()
NewEq
WriteEq "0"
End Sub

Private Sub btn_1_Click()
NewEq
WriteEq "1"
End Sub

Private Sub btn_2_Click()
NewEq
WriteEq "2"
End Sub

Private Sub btn_3_Click()
NewEq
WriteEq "3"
End Sub

Private Sub btn_4_Click()
NewEq
WriteEq "4"
End Sub

Private Sub btn_5_Click()
NewEq
WriteEq "5"
End Sub

Private Sub btn_6_Click()
NewEq
WriteEq "6"
End Sub

Private Sub btn_7_Click()
NewEq
WriteEq "7"
End Sub

Private Sub btn_8_Click()
NewEq
WriteEq "8"
End Sub

Private Sub btn_9_Click()
NewEq
WriteEq "9"
End Sub

Private Sub btn_bksp_Click()
If Eq.Text <> "" Then
    Dim Cursor As Integer
    Cursor = Eq.SelStart
    If IsAlphabetic(Mid(Eq.Text, Cursor, 1)) Then
        Do
            If Cursor = 0 Then Exit Do
            If Not IsAlphabetic(Mid(Eq.Text, Cursor, 1)) Then Exit Do
            Eq.Text = Left(Eq.Text, Cursor - 1) + Right(Eq.Text, Len(Eq.Text) - Cursor)
            Cursor = Cursor - 1
        Loop
    Else
        Eq.Text = Left(Eq.Text, Cursor - 1) + Right(Eq.Text, Len(Eq.Text) - Cursor)
        Cursor = Cursor - 1
    End If
    Edit = True
    Eq.SelStart = Cursor
End If
Eq.SetFocus
End Sub

Private Sub btn_cbrkt_Click()
If Eq.Text <> "" Then WriteEq ")"
Edit = True
End Sub

Private Sub btn_obrkt_Click()
NewEq
WriteEq "("
End Sub

Private Sub btn_add_Click()
If Eq.Text <> "" Then WriteEq "+"
Edit = True
End Sub

Private Sub btn_mul_Click()
If Eq.Text <> "" Then WriteEq "×"
Edit = True
End Sub

Private Sub btn_sub_Click()
WriteEq "-"
Edit = True
End Sub

Private Sub btn_div_Click()
If Eq.Text <> "" Then WriteEq "÷"
Edit = True
End Sub

Private Sub btn_fact_Click()
If Eq.Text <> "" Then WriteEq "!"
Edit = True
End Sub

Private Sub btn_pow_Click()
If Eq.Text <> "" Then WriteEq "^"
Edit = True
End Sub

Private Sub btn_sqr_Click()
If Eq.Text <> "" Then WriteEq "^2"
Edit = True
End Sub

Private Sub btn_sqrt_Click()
If Eq.Text <> "" Then WriteEq "^(0.5)"
Edit = True
End Sub

Private Sub btn_inverse_Click()
If Eq.Text <> "" Then WriteEq "^-1"
Edit = True
End Sub

Private Sub btn_exp_Click(Index As Integer)
If Eq.Text <> "" Then WriteEq "*10^"
Edit = True
End Sub

Private Sub btn_point_Click()
NewEq
WriteEq "."
End Sub

Private Sub btn_C_Click()
Eq.Text = ""
Sol.Text = "0"
tb_mem = "0"
Mem = 0
Eq.SetFocus
End Sub

Private Sub btn_CE_Click()
Eq.Text = ""
Sol.Text = "0"
Eq.SetFocus
End Sub

Private Sub btn_cos_Click()
NewEq
WriteEq "cos"
End Sub

Private Sub btn_cosec_Click()
NewEq
WriteEq "cosec"
End Sub

Private Sub btn_cot_Click()
NewEq
WriteEq "cot"
End Sub

Private Sub btn_tan_Click()
NewEq
WriteEq "tan"
End Sub

Private Sub btn_sec_Click()
NewEq
WriteEq "sec"
End Sub

Private Sub btn_sin_Click()
NewEq
WriteEq "sin"
End Sub

Private Sub btn_ln_Click()
NewEq
WriteEq "ln"
End Sub

Private Sub btn_rnd_Click()
NewEq
WriteEq "rand"
End Sub

Private Sub btn_pi_Click()
NewEq
WriteEq "pi"
End Sub

Private Sub btn_log_Click()
NewEq
WriteEq "log"
End Sub

Private Sub btn_ans_Click()
NewEq
WriteEq "ans"
End Sub

Private Sub btn_mod_Click()
NewEq
WriteEq "mod"
End Sub

Private Sub btn_e_Click(Index As Integer)
NewEq
WriteEq "e"
End Sub

Private Sub btn_MC_Click()
Mem = 0
tb_mem.Text = "0"
Eq.SetFocus
End Sub

Private Sub btn_MPlus_Click()
Sol.Text = Execute
Mem = Mem + Val(Sol.Text)
tb_mem.Text = CStr(Mem)
Eq.SetFocus
End Sub

Private Sub btn_MMinus_Click()
Sol.Text = Execute
Mem = Mem - Val(Sol.Text)
tb_mem.Text = CStr(Mem)
Eq.SetFocus
End Sub

Private Sub btn_MR_Click()
NewEq
WriteEq "m"
End Sub

Private Sub op_degrees_Click()
AngleUnit = 3.14159265358979 / 180
Eq.SetFocus
End Sub

Private Sub op_grads_Click()
AngleUnit = 3.14159265358979 / 200
Eq.SetFocus
End Sub

Private Sub op_radians_Click()
AngleUnit = 1
Eq.SetFocus
End Sub

Private Sub Eq_KeyPress(KeyAscii As Integer)
Select Case KeyAscii
Case Asc("0"), Asc("1"), Asc("2"), Asc("3"), Asc("4"), Asc("5"), Asc("6"), Asc("7"), Asc("8"), Asc("9"), Asc("."), Asc("e")
    NewEq
    WriteEq Chr(KeyAscii)
Case Asc("+")
    btn_add_Click
Case Asc("-")
    btn_sub_Click
Case Asc("*")
    btn_mul_Click
Case Asc("/")
    btn_div_Click
Case Asc("^")
    btn_pow_Click
Case Asc("!")
    btn_fact_Click
Case Asc("("), Asc("{"), Asc("[")
    btn_obrkt_Click
Case Asc(")"), Asc("}"), Asc("]")
    btn_cbrkt_Click
Case Asc("a")
    btn_ans_Click
Case Asc("p")
    btn_pi_Click
Case Asc("m")
    btn_mod_Click
Case Asc("s")
    btn_sin_Click
Case Asc("c")
    btn_cos_Click
Case Asc("t")
    btn_tan_Click
Case Asc("l")
    btn_ln_Click
Case vbKeyReturn, Asc("=")
    btn_equal_Click
Case vbKeyBack
    btn_bksp_Click
Case Asc("c"), vbKeyEscape
    btn_C_Click
End Select
End Sub
