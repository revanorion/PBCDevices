#include "SerialBST.h"

unsigned int Serial_BST::rowNumber;
unsigned int Serial_BST::colomnNumber;



void Serial_BST::Print_Tropos_Comparison_List_to_Excel(const string & filename)
{
	WorkBook^ book = gcnew WorkBook();
	string file = filename;
	if (book) {
		vector<shared_ptr<BST_NODE>> nodeList = comparisionList;
		int row, col;
		row = col = 1;
		book->setText(0, 0, "Assets found");
		book->setText(0, 1, "Assets #");
		book->setText(0, 2, "Serial #");
		book->setText(0, 3, "Device name");
		book->setText(0, 4, "Description");
		book->setText(0, 5, "Location");
		book->setText(0, 6, "Asset Type");
		book->setText(0, 7, "Notes");


		while (!nodeList.empty())
		{
			book->setText(row, col, gcnew System::String(nodeList.back()->get_Asset().c_str()));
			col++;
			book->setText(row, col, gcnew System::String(nodeList.back()->get_SN().c_str()));
			col++;
			book->setText(row, col, gcnew System::String(nodeList.back()->get_Device().c_str()));
			col++;
			book->setText(row, col, gcnew System::String(nodeList.back()->get_Data().Description.c_str()));
			col++;
			book->setText(row, col, gcnew System::String(nodeList.back()->get_Data().Physical_Location.c_str()));
			col++;
			book->setText(row, col, gcnew System::String(nodeList.back()->get_Data().Asset_Type.c_str()));
			col++;
			book->setText(row, col, gcnew System::String(nodeList.back()->get_data().Notes.c_str()));
			col = 1;
			row++;
			nodeList.pop_back();
		}
	}

	if (file.find(".xls") == string::npos || file.substr(file.length() - 4) != ".xls")
		file += ".xls";

	book->write(gcnew System::String(file.c_str()));
}



void Serial_BST::compare(shared_ptr<BST_NODE>& branch, vector<shared_ptr<BST_NODE>>& x)
{
	compare(branch, root, x);
	comparisionList = x;
}

void Serial_BST::compare(shared_ptr<BST_NODE>&branch, shared_ptr<Serial_NODE>&node, vector<shared_ptr<BST_NODE>>& comparableSerials)
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

void Serial_BST::compare_branch(shared_ptr<BST_NODE>&branch, shared_ptr<Serial_NODE>&node, vector<shared_ptr<BST_NODE>>& comparableSerials)
{
	if (node != 0)
	{
		compare_branch(branch, node->get_left_child(), comparableSerials);

		if (branch->get_SN().find(node->get_SN()) != string::npos && node->SN != "")// == node->get_SN()) 
		{

			comparableSerials.push_back(branch);
		}

		compare_branch(branch, node->get_right_child(), comparableSerials);
	}

}


shared_ptr<Serial_NODE>& Serial_BST::insert(const string &SN, const string &dev, shared_ptr<BST_NODE>& parent, shared_ptr<Serial_NODE>& branch)
{
	if (branch == 0)
	{
		return branch = make_shared<Serial_NODE>(SN,dev,parent);
	}

	else {
		if (branch->SN > SN && branch->SN != SN)
		{
			return insert(SN,dev,parent, branch->left_child);
			
		}
		else if (branch->SN <SN && branch->SN != SN)
		{
			return insert(SN,dev,parent, branch->right_child);
			
		}
		else
		{
			cout << "No Dupes nodes!\n";
			return branch;
		}
	}



}

void Serial_BST::insert(shared_ptr<Serial_NODE>& node, shared_ptr<Serial_NODE>& branch)
{
	if (branch == 0)
	{
		branch = node;

	}


	else {
		if (branch->SN > node->SN && branch->SN != node->SN)
		{
			insert(node, branch->left_child);
			return;
		}
		else if (branch->SN < node->SN && branch->SN != node->SN)
		{
			insert(node, branch->right_child);
			return;
		}
		else
		{
			cout << "No Dupes nodes!\n";
			return;
		}
	}
}


shared_ptr<Serial_NODE>& Serial_BST::search(const string &, shared_ptr<Serial_NODE>& branch)
{
	// TODO: insert return statement here
	return branch;
}

void Serial_BST::writeToFile(shared_ptr<Serial_NODE>& branch, ofstream & myfile)
{

	if (branch != 0)
	{

		writeToFile(branch->left_child, myfile);



		if (myfile.is_open())
		{
			myfile << branch->SN << "\n";
		}
		else cout << "Unable to open file";
		writeToFile(branch->right_child, myfile);
	}

}

void Serial_BST::writeToExcel(shared_ptr<Serial_NODE>&branch, WorkBook ^book)
{

	if (branch != 0 && book)
	{
		writeToExcel(branch->left_child, book);

		book->setText(rowNumber, colomnNumber, gcnew System::String(branch->SN.c_str()));

		rowNumber++;

		writeToExcel(branch->right_child, book);
	}



}

void Serial_BST::remove(const string &, shared_ptr<Serial_NODE>&)
{
}

void Serial_BST::print(shared_ptr<Serial_NODE>& branch)
{
	if (branch != 0) {
		print(branch->left_child);
		cout << branch->SN << endl;
		print(branch->right_child);
	}
}

void Serial_BST::printNode(shared_ptr<Serial_NODE>&)
{
}

void Serial_BST::del(shared_ptr<Serial_NODE>&)
{
}

shared_ptr<Serial_NODE> Serial_BST::inorder_succ(const shared_ptr<Serial_NODE>& loc_ptr)
{
	return shared_ptr<Serial_NODE>();
}

void Serial_BST::copy(shared_ptr<Serial_NODE>& root, const shared_ptr<Serial_NODE>& copyN)
{
}

void Serial_BST::Update(const string & s)
{
}

