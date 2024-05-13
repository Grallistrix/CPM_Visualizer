#include <vcl.h>
#pragma hdrstop

#include "Zdarzenie_View.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck(Zdarzenie_View *)
{
	new Zdarzenie_View(NULL);
}

//---------------------------------------------------------------------------
__fastcall Zdarzenie_View::Zdarzenie_View(TComponent* Owner)
	: TPanel(Owner)
{
	// Initialize visual components

    // Set the size and position of the shape
    int shapeWidth = 60;
    int shapeHeight = 60;
    int shapeX = (Width - shapeWidth) / 2; // Center horizontally
    int shapeY = (Height - shapeHeight) / 2; // Center vertically

    TShape* backgroundShape = new TShape(this);
    backgroundShape->Parent = this;
    backgroundShape->Shape = stRectangle;
    backgroundShape->Brush->Color = clWhite;
    backgroundShape->SetBounds(shapeX, shapeY, shapeWidth, shapeHeight);

	// Add labels aligned with the corners of the shape
	TLabel* R_Label = new TLabel(this);
	TLabel* L_Label = new TLabel(this);
	TLabel* ID_Label= new TLabel(this);
	TLabel* Reserve_Label = new TLabel(this);


	ID_Label->Parent = this;
	ID_Label->Left = backgroundShape->Left;
	ID_Label->Top = backgroundShape->Top;
	ID_Label->Caption = "ID";


	L_Label->Parent = this;
	L_Label->Left = backgroundShape->Left + backgroundShape->Width - L_Label->Width;
	L_Label->Top = backgroundShape->Top;
	L_Label->Caption = "ES";


	R_Label->Parent = this;
	R_Label->Left = backgroundShape->Left;
	R_Label->Top = backgroundShape->Top + backgroundShape->Height - R_Label->Height;
	R_Label->Caption = "LF";


	Reserve_Label->Parent = this;
	Reserve_Label->Left = backgroundShape->Left + backgroundShape->Width - Reserve_Label->Width;
	Reserve_Label->Top = backgroundShape->Top + backgroundShape->Height - Reserve_Label->Height;
	Reserve_Label->Caption = "R";
}

//---------------------------------------------------------------------------
void __fastcall PACKAGE Register()
{
	TComponentClass classes[1] = {__classid(Zdarzenie_view)};
	RegisterComponents(L"Samples", classes, 0);
}
//---------------------------------------------------------------------------
