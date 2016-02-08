#define _CRTDBG_MAP_ALLOC
#define _VARIADIC_MAX 10 
#include <stdlib.h>
#include <crtdbg.h>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct DATA {


};


class BST_NODE
{
public:
	BST_NODE() :right_child(0), left_child(0), slaves(0), duplicates(0) { cout << "Constructor"; };
	BST_NODE(const string & d, const string & sn, const string & a)
		:device(d), SN(sn), asset(a), right_child(0), left_child(0), slaves(0), duplicates(0) {};

	string & get_Device() { return device; };
	string & get_SN() { return SN; };
	string & get_Asset() { return asset; };
	DATA & get_data() { return db; };
	~BST_NODE() {
		
	};
	void set_sn(string s) { SN = s; };
	friend class Dump_BST;

private:
	shared_ptr<BST_NODE> right_child;
	shared_ptr<BST_NODE> left_child;
	shared_ptr<BST_NODE> duplicates;
	shared_ptr<BST_NODE> slaves;
	string device, SN, asset;
	DATA db;
};


class Dump_BST
{
public:
	Dump_BST() :root(0) {};
	//Dump_BST(const Dump_BST &x) { if (x.root != 0) copy(root, x.root); };//Copy Constructor
	~Dump_BST() { cout << "Deleted\n"; };//while (root != 0) { del(root); } };
	void insert(const string & dev, const string & x) { insert(dev, x, root); };
	//void insertSlave(const string & dev, const string & x) { insertSlave(dev, x, root); };
	//BST_NODE *& search(const string & x) { return search(x, root); };
	//void remove(const string & x) { remove(x, root); };
	//void Update(const string & s);//{ cout << "   Inside Client_Info_BST Update\n"; };
	//void print() { print(root); cout << endl; };
	//void del(const string & x) { del(search(x)); };
	//void writeToFile(const string & filename) {
	//	ofstream myfile;
	//	myfile.open(filename, ios::out | ios::app);
	//	if (myfile.is_open())
	//	{
	//		writeToFile(root, myfile);
	//	}
	//}


private:
	shared_ptr<BST_NODE>root;
	void insert(const string &, const string &, shared_ptr<BST_NODE>&);
	/*int insertSlave(const string &, const string &, BST_NODE *&);
	void insertDup(const string &, const string &, BST_NODE *&);
	BST_NODE *& search(const string &, BST_NODE *);
	void writeToFile(BST_NODE*, ofstream&);
	void writeToFileSD(BST_NODE*, ofstream&);
	void remove(const string &, BST_NODE *&);
	void print(BST_NODE*);
	void printSD(BST_NODE*);
	void printNode(BST_NODE*);
	void del(BST_NODE*&);
	BST_NODE *inorder_succ(BST_NODE * loc_ptr);
	void copy(BST_NODE *& root, const BST_NODE * copyN);*/
};

void Dump_BST::insert(const string & device, const string &serial, shared_ptr<BST_NODE> &root)
{
	if (root == 0)
	{
		root= make_shared<BST_NODE>(device,serial,"");
	}
	
	else if (root->device > device)
		insert(device, serial, root->left_child);
	else if (root->device < device)
		insert(device, serial, root->right_child);
	else
		cout << "Failed\n";

}

int main()
{
	shared_ptr<Dump_BST>tree(make_shared<Dump_BST>());
	tree->insert("dev1", "sn1");
	tree->insert("dev0", "sn0");
	tree->insert("dev2", "sn2");
	_CrtDumpMemoryLeaks();
	return 0;	
}