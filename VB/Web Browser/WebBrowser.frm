VERSION 5.00
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "ieframe.dll"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form WebBrowserForm 
   Caption         =   "Web Browser"
   ClientHeight    =   8310
   ClientLeft      =   540
   ClientTop       =   960
   ClientWidth     =   15570
   LinkTopic       =   "Form1"
   ScaleHeight     =   8310
   ScaleWidth      =   15570
   StartUpPosition =   2  'CenterScreen
   WindowState     =   2  'Maximized
   Begin VB.CommandButton btnSearch 
      Height          =   375
      Left            =   15120
      Picture         =   "WebBrowser.frx":0000
      Style           =   1  'Graphical
      TabIndex        =   17
      Top             =   140
      Width           =   375
   End
   Begin MSComctlLib.ImageList BookmarkImage 
      Left            =   14160
      Top             =   1080
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   30
      ImageHeight     =   30
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   8
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "WebBrowser.frx":0507
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "WebBrowser.frx":0B45
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "WebBrowser.frx":2BA0
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "WebBrowser.frx":4CF8
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "WebBrowser.frx":52AB
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "WebBrowser.frx":5846
            Key             =   ""
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "WebBrowser.frx":5D43
            Key             =   ""
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "WebBrowser.frx":6216
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.Toolbar BookmarkBar 
      Align           =   3  'Align Left
      Height          =   7155
      Left            =   0
      TabIndex        =   15
      Top             =   660
      Width           =   660
      _ExtentX        =   1164
      _ExtentY        =   12621
      ButtonWidth     =   979
      ButtonHeight    =   953
      Appearance      =   1
      ImageList       =   "BookmarkImage"
      DisabledImageList=   "BookmarkImage"
      HotImageList    =   "BookmarkImage"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   8
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Description     =   "Google"
            Object.ToolTipText     =   "http://www.google.co.in"
            ImageIndex      =   1
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Description     =   "Gmail"
            Object.ToolTipText     =   "https://mail.google.com/mail/?tab=wm"
            ImageIndex      =   2
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Description     =   "Youtube"
            Object.ToolTipText     =   "http://www.youtube.com/?hl=en&tab=w1&gl=IN"
            ImageIndex      =   3
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Description     =   "Facebook"
            Object.ToolTipText     =   "https://www.facebook.com/index.php?stype=lo&lh=Ac9Yl2lsS2T1iFtX"
            ImageIndex      =   4
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Description     =   "LinkedIn"
            Object.ToolTipText     =   "http://in.linkedin.com"
            ImageIndex      =   5
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Description     =   "Twitter"
            Object.ToolTipText     =   "https://twitter.com"
            ImageIndex      =   6
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Description     =   "Wikipedia"
            Object.ToolTipText     =   "http://www.wikipedia.org"
            ImageIndex      =   7
         EndProperty
         BeginProperty Button8 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.ToolTipText     =   "http://in.yahoo.com/?p=us"
            ImageIndex      =   8
         EndProperty
      EndProperty
   End
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   14760
      Top             =   1080
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin SHDocVwCtl.WebBrowser Page 
      Height          =   6855
      Index           =   4
      Left            =   720
      TabIndex        =   13
      Top             =   960
      Visible         =   0   'False
      Width           =   14895
      ExtentX         =   26273
      ExtentY         =   12091
      ViewMode        =   0
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   0
      RegisterAsDropTarget=   1
      AutoArrange     =   0   'False
      NoClientEdge    =   0   'False
      AlignLeft       =   0   'False
      NoWebView       =   0   'False
      HideFileNames   =   0   'False
      SingleClick     =   0   'False
      SingleSelection =   0   'False
      NoFolders       =   0   'False
      Transparent     =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   "http:///"
   End
   Begin SHDocVwCtl.WebBrowser Page 
      Height          =   6855
      Index           =   3
      Left            =   720
      TabIndex        =   12
      Top             =   960
      Visible         =   0   'False
      Width           =   14895
      ExtentX         =   26273
      ExtentY         =   12091
      ViewMode        =   0
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   0
      RegisterAsDropTarget=   1
      AutoArrange     =   0   'False
      NoClientEdge    =   0   'False
      AlignLeft       =   0   'False
      NoWebView       =   0   'False
      HideFileNames   =   0   'False
      SingleClick     =   0   'False
      SingleSelection =   0   'False
      NoFolders       =   0   'False
      Transparent     =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   "http:///"
   End
   Begin SHDocVwCtl.WebBrowser Page 
      Height          =   6855
      Index           =   2
      Left            =   720
      TabIndex        =   11
      Top             =   960
      Visible         =   0   'False
      Width           =   14895
      ExtentX         =   26273
      ExtentY         =   12091
      ViewMode        =   0
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   0
      RegisterAsDropTarget=   1
      AutoArrange     =   0   'False
      NoClientEdge    =   0   'False
      AlignLeft       =   0   'False
      NoWebView       =   0   'False
      HideFileNames   =   0   'False
      SingleClick     =   0   'False
      SingleSelection =   0   'False
      NoFolders       =   0   'False
      Transparent     =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   "http:///"
   End
   Begin SHDocVwCtl.WebBrowser Page 
      Height          =   6855
      Index           =   1
      Left            =   720
      TabIndex        =   10
      Top             =   960
      Visible         =   0   'False
      Width           =   14895
      ExtentX         =   26273
      ExtentY         =   12091
      ViewMode        =   0
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   0
      RegisterAsDropTarget=   1
      AutoArrange     =   0   'False
      NoClientEdge    =   0   'False
      AlignLeft       =   0   'False
      NoWebView       =   0   'False
      HideFileNames   =   0   'False
      SingleClick     =   0   'False
      SingleSelection =   0   'False
      NoFolders       =   0   'False
      Transparent     =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   "http:///"
   End
   Begin MSComctlLib.ProgressBar ProgressBar 
      Height          =   255
      Left            =   12480
      TabIndex        =   9
      Top             =   7920
      Width           =   2655
      _ExtentX        =   4683
      _ExtentY        =   450
      _Version        =   393216
      Appearance      =   1
   End
   Begin SHDocVwCtl.WebBrowser Page 
      Height          =   6855
      Index           =   0
      Left            =   720
      TabIndex        =   8
      Top             =   960
      Width           =   14895
      ExtentX         =   26273
      ExtentY         =   12091
      ViewMode        =   0
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   0
      RegisterAsDropTarget=   1
      AutoArrange     =   0   'False
      NoClientEdge    =   0   'False
      AlignLeft       =   0   'False
      NoWebView       =   0   'False
      HideFileNames   =   0   'False
      SingleClick     =   0   'False
      SingleSelection =   0   'False
      NoFolders       =   0   'False
      Transparent     =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   "http:///"
   End
   Begin MSComctlLib.StatusBar StatusBar 
      Align           =   2  'Align Bottom
      Height          =   495
      Left            =   0
      TabIndex        =   7
      Top             =   7815
      Width           =   15570
      _ExtentX        =   27464
      _ExtentY        =   873
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.Toolbar Toolbar 
      Align           =   1  'Align Top
      Height          =   660
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   15570
      _ExtentX        =   27464
      _ExtentY        =   1164
      ButtonWidth     =   609
      ButtonHeight    =   1005
      Appearance      =   1
      _Version        =   393216
      Begin VB.TextBox txtSearch 
         BeginProperty Font 
            Name            =   "Calibri"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Left            =   12840
         TabIndex        =   16
         Top             =   140
         Width           =   2295
      End
      Begin VB.CommandButton CommandGo 
         Height          =   375
         Left            =   12360
         Picture         =   "WebBrowser.frx":6872
         Style           =   1  'Graphical
         TabIndex        =   14
         Top             =   140
         Width           =   375
      End
      Begin VB.ComboBox TextAddress 
         Height          =   315
         ItemData        =   "WebBrowser.frx":6C56
         Left            =   2640
         List            =   "WebBrowser.frx":6C58
         Sorted          =   -1  'True
         TabIndex        =   6
         Top             =   140
         Width           =   9735
      End
      Begin VB.CommandButton CommandHome 
         Height          =   615
         Left            =   1920
         Picture         =   "WebBrowser.frx":6C5A
         Style           =   1  'Graphical
         TabIndex        =   5
         Top             =   0
         Width           =   615
      End
      Begin VB.CommandButton CommandRefresh 
         Height          =   615
         Left            =   1320
         Picture         =   "WebBrowser.frx":71EF
         Style           =   1  'Graphical
         TabIndex        =   4
         Top             =   0
         Width           =   615
      End
      Begin VB.CommandButton CommandForward 
         Height          =   615
         Left            =   720
         Picture         =   "WebBrowser.frx":7798
         Style           =   1  'Graphical
         TabIndex        =   3
         Top             =   0
         Width           =   615
      End
      Begin VB.CommandButton CommandBack 
         Height          =   615
         Left            =   120
         Picture         =   "WebBrowser.frx":7D93
         Style           =   1  'Graphical
         TabIndex        =   2
         Top             =   0
         Width           =   615
      End
   End
   Begin MSComctlLib.TabStrip TabStrip 
      Height          =   7215
      Left            =   720
      TabIndex        =   0
      Top             =   600
      Width           =   14895
      _ExtentX        =   26273
      _ExtentY        =   12726
      MultiRow        =   -1  'True
      TabMinWidth     =   1058
      _Version        =   393216
      BeginProperty Tabs {1EFB6598-857C-11D1-B16A-00C0F0283628} 
         NumTabs         =   2
         BeginProperty Tab1 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab2 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "+New Tab"
            ImageVarType    =   2
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Calibri"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "File"
      Begin VB.Menu mnuFile_Open 
         Caption         =   "Open"
      End
      Begin VB.Menu mnuFile_Save 
         Caption         =   "Save Page As..."
         Shortcut        =   {F2}
      End
      Begin VB.Menu mnuFile_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile_Exit 
         Caption         =   "Exit"
      End
   End
   Begin VB.Menu mnuNavigate 
      Caption         =   "Navigate"
      Begin VB.Menu mnuNavigate_Back 
         Caption         =   "Back"
      End
      Begin VB.Menu mnuNavigate_Forward 
         Caption         =   "Forward"
      End
      Begin VB.Menu mnuNavigate_Home 
         Caption         =   "Home"
         Shortcut        =   {F12}
      End
      Begin VB.Menu mnuNavigate_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuNavigate_Refresh 
         Caption         =   "Refresh"
         Shortcut        =   {F5}
      End
      Begin VB.Menu mnuNavigate_Stop 
         Caption         =   "Stop"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "Help"
      Begin VB.Menu mnuHelp_About 
         Caption         =   "About"
         Shortcut        =   {F1}
      End
   End
End
Attribute VB_Name = "WebBrowserForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim W As Integer, H As Integer

Private Sub UpdateHistory()
Dim i As Integer, old As Boolean
old = False
For i = 0 To TextAddress.ListCount - 1
    If TextAddress.List(i) = Page(TabStrip.SelectedItem.Index - 1).LocationURL Then
        old = True
        Exit For
    End If
Next
If old = False And Page(TabStrip.SelectedItem.Index - 1).LocationURL <> "" Then TextAddress.AddItem Page(TabStrip.SelectedItem.Index - 1).LocationURL
End Sub

Private Sub CommandGo_Click()
Page(TabStrip.SelectedItem.Index - 1).Navigate TextAddress.Text
End Sub

Private Sub btnSearch_Click()
Page(TabStrip.SelectedItem.Index - 1).Navigate "https://www.google.co.in/search?hl=en&safe=off&output=search&sclient=psy-ab&q=" + Strings.Replace(txtSearch.Text, " ", "+") + "&btnK="
End Sub

Private Sub txtSearch_Change()
Page(TabStrip.SelectedItem.Index - 1).Navigate "https://www.google.co.in/search?hl=en&safe=off&output=search&sclient=psy-ab&q=" + Strings.Replace(txtSearch.Text, " ", "+") + "&btnK="
End Sub

Private Sub Form_Load()
Page(0).GoHome
W = Me.Width
H = Me.Height
End Sub

Private Sub Form_Resize()
If Me.WindowState = 1 Then Exit Sub
On Error GoTo DumpError
If Me.Width < 10000 Then Me.Width = 10000
If Me.Height < 7000 Then Me.Height = 7000
Dim i As Integer
TabStrip.Width = TabStrip.Width + (Me.Width - W)
TabStrip.Height = TabStrip.Height + (Me.Height - H)
For i = 0 To Page.Count - 1
    Page(i).Width = Page(i).Width + (Me.Width - W)
    Page(i).Height = Page(i).Height + (Me.Height - H)
Next
ProgressBar.Left = ProgressBar.Left + (Me.Width - W)
ProgressBar.Top = ProgressBar.Top + (Me.Height - H)
CommandGo.Left = CommandGo.Left + (Me.Width - W)
txtSearch.Left = txtSearch.Left + (Me.Width - W)
btnSearch.Left = btnSearch.Left + (Me.Width - W)
TextAddress.Width = TextAddress.Width + (Me.Width - W)
W = Me.Width
H = Me.Height
DumpError:
End Sub

Private Sub mnuFile_Open_Click()
CommonDialog.FileName = ""
CommonDialog.Filter = "HTML (*.html;*.htm)|*.html;*htm|MHT (*.mht)|*.mht"
CommonDialog.ShowOpen
If CommonDialog.FileName <> "" Then Page(TabStrip.SelectedItem.Index - 1).Navigate CommonDialog.FileName
End Sub

Private Sub mnuFile_Save_Click()
On Error GoTo DoNothing
Page(TabStrip.SelectedItem.Index - 1).ExecWB OLECMDID_SAVEAS, OLECMDEXECOPT_PROMPTUSER, CommonDialog.FileName
DoNothing:
End Sub

Private Sub TabStrip_Click()
HidePages
If TabStrip.SelectedItem.Index = TabStrip.Tabs.Count Then
    Page(TabStrip.SelectedItem.Index - 1).Visible = True
    Page(TabStrip.SelectedItem.Index - 1).Navigate "about:blank"
    If TabStrip.Tabs.Count < Page.Count Then TabStrip.Tabs.Add (TabStrip.Tabs.Count + 1), "", "+New Tab"
    
ElseIf TabStrip.SelectedItem.Index < TabStrip.Tabs.Count Then
    Page(TabStrip.SelectedItem.Index - 1).Visible = True
End If
TabStrip.SelectedItem.Caption = Page(TabStrip.SelectedItem.Index - 1).LocationName
Me.Caption = TabStrip.SelectedItem.Caption
TextAddress.Text = Page(TabStrip.SelectedItem.Index - 1).LocationURL
End Sub

Private Sub TextAddress_KeyPress(KeyAscii As Integer)
Select Case KeyAscii
Case Asc(vbCrLf):
    Page(TabStrip.SelectedItem.Index - 1).Navigate TextAddress.Text
End Select
End Sub

Private Sub Page_StatusTextChange(Index As Integer, ByVal Text As String)
TextAddress.Text = Page(Index).LocationURL
TabStrip.SelectedItem.Caption = Page(Index).LocationName
Me.Caption = Page(Index).LocationName
TabStrip.SelectedItem.Tag = Page(Index).LocationURL
UpdateHistory
End Sub

Private Sub Page_ProgressChange(Index As Integer, ByVal Progress As Long, ByVal ProgressMax As Long)
If ProgressMax > 0 And Progress > 0 And Progress < ProgressMax Then
    CommandRefresh.Picture = LoadPicture(App.Path + "\data\stop.jpg")
    CommandRefresh.ToolTipText = "Stop"
    ProgressBar.Max = ProgressMax
    ProgressBar.Value = Progress
Else
    CommandRefresh.Picture = LoadPicture(App.Path + "\data\refresh.jpg")
    CommandRefresh.ToolTipText = "Stop"
    ProgressBar.Value = 0
End If
End Sub

Private Sub CommandBack_Click()
On Error GoTo DoNothing
Page(TabStrip.SelectedItem.Index - 1).GoBack
DoNothing:
End Sub

Private Sub CommandForward_Click()
On Error GoTo DoNothing
Page(TabStrip.SelectedItem.Index - 1).GoForward
DoNothing:
End Sub

Private Sub CommandHome_Click()
Page(TabStrip.SelectedItem.Index - 1).GoHome
End Sub

Private Sub CommandRefresh_Click()
If CommandRefresh.ToolTipText = "Stop" Then
    Page(TabStrip.SelectedItem.Index - 1).Stop
Else
    Page(TabStrip.SelectedItem.Index - 1).Refresh
End If
End Sub

Private Sub HidePages()
Dim i As Integer
For i = 0 To Page.Count - 1
    Page(i).Visible = False
Next
End Sub

Private Sub mnuFile_Exit_Click()
End
End Sub

Private Sub mnuHelp_About_Click()
MsgBox "Web Browser" + vbCrLf + "       -by Rakesh Malik" + vbCrLf + "       15/10/2012", vbOKOnly, "About"
End Sub

Private Sub mnuNavigate_Back_Click()
CommandBack_Click
End Sub

Private Sub mnuNavigate_Forward_Click()
CommandForward_Click
End Sub

Private Sub mnuNavigate_Home_Click()
CommandHome_Click
End Sub

Private Sub mnuNavigate_Refresh_Click()
CommandRefresh_Click
End Sub

Private Sub mnuNavigate_Stop_Click()
CommandRefresh_Click
End Sub

Private Sub BookmarkBar_ButtonClick(ByVal Button As MSComctlLib.Button)
Page(TabStrip.SelectedItem.Index - 1).Navigate Button.ToolTipText
End Sub
