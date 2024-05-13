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
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <unordered_map>
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
	TButton *Delete_Button;
	TButton *Calculate_Button;
	TButton *CalcFile_Button;
	TOutline *Outline1;
	TButton *Button1;
	TMemo *Memo1;
	TEdit *CPM_Edit;
	TLabel *Label2;
	void __fastcall Button_Info_click(TObject *Sender);
	void __fastcall Add_ButtonClick(TObject *Sender);
	void __fastcall Delete_ButtonClick(TObject *Sender);
	void __fastcall Calculate_ButtonClick(TObject *Sender);
	void __fastcall Edit_ButtonClick(TObject *Sender);
	void __fastcall CalcFile_ButtonClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
