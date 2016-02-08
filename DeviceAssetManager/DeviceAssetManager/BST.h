#ifndef BST_H
#define BST_H
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "libxl.h"
using namespace libxl;
using namespace std;

struct DATA{


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
		cout << "Deleting device: " << device << " SN: " << SN << endl;
	};
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
	Dump_BST() :root(0){ if (rowNumber == NULL || colomnNumber == NULL) rowNumber = colomnNumber = 1; };
	Dump_BST(const Dump_BST &x) { if (x.root != 0) copy(root, x.root); };//Copy Constructor
	~Dump_BST() {  };//while (root != 0) { del(root); } };
	void insert(const string & dev, const string & x) { insert(dev, x, root); };
	void insertSlave(const string & dev, const string & x) { insertSlave(dev, x, root); };
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
	void writeToExcel(Book*& a, Sheet*& b)
	{
		if (a && b)
		{
			writeToExcel(root, a, b);
		}
	};
	friend class HashTable;
	static unsigned int rowNumber;
	static unsigned int colomnNumber;
private:
	
	shared_ptr<BST_NODE> root;
	void insert(const string &, const string &, shared_ptr<BST_NODE>&);
	int insertSlave(const string &, const string &, shared_ptr<BST_NODE>&);
	void insertDup(const string &, const string &, shared_ptr<BST_NODE>&);
	shared_ptr<BST_NODE>& search(const string &, shared_ptr<BST_NODE>&);
	void writeToFile(shared_ptr<BST_NODE>&, ofstream&);
	void writeToExcel(shared_ptr<BST_NODE>&, Book*&, Sheet*&);
	void writeToExcelSlave(shared_ptr<BST_NODE>&, Book*&, Sheet*&);
	void writeToFileSD(shared_ptr<BST_NODE>&, ofstream&);
	void remove(const string &, shared_ptr<BST_NODE>&);
	void print(shared_ptr<BST_NODE>&);
	void printSD(shared_ptr<BST_NODE>&);
	void printNode(shared_ptr<BST_NODE>&);
	void del(shared_ptr<BST_NODE>&);
	shared_ptr<BST_NODE> inorder_succ(const shared_ptr<BST_NODE>& loc_ptr);
	void copy(shared_ptr<BST_NODE>& root, const shared_ptr<BST_NODE>& copyN);
};


#endif