#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "BST.h"
class HashTable
{
public:

	HashTable(); //default constructor will read data from input file "client_address_data.txt".
	HashTable(const HashTable &);//Copy Constructor

	~HashTable() { delete[]hash_table; };
	void insert(const string & x, const string & y) { hash_table[hash(x)].insert(x, y); };
	void remove() {};
	int inline hash(const string & x) { if (x[0] < 96) return 0; else return x[0] - 96; };
	void Print_Hash_Table() { for (int x = 1; x < 27; x++) hash_table[x].print(); };
	void inline Update(const string & x) { hash_table[hash(x.substr(2))].Update(x); };

	void Print_BST(const string & s) { hash_table[hash(s)].print(); };//Print a BST (cell in hash table) inorder to the screen      

	void Print_Hash_Table_to_File(const string & filename);	//function will print hash table to output file                             
private:

	Dump_BST *hash_table;
};


#endif
HashTable::HashTable()
{
	hash_table = new Dump_BST[27];
	
}
HashTable::HashTable(const HashTable & y)
{
	hash_table = new Dump_BST[27];
	for (int x = 1; x < 27; x++);
		//hash_table[x].copy(hash_table[x].root, y.hash_table[x].root);
}


void HashTable::Print_Hash_Table_to_File(const string & filename) {
	for (int x = 1; x < 27; x++)
		hash_table[x].writeToFile(filename);
}