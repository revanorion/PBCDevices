#pragma once
#ifndef SerialBST_H
#define SerialBST_H
#include "BST.h"

class Serial_NODE
{
public:
	Serial_NODE() :right_child(0), left_child(0), parent(0) {  };
	Serial_NODE(const string & sn,const string & dev,shared_ptr<BST_NODE>& p)
		: SN(sn), right_child(0), left_child(0), parent(p),device(dev) {};

	shared_ptr<Serial_NODE>& get_left_child() { return left_child; };
	shared_ptr<Serial_NODE>& get_right_child() { return right_child; };
	shared_ptr<BST_NODE>& get_dump_parent() { return parent; };
	string & get_SN() { return SN; };
	string & get_device() { return device; };
	~Serial_NODE() {
		cout << "Deleting serial: " << SN << endl;
	};
	friend class Serial_BST;


private:
	shared_ptr<Serial_NODE> right_child;
	shared_ptr<Serial_NODE> left_child;
	shared_ptr<BST_NODE> parent;
	string SN;
	string device;
};





class Serial_BST
{



public:
	Serial_BST() :root(0) { if (rowNumber == NULL || colomnNumber == NULL) rowNumber = colomnNumber = 1; };
	Serial_BST(const Serial_BST &x) { if (x.root != 0) copy(root, x.root); };//Copy Constructor
	~Serial_BST() {  };//while (root != 0) { del(root); } };
	void insert(shared_ptr<Serial_NODE>& x) { insert(x, root); };
	shared_ptr<Serial_NODE>& insert(const string & s, const string & d, shared_ptr<BST_NODE>& x) { return insert(s,d, x, root); };
	shared_ptr<Serial_NODE>& search(const string & x) { return search(x, root); };
	void Print_Comparison_List_to_Excel(const string & filename);
	void remove(const string & x) { remove(x, root); };
	void Update(const string & s);//{ cout << "   Inside Client_Info_BST Update\n"; };
	void print() { print(root); cout << endl; };
	void writeToExcel(WorkBook^ book) { writeToExcel(root, book); };
	void del(const string & x) { del(search(x)); };
	void writeToFile(const string & filename) {
		ofstream myfile;
		myfile.open(filename, ios::out | ios::app);
		if (myfile.is_open())
		{
			writeToFile(root, myfile);
		}
	}

	void compare(shared_ptr<BST_NODE>&branch, vector<shared_ptr<BST_NODE>>&);
	friend class HashTable;
	static unsigned int rowNumber;
	static unsigned int colomnNumber;

private:
	shared_ptr<Serial_NODE> root;
	shared_ptr<Serial_NODE>& insert(const string &, const string &, shared_ptr<BST_NODE>&, shared_ptr<Serial_NODE>&);
	void insert(shared_ptr<Serial_NODE>&, shared_ptr<Serial_NODE>&);

	shared_ptr<Serial_NODE>& search(const string &, shared_ptr<Serial_NODE>&);
	void writeToFile(shared_ptr<Serial_NODE>&, ofstream&);
	void compare(shared_ptr<BST_NODE>&, shared_ptr<Serial_NODE>&, vector<shared_ptr<BST_NODE>>&);
	void compare_branch(shared_ptr<BST_NODE>&, shared_ptr<Serial_NODE>&, vector<shared_ptr<BST_NODE>>&);
	void remove(const string &, shared_ptr<Serial_NODE>&);
	void print(shared_ptr<Serial_NODE>&);
	void printNode(shared_ptr<Serial_NODE>&);
	void del(shared_ptr<Serial_NODE>&);
	shared_ptr<Serial_NODE> inorder_succ(const shared_ptr<Serial_NODE>& loc_ptr);
	void copy(shared_ptr<Serial_NODE>& root, const shared_ptr<Serial_NODE>& copyN);
	void writeToExcel(shared_ptr<Serial_NODE>& branch, WorkBook^ book);
	vector<shared_ptr<BST_NODE>> comparisionList;
};
#endif