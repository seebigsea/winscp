//---------------------------------------------------------------------------
#ifndef NetH
#define NetH
//---------------------------------------------------------------------------
#ifndef C_ONLY
//---------------------------------------------------------------------------
class TSecureShell;
extern TSecureShell * CurrentSSH;
//---------------------------------------------------------------------------
extern int SessionsCount;
void __fastcall NetInitialize();
void __fastcall NetFinalize();
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

