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

void HashTable::Print_Comparison_List_to_Excel(const string & filename)
{
	WorkBook^ book = gcnew WorkBook();
	string file = filename;
	if (book) {
		vector<shared_ptr<BST_NODE>> nodeList=comparisionList;
		int row, col;
		row = col = 1;
		book->setText(0, 0, "Assets found");
		book->setText(0, 1, "Assets #");
		book->setText(0, 2, "Serial #");
		book->setText(0, 3, "Device name");
		book->setText(0, 4, "Description");
		book->setText(0, 5, "Location");
		book->setText(0, 6, "Notes");


		while (!nodeList.empty())
		{
			book->setText(row, col, gcnew System::String(nodeList.back()->get_excel_link()->get_Asset().c_str()));
			col++;
			book->setText(row, col, gcnew System::String(nodeList.back()->get_hash_link()->get_SN().c_str()));
			col++;
			book->setText(row, col, gcnew System::String(nodeList.back()->get_hash_link()->get_Device().c_str()));
			col++;
			book->setText(row, col, gcnew System::String(nodeList.back()->get_excel_link()->get_Data().Description.c_str()));
			col++;
			book->setText(row, col, gcnew System::String( nodeList.back()->get_excel_link()->get_Data().Physical_Location.c_str()));
			col++;
			book->setText(row, col, gcnew System::String(nodeList.back()->get_hash_link()->get_data().Notes.c_str()));
			col = 1;
			row++;
			nodeList.pop_back();
		}
	}

	if (file.find(".xls") == string::npos || file.substr(file.length() - 4) != ".xls")
		file += ".xls";

	book->write(gcnew System::String(file.c_str()));
}

void HashTable::Print_serials_to_Excel(const string & filename)
{
	WorkBook^ book = gcnew WorkBook();
	string file = filename;
	if (book) {

		serialList->writeToExcel(book);
	}

	if (file.find(".xls") == string::npos || file.substr(file.length() - 4) != ".xls")
		file += ".xls";

	book->write(gcnew System::String(file.c_str()));



}

bool searchSlaves(shared_ptr<BST_NODE>&branch, shared_ptr<Serial_NODE>&node)
{
	if (branch != 0)
	{
		if (branch->get_SN() == node->get_SN())
			return true;
		else if (branch->get_SN() > node->get_SN())
			return searchSlaves(branch->get_left_child(), node);
		else if (branch->get_SN() < node->get_SN())
			return searchSlaves(branch->get_right_child(), node);
		else
			return false;
	}
}


void HashTable::compare(shared_ptr<BST_NODE>&branch, shared_ptr<Serial_NODE>&node, vector<shared_ptr<BST_NODE>>& comparableSerials)
{
	if (branch != 0)
	{
		compare(branch->get_left_child(), node, comparableSerials);

		if (branch->get_SN() != "")
		{
			compare_branch(branch, node, comparableSerials);

		}

		compare(branch->get_right_child(), node, comparableSerials);

	}

}

void HashTable::compare_branch(shared_ptr<BST_NODE>&branch, shared_ptr<Serial_NODE>&node, vector<shared_ptr<BST_NODE>>& comparableSerials)
{
	if (node != 0)
	{
		compare_branch(branch, node->get_left_child(), comparableSerials);
		if (branch->get_SN().find(node->get_SN())!=string::npos)// == node->get_SN()) 
		{
			
			comparableSerials.push_back(branch);
			shared_ptr<BST_NODE> HashBranch = search_by_device(node->get_device());
			comparableSerials.back()->set_excel_link(branch);
			comparableSerials.back()->set_hash_link(HashBranch);
			HashBranch->set_excel_link(branch);
			branch->set_hash_link(HashBranch);
		}
		else if (!branch->get_slaves().empty())
			for (int x = 0; x < branch->get_slaves().size(); x++)
				if (branch->get_slaves()[x]->get_SN().find(node->get_SN())!=string::npos)// == node->get_SN()) 
				{
					comparableSerials.push_back(branch);
					shared_ptr<BST_NODE> HashBranch = search_by_device(node->get_device());
					comparableSerials.back()->set_excel_link(branch);
					comparableSerials.back()->set_hash_link(HashBranch);
					HashBranch->set_excel_link(branch);
					branch->set_hash_link(HashBranch);
				}

		compare_branch(branch, node->get_right_child(), comparableSerials);
	}

}
















//
//void HashTable::compare(shared_ptr<BST_NODE>&branch, shared_ptr<Serial_NODE>&node, vector<shared_ptr<BST_NODE>>& comparableSerials)
//{
//	// TODO: insert return statement here
//	if (branch != 0 && node!=0)
//	{
//		compare(branch, node->get_left_child(), comparableSerials);
//		if (node->get_SN() == branch->get_SN())
//		{
//			comparableSerials.push_back(branch);
//			node->get_dump_parent()->set_excel_link(branch);
//			
//		}
//		else {
//			if (branch->get_slaves() != 0)
//			{
//				if (searchSlaves(branch->get_slaves(), node))
//				{
//					comparableSerials.push_back(branch);
//					node->get_dump_parent()->set_excel_link(branch);
//				}
//			}
//			if (branch->get_SN() > node->get_SN())
//				compare_branch(branch->get_left_child(), node, comparableSerials);
//			else if (branch->get_SN() < node->get_SN())
//				compare_branch(branch->get_right_child(), node, comparableSerials);
//			
//		}
//		compare(branch, node->get_right_child(), comparableSerials);
//	}
//
//}
//
//void HashTable::compare_branch(shared_ptr<BST_NODE>&branch, shared_ptr<Serial_NODE>&node, vector<shared_ptr<BST_NODE>>& comparableSerials)
//{
//	// TODO: insert return statement here
//	if (branch != 0)
//	{
//		if (node->get_SN() == branch->get_SN())
//		{
//			comparableSerials.push_back(branch);
//			node->get_dump_parent()->set_excel_link(branch);
//			
//		}
//		else {
//			if (branch->get_slaves() != 0)
//			{
//				if (searchSlaves(branch->get_slaves(), node))
//				{
//					comparableSerials.push_back(branch);
//					node->get_dump_parent()->set_excel_link(branch);
//				}
//			}
//			if (branch->get_SN() > node->get_SN())
//				 compare_branch(branch->get_left_child(), node, comparableSerials);
//			else if (branch->get_SN() < node->get_SN())
//				 compare_branch(branch->get_right_child(), node, comparableSerials);
//			
//		}
//
//	}
//
//}
//


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
					serialList->insert(serials.back(),deviceName, node);
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

//params: excel tree and vector list of matched serials
void HashTable::compare(shared_ptr<BST_NODE>& branch, vector<shared_ptr<BST_NODE>>& x)
{

	compare(branch, serialList->root,x);
	set_comparison_list(x);
}
