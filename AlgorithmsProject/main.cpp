#include <iostream>
using namespace std;
#include "graph.h"


int main() {

	int numOfVertices;
	int numOfEdges;

	cout << "Please enter a number of vertices for the graph" << endl;
	cin >> numOfVertices;

	if (numOfVertices < 0)
	{
		cout << "invalid input" << endl;
		exit(1);
	}

	Graph graph(numOfVertices);

	cout << "Please enter a number of edges for the graph" << endl;
	cin >> numOfEdges;

	if (numOfEdges < 0 || numOfEdges > numOfVertices * (numOfVertices - 1))
	{
		cout << "invalid input" << endl;
		exit(1);
	}

	graph.ReceiveEdgesFromUser(numOfEdges);

	graph.KosarajuSharirModified();

}