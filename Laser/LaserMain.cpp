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
	SMObject LaserObj(TEXT("Laser"), sizeof(Laser));

	// Give Laser access to PM and Laser SM
	// LaserObj.SMCreate();
	PMObj.SMAccess();
	LaserObj.SMAccess();

	//int PortNumber = 23000;
	//// Pointer to TcpClent type object on managed heap
	//TcpClient^ Client = nullptr;
	//
	//array<unsigned char>^ SendData = gcnew array<unsigned char>(16);	
	//array<unsigned char>^ ReadData = gcnew array<unsigned char>(2500);
	//String^ zID = gcnew String("5258788\n");

	//// Create TcpClient object and connect to it
	//Client = gcnew TcpClient("192.168.1.200", PortNumber);

	//// Configure connection
	//Client->NoDelay = true;
	//Client->ReceiveTimeout = 500;//ms
	//Client->SendTimeout = 500;//ms
	//Client->ReceiveBufferSize = 1024;
	//Client->SendBufferSize = 1024;

	//// Convert string command to an array of unsigned char
	//SendData = System::Text::Encoding::ASCII->GetBytes(zID);

	//// Get the network streab object associated with client so we 
	//// can use it to read and write
	//NetworkStream^ Stream = Client->GetStream();

	//// Send the data to the stream
	//Stream->Write(SendData, 0, SendData->Length);
	//System::Threading::Thread::Sleep(10);
	//Stream->Read(ReadData, 0, ReadData->Length);

	//// Convert incoming data from an array of unsigned char bytes to an ASCII string
	//String^ ResponseData = System::Text::Encoding::ASCII->GetString(ReadData);
	//Console::WriteLine(ResponseData);
	
	ProcessManagement* PMPtr = (ProcessManagement*)PMObj.pData;
	PMPtr->LIMIT = 10;

	//Loop

	while (!PMPtr->Shutdown.Flags.Laser)
	{

		// PMHeartbeat check
		if (PMPtr->Heartbeats.Flags.Laser == 1)
		{
			Console::WriteLine("In laser, checking laser heartbeat: ");
			Console::WriteLine(PMPtr->Heartbeats.Flags.Laser);
			PMPtr->Heartbeats.Flags.Laser = 0;
			PMPtr->WAIT_COUNT[0] = 0;
			// Reset WaitAndSeeTime
		}
		else
		{
			Console::WriteLine("Waiting and Seeing");
			Console::WriteLine(PMPtr->WAIT_COUNT[0]);
			PMPtr->WAIT_COUNT[0] = PMPtr->WAIT_COUNT[0] + 1;
			if (PMPtr->WAIT_COUNT[0] > PMPtr->LIMIT)
			{
				//Shutdown all
				Console::WriteLine("Shutdown Flag All");
				PMPtr->Shutdown.Status = 0xFF;
			}
		}


		//// (repeatedly) send a request
		//String^ AskScan = gcnew String("sRN LMDscandata");
		//// Convert string command to an array of unsigned char
		//SendData = System::Text::Encoding::ASCII->GetBytes(AskScan);
		//Stream->WriteByte(0x02); // STX
		//Stream->Write(SendData, 0, SendData->Length);
		//Stream->WriteByte(0x03); // ETX

		//// Read data
		//Stream->Read(ReadData, 0, ReadData->Length);
		//ResponseData = System::Text::Encoding::ASCII->GetString(ReadData);
		////Console::WriteLine(ResponseData);

		//array<wchar_t>^ Space = { ' ' };
		//array<String^>^ StringArray = ResponseData->Split(Space);

		//double StartAngle = System::Convert::ToInt32(StringArray[23], 16);
		//double Resolution = System::Convert::ToInt32(StringArray[24], 16) / 10000.0;
	
		//Laser* LaserPtr = (Laser*)LaserObj.pData;
		//LaserPtr->NumPoints = System::Convert::ToInt32(StringArray[25], 16);

		//array<double>^ Range = gcnew array<double>(LaserPtr->NumPoints);

		//for (int i = 0; i < LaserPtr->NumPoints; i++)
		//{
		//	Range[i] = System::Convert::ToInt32(StringArray[26 + i], 16);
		//	LaserPtr->x[i] = Range[i] * sin(i * Resolution);
		//	LaserPtr->y[i] = -Range[i] * cos(i * Resolution);

		//	Console::WriteLine("X Co-ord: ");
		//	Console::WriteLine(LaserPtr->x[i]);

		//	Console::WriteLine("Y Co-ord: ");
		//	Console::WriteLine(LaserPtr->y[i]);

		//	Console::WriteLine("\n");

		//	System::Threading::Thread::Sleep(100);

		//}
		System::Threading::Thread::Sleep(1000);
	}
	


	/*Stream->Close();
	Client->Close();*/

	return 0;
}