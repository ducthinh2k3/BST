#include <iostream>
using namespace std;
#define COUNT 10

struct NODE {
	int key;
	NODE* pLeft;
	NODE* pRight;
	int height;
};

int Weight(NODE*& pRoot)
{
	return Height(pRoot->pLeft) - Height(pRoot->pRight);
}

//1. Initialize a node with key is a given value:
NODE* createNode(int data)
{
	NODE* p = new NODE;
	p->height = 0;
	p->pLeft = NULL;
	p->pRight = NULL;
	p->key = data;
	return p;
}

//2. Add a node with given value x into a given AVL tree (Notify if the given value existed):
void rotateLeft(NODE*& pRoot)
{
	NODE* b = pRoot->pRight;
	NODE* T2 = b->pLeft;
	b->pLeft = pRoot;
	pRoot->pRight = T2;
	pRoot = b;

}

void rotateRight(NODE*& pRoot)
{
	NODE* b = pRoot->pLeft;
	NODE* T2 = b->pRight;
	b->pRight = pRoot;
	pRoot->pLeft = T2;
	pRoot->height = Weight(pRoot);
	b->height = Weight(b);
	pRoot = b;
	
}

void rotateLeftRight(NODE*& pRoot)
{
	rotateLeft(pRoot->pLeft);
	rotateRight(pRoot);
}

void rotateRightLeft(NODE*& pRoot)
{
	rotateRight(pRoot->pRight);
	rotateLeft(pRoot);
}

int Height(NODE* pRoot)
{
	if (pRoot == NULL)
		return 0;
	int left = Height(pRoot->pLeft);
	int right = Height(pRoot->pRight);
	return max(left, right) + 1;
}

void Insert(NODE*& pRoot, int x)
{
	if (pRoot == NULL)
	{
		NODE* pnew = createNode(x);
		pRoot = pnew;
		return;
	}
	if (x < pRoot->key)
		Insert(pRoot->pLeft, x);
	else if (x > pRoot->key)
		Insert(pRoot->pRight, x);
	else
		return;
	// Cập nhật hệ số cho từng Node, hệ số = trái - phải
	pRoot->height = Weight(pRoot);
	if (pRoot->height > 1)
	{
		if (pRoot->pLeft->height < 0)
			rotateLeftRight(pRoot);
		else
			rotateRight(pRoot);
	}
	else if (pRoot->height < -1)
	{
		if (pRoot->pRight->height > 0)
			rotateRightLeft(pRoot);
		else
			rotateLeft(pRoot);
	}

}

//3. Remove a node with given value x from a given AVL tree(Notify if the given value not existed) :
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
		if (pRoot->pLeft == NULL && pRoot->pRight == NULL) //Node lá
		{
			pRoot = NULL;
			return;
		}
		else if (pRoot->pLeft != NULL && pRoot->pRight == NULL)// Node có 1 con trái
		{
			pRoot = pRoot->pLeft;
			return;
		}
		else if (pRoot->pLeft == NULL && pRoot->pRight != NULL)// Node có một con phải
		{
			pRoot = pRoot->pRight;
			return;
		}
		else // Node có 2 con
		{
			NODE* pTemp = maxNodeBST(pRoot->pLeft); //Lấy Node có giá trị lớn nhất bên cây con trái
			pRoot->key = pTemp->key;
			Remove(pRoot->pLeft, pTemp->key);
			
		}
	}
	// Cập nhật hệ số cho từng Node, hệ số = trái - phải
	pRoot->height = Weight(pRoot);
	if (Weight(pRoot) > 1)
	{
		if (Weight(pRoot->pLeft) < 0)
			rotateLeftRight(pRoot);
		else
			rotateRight(pRoot);
	}
	else if (Weight(pRoot) < -1)
	{
		if (Weight(pRoot->pRight) > 0)
			rotateRightLeft(pRoot);
		else
			rotateLeft(pRoot);
	}
	
}

//4. Determine if a given Binary Tree is an AVL Tree:
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

bool isBST(NODE* pRoot) //kiểm tra cay nhi phan
{
	if (pRoot == NULL)
		return true;
	if ((pRoot->pLeft != NULL && (maxOfTree(pRoot->pLeft) > pRoot->key)) || (pRoot->pRight != NULL && (minOfTree(pRoot->pRight) < pRoot->key)))
		return false;
	return isBST(pRoot->pLeft) && isBST(pRoot->pRight);
}

bool isBalacedtemp(NODE* pRoot) // kiem tra cay can bang
{
	if (pRoot == NULL)
		return true;
	if (Weight(pRoot) > 1 || Weight(pRoot) < -1)
		return false;
	return isBalacedtemp(pRoot->pLeft) && isBalacedtemp(pRoot->pRight);
}

bool isBalaced(NODE* pRoot)
{
	return isBalacedtemp(pRoot) && isBST(pRoot);
}

// Cac ham bo sung de in ra man hinh cay nhi phan tu mang 1 chieu
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

void print2DUtil(NODE* root, int space)
{
	if (root == NULL)
		return;

	// Increase distance between levels
	space += COUNT;

	// Process right child first
	print2DUtil(root->pRight, space);

	// Print current node after space
	// count
	cout << endl;
	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << root->key << "\n";

	// Process left child
	print2DUtil(root->pLeft, space);
}

// Wrapper over print2DUtil()
void print2D(NODE* root)
{
	// Pass initial space count as 0
	print2DUtil(root, 0);
}

int main()
{
	NODE* pRoot = new NODE;
	pRoot = NULL;
	//test
	int a[7] = { 4, 2, 6, 1, 3, 5, 7 };
	pRoot = createTree(a, 7);
	Remove(pRoot, 4);
	Remove(pRoot, 1);
	Remove(pRoot, 3);
	//Remove(pRoot, 6);
	print2D(pRoot);
	if (isBalaced(pRoot))
		cout << "true" << endl;
	else
		cout << "false" << endl;
}
