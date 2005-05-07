object LocationProfilesDialog: TLocationProfilesDialog
  Left = 343
  Top = 147
  HelpType = htKeyword
  HelpKeyword = 'ui_locationprofile'
  BorderIcons = [biSystemMenu, biMinimize, biMaximize, biHelp]
  BorderStyle = bsDialog
  Caption = 'Location profiles'
  ClientHeight = 424
  ClientWidth = 557
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poMainFormCenter
  OnShow = FormShow
  DesignSize = (
    557
    424)
  PixelsPerInch = 96
  TextHeight = 13
  object LocalDirectoryLabel: TLabel
    Left = 8
    Top = 8
    Width = 72
    Height = 13
    Caption = '&Local directory:'
    FocusControl = LocalDirectoryEdit
  end
  object RemoteDirectoryLabel: TLabel
    Left = 8
    Top = 56
    Width = 83
    Height = 13
    Caption = '&Remote directory:'
    FocusControl = RemoteDirectoryEdit
  end
  object OKBtn: TButton
    Left = 303
    Top = 390
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 5
  end
  object CancelBtn: TButton
    Left = 387
    Top = 390
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 6
  end
  object BookmarksGroup: TXPGroupBox
    Left = 8
    Top = 104
    Width = 539
    Height = 277
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 3
    DesignSize = (
      539
      277)
    object ProfilesView: TTreeView
      Left = 16
      Top = 22
      Width = 419
      Height = 239
      Anchors = [akLeft, akTop, akRight, akBottom]
      DragMode = dmAutomatic
      HideSelection = False
      Images = BookmarkImageList
      Indent = 19
      TabOrder = 0
      OnChange = ProfilesViewChange
      OnDblClick = ProfilesViewDblClick
      OnDragDrop = ProfilesViewDragDrop
      OnDragOver = ProfilesViewDragOver
      OnGetImageIndex = ProfilesViewGetImageIndex
      OnGetSelectedIndex = ProfilesViewGetSelectedIndex
      OnKeyDown = ProfilesViewKeyDown
      OnStartDrag = ProfilesViewStartDrag
      Items.Data = {
        050000001A0000000100000000000000FFFFFFFFFFFFFFFF0000000001000000
        01311B0000000000000000000000FFFFFFFFFFFFFFFF00000000000000000231
        311A0000000000000000000000FFFFFFFFFFFFFFFF000000000000000001321A
        0000000000000000000000FFFFFFFFFFFFFFFF000000000000000001331A0000
        000100000000000000FFFFFFFFFFFFFFFF000000000100000001341B00000000
        00000000000000FFFFFFFFFFFFFFFF00000000000000000234311A0000000000
        000000000000FFFFFFFFFFFFFFFF00000000000000000135}
    end
    object AddBookmarkButton: TButton
      Left = 442
      Top = 22
      Width = 83
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '&Add ...'
      TabOrder = 1
      OnClick = AddBookmarkButtonClick
    end
    object RemoveBookmarkButton: TButton
      Left = 442
      Top = 54
      Width = 83
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Remo&ve'
      TabOrder = 2
      OnClick = RemoveBookmarkButtonClick
    end
    object DownBookmarkButton: TButton
      Left = 442
      Top = 236
      Width = 83
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = '&Down'
      TabOrder = 4
      OnClick = BookmarkButtonClick
    end
    object UpBookmarkButton: TButton
      Left = 442
      Top = 204
      Width = 83
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = '&Up'
      TabOrder = 5
      OnClick = BookmarkButtonClick
    end
    object RenameButton: TButton
      Left = 442
      Top = 86
      Width = 83
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Re&name ...'
      TabOrder = 3
      OnClick = RenameButtonClick
    end
    object MoveToButton: TButton
      Left = 442
      Top = 118
      Width = 83
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '&Move to ...'
      TabOrder = 6
      OnClick = MoveToButtonClick
    end
  end
  object LocalDirectoryEdit: TIEComboBox
    Left = 8
    Top = 25
    Width = 457
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    ItemHeight = 13
    TabOrder = 0
    Text = 'LocalDirectoryEdit'
    OnChange = DirectoryEditChange
  end
  object RemoteDirectoryEdit: TIEComboBox
    Left = 8
    Top = 73
    Width = 539
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    ItemHeight = 13
    MaxLength = 1000
    TabOrder = 2
    Text = 'RemoteDirectoryEdit'
    OnChange = DirectoryEditChange
  end
  object LocalDirectoryBrowseButton: TButton
    Left = 470
    Top = 23
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'B&rowse...'
    TabOrder = 1
    OnClick = LocalDirectoryBrowseButtonClick
  end
  object SwitchButton: TButton
    Left = 8
    Top = 390
    Width = 97
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = '&Bookmarks...'
    ModalResult = 2
    TabOrder = 4
    OnClick = SwitchButtonClick
  end
  object HelpButton: TButton
    Left = 471
    Top = 390
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = '&Help'
    TabOrder = 7
    OnClick = HelpButtonClick
  end
  object BookmarkImageList: TImageList
    Left = 232
    Top = 384
    Bitmap = {
      494C010103000400040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000001821
      2100182121001821210018212100182121001821210018212100182121001821
      2100182121001821210018212100182121000000000004040400040404000404
      0400040404000404040004040400040404000404040004040400040404000404
      0400040404000404040004040400040404000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000066660099FFFF0000CC
      FF0000CCFF0000CCFF0000CCFF000099CC0000CCFF000099CC0000CCFF000099
      CC000099CC00669999000099CC00000000000000000000000000006666000066
      6600006666000066660000666600006666000066660000666600006666000066
      660000666600006666001821210018212100000000000066660099FFFF0000CC
      FF0000CCFF000099CC0000CCFF000099CC0000CCFF000099CC000099CC000099
      CC00669999000099CC0066999900040404000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000066660099FFFF0000CC
      FF0000CCFF0000CCFF0000CCFF0000CCFF00FF00000000CCFF000099CC0000CC
      FF000099CC000099CC00669999000000000000000000000000000066660099FF
      FF000099CC0000CCFF000099CC0000CCFF000099CC000099CC000099CC006699
      99000099CC00006666001821210018212100000000000066660099FFFF0000CC
      FF0000CCFF0000CCFF000099CC0000CCFF000099CC0000CCFF000099CC000099
      CC000099CC00669999000099CC00040404000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000066660099FFFF0099FF
      FF0000CCFF0000CCFF00FF00000000CCFF00FF00000000CCFF00FF0000000099
      CC0000CCFF000099CC000099CC0000000000000000000066660099FFFF0000CC
      FF0000CCFF000099CC0000CCFF000099CC0000CCFF000099CC000099CC000099
      CC0066999900182121000066660018212100000000000066660099FFFF00FFFF
      FF0000CCFF0000CCFF0000CCFF000099CC0000CCFF000099CC0000CCFF000099
      CC000099CC000099CC0066999900040404000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000066660099FFFF0000CC
      FF0099FFFF0000CCFF0000CCFF00FF000000FF000000FF00000000CCFF0000CC
      FF000099CC0000CCFF000099CC0000000000000000000066660099FFFF00FFFF
      FF0000CCFF0000CCFF0000CCFF0000CCFF000099CC0000CCFF000099CC000099
      CC000099CC00182121000066660018212100000000000066660099FFFF0000CC
      FF00FFFFFF0000CCFF0000CCFF0000CCFF0000CCFF0000CCFF000099CC0000CC
      FF000099CC000099CC000099CC00040404000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000066660099FFFF00F8F8
      F80000CCFF00FF000000FF000000FF00000000FFFF00FF000000FF000000FF00
      000000CCFF000099CC000099CC00000000000066660099FFFF00FFFFFF0000CC
      FF00FFFFFF0000CCFF000099CC0000CCFF0000CCFF000099CC0000CCFF000099
      CC001821210000CCFF0000CCFF0018212100000000000066660099FFFF00FFFF
      FF0000CCFF00FFFFFF0000CCFF0000CCFF0000CCFF0000CCFF0000CCFF000099
      CC0000CCFF000099CC000099CC00040404000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000066660099FFFF0000CC
      FF00F8F8F80000CCFF0000CCFF00FF000000FF000000FF00000000CCFF0000CC
      FF000099CC0000CCFF000099CC00000000000066660099FFFF0000CCFF00FFFF
      FF0000CCFF00FFFFFF0000CCFF0000CCFF000099CC0000CCFF000099CC0000CC
      FF001821210000CCFF0000CCFF0018212100000000000066660099FFFF0000CC
      FF00FFFFFF0000CCFF00FFFFFF0000CCFF00FFFFFF0000CCFF0000CCFF0000CC
      FF0000CCFF0000CCFF000099CC00040404000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000066660099FFFF00F8F8
      F80000CCFF00F8F8F800FF00000000CCFF00FF00000000CCFF00FF00000000CC
      FF0000CCFF000099CC000099CC00000000000066660000666600006666000066
      6600006666000066660000666600006666000066660000666600006666000066
      660000CCFF0000CCFF0000CCFF0018212100000000000066660099FFFF00FFFF
      FF0000CCFF00FFFFFF0000CCFF00FFFFFF0000CCFF00FFFFFF0000CCFF0000CC
      FF0000CCFF000099CC0000CCFF00040404000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000066660099FFFF0000CC
      FF00F8F8F80000CCFF00F8F8F80000CCFF00FF00000000CCFF0000CCFF0000CC
      FF0000CCFF0000CCFF000099CC0000000000000000000066660099FFFF0000CC
      FF00FFFFFF0000CCFF0000CCFF0000CCFF0000CCFF0000CCFF0000CCFF0000CC
      FF0000CCFF0000CCFF0000CCFF0018212100000000000066660099FFFF0000CC
      FF00FFFFFF0000CCFF00FFFFFF0000CCFF00FFFFFF0000CCFF00FFFFFF0000CC
      FF0000CCFF0000CCFF000099CC00040404000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000066660099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF0000000000000000000066660099FFFF00FFFF
      FF0000CCFF00FFFFFF0000CCFF0000CCFF0000CCFF0000CCFF0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF0018212100000000000066660099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00040404000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000666600006666000066
      6600006666000066660000666600006666000066660000666600006666000066
      660000666600006666000066660000000000000000000066660099FFFF0000CC
      FF00FFFFFF0000CCFF00FFFFFF0000CCFF0099FFFF0000666600006666000066
      6600006666000066660000666600000000000000000000666600006666000066
      6600006666000066660000666600006666000066660000666600006666000066
      6600006666000066660000666600040404000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000066660099FF
      FF0099FFFF0099FFFF0099FFFF0099FFFF000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000066660099FF
      FF0099FFFF0099FFFF0099FFFF0099FFFF000066660000000000000000000000
      00000000000000000000000000000000000000000000000000000066660099FF
      FF0099FFFF0099CCCC0099CCCC00009999000404040000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000066
      6600006666000066660000666600006666000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000066
      6600006666000066660000666600006666000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000066
      6600006666000066660000666600006666000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFFFFFF0000FFFFFFFFFFFF0000
      8000E000800000008000C000800000008000C000800000008000800080000000
      8000800080000000800000008000000080000000800000008000000080000000
      800080008000000080008000800000008000800180000000C07FC07FC07F0000
      E0FFE0FFE0FF0000FFFFFFFFFFFF000000000000000000000000000000000000
      000000000000}
  end
end
