#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "BST.h"
#include "SerialBST.h"
class HashTable
{
public:

	HashTable() { hash_table = new Dump_BST[27]; serialList=make_shared<Serial_BST>(); }; //default constructor will read data from input file "client_address_data.txt".
	HashTable(const HashTable &);//Copy Constructor

	~HashTable() { delete[]hash_table; };
	shared_ptr<BST_NODE>& insert(const string & x, const string & y) { return hash_table[hash(x)].insert(x, y);};
	void remove() {};
	int inline hash(const string & x) { if (x[0] < 96) return 0; else return x[0] - 96; };
	void Print_Hash_Table() { for (int x = 1; x < 27; x++) hash_table[x].print(); };
	void inline Update(const string & x) { hash_table[hash(x.substr(2))].Update(x); };
	void read_tool_text(const string & s);
	void Print_Serials() { serialList->print(); };
	void Print_BST(const string & s) { hash_table[hash(s)].print(); };//Print a BST (cell in hash table) inorder to the screen      
	void compare(shared_ptr<BST_NODE>&branch, vector<shared_ptr<BST_NODE>>&);
	void Print_Hash_Table_to_File(const string & filename) {	for (int x = 0; x < 27; x++)	hash_table[x].writeToFile(filename);	};	//function will print hash table to output file         
	void Print_Serial_list_to_File(const string & filename) { 	serialList->writeToFile(filename); };
	void Print_Hash_Table_to_Excel(const string & filename);
	void Print_Comparison_List_to_Excel(const string & filename);
	void Print_serials_to_Excel(const string & filename);
	shared_ptr<BST_NODE>& search_by_device(const string & y) { return search_by_device(hash(y), y); };
	void set_comparison_list(vector<shared_ptr<BST_NODE>>& x) { comparisionList = x; };
private:
	void compare(shared_ptr<BST_NODE>&, shared_ptr<Serial_NODE>&, vector<shared_ptr<BST_NODE>>&);
	void compare_branch(shared_ptr<BST_NODE>&, shared_ptr<Serial_NODE>&, vector<shared_ptr<BST_NODE>>&);
	shared_ptr<BST_NODE>& search_by_device(const int & x, const string & y) { return hash_table[x].search(y); };
	Dump_BST *hash_table;
	shared_ptr<Serial_BST> serialList;
	vector<shared_ptr<BST_NODE>> comparisionList;
};


#endif
