#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; 


class Node {
public:
	Node * left;
	Node * right; 
	int k; // key
	int c; // count of duplicate nodes
	int sc, ltc; 
	Node () : right(0), left (0), k(0), c(0), sc (0), ltc (0) {}
};


vector<int> vc;

void insert (const int k, Node* r, int m)
{
	if (k == r->k) {
		r->sc = r->ltc + m ;     
		r->c++;
		vc.push_back(r->sc);
	} else if (k < r->k) {
		if (r->left) {
			insert (k, r->left, m+1 + r->ltc+r->c);
		} else {
			r->left = new Node; 
			r->left->k = k;       
			r->left->sc =  m+1 + r->ltc + r->c;
			vc.push_back(r->left->sc);
		}
	} else {
		r->ltc++; 
    		if (r->right) {
			insert (k , r->right, m); 
    		} else {
			r->right = new Node; 
			r->right->k = k;       
			r->right->sc = m + r->c;
			vc.push_back(r->right->sc);
		}
	}
}

int main(int argc, char ** argv) {
  int k[] = {82, 74, 17, 93, 96, 20, 25, 55, 15, 24, 25, 56};
  int l = 12; 

  Node * r = new Node;
  r->k = k[l-1]; 
  vc.push_back(0);

  for (int i = l-2; i >= 0; i--){
    insert (k[i], r, 0);
  } 
  for (int i = vc.size()-1; i>=0;i--){
    cout << vc[i] << " ";
  }
  cout << endl;
  cout << "Maximal surpasser count is: " << * max_element(vc.begin(), vc.end()) << endl;
  return(0); 
}
