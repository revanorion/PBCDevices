#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "HashTable.h"


void read_xls_data(Excel_BST& e, const string & s);

string inline getObject(WorkBook^ book, int rowIndex, int colIndex);

int main()
{
	HashTable DataDump;
	Excel_BST e;
	


	
	DataDump.read_tool_text("Dump.txt");
	read_xls_data(e,"FY 2016 20160114.xlsx");
	DataDump.Print_Serial_list_to_File("serialList.txt");
	DataDump.Print_Hash_Table_to_File("MyList.txt");
	e.print();

	vector<shared_ptr<BST_NODE>> nodeList;
	DataDump.compare(e.get_root(),nodeList);
	while (!nodeList.empty())
	{
		cout << nodeList.back()->get_Asset()<<" " << nodeList.back()->get_SN() << endl;
		nodeList.pop_back();
	}
	//_CrtDumpMemoryLeaks();
	DataDump.Print_Hash_Table_to_Excel("newfile");
	//DataDump.read_xls_data("newfile.xls");
	cout << "Hello worl1\n";
	return 0;
}



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
				shared_ptr<BST_NODE> node = make_shared<BST_NODE>(getObject(book, rowIndex, 4), getObject(book, rowIndex, 12), getObject(book, rowIndex, 0));
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
		n = book->getNumber(rowIndex, colIndex);
		//cout << n << endl;
		return to_string(int(n));

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