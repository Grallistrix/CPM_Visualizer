object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'CPM'
  ClientHeight = 613
  ClientWidth = 1117
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Activity_Label: TLabel
    Left = 17
    Top = 14
    Width = 40
    Height = 15
    Caption = 'Activity'
  end
  object Predecesor_LAbel: TLabel
    Left = 144
    Top = 14
    Width = 58
    Height = 15
    Caption = 'Predecesor'
  end
  object Time_Label: TLabel
    Left = 271
    Top = 14
    Width = 81
    Height = 15
    Caption = 'Estimated Time'
  end
  object FileOperation_Label: TLabel
    Left = 17
    Top = 459
    Width = 54
    Height = 15
    Caption = 'FileAccess'
  end
  object Label1: TLabel
    Left = 217
    Top = 460
    Width = 77
    Height = 15
    Caption = 'SaveFile Name'
  end
  object ActivitiesList: TListBox
    Left = 17
    Top = 64
    Width = 375
    Height = 321
    ItemHeight = 15
    TabOrder = 0
  end
  object Predecesor_EditBox: TEdit
    Left = 144
    Top = 35
    Width = 121
    Height = 23
    TabOrder = 1
    Text = 'Predecesor'
  end
  object Time_EditBox: TEdit
    Left = 271
    Top = 35
    Width = 121
    Height = 23
    TabOrder = 2
    Text = 'Time'
  end
  object Activity_EditBox: TEdit
    Left = 17
    Top = 35
    Width = 121
    Height = 23
    TabOrder = 3
    Text = 'Activity'
  end
  object Add_Button: TButton
    Left = 17
    Top = 400
    Width = 75
    Height = 25
    Caption = 'ADD'
    TabOrder = 4
  end
  object Edit_Button: TButton
    Left = 121
    Top = 400
    Width = 75
    Height = 25
    Caption = 'EDIT'
    TabOrder = 5
  end
  object Delete_Button: TButton
    Left = 217
    Top = 400
    Width = 75
    Height = 25
    Caption = 'DELETE'
    TabOrder = 6
  end
  object Calculate_Button: TButton
    Left = 317
    Top = 400
    Width = 75
    Height = 25
    Caption = 'CALC'
    TabOrder = 7
  end
  object LoadFromFile_Button: TButton
    Left = 17
    Top = 480
    Width = 75
    Height = 25
    Caption = 'LOAD'
    TabOrder = 8
  end
  object CalcFile_Button: TButton
    Left = 121
    Top = 480
    Width = 75
    Height = 25
    Caption = 'CALC to FILE'
    TabOrder = 9
  end
  object FileName_EditBox: TEdit
    Left = 217
    Top = 481
    Width = 127
    Height = 25
    TabOrder = 10
    Text = 'FileName'
  end
  object Outline1: TOutline
    Left = 424
    Top = 8
    Width = 685
    Height = 601
    ItemHeight = 14
    TabOrder = 11
    ItemSeparator = '\'
  end
end
