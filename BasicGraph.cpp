#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Vertex;

class Edge
{
private:
	Vertex* orig;
	Vertex* dest;
	int distance;

	Edge () { }

public:
	Edge (Vertex* o, Vertex* d, int s) : orig(o), dest(d), distance (s) { }

	Vertex* GetOrigin () { return orig; }
	Vertex* GetDestination () { return dest; }
	int GetDistance () { return distance; }

	void Print ();
};

class Vertex
{
private:
	string name;
	vector<Edge> edges;

public:
	Vertex (const string& id) : name(id) {}

	void AddEdge (Vertex* v, int dist) {
		Edge newEdge (this, v, dist);
		edges.push_back (newEdge);
    	}

	void PrintEdges () {
		cout << name.c_str () << ":" << endl;

		for (vector<Edge>::iterator it = edges.begin (); it != edges.end (); it++) {
			it->Print ();
		}
		cout << endl;
	}

    string GetName() { return name;} 
    vector<Edge> GetEdges() { return edges;}

};

void Edge::Print ()
{
	cout << this->dest->GetName ().c_str () << " - " << this->distance << endl;
}

class MyGraph
{
private:
	vector<Vertex*> vertices;

public:
	MyGraph () {}

	void AddVertex (Vertex *v) { vertices.push_back(v); }

	void Print () {
		for (vector<Vertex*>::iterator it = vertices.begin (); it != vertices.end (); it++) (*it)->PrintEdges ();
    	}

};

int main (int argc, char* argv[])
{
	Vertex v1 = Vertex ("America");
	Vertex v2 = Vertex ("Canada");
	Vertex v3 = Vertex ("Venezuela");
	Vertex v4 = Vertex ("Brazil");
	Vertex v5 = Vertex ("Chile");
	Vertex v6 = Vertex ("Mexico");
	Vertex v7 = Vertex ("Argentina");
	Vertex v8 = Vertex ("Columbia");

	v1.AddEdge (&v2, 100);
	v1.AddEdge (&v6, 20);
	v2.AddEdge (&v1, 100);
	v3.AddEdge (&v1, 30);
	v3.AddEdge (&v4, 10);
	v3.AddEdge (&v7, 20);
	v4.AddEdge (&v5, 15);
	v5.AddEdge (&v1, 10);
	v6.AddEdge (&v1, 20);
	v8.AddEdge (&v7, 45);


	MyGraph mg;
	mg.AddVertex (&v1);
	mg.AddVertex (&v2);
	mg.AddVertex (&v3);
	mg.AddVertex (&v4);
	mg.AddVertex (&v5);
	mg.AddVertex (&v6);
	mg.AddVertex (&v7);
	mg.AddVertex (&v8);

	mg.Print ();

	return 0;
}
