#include "ExcelBST.h"


unsigned int Excel_BST::rowNumber;
unsigned int Excel_BST::colomnNumber;


void Excel_BST::print(shared_ptr<BST_NODE>& branch)
{
	if (branch != 0)
	{
		print(branch->left_child);


		//cout << "Asset\tSerial\tDivison\tDescription\tModel\tAsset Type\tLocation\tOwner\tNotes\n";
		if (branch->db.Notes != "")
			cout << branch->asset << "\t" << branch->SN << "\t" << branch->db.ISS_Divison << "\t" << branch->db.Description << "\t" << branch->db.Model
			<< "\t" << branch->db.Asset_Type << "\t" << branch->db.Physical_Location << "\t" << branch->db.FATS_Owner << "\t" << branch->db.Notes << "\n\n";
		else
			cout << branch->SN << "\n\n";



		print(branch->right_child);
	}
}



void Excel_BST::insert(shared_ptr<BST_NODE>& node, shared_ptr<BST_NODE>& branch)
{
	if (branch == 0)
	{
		branch = node;

	}


	else {
		if (branch->asset > node->asset && branch->asset != node->asset)
		{
			insert(node, branch->left_child);
			return;
		}
		else if (branch->asset < node->asset && branch->asset != node->asset)
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

void Excel_BST::writeToExcel(const string & filename)
{
	WorkBook^ book = gcnew WorkBook();
	string file = filename;
	if (book) {
		
		this->writeToExcel(root,book);
	}

	if (file.find(".xls") == string::npos || file.substr(file.length() - 4) != ".xls")
		file += ".xls";

	book->write(gcnew System::String(file.c_str()));
}

void Excel_BST::writeToExcel(shared_ptr<BST_NODE>& branch, WorkBook ^ book)
{
	if (branch != 0 && book)
	{
		writeToExcel(branch->left_child, book);
		colomnNumber = 1;

		book->setText(rowNumber, colomnNumber, gcnew System::String(branch->device.c_str()));
		colomnNumber++;
		book->setText(rowNumber, colomnNumber, gcnew System::String(branch->asset.c_str()));
		colomnNumber++;
		book->setText(rowNumber, colomnNumber, gcnew System::String(branch->SN.c_str()));
		colomnNumber++;
		book->setText(rowNumber, colomnNumber, gcnew System::String(branch->db.Description.c_str()));
		
		rowNumber++;

		writeToExcel(branch->right_child, book);
	}
}




