VERSION 5.00
Begin VB.Form ClockWindow 
   BackColor       =   &H00E0E0E0&
   BorderStyle     =   0  'None
   Caption         =   "Clock"
   ClientHeight    =   2025
   ClientLeft      =   18105
   ClientTop       =   195
   ClientWidth     =   2025
   FillStyle       =   0  'Solid
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Picture         =   "clock.frx":0000
   ScaleHeight     =   137.03
   ScaleMode       =   0  'User
   ScaleWidth      =   135
   ShowInTaskbar   =   0   'False
   Begin VB.Timer Timer 
      Interval        =   100
      Left            =   840
      Top             =   1080
   End
   Begin VB.Line HourHand 
      BorderColor     =   &H00808080&
      BorderWidth     =   4
      X1              =   67
      X2              =   80
      Y1              =   68.007
      Y2              =   32.481
   End
   Begin VB.Line MinuteHand 
      BorderColor     =   &H00404040&
      BorderWidth     =   2
      X1              =   67
      X2              =   56
      Y1              =   68.007
      Y2              =   32.481
   End
   Begin VB.Line SecondHand 
      BorderColor     =   &H00000000&
      X1              =   67
      X2              =   67
      Y1              =   68.007
      Y2              =   24.361
   End
End
Attribute VB_Name = "ClockWindow"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim X0 As Integer, Y0 As Integer

Private Sub Form_Load()
X0 = SecondHand.X2
Y0 = SecondHand.Y2
RefreshClock
End Sub

Private Sub Form_MouseDown(Button As Integer, Shift As Integer, x As Single, Y As Single)
If CloseMenu.Visible Then
    CloseMenu.Hide
Else
    If Button = 2 Then
        CloseMenu.Left = Me.Left + (Me.Width - CloseMenu.Width) / 2
        CloseMenu.Top = Me.Top + (Me.Height - CloseMenu.Height) / 2
        CloseMenu.Show
    End If
End If
End Sub

Private Sub Timer_Timer()
RefreshClock
End Sub

Public Sub RefreshClock()
Dim SecondHandAngle As Double, MinuteHandAngle As Double, HourHandAngle As Double
SecondHandAngle = (Second(Time()) * 6) * (3.14159265 / 180)
SecondHand.X2 = (X0 - SecondHand.X1) * Cos(SecondHandAngle) - (Y0 - SecondHand.Y1 - 5) * Sin(SecondHandAngle) + SecondHand.X1
SecondHand.Y2 = (X0 - SecondHand.X1) * Sin(SecondHandAngle) + (Y0 - SecondHand.Y1 - 5) * Cos(SecondHandAngle) + SecondHand.Y1
MinuteHandAngle = (Minute(Time()) * 6) * (3.14159265 / 180)
MinuteHand.X2 = (X0 - MinuteHand.X1) * Cos(MinuteHandAngle) - (Y0 - MinuteHand.Y1) * Sin(MinuteHandAngle) + MinuteHand.X1
MinuteHand.Y2 = (X0 - MinuteHand.X1) * Sin(MinuteHandAngle) + (Y0 - MinuteHand.Y1) * Cos(MinuteHandAngle) + MinuteHand.Y1
HourHandAngle = (Hour(Time()) * 30 + Minute(Time()) * 0.5) * (3.14159265 / 180)
HourHand.X2 = (X0 - HourHand.X1) * Cos(HourHandAngle) - (Y0 - HourHand.Y1 + 15) * Sin(HourHandAngle) + HourHand.X1
HourHand.Y2 = (X0 - HourHand.X1) * Sin(HourHandAngle) + (Y0 - HourHand.Y1 + 15) * Cos(HourHandAngle) + HourHand.Y1
End Sub
