//---------------------------------------------------------------------------

#include <vcl.h>
#include <Windows.h>
#pragma hdrstop
#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TmainForm* mainForm;

int countItems;
String backupPath = ExtractFilePath(Application->ExeName) + "\DATA\\";
String source, destiny, dateTimeFormat;
TTime saveTime, nowTime;

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
                listFiles->Items->Add(FileOpenDialog->Files->Strings[i]);
                listTime->Items->Add(TimeToStr(FileDateToDateTime(
                    FileAge(FileOpenDialog->Files->Strings[i]))));
                lblCount->Caption =
                    "Files: [ " + IntToStr(listFiles->Items->Count) + " ]";
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
        nowTime = StrToTime(TimeToStr(
            FileDateToDateTime(FileAge(listFiles->Items->Strings[i]))));
        saveTime = StrToTime(listTime->Items->Strings[i]);
        ShowMessage(saveTime);

        if (nowTime > saveTime) {
            // Format Date
            dateTimeFormat = StringReplace(DateTimeToStr(Now()), "/", "-",
                TReplaceFlags() << rfReplaceAll);

            // Format Time
            dateTimeFormat = StringReplace(
                dateTimeFormat, ":", "-", TReplaceFlags() << rfReplaceAll);

            listTime->Items->Strings[i] = TimeToStr(nowTime);

            source = listFiles->Items->Strings[i];
            destiny = backupPath + dateTimeFormat + " - " +
                      ExtractFileName(listFiles->Items->Strings[i]);

            CopyFile(source.c_str(), destiny.c_str(), FALSE);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TmainForm::btnClearClick(TObject* Sender)
{
    listFiles->Clear();
    listTime->Clear();
    lblFilename->Caption = "Name: [ ? ]";
    lblCount->Caption = "Total : [ ? ]";
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::listFilesClick(TObject* Sender)
{
    int selected;
    if (mainForm->listFiles->ItemIndex != -1) {
        selected = mainForm->listFiles->ItemIndex;
        mainForm->lblFilename->Caption =
            "Name: [ " +
            ExtractFileName(mainForm->listFiles->Items->Strings[selected]) +
            " ]";
    }
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
        if (listFiles->Items->Count == 0) {
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
