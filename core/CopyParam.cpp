//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Common.h"
#include "CopyParam.h"
//---------------------------------------------------------------------------
__fastcall TCopyParamType::TCopyParamType()
{
  Default();
}
//---------------------------------------------------------------------------
__fastcall TCopyParamType::TCopyParamType(const TCopyParamType & Source)
{
  Assign(&Source);
}
//---------------------------------------------------------------------------
__fastcall TCopyParamType::~TCopyParamType()
{
}
//---------------------------------------------------------------------------
void __fastcall TCopyParamType::Default()
{
  FileNameCase = ncNoChange;
  PreserveReadOnly = true;
  PreserveTime = true;
  Rights.Number = TRights::rfDefault;
  PreserveRights = false; // Was True until #106
  AsciiFileMask.Masks = "*.*html; *.htm; *.txt; *.php*; *.cgi; *.c; *.cpp; *.h; *.pas; "
    "*.bas; *.tex; *.pl; .htaccess; *.xtml; *.css; *.cfg; *.ini; *.sh; *.xml";
  TransferMode = tmAutomatic;
  AddXToDirectories = true;
  ResumeSupport = rsSmart;
  ResumeThreshold = 100 * 1024; // (100 kB)
  ReplaceInvalidChars = true;
  LocalInvalidChars = "/\\:*?\"<>|";
  CalculateSize = true;
  FileMask = "*.*";
  ExcludeFileMask.Masks = "";
  NegativeExclude = false;
  ClearArchive = false;
}
//---------------------------------------------------------------------------
void __fastcall TCopyParamType::Assign(const TCopyParamType * Source)
{
  assert(Source != NULL);
  #define COPY(Prop) Prop = Source->Prop
  COPY(FileNameCase);
  COPY(PreserveReadOnly);
  COPY(PreserveTime);
  COPY(Rights);
  COPY(AsciiFileMask);
  COPY(TransferMode);
  COPY(AddXToDirectories);
  COPY(PreserveRights);
  COPY(ResumeSupport);
  COPY(ResumeThreshold);
  COPY(ReplaceInvalidChars);
  COPY(LocalInvalidChars);
  COPY(CalculateSize);
  COPY(FileMask);
  COPY(ExcludeFileMask);
  COPY(NegativeExclude);
  COPY(ClearArchive);
  #undef COPY
}
//---------------------------------------------------------------------------
TCopyParamType & __fastcall TCopyParamType::operator =(const TCopyParamType & rhp)
{
  Assign(&rhp);
  return *this;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCopyParamType::ValidLocalFileName(AnsiString FileName) const
{
  char * InvalidChar;
  while ((InvalidChar = strpbrk(FileName.c_str(), LocalInvalidChars.c_str())) != NULL)
  {
    FileName[InvalidChar - FileName.c_str() + 1] = '_';
  }
  return FileName;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCopyParamType::ChangeFileName(AnsiString FileName,
  TOperationSide Side, bool FirstLevel) const
{
  if (FirstLevel)
  {
    FileName = MaskFileName(FileName, FileMask);
  }
  switch (FileNameCase) {
    case ncUpperCase: FileName = FileName.UpperCase(); break;
    case ncLowerCase: FileName = FileName.LowerCase(); break;
    case ncFirstUpperCase: FileName = FileName.SubString(1, 1).UpperCase() +
      FileName.SubString(2, FileName.Length()-1).LowerCase(); break;
    case ncLowerCaseShort:
      if ((FileName.Length() <= 12) && (FileName.Pos(".") <= 9) &&
          (FileName == FileName.UpperCase()))
      {
        FileName = FileName.LowerCase();
      }
      break;
    case ncNoChange:
    default:
      /*nothing*/
      break;
  }
  if (ReplaceInvalidChars && (Side == osRemote))
  {
    FileName = ValidLocalFileName(FileName);
  }
  return FileName;
}
//---------------------------------------------------------------------------
bool __fastcall TCopyParamType::UseAsciiTransfer(const AnsiString FileName) const
{
  switch (TransferMode) {
    case tmBinary: return false;
    case tmAscii: return true;
    case tmAutomatic: return AsciiFileMask.Matches(FileName);
    default: assert(false); return false;
  }
}
//---------------------------------------------------------------------------
TRights __fastcall TCopyParamType::RemoteFileRights(Integer Attrs) const
{
  TRights R = Rights;
/*  if ((Attrs & faReadOnly) && PreserveReadOnly)
    R.ReadOnly = True;*/
  if ((Attrs & faDirectory) && AddXToDirectories)
    R.AddExecute();
  return R;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCopyParamType::GetLogStr() const
{
  char CaseC[] = "NULFS";
  char ModeC[] = "BAM";
  char ResumeC[] = "YSN";
  return FORMAT(
    "  PrTime: %s; PrRO: %s; Rght: %s; PrR: %s; FnCs: %s; RIC: %s; "
      "Resume: %s (%d); CalcS: %s; Mask: %s\n"
    "  TM: %s; ClAr: %s; ExclM(%s): %s\n"
    "  AscM: %s\n",
    (BooleanToEngStr(PreserveTime),
     BooleanToEngStr(PreserveReadOnly),
     Rights.Text,
     BooleanToEngStr(PreserveRights),
     CaseC[FileNameCase],
     BooleanToEngStr(ReplaceInvalidChars),
     ResumeC[ResumeSupport],
     (int)ResumeThreshold,
     BooleanToEngStr(CalculateSize),
     FileMask,
     ModeC[TransferMode],
     BooleanToEngStr(ClearArchive),
     BooleanToEngStr(NegativeExclude),
     ExcludeFileMask.Masks,
     AsciiFileMask.Masks));
}
//---------------------------------------------------------------------------
int __fastcall TCopyParamType::LocalFileAttrs(const TRights & Rights) const
{
  int Result = 0;
  if (PreserveReadOnly && !Rights.Right[TRights::rrUserWrite])
  {
    Result |= faReadOnly;
  }
  return Result;
}
//---------------------------------------------------------------------------
bool __fastcall TCopyParamType::AllowResume(__int64 Size) const
{
  switch (ResumeSupport) {
    case rsOn: return true;
    case rsOff: return false;
    case rsSmart: return (Size >= ResumeThreshold);
    default: assert(false); return false;
  }
}
//---------------------------------------------------------------------------
bool __fastcall TCopyParamType::AllowTransfer(AnsiString FileName,
  TOperationSide Side) const
{
  bool Result = true;
  if (!ExcludeFileMask.Masks.IsEmpty())
  {
    // workaround for problems with colons in TFileMasks::Matches
    if (Side == osLocal)
    {
      FileName = ExtractFileName(FileName);
    }
    else
    {
      FileName = UnixExtractFileName(FileName);
    }
    Result = (ExcludeFileMask.Matches(FileName) == NegativeExclude);
  }
  return Result;
}

