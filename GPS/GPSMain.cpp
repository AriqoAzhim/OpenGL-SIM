#include <SMObject.h>
#using <System.dll>
#include <conio.h>//_kbhit()
#include <SMStruct.h>

using namespace System;
using namespace System::Net::Sockets;
using namespace System::Net;
using namespace System::Text;

int main() {
	// Create SMObjects
	SMObject PMObj(TEXT("ProcessManagement"), sizeof(ProcessManagement));

	// Give GPS access to PM and GPS SM
	// LaserObj.SMCreate();
	PMObj.SMAccess();

	ProcessManagement* PMPtr = (ProcessManagement*)PMObj.pData;
	PMPtr->LIMIT = 10;

	//Loop

	while (!PMPtr->Shutdown.Flags.GPS)
	{

		if (PMPtr->Shutdown.Flags.PM == 1)
		{
			//shutdown
			break;
		}

		System::Threading::Thread::Sleep(1000);
	}


	return 0;
}