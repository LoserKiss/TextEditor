#include "stdafx.h"
Filemanager::FileObject::FileObject()
{
	fonts = std::vector<std::pair<HFONT,LOGFONT>>();
	bitmaps = std::vector<std::pair<HBITMAP,BITMAP>>();
	faketext = std::vector<ExtendedChar>();
}
Filemanager::Filemanager(AllWhatYouWantController* controller)
{
	father = controller;
}
Filemanager::~Filemanager(void)
{
}
int Filemanager::LoadMyImage()
{
	OPENFILENAME openFileStruct = {0};
	TCHAR filename[256] = {0};

	openFileStruct.lStructSize = sizeof(openFileStruct);
	openFileStruct.lpstrFile = filename;
	openFileStruct.nMaxFile = sizeof(filename);

	if (GetOpenFileName(&openFileStruct))
	{
		int pos = father->actioncontrol->currentPositionToWrite;
		father->text->AddBitmap((HBITMAP) LoadImage( NULL, openFileStruct.lpstrFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE),pos);
		return 1;
	}
	else
		return 0;
}
int Filemanager::SaveFile()
{
	OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
	ofn.hwndOwner = father->hWindow->_hwnd;
    ofn.lpstrFilter = L"Text Files (*.LUKATDIS)\0*.LUKATDIS\0";
	ofn.lpstrFile = (LPWSTR) szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = L"LUKATDIS";
    if(GetSaveFileName(&ofn)) // ������ ��
    {
		int a = 5;
		FileObject saveFileObject = FileObject();
		ExtendedChar walker;
		BOOL isExistObject;
		std::vector<ExtendedChar> extchrvectr;
		father->text->GetData(&extchrvectr);
		for (int i = 0; i < extchrvectr.size(); i++) // ������� ������ ��� ���������� 	
		{                                            //(������ ��� ��������, ���� ������ ����� ��� ����� ������������� ���������)
			isExistObject = false;
			walker = extchrvectr[i];
			for (int j = 0; j < saveFileObject.fonts.size(); j++)
				if( walker.font == saveFileObject.fonts[i].first)
					isExistObject = true;
			if (!isExistObject)
			{
				LOGFONT font = LOGFONT();
				GetObject(walker.font,sizeof(LOGFONT), &font);
				saveFileObject.fonts.push_back(std::make_pair(walker.font,font));
			}
			isExistObject = false;
			for (int j = 0; j < saveFileObject.bitmaps.size(); j++)
				if( walker.bmp == saveFileObject.bitmaps[i].first)
					isExistObject = true;
			if (!isExistObject)
			{
				BITMAP bmp = BITMAP();
				GetObject(walker.bmp,sizeof(BITMAP), &bmp);
				saveFileObject.bitmaps.push_back(std::make_pair(walker.bmp,bmp));
			}
			saveFileObject.faketext.push_back(walker);
		}// �������. ��������� � ����� ������ � ������
		HANDLE file = CreateFile(ofn.lpstrFile, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD written;
		int countOfChars = saveFileObject.faketext.size();
		int countOfFonts = saveFileObject.fonts.size();
		int countOfBitmaps = saveFileObject.bitmaps.size();
		WriteFile(file,&countOfChars,sizeof(int), &written, NULL);// ����� ������� � ��� ����� ����.
		WriteFile(file,&countOfFonts,sizeof(int), &written, NULL);// ����� ������� � ��� ����� �������.
		WriteFile(file,&countOfBitmaps,sizeof(int), &written, NULL);// ����� ������� � ��� ����� ��������.
		for (int i = 0; i< countOfChars; i++)//���������� �������
			WriteFile(file,&saveFileObject.faketext[i], sizeof(ExtendedChar),&written,NULL);
		for (int i = 0; i< countOfFonts; i++)//���������� ������
			WriteFile(file,&saveFileObject.fonts[i], sizeof(std::pair<HFONT,LOGFONT>),&written,NULL);
		for (int i = 0; i< countOfBitmaps; i++)//���������� �������
			WriteFile(file,&saveFileObject.bitmaps[i], sizeof(std::pair<HBITMAP,BITMAP>),&written,NULL);
		return 1;
    }
	return 0;
}
int Filemanager::NewFile()
{
	delete father->text;
	father->text = new Text(father);
	return 1;
}
int Filemanager::LoadFile()
{
	OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
	ofn.hwndOwner = father->hWindow->_hwnd;
    ofn.lpstrFilter = L"Text Files (*.LUKATDIS)\0*.LUKATDIS\0";
	ofn.lpstrFile = (LPWSTR) szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = L"LUKATDIS";
    if(GetOpenFileName(&ofn))
    {
		FileObject openfileObject = FileObject();//��� ��������
		OFSTRUCT str;
		HANDLE file = CreateFile(ofn.lpstrFile,  GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD readBytes;
		int countOfChars ;
		int countOfFonts ;
		int countOfBitmaps ;
		ReadFile(file,&countOfChars,sizeof(int),&readBytes,NULL);
		ReadFile(file,&countOfFonts,sizeof(int),&readBytes,NULL);
		ReadFile(file,&countOfBitmaps,sizeof(int),&readBytes,NULL);
		//�������� ���������� ����� ��� ����.
		ExtendedChar chrbuffer;
		for(int i = 0; i < countOfChars; i++)
		{
			ReadFile(file,&chrbuffer,sizeof(ExtendedChar),&readBytes,NULL);
			openfileObject.faketext.push_back(chrbuffer);
		}
		std::pair<HFONT,LOGFONT> fontbuffer;
		for(int i = 0; i < countOfFonts; i++)
		{
			ReadFile(file,&fontbuffer,sizeof(std::pair<HFONT,LOGFONT>),&readBytes,NULL);
			openfileObject.fonts.push_back(fontbuffer);
		}
		std::pair<HBITMAP,BITMAP> bmpbuffer;
		for(int i = 0; i < countOfChars; i++)
		{
			ReadFile(file,&countOfBitmaps,sizeof(std::pair<HBITMAP,BITMAP>),&readBytes,NULL);
			openfileObject.bitmaps.push_back(bmpbuffer);
		}
		//���, ������ �����. �������� ���������� ��� � Text.
		Text newText = Text(father);//����������� � �������� �������� �����������
		std::map<HFONT,HFONT> oldToNewFontsMap = std::map<HFONT,HFONT>();
		for (int i = 0; i < openfileObject.fonts.size(); i++)
		{
			HFONT newHFont = CreateFontIndirect(&openfileObject.fonts[i].second);
		    oldToNewFontsMap[openfileObject.fonts[i].first] = newHFont;
		}
		std::map<HBITMAP,HBITMAP> oldToNewBitmapMap = std::map<HBITMAP,HBITMAP>();
		for (int i = 0; i < openfileObject.bitmaps.size(); i++)
		{
			HBITMAP newHBitmap = CreateBitmapIndirect(&openfileObject.bitmaps[i].second);
		    
			oldToNewBitmapMap[openfileObject.bitmaps[i].first] = newHBitmap;
		}
		ExtendedChar walker;
		for (int i = 0; i< openfileObject.faketext.size(); i++)
		{
			walker = openfileObject.faketext[i];
			if (walker.bmp != NULL)
			{
				newText.AddBitmap(oldToNewBitmapMap[walker.bmp],i);
			}
			else
			{
				newText.AddChar(walker.chr,
					oldToNewFontsMap[walker.font],i);
			}
		}//����� ����� �����!
		delete father->text;
		father->text = &newText;//���!
		return 1;
	}
	return 0;
}
