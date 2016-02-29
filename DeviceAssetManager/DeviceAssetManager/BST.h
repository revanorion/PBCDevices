#ifndef BST_H
#define BST_H
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#using <SX.dll>
#include <msclr\marshal_cppstd.h>


using namespace SmartXLS;
using namespace std;

struct DATA {
	string ISS_Divison;
	string Description;
	string Model;
	string Asset_Type;
	string Physical_Location;
	string FATS_Owner;
	string Notes;
};





class BST_NODE
{
public:
	BST_NODE() :right_child(0), left_child(0), slaves(0), duplicates(0), excel_link(0), hash_link(0) { cout << "Constructor"; };
	BST_NODE(const string & d, const string & sn, const string & a)
		:device(d), SN(sn), asset(a), right_child(0), left_child(0), slaves(0), duplicates(0),excel_link(0),hash_link(0) {};

	string & get_Device() { return device; };
	string & get_SN() { return SN; };
	string & get_Asset() { return asset; };
	DATA & get_Data() { return db; };
	vector<shared_ptr<BST_NODE>> & get_slaves() { return slaves; };
	shared_ptr<BST_NODE>& get_left_child() { return left_child; };
	shared_ptr<BST_NODE>& get_right_child() { return right_child; };
	shared_ptr<BST_NODE>& get_excel_link() { return excel_link; };
	void set_excel_link(shared_ptr<BST_NODE>& link) { excel_link = link; };
	shared_ptr<BST_NODE>& get_hash_link() { return hash_link; };
	void set_hash_link(shared_ptr<BST_NODE>& link) { hash_link = link; };
	DATA & get_data() { return db; };
	~BST_NODE() {
		cout << "Deleting device: " << device << "\tSN: " << SN <<"\tAsset: "<<asset<< endl;
	};
	friend class Dump_BST;
	friend class Excel_BST;
	friend class TroposCSV_BST;

private:
	shared_ptr<BST_NODE> right_child;
	shared_ptr<BST_NODE> left_child;
	vector<shared_ptr<BST_NODE>> duplicates;
	vector<shared_ptr<BST_NODE>> slaves;
	shared_ptr<BST_NODE> excel_link;
	shared_ptr<BST_NODE> hash_link;
	string device, SN, asset;
	DATA db;
};




class Dump_BST
{
protected:

	shared_ptr<BST_NODE> root;
	shared_ptr<BST_NODE>& insert(const string &, const string &, shared_ptr<BST_NODE>&);
	shared_ptr<BST_NODE>& insert(shared_ptr<BST_NODE>&, shared_ptr<BST_NODE>&);
	shared_ptr<BST_NODE>& search(const string &, shared_ptr<BST_NODE>&);
	void writeToFile(shared_ptr<BST_NODE>&, ofstream&);
	void writeToExcel(shared_ptr<BST_NODE>&, WorkBook^);
	int partition(vector<shared_ptr<BST_NODE>> &B, int p, int r);
	void quicksort(vector<shared_ptr<BST_NODE>> &B, int p, int r);
	void remove(const string &, shared_ptr<BST_NODE>&);
	void print(shared_ptr<BST_NODE>&);
	void printNode(shared_ptr<BST_NODE>&);
	void del(shared_ptr<BST_NODE>&);
	shared_ptr<BST_NODE> inorder_succ(const shared_ptr<BST_NODE>& loc_ptr);
	void copy(shared_ptr<BST_NODE>& root, const shared_ptr<BST_NODE>& copyN);




public:
	Dump_BST() :root(0) { if (rowNumber == NULL || colomnNumber == NULL) rowNumber = colomnNumber = 1; };
	Dump_BST(const Dump_BST &x) { if (x.root != 0) copy(root, x.root); };//Copy Constructor
	~Dump_BST() {  };//while (root != 0) { del(root); } };
	shared_ptr<BST_NODE>& insert(shared_ptr<BST_NODE>& x) { return insert(x, root); };
	shared_ptr<BST_NODE>& insert(const string & dev, const string & x) { return insert(dev, x, root); };
	shared_ptr<BST_NODE>& get_root() { return root; };

	shared_ptr<BST_NODE>& search(const string & x) { return search(x, root); };
	void remove(const string & x) { remove(x, root); };
	void Update(const string & s);//{ cout << "   Inside Client_Info_BST Update\n"; };
	void print() { print(root); cout << endl; };
	void del(const string & x) { del(search(x)); };
	void writeToFile(const string & filename) {
		ofstream myfile;
		myfile.open(filename, ios::out | ios::app);
		if (myfile.is_open())
		{
			writeToFile(root, myfile);
		}
	}
	void writeToExcel(WorkBook^ a)
	{
		if (a)
		{
			writeToExcel(root, a);
		}
	};
	friend class HashTable;
	static unsigned int rowNumber;
	static unsigned int colomnNumber;


};



#endif