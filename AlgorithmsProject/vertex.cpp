#include "vertex.h"

void Vertex::setValue(int value) {

	m_value = value;
}

void Vertex::AddEdgeToAdjList(int edgeTo) {

	m_adjacencyList.push_back(edgeTo);
}

void Vertex::RemoveEdgeFromAdjList(int edgeTo) {

	for (auto itr = m_adjacencyList.begin(); itr != m_adjacencyList.end(); itr++)
	{
		if (*itr == edgeTo)
		{
			m_adjacencyList.erase(itr);
			break;
		}
	}
}
