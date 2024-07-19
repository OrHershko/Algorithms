#pragma once
#include <list>
#include <vector>
using namespace std;
class Vertex;


class Graph
{
	private:
		int m_numberOfVertices = 0;
		int m_numberOfEdges = 0;
		Vertex* m_verticesArray = nullptr;

	public:
		Graph(int numberOfVertices) { //c'tor

			MakeEmptyGraph(numberOfVertices);
		}
		Graph(){ }

		void MakeEmptyGraph(int numberOfVertices); // builds an empty graph with a input number of vertices

		void MakeEmptySuperGraph(int numberOfVertices); //initialize empty graph by by creating an array of vertices

		void ReceiveEdgesFromUser(int numOfEdges); // get the edges from the user, and if they are valid, insert them to the graph

		bool IsEdgeValid(int edgeFrom, int edgeTo); //check if the edges are valid

		void AddEdge(int edgeFrom, int edgeTo); // and an edge to the graph

		bool IsAdjacent(int edgeFrom, int edgeTo); //return true if there is an edge between to vertices

		const list<int> GetAdjList(int vertex); 

		void RemoveEdge(int edgeFrom, int edgeTo); // remove a edge between to vertices

		void DFS(const vector<int>& mainLoop, vector<int>& endArray, bool isTranspose, Graph* SuperGraph); // CC-DFS algorithen learnd in class

		int* createAndInitColorsArray(); // alllocate and initialize the colors array

		void VISIT(int vertex, int currentRootOfDFSTree, int* rootsOfDFSTreesArray, int* colorsOfVertices, vector<int>& endArray, Graph* SuperGraph); //visit algorithen learnd in class

		void InitMainLoop(vector<int>& mainLoop); // set the main loop in increasing order

		void KosarajuSharirModified(); // prints the super graph by using the Kosaraju-Sharir algorithen with modifications

		void BuildTranspose(Graph* graph); // build the transpose graph

		void setNewVertexToSuperGraph(int vertex); //set a new vertex to the super graph

		void addOneToNumOfEdges(); //add one to the number of edges in the graph

		void addOneToNumOfVertices(); //add one to the number of vertices in the graph

		void printNumOfVerticesAndEdges(); //print the number of vertices and edges
};

enum class eColors { WHITE, GRAY, BLACK };


