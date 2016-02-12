#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "HashTable.h"


int main()
{



	HashTable DataDump;
	//string line, sn, snL;
	//ifstream myfile("Dump.txt");


	//ofstream myfiles;
	//myfiles.open("OutPut.txt");//, ios::out | ios::app);


	//if (myfile.is_open())
	//{
	//	while (getline(myfile, line))
	//	{
	//		if (line.find("Device Name") != std::string::npos) {
	//			string deviceName = line.substr(line.find(":") + 2, line.length());
	//			myfiles << deviceName << endl;
	//			while (getline(myfile, line) && (line.find("#") == std::string::npos || line.find("Serial#") != std::string::npos))
	//			{
	//				if (line.find("SN: 0x") == std::string::npos && line.find("SN: N/A") == std::string::npos && line.find("NAME:") == std::string::npos)
	//					if (line.find("SN:") != std::string::npos) {
	//						sn = line.substr(line.find("SN:") + 4, line.length());
	//						if (sn != "") {
	//							//cout << "\t" << sn << endl;
	//							snL += sn + ",";
	//							myfiles << "\t" << sn << endl;
	//						}
	//					}
	//			}
	//			snL = snL.substr(0, snL.length() - 1);
	//			DataDump.insert(deviceName, snL);
	//			snL = "";
	//			//instert into hashtable
	//			//system("pause");
	//		}


	//	}
	//	myfile.close();

	//}
	//else cout << "Unable to open file";
	//DataDump.Print_Hash_Table();

	//DataDump.Print_BST("f");

	DataDump.read_tool_text("Dump.txt");
	//DataDump.read_xls_data("FY 2016 20160114.xlsx");
	DataDump.Print_Hash_Table_to_File("MyList.txt");
	//_CrtDumpMemoryLeaks();
	DataDump.Print_Hash_Table_to_Excel("newfile");
	DataDump.read_xls_data("newfile.xls");
	cout << "Hello worl1\n";
	return 0;
}