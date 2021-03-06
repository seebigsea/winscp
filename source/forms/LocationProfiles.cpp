//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <CoreMain.h>
#include <Configuration.h>
#include <RemoteFiles.h>
#include <VCLCommon.h>
#include <TextsWin.h>
#include <HelpWin.h>
#include <Common.h>

#include "LocationProfiles.h"
#include "WinConfiguration.h"
#include "Custom.h"
//---------------------------------------------------------------------
#pragma link "IEComboBox"
#pragma link "PngImageList"
#ifndef NO_RESOURCES
#pragma resource "*.dfm"
#endif
//---------------------------------------------------------------------
bool __fastcall LocationProfilesDialog(TOpenDirectoryMode Mode,
  TOperationSide Side, UnicodeString & LocalDirectory, UnicodeString & RemoteDirectory,
  TStrings * LocalDirectories, TStrings * RemoteDirectories, TTerminal * Terminal)
{
  bool Result;
  TLocationProfilesDialog * Dialog = new TLocationProfilesDialog(Application);
  try
  {
    Dialog->LocalDirectory = LocalDirectory;
    Dialog->RemoteDirectory = RemoteDirectory;
    Dialog->OperationSide = Side;
    Dialog->Terminal = Terminal;
    Dialog->RemoteDirectories = RemoteDirectories;
    Dialog->LocalDirectories = LocalDirectories;
    Dialog->Mode = Mode;

    Result = Dialog->Execute();
    if (Result)
    {
      LocalDirectory = Dialog->LocalDirectory;
      RemoteDirectory = Dialog->RemoteDirectory;
    }
  }
  __finally
  {
    delete Dialog;
  }
  return Result;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall BookmarkNameValidateName(const UnicodeString Name)
{
  if (Name.IsEmpty() || IsNumber(Name))
  {
    throw Exception(FMTLOAD(BOOKMARK_INVALID_NAME, (Name)));
  }
}
//---------------------------------------------------------------------------
void __fastcall BookmarkFolderValidateName(const UnicodeString Name,
  bool AllowEmpty)
{
  if ((!AllowEmpty && Name.IsEmpty()) || Name.Pos(L"\\"))
  {
    throw Exception(FMTLOAD(BOOKMARK_FOLDER_INVALID_NAME, (Name)));
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TBookmarkNameDialog : public TCustomDialog
{
public:
  __fastcall TBookmarkNameDialog(TStrings * PeerBookmarks, bool AllowShared);

  bool __fastcall Execute(UnicodeString & Name, bool & Shared);

protected:
  virtual void __fastcall DoValidate();

private:
  TComboBox * NameCombo;
  TCheckBox * SharedCheck;
};
//---------------------------------------------------------------------
__fastcall TBookmarkNameDialog::TBookmarkNameDialog(TStrings * PeerBookmarks,
    bool AllowShared) :
  TCustomDialog(HELP_LOCATION_PROFILE_ADD)
{
  Caption = LoadStr(ADD_BOOKMARK_CAPTION);

  NameCombo = new TComboBox(this);
  NameCombo->AutoComplete = false;
  AddComboBox(NameCombo, CreateLabel(LoadStr(ADD_BOOKMARK_PROMPT)));
  NameCombo->Items = PeerBookmarks;

  if (AllowShared)
  {
    SharedCheck = new TCheckBox(this);
    SharedCheck->Caption = LoadStr(ADD_BOOKMARK_SHARED);
    AddButtonControl(SharedCheck);
  }
  else
  {
    SharedCheck = NULL;
  }
}
//---------------------------------------------------------------------
void __fastcall TBookmarkNameDialog::DoValidate()
{
  if (NameCombo->Text.IsEmpty() || IsNumber(NameCombo->Text))
  {
    throw Exception(FMTLOAD(BOOKMARK_INVALID_NAME, (NameCombo->Text)));
  }
  TCustomDialog::DoValidate();
}
//---------------------------------------------------------------------
bool __fastcall TBookmarkNameDialog::Execute(UnicodeString & Name, bool & Shared)
{
  NameCombo->Text = Name;
  if (SharedCheck != NULL)
  {
    SharedCheck->Checked = Shared;
  }
  bool Result = TCustomDialog::Execute();
  if (Result)
  {
    Name = NameCombo->Text;
    if (SharedCheck != NULL)
    {
      Shared = SharedCheck->Checked;
    }
  }
  return Result;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TBookmarkFolderDialog : public TCustomDialog
{
public:
  __fastcall TBookmarkFolderDialog(TStrings * Folders);

  bool __fastcall Execute(UnicodeString & Name);

protected:
  virtual void __fastcall DoValidate();

private:
  TComboBox * NameCombo;
};
//---------------------------------------------------------------------
__fastcall TBookmarkFolderDialog::TBookmarkFolderDialog(TStrings * Folders) :
  TCustomDialog(HELP_LOCATION_PROFILE_MOVE)
{
  Caption = LoadStr(MOVE_BOOKMARK_CAPTION);

  NameCombo = new TComboBox(this);
  NameCombo->AutoComplete = false;
  AddComboBox(NameCombo, CreateLabel(LoadStr(MOVE_BOOKMARK_PROMPT)));
  NameCombo->Items = Folders;
}
//---------------------------------------------------------------------
void __fastcall TBookmarkFolderDialog::DoValidate()
{
  BookmarkFolderValidateName(NameCombo->Text, true);
  TCustomDialog::DoValidate();
}
//---------------------------------------------------------------------
bool __fastcall TBookmarkFolderDialog::Execute(UnicodeString & Name)
{
  NameCombo->Text = Name;
  bool Result = TCustomDialog::Execute();
  if (Result)
  {
    Name = NameCombo->Text;
  }
  return Result;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
__fastcall TLocationProfilesDialog::TLocationProfilesDialog(TComponent * AOwner):
  TForm(AOwner)
{
  FOperationSide = osLocal;
  FBookmarkDragSource = NULL;
  FTerminal = NULL;
  FSessionBookmarkList = new TBookmarkList();
  FSharedBookmarkList = new TBookmarkList();
  FChanging = false;

  FSessionFolders = new TStringList;
  FSessionFolders->CaseSensitive = false;
  FSessionFolders->Sorted = true;
  FSessionFolders->Duplicates = dupIgnore;
  FSharedFolders = new TStringList;
  FSharedFolders->CaseSensitive = false;
  FSharedFolders->Sorted = true;
  FSharedFolders->Duplicates = dupIgnore;

  FSessionScrollOnDragOver = new TTreeViewScrollOnDragOver(SessionProfilesView, true);
  FSharedScrollOnDragOver = new TTreeViewScrollOnDragOver(SharedProfilesView, true);

  UseSystemSettings(this);
}
//---------------------------------------------------------------------
__fastcall TLocationProfilesDialog::~TLocationProfilesDialog()
{
  SAFE_DESTROY(FSharedScrollOnDragOver);
  SAFE_DESTROY(FSessionScrollOnDragOver);
  SAFE_DESTROY(FSharedBookmarkList);
  SAFE_DESTROY(FSessionBookmarkList);
  SAFE_DESTROY(FSharedFolders);
  SAFE_DESTROY(FSessionFolders);
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::SetLocalDirectory(UnicodeString value)
{
  if (LocalDirectory != value)
  {
    LocalDirectoryEdit->Text = value;
    FindProfile();
    UpdateControls();
  }
}
//---------------------------------------------------------------------------
UnicodeString __fastcall TLocationProfilesDialog::GetLocalDirectory()
{
  return ExcludeTrailingBackslash(LocalDirectoryEdit->Text);
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::SetRemoteDirectory(UnicodeString value)
{
  if (RemoteDirectory != value)
  {
    RemoteDirectoryEdit->Text = value;
    FindProfile();
    UpdateControls();
  }
}
//---------------------------------------------------------------------------
UnicodeString __fastcall TLocationProfilesDialog::GetRemoteDirectory()
{
  return UnixExcludeTrailingBackslash(RemoteDirectoryEdit->Text);
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::SetRemoteDirectories(TStrings * value)
{
  RemoteDirectoryEdit->Items = value;
}
//---------------------------------------------------------------------------
TStrings * __fastcall TLocationProfilesDialog::GetRemoteDirectories()
{
  return RemoteDirectoryEdit->Items;
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::SetLocalDirectories(TStrings * value)
{
  LocalDirectoryEdit->Items = value;
}
//---------------------------------------------------------------------------
TStrings * __fastcall TLocationProfilesDialog::GetLocalDirectories()
{
  return LocalDirectoryEdit->Items;
}
//---------------------------------------------------------------------------
bool __fastcall TLocationProfilesDialog::ProfileMatch(TTreeNode * Node)
{
  bool Result = false;
  if (Node->Data)
  {
    TBookmark * Bookmark = (TBookmark *)Node->Data;
    Result =
      (Bookmark->Local == LocalDirectory) &&
      (Bookmark->Remote == RemoteDirectory);
  }
  return Result;
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::FindProfile(TTreeView * ProfilesView)
{
  if ((ProfilesView->Selected == NULL) ||
      !ProfileMatch(ProfilesView->Selected))
  {
    TTreeNode * Match = NULL;
    for (int Index = 0; Index < ProfilesView->Items->Count; Index++)
    {
      TTreeNode * Node = ProfilesView->Items->Item[Index];
      if (ProfileMatch(Node))
      {
        Match = Node;
        break;
      }
    }

    if (Match)
    {
      ProfilesView->Selected = Match;
      Match->MakeVisible();
    }
    else
    {
      ProfilesView->Selected = NULL;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::FindProfile()
{
  FindProfile(SessionProfilesView);
  FindProfile(SharedProfilesView);
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::ControlChange(TObject * /*Sender*/)
{
  UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::UpdateProfilesControls(
  TTreeView * ProfilesView,
  TButton * AddBookmarkButton, TButton * RemoveBookmarkButton,
  TButton * RenameBookmarkButton,  TButton * BookmarkMoveToButton,
  TButton * ShortCutBookmarkButton,
  TButton * UpBookmarkButton, TButton * DownBookmarkButton)
{
  EnableControl(AddBookmarkButton,
    !LocalDirectory.IsEmpty() || !RemoteDirectory.IsEmpty());
  EnableControl(RemoveBookmarkButton, ProfilesView->Selected);
  EnableControl(RenameBookmarkButton, ProfilesView->Selected);
  EnableControl(BookmarkMoveToButton, ProfilesView->Selected && ProfilesView->Selected->Data);
  if (ShortCutBookmarkButton != NULL)
  {
    EnableControl(ShortCutBookmarkButton, ProfilesView->Selected && ProfilesView->Selected->Data);
  }
  EnableControl(UpBookmarkButton, ProfilesView->Selected &&
    ProfilesView->Selected->Data && ProfilesView->Selected->getPrevSibling() &&
    ProfilesView->Selected->getPrevSibling()->Data);
  EnableControl(DownBookmarkButton, ProfilesView->Selected &&
    ProfilesView->Selected->Data && ProfilesView->Selected->getNextSibling() &&
    ProfilesView->Selected->getNextSibling()->Data);
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::UpdateControls()
{
  EnableControl(OKBtn, !LocalDirectory.IsEmpty() || !RemoteDirectory.IsEmpty());
  UpdateProfilesControls(SessionProfilesView,
    AddSessionBookmarkButton, RemoveSessionBookmarkButton,
    RenameSessionBookmarkButton,  SessionBookmarkMoveToButton, NULL,
    UpSessionBookmarkButton, DownSessionBookmarkButton);
  UpdateProfilesControls(SharedProfilesView,
    AddSharedBookmarkButton, RemoveSharedBookmarkButton,
    RenameSharedBookmarkButton, SharedBookmarkMoveToButton,
    ShortCutSharedBookmarkButton,
    UpSharedBookmarkButton, DownSharedBookmarkButton);
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::LoadBookmarks(
  TTreeView * ProfilesView, TStringList * Folders, TBookmarkList * BookmarkList,
  TBookmarkList * Source)
{
  if (Source != NULL)
  {
    BookmarkList->Assign(Source);
  }
  else
  {
    BookmarkList->Clear();
  }

  Configuration->Usage->SetMax(L"MaxBookmarks", BookmarkList->Count);

  assert(BookmarkList != NULL);

  Folders->Clear();
  for (int Index = 0; Index < BookmarkList->Count; Index++)
  {
    TBookmark * Bookmark = BookmarkList->Bookmarks[Index];
    if (!Bookmark->Node.IsEmpty())
    {
      Folders->Add(Bookmark->Node);
    }
  }

  ProfilesView->Items->Clear();

  for (int Index = 0; Index < Folders->Count; Index++)
  {
    Folders->Objects[Index] = ProfilesView->Items->Add(NULL, Folders->Strings[Index]);
  }

  for (int Index = 0; Index < BookmarkList->Count; Index++)
  {
    TBookmark * Bookmark = BookmarkList->Bookmarks[Index];
    TTreeNode * Parent = NULL;
    if (!Bookmark->Node.IsEmpty())
    {
      assert(Folders->IndexOf(Bookmark->Node) >= 0);
      Parent = dynamic_cast<TTreeNode *>(Folders->Objects[Folders->IndexOf(Bookmark->Node)]);
    }
    ProfilesView->Items->AddChildObject(Parent, BookmarkText(Bookmark), Bookmark);
    if ((Parent != NULL) && (Parent->Count == 1))
    {
      // only now, when folder node has its first child, we can eventually expand it
      Parent->Expanded = BookmarkList->NodeOpened[Parent->Text];
    }
  }
}
//---------------------------------------------------------------------------
bool __fastcall TLocationProfilesDialog::Execute()
{
  bool Result;
  PageControl->ActivePage = GetProfilesSheet();
  Result = (ShowModal() == DefaultResult(this));
  if (Terminal)
  {
    WinConfiguration->Bookmarks[FSessionKey] = FSessionBookmarkList;
    WinConfiguration->SharedBookmarks = FSharedBookmarkList;
    WinConfiguration->UseSharedBookmarks = (PageControl->ActivePage == SharedProfilesSheet);
  }
  return Result;
}
//---------------------------------------------------------------------------
TTabSheet * TLocationProfilesDialog::GetProfilesSheet()
{
  return WinConfiguration->UseSharedBookmarks ? SharedProfilesSheet : SessionProfilesSheet;
}
//---------------------------------------------------------------------------
template<class T>
typename T * GetProfilesObject(TObject * Sender, T * SessionObject, T * SharedObject)
{
  TControl * Control = dynamic_cast<TControl *>(Sender);
  assert(Control != NULL);
  switch (abs(Control->Tag))
  {
    case 1: return SessionObject;
    case 2: return SharedObject;
    default: assert(false); return NULL;
  }
}
//---------------------------------------------------------------------------
TBookmarkList * TLocationProfilesDialog::GetBookmarkList(TObject * Sender)
{
  return GetProfilesObject(Sender, FSessionBookmarkList, FSharedBookmarkList);
}
//---------------------------------------------------------------------------
TStringList * TLocationProfilesDialog::GetFolders(TObject * Sender)
{
  #ifdef _DEBUG
  assert(FSessionProfilesViewHandle == SessionProfilesView->Handle);
  assert(FSharedProfilesViewHandle == SharedProfilesView->Handle);
  #endif
  return GetProfilesObject(Sender, FSessionFolders, FSharedFolders);
}
//---------------------------------------------------------------------------
TTreeView * TLocationProfilesDialog::GetProfilesView(TObject * Sender)
{
  return GetProfilesObject(Sender, SessionProfilesView, SharedProfilesView);
}
//---------------------------------------------------------------------------
TTreeViewScrollOnDragOver * TLocationProfilesDialog::GetScrollOnDragOver(TObject * Sender)
{
  return GetProfilesObject(Sender, FSessionScrollOnDragOver, FSharedScrollOnDragOver);
}
//---------------------------------------------------------------------------
bool __fastcall TLocationProfilesDialog::AddAsBookmark(TObject * Sender, bool Initial)
{
  TBookmarkList * BookmarkList = GetBookmarkList(Sender);
  TTreeView * ProfilesView = GetProfilesView(Sender);

  assert(!LocalDirectory.IsEmpty() || !RemoteDirectory.IsEmpty());

  bool Result;
  UnicodeString BookmarkName;
  if ((OperationSide == osLocal && !LocalDirectory.IsEmpty()) ||
      RemoteDirectory.IsEmpty())
  {
    BookmarkName = LocalDirectory;
  }
  else
  {
    BookmarkName = RemoteDirectory;
  }

  TTreeNode * Selected = ProfilesView->Selected;
  TBookmark * SelectedBookmark = NULL;
  UnicodeString SelectedNode;
  if (Selected != NULL)
  {
    assert(!Initial);
    SelectedBookmark = (TBookmark *)Selected->Data;
    if (SelectedBookmark != NULL)
    {
      SelectedNode = SelectedBookmark->Node;
    }
    else
    {
      SelectedNode = Selected->Text;
    }
  }

  TStrings * PeerBookmarks = new TStringList();
  try
  {
    for (int Index = 0; Index < BookmarkList->Count; Index++)
    {
      TBookmark * Bookmark = BookmarkList->Bookmarks[Index];
      if (Bookmark->Node == SelectedNode)
      {
        PeerBookmarks->Add(Bookmark->Name);
      }
    }

    TBookmarkNameDialog * Dialog = new TBookmarkNameDialog(PeerBookmarks, Initial);
    try
    {
      bool Shared = WinConfiguration->UseSharedBookmarks;
      Result = Dialog->Execute(BookmarkName, Shared);
      if (Result)
      {
        if (Initial)
        {
          WinConfiguration->UseSharedBookmarks = Shared;
          BookmarkList = GetBookmarkList(GetProfilesSheet());
          ProfilesView = GetProfilesView(GetProfilesSheet());
        }

        TBookmark * Bookmark = BookmarkList->FindByName(SelectedNode, BookmarkName);
        if (Bookmark != NULL)
        {
          Bookmark->Local = LocalDirectory;
          Bookmark->Remote = RemoteDirectory;

          for (int Index = 0; Index < ProfilesView->Items->Count; Index++)
          {
            TTreeNode * Node = ProfilesView->Items->Item[Index];
            if (Node->Data == Bookmark)
            {
              Selected = Node;
              break;
            }
          }
        }
        else
        {
          Bookmark = new TBookmark();
          Bookmark->Name = BookmarkName;
          Bookmark->Local = LocalDirectory;
          Bookmark->Remote = RemoteDirectory;
          if (SelectedBookmark != NULL)
          {
            Bookmark->Node = SelectedBookmark->Node;
            BookmarkList->InsertBefore(SelectedBookmark, Bookmark);
            Selected = ProfilesView->Items->InsertObject(Selected, BookmarkText(Bookmark), Bookmark);
          }
          else if ((Selected != NULL) && (SelectedBookmark == NULL))
          {
            // must be a folder
            assert(!Selected->Parent); // more than one level of folders is not supported
            Bookmark->Node = Selected->Text;
            BookmarkList->Add(Bookmark);
            Selected = ProfilesView->Items->AddChildObject(Selected, BookmarkText(Bookmark), Bookmark);
          }
          else
          {
            BookmarkList->Add(Bookmark);
            Selected = ProfilesView->Items->AddObject(NULL, BookmarkText(Bookmark), Bookmark);
          }
        }
        ProfilesView->Selected = Selected;
      }
    }
    __finally
    {
      delete Dialog;
    }
  }
  __finally
  {
    delete PeerBookmarks;
  }

  UpdateControls();
  return Result;
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::AddBookmarkButtonClick(TObject * Sender)
{
  AddAsBookmark(Sender, false);
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::RemoveBookmark(TObject * Sender)
{
  TBookmarkList * BookmarkList = GetBookmarkList(Sender);
  TTreeView * ProfilesView = GetProfilesView(Sender);
  TStringList * Folders = GetFolders(Sender);

  assert(ProfilesView->Selected);
  TTreeNode * Node = ProfilesView->Selected;
  if (Node->Data)
  {
    BookmarkList->Delete((TBookmark *)Node->Data);
    TTreeNode * ParentNode = Node->Parent;
    Node->Delete();
    if (ParentNode && !ParentNode->Count)
    {
      assert(Folders->IndexOfObject(ParentNode) >= 0);
      Folders->Delete(Folders->IndexOfObject(ParentNode));
      ParentNode->Delete();
    }
  }
  else
  {
    if (MessageDialog(LoadStr(DELETE_BOOKMARK_FOLDER), qtConfirmation,
          qaYes | qaNo, HELP_LOCATION_PROFILE_DELETE) == qaYes)
    {
      assert(Node->Count);
      for (int i = 0; i < Node->Count; i++)
      {
        BookmarkList->Delete((TBookmark *)Node->Item[i]->Data);
      }
      assert(Folders->IndexOfObject(Node) >= 0);
      Folders->Delete(Folders->IndexOfObject(Node));
      Node->Delete();
    }
  }
  UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::RemoveBookmarkButtonClick(TObject * Sender)
{
  RemoveBookmark(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::BookmarkMove(TObject * Sender,
  TTreeNode * Source, TTreeNode * Dest)
{
  TBookmarkList * BookmarkList = GetBookmarkList(Sender);
  TTreeView * ProfilesView = GetProfilesView(Sender);
  TStringList * Folders = GetFolders(Sender);

  assert(Source && Source->Data);

  TBookmark * Bookmark = (TBookmark *)Source->Data;
  TTreeNode * PrevFolderNode = Source->Parent;

  if (!Dest || !Dest->Data)
  {
    Bookmark->Node = Dest ? Dest->Text : UnicodeString();
    BookmarkList->MoveTo(BookmarkList->Bookmarks[BookmarkList->Count - 1],
      Bookmark, false);
    ProfilesView->Selected->MoveTo(Dest, naAddChild);
  }
  else
  {
    TBookmark * DestBookmark = (TBookmark *)Dest->Data;

    Bookmark->Node = DestBookmark->Node;
    BookmarkList->MoveTo(DestBookmark, Bookmark,
      Source->AbsoluteIndex > Dest->AbsoluteIndex);
    if (Source->AbsoluteIndex > Dest->AbsoluteIndex)
    {
      Source->MoveTo(Dest, naInsert);
    }
    else if (Dest->getNextSibling() != NULL)
    {
      Source->MoveTo(Dest->getNextSibling(), naInsert);
    }
    else
    {
      Source->MoveTo(Dest, naAdd);
    }
  }

  if (PrevFolderNode && !PrevFolderNode->Count)
  {
    assert(Folders->IndexOfObject(PrevFolderNode) >= 0);
    Folders->Delete(Folders->IndexOfObject(PrevFolderNode));
    PrevFolderNode->Delete();
  }

  Source->MakeVisible();
  UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::BookmarkButtonClick(TObject * Sender)
{
  TControl * Control = dynamic_cast<TControl *>(Sender);
  TTreeNode * Node = GetProfilesView(Sender)->Selected;
  assert(Node);
  assert(Node->Data);

  TTreeNode * TargetNode;
  if (Control->Tag < 0)
  {
    TargetNode = Node->getPrevSibling();
    assert(TargetNode);
  }
  else
  {
    TargetNode = Node->getNextSibling();
  }

  BookmarkMove(Sender, Node, TargetNode ? TargetNode : Node->Parent);
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::ProfilesViewStartDrag(
  TObject * Sender, TDragObject *& /*DragObject*/)
{
  TTreeView * ProfilesView = GetProfilesView(Sender);

  if (!ProfilesView->Selected->Data)
  {
    Abort();
  }
  FBookmarkDragSource = ProfilesView->Selected;
  GetScrollOnDragOver(Sender)->StartDrag();
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::ProfilesViewDragOver(
  TObject * Sender, TObject * Source, int X, int Y,
  TDragState /*State*/, bool & Accept)
{
  TTreeView * ProfilesView = GetProfilesView(Sender);

  if (Source == ProfilesView)
  {
    Accept = (ProfilesView->DropTarget != NULL) &&
      (FBookmarkDragSource != ProfilesView->DropTarget);
    GetScrollOnDragOver(Sender)->DragOver(TPoint(X, Y));
  }
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::ProfilesViewDragDrop(
  TObject * Sender, TObject * Source, int /*X*/, int /*Y*/)
{
  TTreeView * ProfilesView = GetProfilesView(Sender);

  if ((Source == ProfilesView) && (ProfilesView->DropTarget != NULL) &&
      (FBookmarkDragSource != ProfilesView->DropTarget))
  {
    assert(FBookmarkDragSource);

    TTreeNode * Target = ProfilesView->DropTarget;
    BookmarkMove(Sender, FBookmarkDragSource, Target);
    FBookmarkDragSource = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::ProfilesViewDblClick(TObject * Sender)
{
  TTreeView * ProfilesView = GetProfilesView(Sender);
  TPoint P = ProfilesView->ScreenToClient(Mouse->CursorPos);
  TTreeNode * Node = ProfilesView->GetNodeAt(P.x, P.y);
  if (OKBtn->Enabled && Node && Node->Data && Node->Selected)
  {
    ModalResult = DefaultResult(this);
  }
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::FormShow(TObject * /*Sender*/)
{
  if (Terminal)
  {
    // cache session key, in case terminal is closed while the window is open
    FSessionKey = Terminal->SessionData->SessionKey;
    // WORAROUND
    // Has to load this only now (not in Execute before ShowModal),
    // when the trees are finally (re)created,
    // otherwise the references in *Folders would be invalid already
    LoadBookmarks(SessionProfilesView, FSessionFolders, FSessionBookmarkList, WinConfiguration->Bookmarks[FSessionKey]);
    LoadBookmarks(SharedProfilesView, FSharedFolders, FSharedBookmarkList, WinConfiguration->SharedBookmarks);
    #ifdef _DEBUG
    FSessionProfilesViewHandle = SessionProfilesView->Handle;
    FSharedProfilesViewHandle = SharedProfilesView->Handle;
    #endif
  }
  if (Mode == odAddBookmark)
  {
    AddAsBookmark(GetProfilesSheet(), true);
  }

  InstallPathWordBreakProc(LocalDirectoryEdit);
  InstallPathWordBreakProc(RemoteDirectoryEdit);

  FindProfile();
  if (OperationSide == osLocal)
  {
    ActiveControl = LocalDirectoryEdit;
  }
  else
  {
    ActiveControl = RemoteDirectoryEdit;
  }
  UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::ProfilesViewKeyDown(TObject * Sender,
  WORD & Key, TShiftState /*Shift*/)
{
  TTreeView * ProfilesView = GetProfilesView(Sender);

  if (!ProfilesView->IsEditing())
  {
    if ((ProfilesView->Selected != NULL) && (Key == VK_DELETE))
    {
      RemoveBookmark(Sender);
      Key = 0;
    }
    else if ((ProfilesView->Selected != NULL) && (Key == VK_F2))
    {
      RenameBookmark(Sender);
      Key = 0;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::DirectoryEditChange(TObject * /*Sender*/)
{
  if (!FChanging)
  {
    FindProfile();
    UpdateControls();
  }
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::ProfilesViewChange(
  TObject * /*Sender*/, TTreeNode * Node)
{
  if (Node && Node->Data)
  {
    assert(!FChanging);
    FChanging = true;
    try
    {
      LocalDirectoryEdit->Text = ((TBookmark *)Node->Data)->Local;
      RemoteDirectoryEdit->Text = ((TBookmark *)Node->Data)->Remote;
    }
    __finally
    {
      FChanging = false;
    }
    // try to locate the same profile in the other set
    FindProfile();
  }
  UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::BookmarkMoveToButtonClick(TObject * Sender)
{
  TTreeView * ProfilesView = GetProfilesView(Sender);
  TStringList * Folders = GetFolders(Sender);

  assert(ProfilesView->Selected->Data);
  TBookmark * Bookmark = (TBookmark *)ProfilesView->Selected->Data;

  TBookmarkFolderDialog * Dialog = new TBookmarkFolderDialog(Folders);
  try
  {
    UnicodeString NodeName = Bookmark->Node;
    if (Dialog->Execute(NodeName) &&
        (NodeName != Bookmark->Node))
    {
      TTreeNode * FolderNode;
      int I = Folders->IndexOf(NodeName);
      if (NodeName.IsEmpty())
      {
        FolderNode = NULL;
      }
      else if (I >= 0)
      {
        FolderNode = dynamic_cast<TTreeNode *>(Folders->Objects[I]);
        assert(FolderNode);
      }
      else
      {
        I = Folders->Add(NodeName);
        TTreeNode * NextNode;
        // duplicated in RenameButtonClick()
        if (I < Folders->Count-1)
        {
          NextNode = dynamic_cast<TTreeNode *>(Folders->Objects[I+1]);
          assert(NextNode);
        }
        else if (Folders->Count > 1)
        {
          NextNode = (dynamic_cast<TTreeNode *>(Folders->Objects[I-1]))->getNextSibling();
        }
        else
        {
          assert(ProfilesView->Items->Count);
          NextNode = ProfilesView->Items->Item[0];
        }
        FolderNode = ProfilesView->Items->Insert(NextNode, NodeName);
        assert(FolderNode);
        Folders->Objects[I] = FolderNode;
      }

      BookmarkMove(Sender, ProfilesView->Selected, FolderNode);
    }
  }
  __finally
  {
    delete Dialog;
  }
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::RenameBookmark(TObject * Sender)
{
  TTreeView * ProfilesView = GetProfilesView(Sender);

  assert(ProfilesView->Selected != NULL);
  if (ProfilesView->Selected != NULL)
  {
    ProfilesView->SetFocus();
    ProfilesView->Selected->EditText();
  }
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::RenameBookmarkButtonClick(TObject * Sender)
{
  RenameBookmark(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::ProfilesViewGetImageIndex(
      TObject * /*Sender*/, TTreeNode * Node)
{
  Node->ImageIndex = Node->Data ? 0 : (Node->Expanded ? 1 : 2);
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::ProfilesViewGetSelectedIndex(
      TObject * /*Sender*/, TTreeNode * Node)
{
  Node->SelectedIndex = Node->Data ? 0 : (Node->Expanded ? 1 : 2);
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::LocalDirectoryBrowseButtonClick(
  TObject * /*Sender*/)
{
  UnicodeString Directory = LocalDirectoryEdit->Text;
  if (SelectDirectory(Directory, LoadStr(SELECT_LOCAL_DIRECTORY), true))
  {
    LocalDirectoryEdit->Text = Directory;
    DirectoryEditChange(LocalDirectoryEdit);
  }
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::SwitchButtonClick(TObject * /*Sender*/)
{
  WinConfiguration->UseLocationProfiles = false;
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::HelpButtonClick(TObject * /*Sender*/)
{
  FormHelp(this);
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::ProfilesViewCollapsed(
  TObject * Sender, TTreeNode * Node)
{
  assert(Node != NULL);
  assert(Node->Data == NULL);
  GetBookmarkList(Sender)->NodeOpened[Node->Text] = false;
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::ProfilesViewExpanded(
  TObject * Sender, TTreeNode * Node)
{
  assert(Node != NULL);
  assert(Node->Data == NULL);
  GetBookmarkList(Sender)->NodeOpened[Node->Text] = true;
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::ProfilesViewEdited(
  TObject * Sender, TTreeNode * Node, UnicodeString & S)
{
  TTreeView * ProfilesView = GetProfilesView(Sender);
  TStringList * Folders = GetFolders(Sender);

  if (Node->Data != NULL)
  {
    BookmarkNameValidateName(S);
    // raises exception in case of duplicate name??
    ((TBookmark *)Node->Data)->Name = S;
  }
  else
  {
    BookmarkFolderValidateName(S, false);
    if (S.IsEmpty())
    {
      throw Exception(FMTLOAD(BOOKMARK_FOLDER_INVALID_NAME, (S)));
    }
    if ((Folders->IndexOf(S) >= 0) && AnsiCompareText(S, Node->Text))
    {
      throw Exception(FMTLOAD(DUPLICATE_BOOKMARK_FOLDER, (S)));
    }
    assert(Node->Count);
    Folders->Delete(Folders->IndexOf(Node->Text));
    int I = Folders->AddObject(S, Node);

    TTreeNode * NextNode;
    // duplicated in MoveToButtonClick()
    if (I < Folders->Count-1)
    {
      NextNode = dynamic_cast<TTreeNode *>(Folders->Objects[I+1]);
      assert(NextNode);
    }
    else if (Folders->Count > 1)
    {
      NextNode = (dynamic_cast<TTreeNode *>(Folders->Objects[I-1]))->getNextSibling();
    }
    else
    {
      assert(ProfilesView->Items->Count);
      NextNode = ProfilesView->Items->Item[0];
    }

    if (NextNode != Node)
    {
      Node->MoveTo(NextNode, NextNode ? naInsert : naAddChild);
    }

    for (int i = 0; i < Node->Count; i++)
    {
      ((TBookmark *)Node->Item[i]->Data)->Node = S;
    }
    Node->MakeVisible();
  }
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::ProfilesViewEditing(
  TObject * /*Sender*/, TTreeNode * /*Node*/, bool & /*AllowEdit*/)
{
  OKBtn->Default = false;
  CancelBtn->Cancel = false;
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::UpdateActions()
{
  TForm::UpdateActions();

  if ((!OKBtn->Default || !CancelBtn->Cancel) &&
      !GetProfilesView(PageControl->ActivePage)->IsEditing())
  {
    OKBtn->Default = true;
    CancelBtn->Cancel = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::ProfilesViewEndDrag(
  TObject * Sender, TObject * /*Target*/, int /*X*/, int /*Y*/)
{
  GetScrollOnDragOver(Sender)->EndDrag();
}
//---------------------------------------------------------------------------
void __fastcall TLocationProfilesDialog::ShortCutBookmarkButtonClick(
  TObject * Sender)
{
  TBookmarkList * BookmarkList = GetBookmarkList(Sender);
  TTreeView * ProfilesView = GetProfilesView(Sender);

  assert(ProfilesView->Selected != NULL);
  TTreeNode * Node = ProfilesView->Selected;
  assert(Node->Data != NULL);

  TBookmark * Bookmark = static_cast<TBookmark *>(Node->Data);

  TShortCuts ShortCuts;
  WinConfiguration->CustomCommandList->ShortCuts(ShortCuts);
  BookmarkList->ShortCuts(ShortCuts);
  TShortCut ShortCut = Bookmark->ShortCut;
  if (DoShortCutDialog(ShortCut, ShortCuts, HelpKeyword))
  {
    Bookmark->ShortCut = ShortCut;
    Node->Text = BookmarkText(Bookmark);
    UpdateControls();
  }
}
//---------------------------------------------------------------------------
UnicodeString __fastcall TLocationProfilesDialog::BookmarkText(TBookmark * Bookmark)
{
  UnicodeString Result = Bookmark->Name;
  if (!Result.IsEmpty() && (Bookmark->ShortCut != 0))
  {
    Result = FORMAT(L"%s (%s)", (Result, ShortCutToText(Bookmark->ShortCut)));
  }
  return Result;
}
//---------------------------------------------------------------------------
