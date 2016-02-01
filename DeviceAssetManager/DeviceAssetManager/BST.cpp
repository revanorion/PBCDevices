#include "BST.h"
void Dump_BST::print(BST_NODE* branch)
{
	if (branch != 0)
	{
		print(branch->left_child);
		//cout << branch->device << endl;
		cout <<"|\t"<< branch->SN<<" "<<branch->asset;
		cout << endl;
		if (branch->slaves != 0)
			print(branch->slaves);
		print(branch->right_child);
	}
}

void Dump_BST::printNode(BST_NODE* branch)
{
	if (branch != 0)
	{
		
		cout << branch->device << endl;
		cout << "| Master\t" << branch->SN << " " << branch->asset;
		cout << endl;
		if (branch->slaves != 0)
			print(branch->slaves);
		
	}
}


//MODIFY
void Dump_BST::writeToFile(BST_NODE* branch, const string & filename)
{
	if (branch != 0)
	{
		writeToFile(branch->left_child, filename);

		ofstream myfile;
		myfile.open(filename, ios::out | ios::app);
		if (myfile.is_open())
		{
			//myfile << branch->s << "\n";
		}
		else cout << "Unable to open file";
		writeToFile(branch->right_child, filename);
	}
}



void Dump_BST::insert(const string & dev, const string & x, BST_NODE * & branch)
{

	
	
	string device = dev,slave="", serials=x, sn;

	while ((serials.find_first_of(" ") != std::string::npos && serials[serials.find_first_of(" ")+1]==',') || serials.back()==' ')
	{
		int j = serials.find(" ");
		cout << "last char is " << serials[serials.length()]<<" done\n";
		serials.erase(j, 1);
	}

	sn = serials.substr(0, x.find(","));
	//serials.
	int length = sn.length();
	
	if (branch == 0)
	{
		branch = new BST_NODE(device, sn,"");
	}
	else {
		if (branch->device > device && branch->device != device)
			insert(dev, serials, branch->left_child);
		else if (branch->device < device && branch->device != device)
			insert(dev, serials, branch->right_child);
		else
			cout << "No Dupes masters!\t "<<dev<<" "<< serials << "\n";
	}
	//out of bounds
	try {
		if (serials.find_first_of(",") != std::string::npos) {
			do
			{
				slave = serials.substr(length + 1);// ;
				slave = slave.substr(0, serials.find(","));

				if (slave.find(",") != std::string::npos)
					throw 10;
				insertSlave(dev, slave, branch->slaves);
				length += slave.length() + 1;
			} while (length < serials.length());
		}
	}
	catch (int e)
	{
		cout << "Error!\n";
	}
	cout << "Complete!\n";
	printNode(branch);
}

void Dump_BST::insertSlave(const string & dev, const string & x, BST_NODE * & branch)
{

	string device = dev, sn = x;
	if (sn != "") {
		if (branch == 0)
		{
			branch = new BST_NODE(device, sn, "");
		}
		else {
			if (branch->SN > sn && branch->SN != sn)
				insertSlave(dev, x, branch->left_child);
			else if (branch->SN < sn && branch->SN != sn)
				insertSlave(dev, x, branch->right_child);
			else
				cout << "No Dupes slaves!\t " << dev << " " << x << "\n";
		}
	}
}





BST_NODE *& Dump_BST::search(const string & x, BST_NODE * branch)
{
	/*string lastname, firstname;
	lastname = x.substr(0, x.find(" "));
	firstname = firstname = x.substr(lastname.length() + 1, x.find(" ", lastname.length() + 1) - (lastname.length() + 1));
	if (branch == 0)
	{
		cout << "Leaf Reached!\n";
		return branch;
	}
	else {
		if (branch->last_name > lastname)
			return search(x, branch->left_child);
		else if (branch->last_name < lastname)
			return search(x, branch->right_child);
		else if (branch->first_name == firstname)
		{
			if (x == branch->s)
			{
				cout << "Really found it\n";
			}
			cout << "FOUND IT!\n";
			return branch;
		}
	}*/
	return root;
}

void Dump_BST::del(BST_NODE *& branch)
{
	if (branch != 0)
	{
		BST_NODE *ptr;

		if (branch->left_child == 0)  //node has  1 child which is the rchild
		{
			ptr = branch->right_child;
			delete branch;
			branch = ptr;
		}
		else if (branch->right_child == 0)  //node has 1 child which is the lchild 
		{
			ptr = branch->left_child;
			delete branch;
			branch = ptr;
		}
		else   //node has 2 children; non-trivial; recursion coming into play
		{
			ptr = inorder_succ(branch);
			branch->device = ptr->device;
			branch->SN = ptr->SN;
		
			del(branch);
		}
	}

}

BST_NODE * Dump_BST::inorder_succ(BST_NODE * loc_ptr)
{
	BST_NODE * ptr = loc_ptr->right_child;

	while (ptr->left_child != 0)
	{
		ptr = ptr->left_child;
	}

	return ptr;
}

void Dump_BST::remove(const string & x, BST_NODE *&branch)
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


void Dump_BST::copy(BST_NODE *& root, const BST_NODE * copyN)
{
	/*if (copyN != 0)
	{
		root = new BST_NODE(copyN->first_name, copyN->last_name, copyN->address, copyN->phone_number);
		copy(root->left_child, copyN->left_child);
		copy(root->right_child, copyN->right_child);
	}*/
}