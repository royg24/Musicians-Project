#ifndef TREES_H
#define TREES_H

typedef struct treeNode {
	char* instrument; // name of instrument
	unsigned short insId; // ID of the instrument
	struct treeNode* left;
	struct treeNode* right;
}TreeNode;


typedef struct tree {
	TreeNode* root;
}InstrumentTree;

#include "General.h"

//creat new node for an InstrumentTree
TreeNode* createNewTreenode(char* name, unsigned short insId, TreeNode* left, TreeNode* right);

//print the tree in order
void printTreeLDR(InstrumentTree* tr);
void printLDRHeldper(TreeNode* node);

//free the tree
void freeTree (InstrumentTree* tr);
void freeTreeHelper(TreeNode* root);


//get an instrument and returen the id of the istrument
int findInsId(InstrumentTree tree,char* instrument); //part 2
int findInsIdHelper(TreeNode* root, char* instrument);

//create an empty tree
void makeEmptyTree(InstrumentTree* tr);

//get data from file to tree
InstrumentTree getDataFromFileToTree(char* fileName, int* numOfInst);

//put node in its right place in the tree
TreeNode* putNodeInTree(TreeNode* root, TreeNode* node);

//find the father of our new node
TreeNode* findPlace(TreeNode* root,TreeNode* node);

//checks if the node should be the left child or the right child
//and puts it
TreeNode* placeToPut(TreeNode* father, TreeNode* node);

//search for the name of instrument according to its id
char* insIdToName(short int insid, InstrumentTree tr);
char* insIdToNameHelper(short int insid, TreeNode* root);

#endif // !TREES_H
