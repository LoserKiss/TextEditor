#pragma once
static class Filemanager
{
public:
	Filemanager(AllWhatYouWantController* controller);
	~Filemanager(void);
	  int LoadMyImage();
	  int SaveFile();
	  int LoadFile();
	  int NewFile();
private:
	AllWhatYouWantController* father;
};

