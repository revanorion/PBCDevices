#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "BST.h"
#include "SerialBST.h"
class HashTable
{
public:

	HashTable() { hash_table = new Dump_BST[27]; }; //default constructor will read data from input file "client_address_data.txt".
	HashTable(const HashTable &);//Copy Constructor

	~HashTable() { delete[]hash_table; };
	shared_ptr<BST_NODE>& insert(const string & x, const string & y) { return hash_table[hash(x)].insert(x, y);};
	void remove() {};
	int inline hash(const string & x) { if (x[0] < 96) return 0; else return x[0] - 96; };
	void Print_Hash_Table() { for (int x = 1; x < 27; x++) hash_table[x].print(); };
	void inline Update(const string & x) { hash_table[hash(x.substr(2))].Update(x); };
	void read_tool_text(const string & s);
	void Print_Serials() { serialList.print(); };
	void Print_BST(const string & s) { hash_table[hash(s)].print(); };//Print a BST (cell in hash table) inorder to the screen      
	void compare(shared_ptr<BST_NODE>&branch, vector<shared_ptr<BST_NODE>>&);
	void Print_Hash_Table_to_File(const string & filename) {	for (int x = 0; x < 27; x++)	hash_table[x].writeToFile(filename);	};	//function will print hash table to output file         
	void Print_Serial_list_to_File(const string & filename) { 	serialList.writeToFile(filename); };
	void Print_Hash_Table_to_Excel(const string & filename);
private:
	void compare(shared_ptr<BST_NODE>&, shared_ptr<Serial_NODE>&, vector<shared_ptr<BST_NODE>>&);
	void compare_branch(shared_ptr<BST_NODE>&, shared_ptr<Serial_NODE>&, vector<shared_ptr<BST_NODE>>&);
	Dump_BST *hash_table;
	Serial_BST serialList;
};


#endif
