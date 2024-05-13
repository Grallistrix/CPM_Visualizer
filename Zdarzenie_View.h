//---------------------------------------------------------------------------

#ifndef Zdarzenie_ViewH
#define Zdarzenie_ViewH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE Zdarzenie_View : public TPanel
{
private:
protected:
public:
	int Width = 75;
	int Height = 75;
	__fastcall Zdarzenie_View(TComponent* Owner);
__published:
};
//---------------------------------------------------------------------------
#endif
