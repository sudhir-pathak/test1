#include <stdio.h>

class TreeNode {
public:
	TreeNode* left;
	TreeNode* right;
	int value;

	TreeNode () : left (0), right (0), value (0) { }
	TreeNode (int v) : left (0), right (0), value (v) { }
	TreeNode (int v, TreeNode* l, TreeNode* r) : left (l), right (r), value (v) { }

	void Print () { printf ("Value of this node <%d>\n", value); }

	~TreeNode () { printf ("Deleted Node <%d>\n", value); }
};

class BST
{
private:
	TreeNode* root;

	TreeNode* AddNode (TreeNode*, int);
	void Print (TreeNode*);

	void Destruct (TreeNode*);

	int SecondLargest (TreeNode*, int&);

public:
	BST () : root(0) { }
	~BST () { Destruct (root); }
	void AddNode (int v);
	void Print ();

	int SecondLargest ();
};
 
int BST::SecondLargest ()
{
	int c = 0;
	int v = this->SecondLargest (root, c);
	return v;
}

int BST::SecondLargest (TreeNode* n, int &c)
{
	static int v = -1;

	if (n == 0 || c >= 2) {
		return v;
	}

    	v = this->SecondLargest (n->right, c);
 
	c++;
 
	if (c == 2) {
		printf ("2nd largest element found <%d>\n", n->value);
		v = n->value;
		return v;
	}

	v = this->SecondLargest (n->left, c);

	return v;
}

void BST::AddNode (int v)
{
	if (!root) {
		root = new TreeNode (v);
		return;
	} else {
		this->AddNode (root, v);
	}
}

TreeNode* BST::AddNode (TreeNode* n, int v)
{
	if (!n) {
		TreeNode* node = new TreeNode (v);
		return node;
	} else {
    		if (v <= n->value) n->left  = this->AddNode (n->left, v);
		else n->right = this->AddNode (n->right, v);
 
    		return n;
	}

	return 0;
}

void BST::Print ()
{
	this->Print (root);
}

void BST::Print (TreeNode* n)
{
	if (!n) return;

	this->Print (n->left);
	n->Print ();
	this->Print (n->right);
}

void BST::Destruct (TreeNode* n)
{
	if (!n) return;

	this->Destruct (n->left);
	this->Destruct (n->right);

	delete n;
}

int main (int argc, char* argv[])
{
	/* BST
             10
           /    \
          5      20
           \    /  \
            8  15   30
                     \
                     35
	*/

	BST bst;

	bst.AddNode (10);
	bst.AddNode (5);
	bst.AddNode (8);
	bst.AddNode (20);
	bst.AddNode (15);
	bst.AddNode (30);
	bst.AddNode (35);

	bst.Print ();


	int v = bst.SecondLargest ();
	printf ("Second Largest element is <%d>\n", v);
 
	return 0;
}
