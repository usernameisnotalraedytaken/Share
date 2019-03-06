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
void insert(node* &root, int left, int right, int key)
{
    if(root == NULL)
    {
        return;
    }
    if(root -> id == key)
    {
        if(right != -1)
        {
            node* rnode = newnode(right);
            root -> rchild = rnode;
        }
        if(left != -1)
        {
            node* lnode = newnode(left);
            root -> lchild = lnode;
        }
        return;
    }
    insert(root -> lchild, left, right, key);
    insert(root -> rchild, left, right, key);
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
void in(node *root)
{
    if(root == NULL)
    {
        return;
    }
    pre(root -> lchild);
    putchar(root->id);
    pre(root -> rchild);
}
void post(node *root)
{
    if(root == NULL)
    {
        return;
    }
    pre(root -> lchild);
    pre(root -> rchild);
    putchar(root->id);
}
int main()
{
    int n;
    cin >> n;
    string a;
    cin >> a;
    node* tree = newnode(a[0]);
    if(a[1] == '*')
    {
        a[1] = -1;
    }
    if(a[2] == '*')
    {
        a[2] = -1;
    }
    insert(tree, a[1], a[2], a[0]);
    n--;
    while(n--)
    {
        cin >> a;
        if(a[1] == '*')
        {
            a[1] = -1;
        }
        if(a[2] == '*')
        {
            a[2] = -1;
        }
        insert(tree, a[1], a[2], a[0]);
    }
    pre(tree);
    cout << endl;
    in(tree);
    cout << endl;
    post(tree);
    return 0;
}
