#include "SerialBST.h"

unsigned int Serial_BST::rowNumber;
unsigned int Serial_BST::colomnNumber;



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

void Serial_BST::insert(shared_ptr<Serial_NODE>&, shared_ptr<Serial_NODE>&)
{
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

