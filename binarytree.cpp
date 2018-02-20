#include <stdio.h>
#include <string>
using namespace std;

class Node
{
private:
	char n;
	Node* l;
	Node* r;
	Node (): n(0), l(0), r(0) { }
public:
	Node (char v): n(v), l(0), r(0) {}
	~Node () { /* printf ("Deleted node with value <%c>\n", n); */ }
	void Left (Node* left) {l=left; }
	void Right (Node* right) {r=right; }
	Node* L () const { return l; }
	Node* R () const { return r; }
	char V() const { return n; }
};

class BinaryTree
{
private:
	Node* root;
	void InOrderPrint (const Node* r) const;
	void PreOrderPrint (const Node* r) const;
	void DestroyTree (Node* r);

	string preorders;
	string inorders;

	void PreOrderString (const Node* r);
	void InOrderString (const Node* r);

	Node* ReconstructTree (const string& pre, const string&in, const short ps, const short pe, const short ins, const short ine) const;

public:
	BinaryTree () : root (0) {}
	BinaryTree (Node* n) : root (n) {}
	~BinaryTree () { this->DestroyTree (root); }
	void MakeTree ();

	void InOrderPrint () const { printf ("INORDER: "); this->InOrderPrint(root); printf ("\n"); }
	void PreOrderPrint () const { printf ("PREORDER: "); this->PreOrderPrint(root); printf ("\n"); }

	string PreOrderString () { this->PreOrderString(root); return preorders; }
	string InOrderString () { this->InOrderString(root); return inorders; }
	void ReconstructTree (const string& pre, const string&in) { if (in.length() != pre.length()) return; root = this->ReconstructTree (pre, in, 0, pre.length(), 0, in.length ()); }
};


short FindIndex (const string& in, const short ins, const char c)
{
	for (short i = ins; i < in.length (); i++) {
		if (in[i] == c) return i - ins;
	}

	return -1;
}

Node* BinaryTree::ReconstructTree (const string& pre, const string&in, const short ps, const short pe, const short ins, const short ine) const
{

	//printf ("HERE1 <%d> --  <%d> -- <%d>  -- <%d>\n", ps, pe, ins, ine);

	if (pe < ps || ine < ins) return 0;

	Node* n = new Node(pre[ps]);

	short index = FindIndex (in, ins, pre[ps]);
	if (index == -1) return 0;

	//printf ("HERE2 <%d>\n", index);

	n->Left (this->ReconstructTree (pre, in, ps+1, ps+index, ins, ins+index));
	n->Right (this->ReconstructTree (pre, in, ps+index+1, pe, ins+index+1, ine));

	return n;
}

void BinaryTree::PreOrderString (const Node* r)
{
	if (0 == r) return;

	preorders += r->V();
	this->PreOrderString(r->L());
	this->PreOrderString(r->R());
}

void BinaryTree::InOrderString (const Node* r)
{
	if (0 == r) return;

	this->InOrderString(r->L());
	inorders += r->V();
	this->InOrderString(r->R());
}

void BinaryTree::InOrderPrint (const Node* r) const
{
	if (0 == r) return;

	this->InOrderPrint(r->L());
	printf ("%c ", r->V());
	this->InOrderPrint(r->R());
}

void BinaryTree::PreOrderPrint (const Node* r) const
{
	if (0 == r) return;

	printf ("%c ", r->V());
	this->PreOrderPrint(r->L());
	this->PreOrderPrint(r->R());
}

void BinaryTree::DestroyTree (Node* r)
{
	if (0 == r) return;
	this->DestroyTree(r->L());
	this->DestroyTree(r->R());

	delete r;
}

void BinaryTree::MakeTree ()
{
	Node* n1 = new Node ('B');
	Node* n2 = new Node ('C');
	Node* n3 = new Node ('D');
	Node* n4 = new Node ('E');
	Node* n5 = new Node ('F');
	Node* n6 = new Node ('G');
	Node* n7 = new Node ('H');

	root->Left(n1);
	root->Right(n2);

	n1->Left(n3);
	n1->Right(n4);

	n2->Left(n5);
	n2->Right(n6);

	n3->Left(n7);
}

int main (int argc, char* argv[])
{
	Node* n = new Node ('A');
	BinaryTree bt(n);
	bt.MakeTree ();
	

	bt.InOrderPrint ();
	bt.PreOrderPrint ();

	string in = bt.InOrderString ();
	string pre = bt.PreOrderString ();

	printf ("PREORDER STRING <%s>\n", pre.c_str ());
	printf ("INORDER STRING <%s>\n", in.c_str ());


	BinaryTree bt2;
	bt2.ReconstructTree (pre, in);
	bt2.InOrderPrint ();
	bt2.PreOrderPrint ();
}
