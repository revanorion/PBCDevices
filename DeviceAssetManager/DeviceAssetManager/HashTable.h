#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "BST.h"
class HashTable
{
public:

	HashTable (); //default constructor will read data from input file "client_address_data.txt".
	HashTable(const HashTable &);//Copy Constructor

	~HashTable() { delete[]hash_table; };
	void insert(const string & x, const string & y) { hash_table[hash(x)].insert(x, y); };
	void remove() {};
	int inline hash(const string & x) { if (x[0] < 96) return 0; else return x[0] - 96; };
	void Print_Hash_Table() { for (int x = 1; x < 27; x++) hash_table[x].print(); };
	void inline Update(const string & x) { hash_table[hash(x.substr(2))].Update(x); };
	void read_tool_text(const string & s);
	void read_xls_data(const string & s);
	void Print_BST(const string & s) { hash_table[hash(s)].print(); };//Print a BST (cell in hash table) inorder to the screen      

	void Print_Hash_Table_to_File(const string & filename);	//function will print hash table to output file         
	void Print_Hash_Table_to_Excel(const string & filename);
private:

	Dump_BST *hash_table;
	
};


#endif
HashTable::HashTable()
{
	hash_table = new Dump_BST[27];

}
HashTable::HashTable(const HashTable & y)
{
	hash_table = new Dump_BST[27];
	for (int x = 1; x < 27; x++);
		//hash_table[x].copy(hash_table[x].root, y.hash_table[x].root);
}


void HashTable::Print_Hash_Table_to_File(const string & filename) {
	for (int x = 0; x < 27; x++)
		hash_table[x].writeToFile(filename);
}

void HashTable::Print_Hash_Table_to_Excel(const string & filename) {
	WorkBook^ book = gcnew WorkBook();
	string file = filename;
	if (book) {
		//add some sheet name
		
			for (int x = 0; x < 27; x++)
				hash_table[x].writeToExcel(book);
		}

		if (file.find(".xls")==string::npos || file.substr(file.length() - 4) != ".xls")
			file +=".xls";
	
		book->write(gcnew System::String(file.c_str()));

	}



void HashTable::read_tool_text(const string & s) {

	string line, sn, snL;
	ifstream myfile(s);


	ofstream myfiles;
	myfiles.open("OutPut.txt");//, ios::out | ios::app);


	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line.find("Device Name") != std::string::npos) {
				string deviceName = line.substr(line.find(":") + 2, line.length());
				myfiles << deviceName << endl;
				while (getline(myfile, line) && (line.find("#") == std::string::npos || line.find("Serial#") != std::string::npos))
				{
					if (line.find("SN: 0x") == std::string::npos && line.find("SN: N/A") == std::string::npos && line.find("NAME:") == std::string::npos)
						if (line.find("SN:") != std::string::npos) {
							sn = line.substr(line.find("SN:") + 4, line.length());
							if (sn != "") {
								//cout << "\t" << sn << endl;
								snL += sn + ",";
								myfiles << "\t" << sn << endl;
							}
						}
				}
				snL = snL.substr(0, snL.length() - 1);
				this->insert(deviceName, snL);
				snL = "";
				//instert into hashtable
				//system("pause");
			}


		}
		myfile.close();

	}
	else cout << "Unable to open file";



}
void HashTable::read_xls_data(const string & s)
{
	WorkBook^ book= gcnew WorkBook();
	if(s.find(".xlsx")!=std::string::npos)
		book->readXLSX(gcnew System::String(s.c_str()));
	else
		book->read(gcnew System::String(s.c_str()));
	
	int numsheets = 0;// only first sheet book->NumSheets;
	for (int sheetIndex = 0; sheetIndex < numsheets; sheetIndex++)
	{
		//select sheet
		book->Sheet = sheetIndex;
		string sheetName = msclr::interop::marshal_as<std::string>(book->getSheetName(sheetIndex));
		//get the last row of this sheet.
		int lastRow = book->LastRow;
		for (int rowIndex = 0; rowIndex <= lastRow; rowIndex++)
		{
			//get the last column of this row.
			int lastColForRow = book->getLastColForRow(rowIndex);
			for (int colIndex = 0; colIndex <= lastColForRow; colIndex++)
			{
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
					cout << n << endl;
					continue;

				case WorkBook::TypeText:
					t = msclr::interop::marshal_as<std::string>(book->getText(rowIndex, colIndex));
					cout << t << endl;
					continue;

				case WorkBook::TypeLogical:
				case WorkBook::TypeError:
					n = book->getNumber(rowIndex, colIndex);
					continue;

				case WorkBook::TypeEmpty:
					continue;
				}
			}
		}
	}

}