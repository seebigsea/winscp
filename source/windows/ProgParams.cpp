//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <Common.h>
#include "ProgParams.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// auto_ptr-like class
class TProgramParamsOwner
{
public:
  TProgramParamsOwner() :
    FProgramParams(NULL)
  {
  }

  ~TProgramParamsOwner()
  {
    delete FProgramParams;
  }

  TProgramParams * Get()
  {
    if (FProgramParams == NULL)
    {
      FProgramParams = new TProgramParams();
    }
    return FProgramParams;
  }

private:
  TProgramParams * FProgramParams;
};
//---------------------------------------------------------------------------
TProgramParamsOwner ProgramParamsOwner;
//---------------------------------------------------------------------------
TProgramParams * __fastcall TProgramParams::Instance()
{
  return ProgramParamsOwner.Get();
}
//---------------------------------------------------------------------------
__fastcall TProgramParams::TProgramParams()
{
  Init(CmdLine);
}
//---------------------------------------------------------------------------
__fastcall TProgramParams::TProgramParams(const UnicodeString & CmdLine)
{
  Init(CmdLine);
}
//---------------------------------------------------------------------------
void __fastcall TProgramParams::Init(const UnicodeString & CmdLine)
{
  UnicodeString CommandLine = CmdLine;

  UnicodeString Param;
  CutToken(CommandLine, Param);
  while (CutToken(CommandLine, Param))
  {
    Add(Param);
  }
}
