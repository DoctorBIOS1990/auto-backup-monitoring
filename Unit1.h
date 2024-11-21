//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.WinXCtrls.hpp>
//---------------------------------------------------------------------------
class TmainForm : public TForm
{
__published:	// IDE-managed Components
	TListBox *listFiles;
	TBitBtn *btnOpen;
	TTimer *time;
	TFileOpenDialog *FileOpenDialog;
	TListBox *listTime;
	TLabel *Label1;
	TLabel *Label2;
	TBitBtn *btnClear;
	TLabel *Label4;
	TImage *Image1;
	TImage *Image2;
	TLabel *lblGithub;
	TLabel *lblFilename;
	TLabel *Label3;
	TGroupBox *GroupBox1;
	TImage *imgGithub;
	TToggleSwitch *ToggleSwitch;
	TLabel *Label5;
	TLabel *lblCount;
	TTimer *timeActive;
	TLabel *lblActive;
	TImage *lblImgOutput;
	TLabel *lblOutput;
	void __fastcall btnOpenClick(TObject *Sender);
	void __fastcall timeTimer(TObject *Sender);
	void __fastcall btnClearClick(TObject *Sender);
	void __fastcall listFilesClick(TObject *Sender);
	void __fastcall imgGithubClick(TObject *Sender);
	void __fastcall ToggleSwitchClick(TObject *Sender);
	void __fastcall timeActiveTimer(TObject *Sender);
	void __fastcall lblImgOutputClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TmainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TmainForm *mainForm;
//---------------------------------------------------------------------------
#endif
