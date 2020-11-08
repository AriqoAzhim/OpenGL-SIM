////Compile in a C++ CLR empty project
//#using <System.dll>
//#include <conio.h>//_kbhit()
//#include <SMObject.h>
//
//using namespace System;
//using namespace System::Net::Sockets;
//using namespace System::Net;
//using namespace System::Text;
//
//struct SMData
//{
//	double SMfromGalil;
//};
//int main()
//{	//SM stuff
//	SMObject GalilSMObj(_TEXT("GalilSMObj"), sizeof(SMData));
//	GalilSMObj.SMCreate();
//	GalilSMObj.SMAccess();
//	SMData* GalilSMObjPtr = (SMData*)GalilSMObj.pData;
//
//	// Galil PLC any port number is OK
//	int PortNumber = 23000;
//	// Pointer to TcpClent type object on managed heap
//	TcpClient^ Client = nullptr;
//	// arrays of unsigned chars to send and receive data
//	array<unsigned char>^ SendData = nullptr;
//	array<unsigned char>^ ReadData = nullptr;
//	// String command to ask for Channel 1 analogue voltage from the PLC
//	// These command are available on Galil RIO47122 command reference manual
//	// available online
//	String^ AskVoltage = gcnew String("5258788\n");
//	// String to store received data for display
//	String^ ResponseData;
//
//	// Creat TcpClient object and connect to it
//	Client = gcnew TcpClient("192.168.1.200", PortNumber);
//	// Configure connection
//	Client->NoDelay = true;
//	Client->ReceiveTimeout = 500;//ms
//	Client->SendTimeout = 500;//ms
//	Client->ReceiveBufferSize = 1024;
//	Client->SendBufferSize = 1024;
//
//	// unsigned char arrays of 16 bytes each are created on managed heap
//	SendData = gcnew array<unsigned char>(16);
//	ReadData = gcnew array<unsigned char>(16);
//	// Convert string command to an array of unsigned char
//	SendData = System::Text::Encoding::ASCII->GetBytes(AskVoltage);
//
//
//	// Get the network streab object associated with client so we 
//	// can use it to read and write
//	NetworkStream^ Stream = Client->GetStream();
//
//
//	//Loop
//	//while (!_kbhit())
//	//{
//	//	// Write command asking for data
//		Stream->Write(SendData, 0, SendData->Length);
//	//	// Wait for the server to prepare the data, 1 ms would be sufficient, but used 10 ms
//	//	System::Threading::Thread::Sleep(10);
//	//	// Read the incoming data
//		Stream->Read(ReadData, 0, ReadData->Length);
//	//	// Convert incoming data from an array of unsigned char bytes to an ASCII string
//		ResponseData = System::Text::Encoding::ASCII->GetString(ReadData);
//	//	//Remove ":" from the string
//		ResponseData = ResponseData->Replace(":", "");
//	//	// Print the received string on the screen
//		Console::WriteLine(ResponseData);
//		GalilSMObjPtr->SMfromGalil = 159.951;
//	//}
//
//	Stream->Close();
//	Client->Close();
//
//	Console::ReadKey();
//
//
//	return 0;
//}