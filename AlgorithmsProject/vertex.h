#pragma once
#include <list>
using namespace std;

class Vertex
{
	private:
		int m_value;
		list<int> m_adjacencyList;

	public:
		void setValue(int value); // set a vertex value

		void AddEdgeToAdjList(int edgeTo); // add an adj to adjacency list

		const list<int> GetAdjList() { return m_adjacencyList; }

		void RemoveEdgeFromAdjList(int edgeTo); // remove an adj from adjacency list

};

