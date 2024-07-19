#include "graph.h"
#include "vertex.h"
#include <iostream>
#include <algorithm>
using namespace std;


void Graph::MakeEmptyGraph(int numberOfVertices) { 

	m_numberOfVertices = numberOfVertices;
	m_verticesArray = new Vertex[m_numberOfVertices];
	

	for (int i = 0; i < m_numberOfVertices; i++) {
		
		m_verticesArray[i].setValue(i + 1);
	}
}

void Graph::ReceiveEdgesFromUser(int numOfEdges) {

	for (int i = 0; i < numOfEdges; i++) {

		int edgeFrom, edgeTo;
		cin >> edgeFrom;
		cin >> edgeTo;

		if (IsEdgeValid(edgeFrom, edgeTo)) {

			AddEdge(edgeFrom, edgeTo);

		}
		else {

			cout << "invalid input" << endl;
			exit(1);
		}
	}
}

bool Graph::IsEdgeValid(int edgeFrom, int edgeTo){

	return (edgeFrom <= m_numberOfVertices && edgeTo <= m_numberOfVertices && edgeFrom > 0 && edgeTo > 0 && edgeTo != edgeFrom);
}

void Graph::AddEdge(int edgeFrom, int edgeTo) {

	m_verticesArray[edgeFrom - 1].AddEdgeToAdjList(edgeTo);
}

bool Graph::IsAdjacent(int edgeFrom, int edgeTo) {

	if (!IsEdgeValid(edgeFrom, edgeTo)) {

		return false;
	}
	else {

		list<int> adjList = m_verticesArray[edgeFrom - 1].GetAdjList();

		for (auto i : adjList)
		{
			if (i == edgeTo)
			{
				return true;
			}
		}

		return false;
	}
}

const list<int> Graph::GetAdjList(int vertex){

	return m_verticesArray[vertex - 1].GetAdjList();
}

void Graph::RemoveEdge(int edgeFrom, int edgeTo)
{
	if (!IsEdgeValid(edgeFrom, edgeTo)) {

		cout << "invalid input" << endl;
		exit(1);
	}
	else {

		m_verticesArray[edgeFrom - 1].RemoveEdgeFromAdjList(edgeTo);
	}
}

void Graph::DFS(const vector<int>& mainLoop, vector<int>& endArray, bool isTranspose, Graph* SuperGraph) {

	int currentRootOfDFSTree;
	int* rootsOfDFSTreesArray = new int[m_numberOfVertices];
	int* colorsOfVertices = createAndInitColorsArray();

	for (int i = 0; i < m_numberOfVertices; i++) {

		if (colorsOfVertices[mainLoop[i] - 1] == (int)eColors::WHITE)
		{
			currentRootOfDFSTree = mainLoop[i];
			if (isTranspose)
			{
				SuperGraph->setNewVertexToSuperGraph(currentRootOfDFSTree);
				SuperGraph->addOneToNumOfVertices();
			}
			VISIT(mainLoop[i], currentRootOfDFSTree, rootsOfDFSTreesArray, colorsOfVertices, endArray, SuperGraph);
		}
	}

	delete[] colorsOfVertices;
	delete[] rootsOfDFSTreesArray;
}

void Graph::VISIT(int vertex, int currentRootOfDFSTree, int* rootsOfDFSTreesArray, int* colorsOfVertices, vector<int>& endArray, Graph* SuperGraph)
{
	rootsOfDFSTreesArray[vertex - 1] = currentRootOfDFSTree;
	colorsOfVertices[vertex - 1] = (int)eColors::GRAY;

	for (auto i : m_verticesArray[vertex - 1].GetAdjList())
	{
		if (colorsOfVertices[i - 1] == (int)eColors::WHITE)
		{
			VISIT(i, currentRootOfDFSTree, rootsOfDFSTreesArray, colorsOfVertices, endArray, SuperGraph);
		}
		else if (colorsOfVertices[i - 1] == (int)eColors::BLACK && SuperGraph != nullptr) 
		{

			if (SuperGraph->GetAdjList(rootsOfDFSTreesArray[i - 1]).size() != 0)
			{
				if (SuperGraph->GetAdjList(rootsOfDFSTreesArray[i - 1]).back() != currentRootOfDFSTree)
				{
					SuperGraph->AddEdge(rootsOfDFSTreesArray[i - 1], currentRootOfDFSTree);
					SuperGraph->addOneToNumOfEdges();
				}
			}
			else
			{
				if (rootsOfDFSTreesArray[i - 1] != currentRootOfDFSTree)
				{
					SuperGraph->AddEdge(rootsOfDFSTreesArray[i - 1], currentRootOfDFSTree);
					SuperGraph->addOneToNumOfEdges();
				}
			}
		}
	}

	colorsOfVertices[vertex - 1] = (int)eColors::BLACK;
	endArray.push_back(vertex);
}

int* Graph::createAndInitColorsArray()
{
	int* colorsOfVertices = new int[m_numberOfVertices];

	for (int i = 0; i < m_numberOfVertices; i++)
	{
		colorsOfVertices[i] = (int)eColors::WHITE;
	}

	return colorsOfVertices;
}

void Graph::InitMainLoop(vector<int>& mainLoop)
{
	for (int i = 0; i < m_numberOfVertices; i++)
	{
		mainLoop.push_back(i + 1);
	}
}

void Graph::KosarajuSharirModified(){

	vector<int> mainLoop;
	vector<int> endArray;
	vector<int> transposeEndArray;

	endArray.reserve(m_numberOfVertices);

	InitMainLoop(mainLoop);
	
	DFS(mainLoop, endArray, false, nullptr);

	Graph G_Transpose(m_numberOfVertices);

	G_Transpose.BuildTranspose(this);

	reverse(endArray.begin(), endArray.end());

	Graph superGraph;

	superGraph.MakeEmptySuperGraph(m_numberOfVertices);

	G_Transpose.DFS(endArray, transposeEndArray, true, &superGraph);

	superGraph.printNumOfVerticesAndEdges();
	
}

void Graph::BuildTranspose(Graph* graph) {
	
	for (int i = 0; i < m_numberOfVertices; i++)
	{
		for (auto j : graph->GetAdjList(i + 1))
		{
			AddEdge(j, i + 1);
		}
	}
}

void Graph::MakeEmptySuperGraph(int numberOfVertices)
{
	m_verticesArray = new Vertex[numberOfVertices];

	for (int i = 0; i < numberOfVertices; i++) {

		m_verticesArray[i].setValue(0);
	}
}

void Graph::setNewVertexToSuperGraph(int vertex)
{
	m_verticesArray[vertex - 1].setValue(vertex);
}

void Graph::addOneToNumOfEdges()
{
	m_numberOfEdges++;
}

void Graph::addOneToNumOfVertices()
{
	m_numberOfVertices++;
}

void Graph::printNumOfVerticesAndEdges()
{
	cout << m_numberOfVertices << " " << m_numberOfEdges;
}


