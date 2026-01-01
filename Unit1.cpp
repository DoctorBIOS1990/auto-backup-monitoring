//---------------------------------------------------------------------------

#include <vcl.h>
#include <Windows.h>
#include <System.SysUtils.hpp>
#pragma hdrstop
#include "Unit1.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TmainForm* mainForm;

int countItems;
String backupPath = ExtractFilePath(Application->ExeName) + "\DATA\\";
String source, destiny, dateTimeFormat;

//---------------------------------------------------------------------------
__fastcall TmainForm::TmainForm(TComponent* Owner) : TForm(Owner) {}

//---------------------------------------------------------------------------
void __fastcall TmainForm::btnOpenClick(TObject* Sender)
{
    FileOpenDialog->FileName = "";
    countItems = 0;

    if (FileOpenDialog->Execute()) {
        countItems = FileOpenDialog->Files->Count;
    }

	if (countItems > 0) {
		for (int i = 0; i < countItems; i++) {
			try {
				//listFiles->Items->Add(FileOpenDialog->Files->Strings[i]);

				TListItem* listItem = listView->Items->Add();
				listItem->Caption = FileOpenDialog->Files->Strings[i];
				listItem->ImageIndex = 0 ;

				listTime->Items->Add(DateTimeToStr(FileDateToDateTime(
					FileAge(FileOpenDialog->Files->Strings[i]) )));
                lblCount->Caption =
					"Files: [ " + IntToStr(listView->Items->Count) + " ]";
            } catch (Exception &Exception) {
            }

			FileOpenDialog->Files->Strings[i] = "";
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::timeTimer(TObject* Sender)
{
    // Looking Files
	for (int i = 0; i < countItems; i++) {

		TDateTime nowTime =
			FileDateToDateTime( FileAge(listView->Items->Item[i]->Caption ) );

		TDateTime saveTime = StrToDateTime(listTime->Items->Strings[i]);

		if (nowTime > saveTime) {

			// Format Date
			dateTimeFormat = StringReplace(DateTimeToStr(Now()), "/", "-",
				TReplaceFlags() << rfReplaceAll);

			// Format Time
			dateTimeFormat = StringReplace(
				dateTimeFormat, ":", "-", TReplaceFlags() << rfReplaceAll);

			listTime->Items->Strings[i] = DateTimeToStr(nowTime);

			source = listView->Items->Item[i]->Caption;
			destiny = backupPath + dateTimeFormat + " - " +
					  ExtractFileName(listView->Items->Item[i]->Caption);

			CopyFile(source.c_str(), destiny.c_str(), FALSE);
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TmainForm::btnClearClick(TObject* Sender)
{
	listView->Clear();
	listTime->Clear();
    lblFilename->Caption = "Name: [ ? ]";
    lblCount->Caption = "Total : [ ? ]";
}

//---------------------------------------------------------------------------
void __fastcall TmainForm::imgGithubClick(TObject* Sender)
{
    ShellExecute(mainForm->Handle, TEXT("open"),
        TEXT("https://github.com/DoctorBIOS1990"), NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::ToggleSwitchClick(TObject* Sender)
{
    if (ToggleSwitch->State == tssOn) {
		if (listView->Items->Count == 0) {
            ToggleSwitch->State = tssOff;
            Application->MessageBox(TEXT("Must by include files in the list."),
                TEXT("Error"), MB_OK | MB_ICONERROR);
        } else {
            time->Enabled = True;
            btnClear->Enabled = False;
            btnOpen->Enabled = False;
            lblActive->Show();
        }
    } else {
        lblActive->Hide();
        timeActive->Enabled = False;
        time->Enabled = False;
        btnClear->Enabled = True;
        btnOpen->Enabled = True;
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::timeActiveTimer(TObject* Sender)
{
    // Effect the active text
    if (lblActive->Color == clGreen) {
        lblActive->Color = clWhite;
        lblActive->Font->Color = clBlack;
    } else {
        lblActive->Color = clGreen;
        lblActive->Font->Color = clWhite;
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::lblImgOutputClick(TObject* Sender)
{
    ShellExecute(mainForm->Handle, TEXT("open"), backupPath.c_str(), NULL, NULL,
        SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FormCreate(TObject* Sender)
{
	if (!DirectoryExists(backupPath)) {
		CreateDir(backupPath);
	}
//---------------------------------------------------------------------------
}
void __fastcall TmainForm::listViewClick(TObject *Sender)
{
    int selected;
	if (mainForm->listView->ItemIndex != -1) {
		selected = mainForm->listView->ItemIndex;
		mainForm->lblFilename->Caption =
			"Name: [ " +
			ExtractFileName(mainForm->listView->Items->Item[selected]->Caption) +
			" ]";
	}
}
//---------------------------------------------------------------------------

