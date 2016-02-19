#include "HashTable.h"


HashTable::HashTable(const HashTable & y)
{
	hash_table = new Dump_BST[27];
	for (int x = 1; x < 27; x++);
	//hash_table[x].copy(hash_table[x].root, y.hash_table[x].root);
}



void HashTable::Print_Hash_Table_to_Excel(const string & filename) {
	WorkBook^ book = gcnew WorkBook();
	string file = filename;
	if (book) {
		//add some sheet name

		for (int x = 0; x < 27; x++)
			hash_table[x].writeToExcel(book);
	}

	if (file.find(".xls") == string::npos || file.substr(file.length() - 4) != ".xls")
		file += ".xls";

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
				vector<string> serials;
				myfiles << deviceName << endl;
				while (getline(myfile, line) && (line.find("#") == std::string::npos || line.find("Serial#") != std::string::npos))
				{
					if (line.find("SN: 0x") == std::string::npos && line.find("SN: N/A") == std::string::npos && line.find("NAME:") == std::string::npos)
						if (line.find("SN:") != std::string::npos) {
							sn = line.substr(line.find("SN:") + 4, line.length());
							if (sn != "") {
								//cout << "\t" << sn << endl;
								snL += sn + ",";
								serials.push_back(sn);
								myfiles << "\t" << sn << endl;
							}
						}
				}
				snL = snL.substr(0, snL.length() - 1);
				shared_ptr<BST_NODE> node = insert(deviceName, snL);
				while (!serials.empty())
				{
					serialList.insert(serials.back(), node);
					serials.pop_back();
				}
				snL = "";
				//instert into hashtable
				//system("pause");
			}


		}
		myfile.close();

	}
	else cout << "Unable to open file";



}
