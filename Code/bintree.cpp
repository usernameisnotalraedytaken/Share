#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

struct node
{
    int id;
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
void pre(node *root)
{
    if(root == NULL)
    {
        return;
    }
    putchar(root->id);
    pre(root -> lchild);
    pre(root -> rchild);
}
node* create(string i, string p)
{
	cout << "Root is " << p[p.length() - 1] << endl;
	cout << "in-order is " << i << endl << "post-order is " << p << endl;
	node* root = newnode(p[p.length() - 1]);
	if(p.length() == 1)
		return root;
	string lc, rc;
	bool psn = false;
	for(int j = 0; j < i.length(); ++j)
	{
		if(i[j] == p[p.length() - 1])
		{
			psn = true;
			continue;
		}
		if(!psn)
		{
			lc.push_back(i[j]);
		}
		else
		{
			rc.push_back(i[j]);
		}
	}
	string px;
	for(int k = 0; k < p.length() - 1; ++k)
	{
		px.push_back(p[k]);
	}
	cout << "left chlidren order is " << lc << endl << "right children order is " << rc << endl << "left post-order is " << px << endl << endl;
	root -> lchild = create(lc, px);
	root -> rchild = create(rc, px);
	return root;
}
int main()
{
	string in_order, post_order;
	cin >> in_order >> post_order;
	node* tree = create(in_order, post_order);
	pre(tree);
    return 0;
}
