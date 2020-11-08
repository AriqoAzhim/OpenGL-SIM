//Compile in a C++ CLR empty project
#using <System.dll>

#include <conio.h>//_kbhit()
#include <SMObject.h>
using namespace System;
using namespace System::Net::Sockets;
using namespace System::Net;
using namespace System::Text;

struct SMData
{
	double SMfromGalil;
};
int main()
{	//SM stuff
	SMObject GalilSMObj(_TEXT("GalilSMObj"), sizeof(SMData));
	GalilSMObj.SMCreate();
	GalilSMObj.SMAccess();
	SMData* GalilSMObjPtr = (SMData*)GalilSMObj.pData;

	while (!_kbhit())
	{
		Console::WriteLine("0,12:F3", GalilSMObjPtr->SMfromGalil);
	}

	return 0;
}