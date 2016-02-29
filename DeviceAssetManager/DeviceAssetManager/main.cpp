#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "HashTable.h"
#include "ExcelBST.h"


void read_xls_data(Excel_BST& e, const string & s);
void read_csv_tropos_data(Serial_BST& e, const string & s);
void read_csv_wireless_controller_data(Serial_BST& e, const string & s);
void read_csv_APS_wireless_data(Serial_BST& e, const string & s);
void read_csv_wireless_controller_data(Serial_BST& e, const string & s);

string inline getObject(WorkBook^ book, int rowIndex, int colIndex);

int main()
{
	HashTable DataDump;
	Excel_BST excelData;
	Serial_BST troposData;
	Serial_BST WirelessControllerData;
	Serial_BST APSWirelessData;

	read_csv_tropos_data(troposData, "Data\\Tropos Export Data.csv");
	read_csv_tropos_data(troposData, "Data\\Tropos Export Data-2.csv");
	read_csv_tropos_data(troposData, "Data\\Tropos Export Data-3.csv");
	read_csv_wireless_controller_data(WirelessControllerData, "Data\\Wireless_Controllers_20160226_110151_219.csv");
	read_csv_APS_wireless_data(APSWirelessData, "Data\\aps_wireless_with_serial_number_20160226_104838_679.csv");

	DataDump.read_tool_text("Dump.txt");
	read_xls_data(excelData, "FY 2016 20160114.xlsx");
	DataDump.Print_Serial_list_to_File("serialList.txt");
	DataDump.Print_Hash_Table_to_File("MyList.txt");
	excelData.print();
	excelData.writeToExcel("ExcelList.xls");




	vector<shared_ptr<BST_NODE>> nodeListTropos;
	troposData.compare(excelData.get_root(), nodeListTropos);
	while (!nodeListTropos.empty())
	{
		cout << nodeListTropos.back()->get_Asset() << " " << nodeListTropos.back()->get_SN() << endl;
		nodeListTropos.pop_back();
	}
	troposData.Print_Comparison_List_to_Excel("TroposCompared.xls");

	vector<shared_ptr<BST_NODE>> nodeController;
	WirelessControllerData.compare(excelData.get_root(), nodeController);
	WirelessControllerData.Print_Comparison_List_to_Excel("WirelessControllerCompared.xls");
	
	vector<shared_ptr<BST_NODE>> nodeAPS;
	APSWirelessData.compare(excelData.get_root(), nodeAPS);
	APSWirelessData.Print_Comparison_List_to_Excel("APSWirelessControllerCompared.xls");

	vector<shared_ptr<BST_NODE>> nodeList;
	DataDump.compare(excelData.get_root(), nodeList);
	while (!nodeList.empty())
	{
		cout << nodeList.back()->get_Asset() << " " << nodeList.back()->get_SN() << endl;
		nodeList.pop_back();
	}








	DataDump.Print_Comparison_List_to_Excel("comparisionlist.xls");
	DataDump.Print_Hash_Table_to_Excel("newfile");
	DataDump.Print_Serial_list_to_File("AllSerials.xls");


	return 0;
}

void read_csv_APS_wireless_data(Serial_BST& e, const string & s)
{
	WorkBook^ book = gcnew WorkBook();
	book->read(gcnew System::String(s.c_str()));
	int numsheets = 1;// only first sheet book->NumSheets;
	for (int sheetIndex = 0; sheetIndex < numsheets; sheetIndex++)
	{
		//select sheet
		book->Sheet = sheetIndex;
		string sheetName = msclr::interop::marshal_as<std::string>(book->getSheetName(sheetIndex));
		//get the last row of this sheet.
		int lastRow = book->LastRow;

		for (int rowIndex = 1; rowIndex <= lastRow && getObject(book,rowIndex,0)!="Disassociated AP(s)"; rowIndex++)
		{
			string serial = getObject(book, rowIndex, 3);
			if (serial != ""&& serial != "Serial Number")
			{
				string device = getObject(book, rowIndex, 0);
				shared_ptr<Serial_NODE> node = make_shared<Serial_NODE>();
				node->get_device() = device;
				node->get_SN() = serial;
				e.insert(node);
			}
		}
	}

}


void read_csv_wireless_controller_data(Serial_BST& e, const string & s)
{
	WorkBook^ book = gcnew WorkBook();
	book->read(gcnew System::String(s.c_str()));
	int numsheets = 1;// only first sheet book->NumSheets;
	for (int sheetIndex = 0; sheetIndex < numsheets; sheetIndex++)
	{
		//select sheet
		book->Sheet = sheetIndex;
		string sheetName = msclr::interop::marshal_as<std::string>(book->getSheetName(sheetIndex));
		//get the last row of this sheet.
		int lastRow = book->LastRow;

		for (int rowIndex = 1; rowIndex <= lastRow; rowIndex++)
		{
			string serial = getObject(book, rowIndex, 4);
			if (serial != "" && serial !="Serial Number")
			{
				string device = getObject(book, rowIndex, 0);
				shared_ptr<Serial_NODE> node = make_shared<Serial_NODE>();
				node->get_device() = device;
				node->get_SN() = serial;
				e.insert(node);
			}
		}
	}

}

void read_csv_tropos_data(Serial_BST& e, const string & s)
{
	WorkBook^ book = gcnew WorkBook();
	book->read(gcnew System::String(s.c_str()));
	int numsheets = 1;// only first sheet book->NumSheets;
	for (int sheetIndex = 0; sheetIndex < numsheets; sheetIndex++)
	{
		//select sheet
		book->Sheet = sheetIndex;
		string sheetName = msclr::interop::marshal_as<std::string>(book->getSheetName(sheetIndex));
		//get the last row of this sheet.
		int lastRow = book->LastRow;

		for (int rowIndex = 1; rowIndex <= lastRow; rowIndex++)
		{
			string serial = getObject(book, rowIndex, 0);
			if (serial != "")
			{
				string device = getObject(book, rowIndex, 0);
				shared_ptr<Serial_NODE> node = make_shared<Serial_NODE>();
				node->get_device() = device;
				node->get_SN() = serial;
				e.insert(node);
			}
		}
	}

}
//

void read_xls_data(Excel_BST& e, const string & s)
{
	WorkBook^ book = gcnew WorkBook();
	if (s.find(".xlsx") != std::string::npos)
		book->readXLSX(gcnew System::String(s.c_str()));
	else
		book->read(gcnew System::String(s.c_str()));

	int numsheets = 1;// only first sheet book->NumSheets;
	for (int sheetIndex = 0; sheetIndex < numsheets; sheetIndex++)
	{
		//select sheet
		book->Sheet = sheetIndex;
		string sheetName = msclr::interop::marshal_as<std::string>(book->getSheetName(sheetIndex));
		//get the last row of this sheet.
		int lastRow = book->LastRow;

		for (int rowIndex = book->find(0, 0, "Asset #")->Row1 + 1; rowIndex <= lastRow; rowIndex++)
		{
			string divison = getObject(book, rowIndex, 2);
			if (divison == "NETWORK")
			{
				string asset = getObject(book, rowIndex, 0);
				string device = getObject(book, rowIndex, 4);
				string serial = getObject(book, rowIndex, 12);


				shared_ptr<BST_NODE> node = make_shared<BST_NODE>(device, serial, asset);
				node->get_data().Asset_Type = getObject(book, rowIndex, 5);
				node->get_data().Description = getObject(book, rowIndex, 3);
				node->get_data().FATS_Owner = getObject(book, rowIndex, 13);
				node->get_data().ISS_Divison = divison;
				node->get_data().Model = getObject(book, rowIndex, 4);
				node->get_data().Notes = getObject(book, rowIndex, 14);
				node->get_data().Physical_Location = getObject(book, rowIndex, 7);
				e.insert(node);
			}
		}
	}

}

string inline getObject(WorkBook^ book, int rowIndex, int colIndex) {


	double n;
	std::string t, f;
	int type = book->getType(rowIndex, colIndex);
	if (type < 0)
	{
		f = msclr::interop::marshal_as<std::string>(book->getFormula(rowIndex, colIndex));
		type -= 0;
	}
	switch (type)
	{

	case WorkBook::TypeNumber:
		n = floor(book->getNumber(rowIndex, colIndex));
		//cout << n << endl;
		return to_string(long long(n));

	case WorkBook::TypeText:
		t = msclr::interop::marshal_as<std::string>(book->getText(rowIndex, colIndex));
		//cout << t << endl;
		return t;

	case WorkBook::TypeLogical:
	case WorkBook::TypeError:
		n = book->getNumber(rowIndex, colIndex);
		return to_string(int(n));

	case WorkBook::TypeEmpty:
		return "";
	}




}