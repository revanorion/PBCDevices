#ifndef ExcelBST
#define ExcelBST
#include "BST.h"

class Excel_BST : public virtual Dump_BST
{
public:
	Excel_BST() { if (rowNumber == NULL || colomnNumber == NULL) rowNumber = colomnNumber = 1; };
	~Excel_BST() {};
	void insert(shared_ptr<BST_NODE>& x) { insert(x, root); };
	void insert(shared_ptr<BST_NODE>& node, shared_ptr<BST_NODE>& branch);
	void writeToExcel(const string & filename);
	
	void print() { print(root); };
	static unsigned int rowNumber;
	static unsigned int colomnNumber;
private:
	
	void print(shared_ptr<BST_NODE>&);
	void writeToExcel(shared_ptr<BST_NODE>& branch, WorkBook^ book);
};
#endif