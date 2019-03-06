#include <cmath>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

struct node
{
    int id;
    int val;
    node* lchild;
    node* rchild;
};

node* newnode(int id)
{
    node* n = new node;
    n->id = id;
    n->lchild = NULL;
    n->rchild = NULL;
    return n;
}
void post(node *root)
{
    if(root == NULL)
    {
        return;
    }
    post(root -> lchild);
    post(root -> rchild);
    if(root->val == 2)
    {
    	putchar('F');
	}
	if(root->val == 0)
    {
    	putchar('B');
	}
	if(root->val == 1)
    {
    	putchar('I');
	}
}
int ForBorI(int *FBI, int len)
{
	bool F = false, B = false, I = false;
	for(int i = 0; i < len; ++i)
	{
		if(FBI[i] == 1)
		{
			I = true;
		}
		if(FBI[i] == 0)
		{
			B = true;
		}
	}
	if(I&&B)
	{
		F = true;
	}
	if(F)
	{
		return 2;
	}
	if(B)
	{
		return 0;
	}
	if(I)
	{
		return 1;
	}
}
node* FBI(int* p, int len)
{
	node* root = newnode(0);
	root->val = ForBorI(p, len);
	int *lp = (int*)malloc(sizeof(int) * len / 2 + 5);
	for(int i = (len / 2); i < len; ++i)
	{
		lp[i - (len / 2)] = p[i];
	}
	cout << endl;
	if(len == 1)
		return root;
	root->lchild = FBI(p, len / 2);
	root->rchild = FBI(lp, len / 2);
	return root;
}
int main()
{
	int n;
	cin >> n;
	int l = pow(2, n);
	int *p = (int*)malloc(sizeof(int) * l + 5);
	string FBIs;
	cin >> FBIs;
	for(int i = 0; i < FBIs.length(); ++i)
	{
		if(FBIs[i] == '0')
    	{
    		p[i] = 0;
		}
		else
		{
			p[i] = 1;
		}
	}
	node *tree = FBI(p, l);
	post(tree);
    return 0;
}
