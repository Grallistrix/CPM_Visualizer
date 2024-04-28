//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Outline.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TListBox *ActivitiesList;
	TEdit *Predecesor_EditBox;
	TEdit *Time_EditBox;
	TEdit *Activity_EditBox;
	TLabel *Activity_Label;
	TLabel *Predecesor_LAbel;
	TLabel *Time_Label;
	TButton *Add_Button;
	TButton *Edit_Button;
	TButton *Delete_Button;
	TButton *Calculate_Button;
	TButton *LoadFromFile_Button;
	TLabel *FileOperation_Label;
	TButton *CalcFile_Button;
	TEdit *FileName_EditBox;
	TLabel *Label1;
	TOutline *Outline1;

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
