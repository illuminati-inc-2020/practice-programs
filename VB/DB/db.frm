VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form lms_form 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Library Management System"
   ClientHeight    =   4575
   ClientLeft      =   45
   ClientTop       =   375
   ClientWidth     =   8700
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4575
   ScaleWidth      =   8700
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox tb_Residence 
      Height          =   735
      Left            =   1200
      TabIndex        =   25
      Top             =   2760
      Width           =   5295
   End
   Begin VB.CommandButton remove_picture 
      Caption         =   "Remove"
      Height          =   375
      Left            =   7680
      TabIndex        =   24
      Top             =   2040
      Width           =   855
   End
   Begin VB.CommandButton change_picture 
      Caption         =   "Change"
      Height          =   375
      Left            =   6600
      TabIndex        =   23
      Top             =   2040
      Width           =   855
   End
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   3240
      Top             =   5040
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.PictureBox PictureBox 
      Height          =   1695
      Left            =   6600
      ScaleHeight     =   1635
      ScaleWidth      =   1875
      TabIndex        =   22
      Top             =   240
      Width           =   1935
   End
   Begin VB.CommandButton edit 
      Caption         =   "Edit"
      Height          =   375
      Left            =   3840
      TabIndex        =   21
      Top             =   4080
      Width           =   1215
   End
   Begin VB.CommandButton delete 
      Caption         =   "Delete"
      Height          =   375
      Left            =   5160
      TabIndex        =   20
      Top             =   4080
      Width           =   1215
   End
   Begin VB.CommandButton insert 
      Caption         =   "Insert"
      Height          =   375
      Left            =   2520
      TabIndex        =   17
      Top             =   4080
      Width           =   1215
   End
   Begin VB.CommandButton btn_clear 
      Caption         =   "New"
      Height          =   375
      Left            =   1200
      TabIndex        =   19
      Top             =   4080
      Width           =   1215
   End
   Begin VB.ListBox List 
      Height          =   1815
      ItemData        =   "db.frx":0000
      Left            =   6600
      List            =   "db.frx":0002
      Sorted          =   -1  'True
      TabIndex        =   18
      ToolTipText     =   "Member No."
      Top             =   2520
      Width           =   1935
   End
   Begin VB.Data DB 
      Caption         =   "Data1"
      Connect         =   "Access"
      DatabaseName    =   "D:\My Codes\VB\DB\db.mdb"
      DefaultCursorType=   0  'DefaultCursor
      DefaultType     =   2  'UseODBC
      Exclusive       =   0   'False
      Height          =   465
      Left            =   720
      Options         =   0
      ReadOnly        =   0   'False
      RecordsetType   =   1  'Dynaset
      RecordSource    =   "Student"
      Top             =   5280
      Visible         =   0   'False
      Width           =   2100
   End
   Begin VB.ComboBox cb_BloodGroup 
      Height          =   315
      ItemData        =   "db.frx":0004
      Left            =   1200
      List            =   "db.frx":0020
      TabIndex        =   16
      Text            =   "--select--"
      Top             =   2400
      Width           =   5300
   End
   Begin VB.TextBox tb_TelNo 
      Height          =   285
      Left            =   1200
      TabIndex        =   15
      Top             =   3600
      Width           =   5300
   End
   Begin VB.TextBox tb_DOB 
      Height          =   285
      Left            =   1200
      TabIndex        =   11
      Top             =   2040
      Width           =   5300
   End
   Begin VB.TextBox tb_Validity 
      Height          =   285
      Left            =   1200
      TabIndex        =   9
      Top             =   1680
      Width           =   5300
   End
   Begin VB.TextBox tb_Department 
      Height          =   285
      Left            =   1200
      TabIndex        =   7
      Top             =   1320
      Width           =   5300
   End
   Begin VB.TextBox tb_Course 
      Height          =   285
      Left            =   1200
      TabIndex        =   5
      Top             =   960
      Width           =   5300
   End
   Begin VB.TextBox tb_MemberNo 
      Height          =   285
      Left            =   1200
      TabIndex        =   3
      Top             =   600
      Width           =   5300
   End
   Begin VB.TextBox tb_Name 
      Height          =   285
      Left            =   1200
      TabIndex        =   1
      Top             =   240
      Width           =   5300
   End
   Begin VB.Label Label9 
      Alignment       =   1  'Right Justify
      Caption         =   "Tel No."
      Height          =   255
      Left            =   100
      TabIndex        =   14
      Top             =   3600
      Width           =   1000
   End
   Begin VB.Label Label8 
      Alignment       =   1  'Right Justify
      Caption         =   "Residence"
      Height          =   255
      Left            =   100
      TabIndex        =   13
      Top             =   3000
      Width           =   1000
   End
   Begin VB.Label Label7 
      Alignment       =   1  'Right Justify
      Caption         =   "Blood Group"
      Height          =   255
      Left            =   100
      TabIndex        =   12
      Top             =   2400
      Width           =   1000
   End
   Begin VB.Label Label6 
      Alignment       =   1  'Right Justify
      Caption         =   "DOB"
      Height          =   255
      Left            =   100
      TabIndex        =   10
      Top             =   2040
      Width           =   1000
   End
   Begin VB.Label Label5 
      Alignment       =   1  'Right Justify
      Caption         =   "Validity"
      Height          =   255
      Left            =   100
      TabIndex        =   8
      Top             =   1680
      Width           =   1000
   End
   Begin VB.Label Label4 
      Alignment       =   1  'Right Justify
      Caption         =   "Department"
      Height          =   255
      Left            =   100
      TabIndex        =   6
      Top             =   1320
      Width           =   1000
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Right Justify
      Caption         =   "Course"
      Height          =   255
      Left            =   100
      TabIndex        =   4
      Top             =   960
      Width           =   1000
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Caption         =   "Member No."
      Height          =   255
      Left            =   100
      TabIndex        =   2
      Top             =   600
      Width           =   1000
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "Name"
      Height          =   255
      Left            =   100
      TabIndex        =   0
      Top             =   240
      Width           =   1000
   End
End
Attribute VB_Name = "lms_form"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim index As Integer, length As Integer
Dim PicturePath As String

Private Sub btn_clear_Click()
Clear
End Sub

Private Sub change_picture_Click()
CommonDialog.InitDir = App.Path
CommonDialog.Filter = "Image File(*.jpg;*.bmp;*.gif)|*.jpg;*.jpeg;*.bmp;*.gif|All Files|*.*"
CommonDialog.ShowOpen
PicturePath = CommonDialog.FileName
PictureBox.Picture = LoadPicture(PicturePath)
End Sub

Private Sub remove_picture_Click()
PictureBox.Picture = Nothing
PicturePath = ""
End Sub

Private Sub delete_Click()
If (delete.Caption = "Delete") Then
    List.RemoveItem index
    DB.Recordset.edit
    DB.Recordset.delete
    length = length - 1
    index = 0
    edit.Enabled = False
Else
    DB.Recordset.CancelUpdate
    delete.Caption = "Delete"
    edit.Caption = "Edit"
    tb_Name.Enabled = False
    tb_Course.Enabled = False
    tb_Department.Enabled = False
    tb_DOB.Enabled = False
    tb_MemberNo.Enabled = False
    tb_Residence.Enabled = False
    tb_TelNo.Enabled = False
    tb_Validity.Enabled = False
    cb_BloodGroup.Enabled = False
    PictureBox.Enabled = True
    insert.Enabled = True
    btn_clear.Enabled = True
    change_picture.Enabled = False
    remove_picture.Enabled = False
End If
End Sub

Private Sub edit_Click()
If (edit.Caption = "Edit") Then
    DB.Recordset.edit
    edit.Caption = "Update"
    delete.Caption = "Cancel"
    tb_Name.Enabled = True
    tb_Course.Enabled = True
    tb_Department.Enabled = True
    tb_DOB.Enabled = True
    tb_MemberNo.Enabled = True
    tb_Residence.Enabled = True
    tb_TelNo.Enabled = True
    tb_Validity.Enabled = True
    cb_BloodGroup.Enabled = True
    PictureBox.Enabled = True
    insert.Enabled = False
    btn_clear.Enabled = False
    change_picture.Enabled = True
    remove_picture.Enabled = True
Else
    UpdateTable
    DB.Recordset.Update
    edit.Caption = "Edit"
    delete.Caption = "Delete"
    tb_Name.Enabled = False
    tb_Course.Enabled = False
    tb_Department.Enabled = False
    tb_DOB.Enabled = False
    tb_MemberNo.Enabled = False
    tb_Residence.Enabled = False
    tb_TelNo.Enabled = False
    tb_Validity.Enabled = False
    cb_BloodGroup.Enabled = False
    PictureBox.Enabled = True
    insert.Enabled = True
    btn_clear.Enabled = True
    change_picture.Enabled = False
    remove_picture.Enabled = False
End If
End Sub

Private Sub Form_Activate()
Clear
DB.Recordset.MoveFirst
length = 0
While Not DB.Recordset.EOF
    List.AddItem (DB.Recordset.Fields("Member No"))
    DB.Recordset.MoveNext
    length = length + 1
Wend
DB.Recordset.MoveFirst
index = 0
edit.Enabled = False
tb_Name.SetFocus
End Sub

Private Sub insert_Click()
DB.Recordset.AddNew
UpdateTable
DB.Recordset.Update
List.AddItem (tb_MemberNo.Text)
length = length + 1
Clear
edit.Enabled = False
End Sub

Public Sub UpdateTable()
On Error GoTo DoNothing
DB.Recordset.Fields("Name") = tb_Name.Text
DB.Recordset.Fields("Member No") = tb_MemberNo.Text
DB.Recordset.Fields("Course") = tb_Course.Text
DB.Recordset.Fields("DepartMent") = tb_Department.Text
DB.Recordset.Fields("Validity") = CDate(tb_Validity.Text)
DB.Recordset.Fields("DOB") = CDate(tb_DOB.Text)
DB.Recordset.Fields("Blood Group") = cb_BloodGroup.Text
DB.Recordset.Fields("Residence") = tb_Residence.Text
DB.Recordset.Fields("Tel No") = tb_TelNo.Text
DB.Recordset.Fields("Picture") = PicturePath
DoNothing:
Update
End Sub

Public Sub Update()
tb_Name.Text = DB.Recordset.Fields("Name")
tb_MemberNo.Text = DB.Recordset.Fields("Member No")
tb_Course.Text = DB.Recordset.Fields("Course")
tb_Department.Text = DB.Recordset.Fields("DepartMent")
tb_Validity.Text = DB.Recordset.Fields("Validity")
tb_DOB.Text = DB.Recordset.Fields("DOB")
cb_BloodGroup.Text = DB.Recordset.Fields("Blood Group")
tb_Residence.Text = DB.Recordset.Fields("Residence")
tb_TelNo.Text = DB.Recordset.Fields("Tel No")
PictureBox.Picture = Nothing
On Error GoTo NoPicture
PicturePath = DB.Recordset.Fields("Picture")
PictureBox.Picture = LoadPicture(PicturePath)
NoPicture:
End Sub

Public Sub Clear()
tb_Name.Text = ""
tb_MemberNo.Text = "S"
tb_Course.Text = ""
tb_Department.Text = ""
tb_Validity.Text = ""
tb_DOB.Text = ""
cb_BloodGroup.Text = "--select--"
tb_Residence.Text = ""
tb_TelNo.Text = ""
List.Text = ""
PicturePath = ""
PictureBox.Picture = Nothing
tb_Name.Enabled = True
tb_Course.Enabled = True
tb_Department.Enabled = True
tb_DOB.Enabled = True
tb_MemberNo.Enabled = True
tb_Residence.Enabled = True
tb_TelNo.Enabled = True
tb_Validity.Enabled = True
cb_BloodGroup.Enabled = True
PictureBox.Enabled = True
edit.Enabled = False
insert.Enabled = True
change_picture.Enabled = True
remove_picture.Enabled = True
delete.Enabled = False
End Sub

Private Sub List_Click()
tb_Name.Enabled = False
tb_Course.Enabled = False
tb_Department.Enabled = False
tb_DOB.Enabled = False
tb_MemberNo.Enabled = False
tb_Residence.Enabled = False
tb_TelNo.Enabled = False
tb_Validity.Enabled = False
cb_BloodGroup.Enabled = False
PictureBox.Enabled = True
edit.Enabled = True
insert.Enabled = False
change_picture.Enabled = False
remove_picture.Enabled = False
edit.Caption = "Edit"
delete.Caption = "Delete"
delete.Enabled = True
DB.Recordset.MoveFirst
While Not DB.Recordset.EOF
    If DB.Recordset.Fields("Member No") = List.Text Then
        Update
        Exit Sub
    End If
    DB.Recordset.MoveNext
Wend
End Sub
