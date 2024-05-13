object Form1: TForm1
  Left = 225
  Top = 187
  Caption = 'CPM'
  ClientHeight = 624
  ClientWidth = 1588
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
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
  object Label2: TLabel
    Left = 218
    Top = 460
    Width = 29
    Height = 15
    Caption = 'CPM:'
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
    OnClick = Add_ButtonClick
  end
  object Delete_Button: TButton
    Left = 119
    Top = 400
    Width = 75
    Height = 25
    Caption = 'DELETE'
    TabOrder = 5
    OnClick = Delete_ButtonClick
  end
  object Calculate_Button: TButton
    Left = 317
    Top = 400
    Width = 75
    Height = 25
    Caption = 'CALC'
    TabOrder = 6
    OnClick = Calculate_ButtonClick
  end
  object CalcFile_Button: TButton
    Left = 218
    Top = 400
    Width = 75
    Height = 25
    Caption = 'CALC to FILE'
    TabOrder = 7
    OnClick = CalcFile_ButtonClick
  end
  object Outline1: TOutline
    Left = 424
    Top = 8
    Width = 841
    Height = 609
    ItemHeight = 14
    TabOrder = 8
    ItemSeparator = '\'
  end
  object Memo1: TMemo
    Left = 217
    Top = 184
    Width = 175
    Height = 201
    Color = clInactiveCaption
    Lines.Strings = (
      'Memo1')
    TabOrder = 10
  end
  object Button1: TButton
    Left = 317
    Top = 360
    Width = 75
    Height = 25
    Caption = 'INFO'
    TabOrder = 9
    OnClick = Button_Info_click
  end
  object CPM_Edit: TEdit
    Left = 217
    Top = 481
    Width = 121
    Height = 23
    ImeName = 'Polish (Programmers)'
    TabOrder = 11
  end
end
