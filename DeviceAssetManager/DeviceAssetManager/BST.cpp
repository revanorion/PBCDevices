#include "BST.h"

unsigned int Dump_BST::rowNumber;
unsigned int Dump_BST::colomnNumber;




void Dump_BST::print(shared_ptr<BST_NODE>& branch)
{
	if (branch != 0)
	{
		print(branch->left_child);
		//cout << branch->device << endl;



		cout << "+---" << branch->device;
		if (!branch->slaves.empty()) {
			cout << "\n|";
			cout << "\t\\---" << branch->SN << "\n|";
			cout << "\t\t\--- slaves\n|";
			for (int x = 0; x < branch->slaves.size();x++)
				cout << "\t\t\\---" << branch->slaves[x]->SN << "\n|";
		}
		else
			cout << "\n|\t+---" << branch->SN << "\n|";
		if (!branch->duplicates.empty()) {
			cout << "\t--- duplicates\n|";
			for (int x = 0; x < branch->duplicates.size(); x++)
				cout << "\t\t\\---" << branch->duplicates[x]->SN << "\n|";
		}



		print(branch->right_child);
	}
}






void Dump_BST::printNode(shared_ptr<BST_NODE>& branch)
{
	if (branch != 0)
	{
		
		cout << branch->device << endl;
		cout << "| Master\t" << branch->SN << " " << branch->asset;
		cout << endl;
		if (!branch->slaves.empty()) {
			cout << "\n|";
			cout << "\t\\---" << branch->SN << "\n|";
			cout << "\t\t\--- slaves\n|";
			for (int x = 0; x < branch->slaves.size(); x++)
				cout << "\t\t\\---" << branch->slaves[x]->SN << "\n|";
		}
		if (!branch->duplicates.empty()) {
			cout << "\t--- duplicates\n|";
			for (int x = 0; x < branch->duplicates.size(); x++)
				cout << "\t\t\\---" << branch->duplicates[x]->SN << "\n|";
		}
		
	}
}

//need to write duplicates
void Dump_BST::writeToExcel(shared_ptr<BST_NODE>& branch, WorkBook^ book) 
{
	if (branch!=0 && book)
	{
		writeToExcel(branch->left_child, book);
	
		book->setText(rowNumber, colomnNumber, gcnew System::String(branch->device.c_str()));





		colomnNumber++;
		book->setText(rowNumber, colomnNumber, gcnew System::String(branch->SN.c_str()));

		rowNumber++;
		//int rowTop = rowNumber;
		if (!branch->slaves.empty())
			for (int x = 0; x < branch->slaves.size(); x++)
			{
				book->setText(rowNumber, colomnNumber, gcnew System::String(branch->slaves[x]->SN.c_str()));
				rowNumber++;
			}

		
		colomnNumber = 1;
		

		writeToExcel(branch->right_child, book);
	}

}






//MODIFY
void Dump_BST::writeToFile(shared_ptr<BST_NODE>& branch, ofstream& myfile)
{
	

	if (branch != 0)
	{
		
		writeToFile(branch->left_child, myfile);
	
		if (myfile.is_open())
		{
			myfile << "+---" << branch->device; 
			if (!branch->slaves.empty()) {
				myfile << "\n|";
				myfile << "\t\\---" << branch->SN << "\n|";
				myfile << "\t\t\--- slaves\n|";
				for (int x = 0; x < branch->slaves.size(); x++)
					myfile << "\t\t\\---" << branch->slaves[x]->SN << "\n|";
			}
			else
				myfile << "\n|\t+---" << branch->SN << "\n|";
			if (!branch->duplicates.empty()) {
				myfile << "\t--- duplicates\n|";
				for (int x = 0; x < branch->duplicates.size(); x++)
					myfile << "\t\t\\---" << branch->duplicates[x]->SN << "\n|";
			}
			
		}
		else cout << "Unable to open file";
		writeToFile(branch->right_child, myfile);
	}
}

shared_ptr<BST_NODE>& Dump_BST::insert(const string & dev, const string & x, shared_ptr<BST_NODE>& branch)
{
	string device = dev,slave="", serials=x, sn;
	while ((serials.find_first_of(" ") != std::string::npos && serials[serials.find_first_of(" ")+1]==',') || serials.back()==' ')
	{
		int j = serials.find(" ");
		serials.erase(j, 1);
	}
	sn = serials.substr(0, serials.find(","));
	if (branch == 0)
	{
		branch = make_shared<BST_NODE>(device, sn,"");
		serials = serials.substr(sn.length());
		if (serials[0] == ',')
			serials = serials.substr(1);
			if (serials != "") {		
				if (serials.find_first_of(",") == std::string::npos)
				{
					//int error = insertSlave(dev, serials, branch->slaves);
					if(serials==sn)
						branch->duplicates.push_back(make_shared<BST_NODE>(dev, serials, ""));
					else
						branch->slaves.push_back(make_shared<BST_NODE>(dev, serials, ""));
				}
				else {
					do
					{

						slave = serials.substr(0, serials.find(","));
						serials = serials.substr(slave.length());
						if (serials[0] == ',')
							serials = serials.substr(1);


						for (int x = 0; x < branch->slaves.size();x++)
							if(slave==branch->slaves[x]->SN)
								branch->duplicates.push_back(make_shared<BST_NODE>(dev, slave, ""));
							else
								branch->slaves.push_back(make_shared<BST_NODE>(dev, slave, ""));

	
					} while (serials != "");
					quicksort(branch->slaves, 0, branch->slaves.size());
					quicksort(branch->duplicates, 0, branch->duplicates.size());
				}
			}
			return branch;
		}

	
	else {
		if (branch->device > device && branch->device != device)
		{
			return insert(dev, serials, branch->left_child);
			
		}
		else if (branch->device < device && branch->device != device)
		{
			return insert(dev, serials, branch->right_child);
			
		}
		else
		{
			cout << "No Dupes masters!\t " << dev << " " << serials << "\n";
			return branch;
		}
	}
}







shared_ptr<BST_NODE>& Dump_BST::insert(shared_ptr<BST_NODE>& node, shared_ptr<BST_NODE>& branch)
{
	if (branch == 0)
	{
		return branch = node;
		
	}


	else {
		if (branch->device > node->device && branch->device != node->device)
		{
			return insert(node, branch->left_child);

		}
		else if (branch->device < node->device && branch->device != node->device)
		{
			return insert(node, branch->right_child);
	
		}
		else
		{
			cout << "No Dupes nodes!\n";
			return branch;
		}
	}
}




shared_ptr<BST_NODE>& Dump_BST::search(const string & x, shared_ptr<BST_NODE>& branch)
{

	if (branch == 0)
	{
		cout << "Leaf Reached!\n";
		return branch;
	}
	else {
		if (branch->device > x)
			return search(x, branch->left_child);
		else if (branch->device < x)
			return search(x, branch->right_child);
		else if (branch->device == x)
		{
			return branch;
		}
	}

	return root;
}

shared_ptr<BST_NODE> Dump_BST::inorder_succ(const shared_ptr<BST_NODE>& loc_ptr)
{
	shared_ptr<BST_NODE> ptr = loc_ptr->right_child;

	while (ptr->left_child != 0)
	{
		ptr = ptr->left_child;
	}

	return ptr;
}

void Dump_BST::remove(const string & x, shared_ptr<BST_NODE>&branch)
{
	//string lastname, firstname, tmp = x;
	//lastname = tmp.substr(0, x.find(" "));
	//tmp.erase(0, tmp.find(" ") + 1);
	//firstname = tmp.substr(0, x.find(" ") + 1);
	//if (branch == 0)
	//{

	//}
	//else if (branch->last_name > lastname)// value to delete is less than the value store in the root 
	//{
	//	remove(x, branch->left_child);
	//}
	//else if (branch->last_name < lastname) // value to delete is greater than the value store in the root
	//{
	//	remove(x, branch->right_child);
	//}
	//else if (branch->first_name == firstname)  //value to delete is equal to the value store in the root
	//{
	//	BST_NODE *ptr;

	//	if (branch->left_child == 0)  //node has  1 child which is the rchild
	//	{
	//		ptr = branch->right_child;
	//		delete branch;
	//		branch = ptr;
	//	}
	//	else if (branch->right_child == 0)  //node has 1 child which is the lchild 
	//	{
	//		ptr = branch->left_child;
	//		delete branch;
	//		branch = ptr;
	//	}
	//	else   //node has 2 children; non-trivial; recursion coming into play
	//	{
	//		ptr = inorder_succ(branch);
	//		branch->last_name = ptr->last_name;
	//		branch->first_name = ptr->first_name;
	//		branch->address = ptr->address;
	//		branch->phone_number = ptr->phone_number;
	//		branch->s = ptr->s;
	//		remove(ptr->s, branch);
	//	}
	//}
}

void Dump_BST::Update(const string & x)
{
	char y = x[0];
	string tmp = x;
	string lastname, firstname, address, phonenumber, s;
	string newlastname, newfirstname, newaddress, newphonenumber;
	tmp.erase(0, 2);

}


void Dump_BST::copy(shared_ptr<BST_NODE>& root, const shared_ptr<BST_NODE>& copyN)
{
	/*if (copyN != 0)
	{
		root = new BST_NODE(copyN->first_name, copyN->last_name, copyN->address, copyN->phone_number);
		copy(root->left_child, copyN->left_child);
		copy(root->right_child, copyN->right_child);
	}*/
}




int Dump_BST::partition(vector<shared_ptr<BST_NODE>> &B, int p, int r)
{
	string x = B[r]->get_SN();
	int i = p - 1;

	for (int j = p; j <= r - 1; j++)
	{
		if (B[j]->get_SN() <= x)
		{
			i++;
			shared_ptr<BST_NODE> temp = B[j];
			B[j] = B[i];
			B[i] = temp;
		}

	}
	shared_ptr<BST_NODE> temp = B[r];
	B[r] = B[i + 1];
	B[i + 1] = temp;
	return i + 1;
}

void Dump_BST::quicksort(vector<shared_ptr<BST_NODE>> &B, int p, int r)
{
	if (p<r)
	{
		int q = partition(B, p, r);
		quicksort(B, p, q - 1);
		quicksort(B, q + 1, r);
	}
}