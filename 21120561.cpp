#include <iostream>
using namespace std;

struct NODE {
	int key;
	NODE* pLeft;
	NODE* pRight;
};

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

//1. Initialize a NODE from a given value:
NODE* createNode(int data)
{
	NODE* p_new = new NODE;
	p_new->key = data;
	p_new->pLeft = NULL;
	p_new->pRight = NULL;
	return p_new;
}

//2. Add a NODE with given value into a given Binary Search Tree:
void Insert(NODE*& pRoot, int x)
{
	if (pRoot == NULL)
	{
		NODE* newNODE = createNode(x);
		pRoot = newNODE;
		return;
	}
	if (pRoot->key < x)
		Insert(pRoot->pRight, x);
	else if (pRoot->key > x)
		Insert(pRoot->pLeft, x);
	else
		return;
}

//3. Pre - order Traversal :
void NLR(NODE* pRoot)
{
	if (pRoot == NULL)
		return;
	cout << pRoot->key << " ";
	NLR(pRoot->pLeft);
	NLR(pRoot->pRight);
}

//4. In - order Traversal :
void LNR(NODE* pRoot)
{
	if (pRoot == NULL)
		return;
	LNR(pRoot->pLeft);
	cout << pRoot->key << " ";
	LNR(pRoot->pRight);
}

//5. Post - order Traversal :
void LRN(NODE* pRoot)
{
	if (pRoot == NULL)
		return;
	LRN(pRoot->pLeft);
	LRN(pRoot->pRight);
	cout << pRoot->key << " ";
}

//7. Calculate the height of a given Binary Tree;
// Tính chiều cao dựa vào số Node
int Height(NODE* pRoot)
{
	if (pRoot == NULL)
		return 0;
	int left = Height(pRoot->pLeft);
	int right = Height(pRoot->pRight);
	return max(left, right) + 1;
}

//6. Level-order Traversal:
void printLevel(NODE* pRoot, int level)
{
	if (pRoot == NULL)
		return;
	if (level == 1)
	{
		cout << pRoot->key << " ";
		return;
	}
	printLevel(pRoot->pLeft, level - 1);
	printLevel(pRoot->pRight, level - 1);

}

void LevelOrder(NODE* pRoot)
{
	if (pRoot == NULL)
		return;
	int height = Height(pRoot);
	for (int i = 1; i <= height; i++)
	{
		printLevel(pRoot, i);
	}
}

//8. Count the number of NODE from a given Binary Tree :
int countNode(NODE* pRoot)
{
	if (pRoot == NULL)
		return 0;
	int cur = 0;
	cur = 1;
	int left = countNode(pRoot->pLeft);
	int right = countNode(pRoot->pRight);
	return left + right + cur;
}

//9. Calculate the total value of all NODEs from a given Binary Tree:
int sumNode(NODE* pRoot)
{
	if (pRoot == NULL)
		return 0;
	int cur = pRoot->key;
	int left = sumNode(pRoot->pLeft);
	int right = sumNode(pRoot->pRight);
	return cur + left + right;
}

//10. Find and return a NODE with given value from a given Binary Search Tree:
NODE* Search(NODE* pRoot, int x)
{
	if (pRoot == NULL)
		return NULL;
	if (pRoot->key == x)
		return pRoot;
	if (pRoot->key > x)
		return Search(pRoot->pLeft, x);
	else
		return Search(pRoot->pRight, x);
}

//11. Remove a NODE with given value from a given Binary Search Tree:
NODE* maxNodeBST(NODE* pRoot)
{
	if (pRoot->pRight == NULL)
		return pRoot;
	return maxNodeBST(pRoot->pRight);
}

void Remove(NODE*& pRoot, int x)
{
	if (pRoot == NULL)
		return;
	if (x < pRoot->key)
		Remove(pRoot->pLeft, x);
	else if (x > pRoot->key)
		Remove(pRoot->pRight, x);
	else
	{
		if (pRoot->pLeft == NULL && pRoot->pRight == NULL)
		{
			pRoot = NULL;
		}
		else if (pRoot->pLeft != NULL && pRoot->pRight == NULL)
		{
			pRoot = pRoot->pLeft;
		}
		else if (pRoot->pLeft == NULL && pRoot->pRight != NULL)
		{
			pRoot = pRoot->pRight;
		}
		else
		{
			NODE* pTemp = maxNodeBST(pRoot->pLeft);
			pRoot->key = pTemp->key;
			Remove(pRoot->pLeft, pTemp->key);
		}

	}
}

//12. Initialize a Binary Search Tree from a given array:
NODE* createTree(int a[], int n)
{
	NODE* pRoot = new NODE;
	pRoot = NULL;
	for (int i = 0; i < n; i++)
	{
		Insert(pRoot, a[i]);
	}
	return pRoot;
}

//13. Completely remove a given Binary Search Tree:
void removeTree(NODE*& pRoot)
{
	if (pRoot == NULL)
		return;
	removeTree(pRoot->pLeft);
	removeTree(pRoot->pRight);
	delete pRoot;
}

//14. Calculate the height of a NODE with given value: (return -1 if value not exist)
//Tinh theo so Node
void heightNodeTemp(NODE* pRoot, int value, int& height)
{
	if (pRoot == NULL)
		return;
	if (value == pRoot->key)
	{
		height = Height(pRoot);
		return;
	}
	heightNodeTemp(pRoot->pLeft, value, height);
	heightNodeTemp(pRoot->pRight, value, height);

}

int heightNode(NODE* pRoot, int value)
{
	int height = -1;
	heightNodeTemp(pRoot, value, height);
	return height;
	
}

//15. * Calculate the level of a given NODE:
void Leveltemp(NODE* pRoot, NODE* p, int level, int &result)
{
	if (pRoot == NULL)
		return;
	if (pRoot == p)
	{
		result = level;
		return;
	}
	Leveltemp(pRoot->pLeft, p, level + 1, result);
	Leveltemp(pRoot->pRight, p, level + 1, result);
}

int Level(NODE* pRoot, NODE* p)
{
	int level = 0;
	int result = 0;
	Leveltemp(pRoot, p, level, result);
	return result;
}

//16. * Count the number leaves from a given Binary Tree:
int countLeaf(NODE* pRoot)
{
	if (pRoot == NULL)
		return 0;
	int c = 0;
	if (pRoot->pLeft == NULL && pRoot->pRight == NULL)
	{
		c = c + 1;
	}
	int left = countLeaf(pRoot->pLeft);
	int right = countLeaf(pRoot->pRight);
	return left + right + c;
}

//17. * Count the number of NODE from a given Binary Search Tree which key value is less than a given
//value :
int countLess(NODE* pRoot, int x)
{
	if (pRoot == NULL)
		return 0;
	int c = 0;
	if (pRoot->key < x)
		c++;
	int left = countLess(pRoot->pLeft, x);
	int right = countLess(pRoot->pRight, x);
	return left + right + c;
}

/*18. * Count the number of NODE from a given Binary Search Tree which key value is greater than a
given value*/
int countGreater(NODE* pRoot, int x)
{
	if (pRoot == NULL)
		return 0;
	int c = 0;
	if (pRoot->key > x)
		c++;
	int left = countGreater(pRoot->pLeft, x);
	int right = countGreater(pRoot->pRight, x);
	return left + right + c;
}

//19. Determine if a given Binary Tree is Binary Search Tree:
int minOfTree(NODE* pRoot)
{
	while (pRoot->pLeft != NULL)
		pRoot = pRoot->pLeft;
	return pRoot->key;
}

int maxOfTree(NODE* pRoot)
{
	while (pRoot->pRight != NULL)
		pRoot = pRoot->pRight;
	return pRoot->key;
}

bool isBST(NODE* pRoot)
{
	if (pRoot == NULL)
		return true;
	if ((pRoot->pLeft != NULL && (maxOfTree(pRoot->pLeft) > pRoot->key)) || (pRoot->pRight != NULL && (minOfTree(pRoot->pRight) < pRoot->key)))
		return false;
	return isBST(pRoot->pLeft) && isBST(pRoot->pRight);
}

//20.Determine if a given Binary Tree is a Full Binary Search Tree

bool isFullTree(NODE* pRoot)
{
	if (pRoot == NULL)
		return true;
	if (pRoot->pLeft == NULL && pRoot->pRight != NULL)
		return false;
	if (pRoot->pLeft != NULL && pRoot->pRight == NULL)
		return false;
	return isFullTree(pRoot->pLeft) && isFullTree(pRoot->pRight);
}

bool isFullBST(NODE* pRoot)
{
	return isFullTree(pRoot) && isBST(pRoot);
}

int main()
{
	// Test case
	NODE* pRoot = new NODE;
	pRoot = NULL;
	int a[9] = { 33, 14, 15, 92, 64, 35, 95, 10, 72};
	pRoot = createTree(a, 9);
	LNR(pRoot);
	
	

}