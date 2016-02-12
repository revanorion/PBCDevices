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
	Book* book = xlCreateBook();
	string file = filename;
	if (book) {
		Sheet* sheet = book->addSheet(L"Sheet1");
		if (sheet) {
			for (int x = 0; x < 27; x++)
				hash_table[x].writeToExcel(book,sheet);
		}

		if (file.find(".xls")==string::npos || file.substr(file.length() - 4) != ".xls")
			file +=".xls";
		std::wstring widestr = std::wstring(file.begin(), file.end());
		const wchar_t* widecstr = widestr.c_str();


		book->save(widecstr);
		book->release();
	}
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
	Book* book;
	if(s.find(".xlxs")!=std::string::npos)
		book = xlCreateXMLBook();
	else
		book = xlCreateBook();
	std::wstring widestr = std::wstring(s.begin(), s.end());
	const wchar_t* widecstr = widestr.c_str();



	if (book->load(widecstr))
	{
		Sheet* sheet = book->getSheet(0);
		if (sheet)
		{
			
			for (int row = sheet->firstRow(); row < sheet->lastRow(); ++row)
			{

				for (int col = sheet->firstCol(); col < 4; ++col)
				{
					CellType cellType = sheet->cellType(row, col);
					//std::wcout << "(" << row << ", " << col << ") = ";
					if (sheet->isFormula(row, col))
					{
						const wchar_t* s = sheet->readFormula(row, col);
						std::wcout << (s ? s : L"null") << " [formula]\n";
					}
					else
					{
						switch (cellType)
						{
						//case CELLTYPE_EMPTY: std::wcout << "[empty]"; break;
						case CELLTYPE_NUMBER:
						{
							double d = sheet->readNum(row, col);
							if(d!=0)
							std::wcout << d << " [number]\n";
							break;
						}
						case CELLTYPE_STRING:
						{
							
							const wchar_t* s = sheet->readStr(row, col);
							if (s != NULL)
								wcout << s << " [string]\n";
							//std::wcout << (s ? s : L"null") << " [string]\n";
							break;
						}
						case CELLTYPE_BOOLEAN:
						{
							bool b = sheet->readBool(row, col);
							std::wcout << (b ? "true" : "false") << " [boolean]\n";
							break;
						}
						default:
							if (sheet->readStr(row, col) != NULL)
								wcout << sheet->readStr(row, col) << " [string]\n";
							break;
						//case CELLTYPE_BLANK: std::wcout << "[blank]"; break;
						//case CELLTYPE_ERROR: std::wcout << "[error]"; break;
						}
					}
					//std::wcout << std::endl;
				}
			}
		}
	}
	else { cout << "cannot open book " << widecstr << endl; }
	book->release();
}