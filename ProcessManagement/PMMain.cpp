#using <System.dll>

#include <SMObject.h>
#include <stdio.h>
#include <iostream>
#include <TLHelp32.h>
#include <SMStruct.h>
#include <conio.h>

using namespace System;

#define NUM_UNITS 1
// Start up sequence
TCHAR Units[10][20] =
{
	TEXT("Laser.exe"),
	// TEXT("GPS.exe"),
	// TEXT("XBox.exe"),
	// TEXT("VehicleControl.exe"),
	// TEXT("OpenGL.exe"),

};

bool IsProcessRunning(const char* processName);

/*set up shared memory. the shared memory module must have the capability to:
(a) provide read/write access to laser data.
(b) provide read/write access to GPS data.
(c) provide read/write access to Camera data.
(d) provide read/write access to vehicle control data.
(e) provide read/write access to process management data.
2. start all other processes one by one in the most logical sequence suitable for tele-operation of the UGV.
3. monitor the heartbeats of all the other processes.
4. carry out a complete shutdown in the event the process management process detects the failure of a critically important process.
5. attempt to restart a failed non-critical process.
6. carry out a routine shutdown of all the processes in response to a keypress event of your choosing
7. indicate to all the other modules that it is alive and operational. If process management fails all other processes should terminate.*/

int main() {

	// Set up shared memory
	SMObject PMObj(_TEXT("ProcessManagement"), sizeof(ProcessManagement));
	SMObject LaserObj(TEXT("Laser"), sizeof(Laser));
	PMObj.SMCreate();
	LaserObj.SMCreate();
	PMObj.SMAccess();
	ProcessManagement* PMPtr = (ProcessManagement*)PMObj.pData;

	// Set up heartbeats
	PMPtr->Heartbeats.Status = 0;

	/*
	//TESTING:
	while (1) {
		if (PMPtr->Heartbeats.Flags.Laser == 1) {
			// SMObjectPtr->Heartbeats.Status = SMObjectPtr->Heartbeats.Status | 0x04;
			PMPtr->Heartbeats.Status = 0;
			std::cout << "PM reset heartbeat" << std::endl << std::endl;
		}
		Sleep(100);
	}
	*/

	// Convert ascii to hex

	// Set up shutdown data
	PMPtr->Shutdown.Status = 0;

	// Start all processes

	// Module execution based variable declarations
	STARTUPINFO s[10];
	PROCESS_INFORMATION p[10];

	std::string str = "Laser.exe";
	const char* pointer = str.c_str();

	// Starting the processes
	for (int i = 0; i < NUM_UNITS; i++)
	{
		// Check if each process is running
		// if (!IsProcessRunning((const char*)Units[i])) DOESN'T WORK
		if (!IsProcessRunning(pointer))
		{
			std::cout << str.c_str() << std::endl;
			ZeroMemory(&s[i], sizeof(s[i]));
			s[i].cb = sizeof(s[i]);
			ZeroMemory(&p[i], sizeof(p[i]));
			// Start the child processes.

			if (!CreateProcess(NULL,   // No module name (use command line)
				Units[i],        // Command line
				NULL,           // Process handle not inheritable
				NULL,           // Thread handle not inheritable
				FALSE,          // Set handle inheritance to FALSE
				CREATE_NEW_CONSOLE,              // No creation flags
				NULL,           // Use parent's environment block
				NULL,           // Use parent's starting directory
				&s[i],            // Pointer to STARTUPINFO structure
				&p[i])           // Pointer to PROCESS_INFORMATION structure
				)
			{
				printf("%s failed (%d).\n", Units[i], GetLastError());
				getchar();
				return -1;
			}
		}
		std::cout << "Started: " << Units[i] << std::endl;
		Sleep(1000);
	}

	// getchar();

	// While PM shutdown flag is LOW, loop through heartbeat process
	//while (!PMPtr->Shutdown.Flags.PM)
	//{
	//	if (PMPtr->PMHeartbeats.Flags.Laser == 1)
	//	{
	//		PMPtr->Heartbeats.Flags.Laser == 0;
	//		Wait_Count[0] = 0;
	//	}
	//	else
	//		Wait_Count[0]++;

	//	if (Wait_Count[0] > LIMIT)
	//	{
	//		if (Laser Critical)
	//		{
	//			//Shutdown Laser
	//		}
	//		else
	//		{
	//			if (!GPS running)
	//			{
	//				//restart Laser
	//			}
	//			else
	//			{
	//				//kill Laser
	//				//restart Laser
	//			}
	//		}
	//	}
	//}

	while (!_kbhit())
	{
		// printf("in kb loop");

		System::Threading::Thread::Sleep(10);

		// While PM shutdown flag is LOW, loop through heartbeat process
		while (!PMPtr->Shutdown.Flags.PM)
		{
			
			//if (PMPtr->PMHeartbeats.Flags.Laser == 1)
			//{
			//	PMPtr->Heartbeats.Flags.Laser == 0;
			//	Wait_Count[0] = 0;
			//}
			//else
			//	Wait_Count[0]++;

			//if (Wait_Count[0] > PMPtr->LIMIT)
			//{
			//	//if (Laser Critical)
			//	//{
			//	//	//Shutdown Laser
			//	//}
			//	//else
			//	//{
			//	//	if (!GPS running)
			//	//	{
			//	//		//restart Laser
			//	//	}
			//	//	else
			//	//	{
			//	//		//kill Laser
			//	//		//restart Laser
			//	//	}
			//	//}
			//	break;
			//}

			if (_kbhit)
			{
				PMPtr->Shutdown.Flags.PM = 1;
			}
		}
	}

	PMPtr->Shutdown.Status = 0xFF;

	return 0;
}

//Is process running function
bool IsProcessRunning(const char* processName)
{
	bool exists = false;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry))
		while (Process32Next(snapshot, &entry))
			if (!_stricmp((const char*)entry.szExeFile, processName))
				exists = true;

	CloseHandle(snapshot);
	return exists;
}