#include "Trees.h"

TreeNode* createNewTreenode(char* name, unsigned short insId, TreeNode* left, TreeNode* right)
{
	/*
	This function creates a new tree node with the data given
	*/
	TreeNode* newNode;
	newNode = (TreeNode*)malloc(sizeof(TreeNode));
	checkMalloc(newNode);
	newNode->instrument = strdup(name);
	newNode->insId = insId;
	newNode->left = left;
	newNode->right = right;

	return newNode;
}

void printTreeLDR(InstrumentTree* tr)
{
	/*
	This function warps one that prints the tree in order
	*/
	printLDRHeldper(tr->root);
}

void printLDRHeldper(TreeNode* node)
{
	/*
	This function prints the tree in order
	*/
	if (node == NULL)
	{
		return;
	}
	else
	{
		printLDRHeldper(node->left);
		printf("Name: %s | ID: %u\n", node->instrument, node->insId);
		printLDRHeldper(node->right);
	}
}

void freeTree(InstrumentTree* tr)
{
	/*
	This function warps one that frees the tree
	*/
	freeTreeHelper(tr->root);
}

void freeTreeHelper(TreeNode* root)
{
	/*
	This function frees the root and his descendants
	*/
	if (root == NULL)
	{
		return;
	}
	else
	{
		freeTreeHelper(root->left);
		freeTreeHelper(root->right);
		free(root->instrument);
		free(root);
	}
}

int findInsId(InstrumentTree tree, char* instrument)
{
	//this function finds the id of a given instrument
	int res;
	res = findInsIdHelper(tree.root, instrument);
	return res;
}

int findInsIdHelper(TreeNode* root, char* instrument)
{
	/*
	Thus function finds the node with the same name as instrument and returns its id
	or NOT_FOUND if we didn't find it
	*/
	int res;
	if (root == NULL)
	{
		res = NOT_FOUND;
	}
	else
	{
		if (strcmp(root->instrument, instrument) == 0)
		{
			res = root->insId;
		}
		else if (strcmp(root->instrument, instrument) > 0)
		{
			res = findInsIdHelper(root->left, instrument);
		}
		else
		{
			res = findInsIdHelper(root->right, instrument);
		}
	}
	return res;
}

void makeEmptyTree(InstrumentTree* tr)
{
	/*
	create a new tree
	*/
	tr->root = NULL;
}

InstrumentTree getDataFromFileToTree(char* fileName, int* numOfInst)
{
	/*
	This function gets a filename and puts its data in a tree
	*/
	int counter = 0;
	InstrumentTree tr;
	TreeNode* node;
	char line[MAX_LINE_LEN];
	FILE* fInst;
	int endOfInput = TRUE;

	fInst = fopen(fileName, "r");
	openFilesCheck(fInst);
	makeEmptyTree(&tr);

	while (endOfInput == TRUE)
	{
		endOfInput = fscanf(fInst, "%s\n", line);
		if (endOfInput == TRUE)
		{
			node = createNewTreenode(line, counter, NULL, NULL);
			tr.root = putNodeInTree(tr.root, node);
			counter++;
		}
	}
	fclose(fInst);
	*numOfInst = counter;
	return tr;
}

TreeNode* putNodeInTree(TreeNode* root, TreeNode* node)
{
	TreeNode* curr = root;
	int compare = 0;

	if (root == NULL)
	{
		root = node;
	}
	else
	{
		while (curr != NULL)
		{
			compare = strcmp(node->instrument, curr->instrument);
			if (compare > 0)
			{
				if (curr->right == NULL)
				{
					curr->right = node;
					curr = NULL;
				}
				else
					curr = curr->right;
			}
			else
			{
				if (curr->left == NULL)
				{
					curr->left = node;
					curr = NULL;
				}
				else
					curr = curr->left;
			}
		}
	}
	return root;
}

char* insIdToName(short int insid, InstrumentTree tr)
{
	/*
	This functions wraps an function that gets an id of an istruments and returns its name.
	*/
	char* res;
	res = insIdToNameHelper(insid, tr.root);
	return res;
}

char* insIdToNameHelper(short int insid, TreeNode* root)
{
	/*
	This functin gets an id of an istruments and returns its name.
	*/
	char* left, * right;
	if (root == NULL)
		return NULL;
	else
	{
		if (insid == root->insId)
			return root->instrument;
		else
		{
			right = insIdToNameHelper(insid, root->right);
			left = insIdToNameHelper(insid, root->left);
			if (right != NULL)
				return right;
			else if (left != NULL)
				return left;
			else
				return NULL;
		}
	}
}

