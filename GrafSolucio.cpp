#include "GrafSolucio.h"

GrafSolucio::GrafSolucio(const vector<Coordinate>& nodes, const vector<vector<int>>& parellesNodes, bool dirigit)
{
	m_nodes = nodes;
	m_numNodes = m_nodes.size();
	m_dirigit = dirigit;
	crearMatriu(parellesNodes);
}
GrafSolucio::GrafSolucio(const vector<Coordinate>& nodes, const vector<vector<int>>& parellesNodes, const vector<int>& pesos, bool dirigit)
{
	m_nodes = nodes;
	m_numNodes = m_nodes.size();
	m_dirigit = dirigit;
	crearMatriu(parellesNodes, pesos);
}
GrafSolucio::~GrafSolucio()
{

}
void GrafSolucio::dijkstra(int node, int node2, vector<double>& dist, vector<int>& anterior) 
{
	const double DISTMAX = 1.79769313486231e308;
	dist.resize(m_numNodes, DISTMAX);
	vector<bool> visitat;
	visitat.resize(m_numNodes, false);
	anterior.resize(m_numNodes, -1);
	dist[node] = 0;
	anterior[node] = node;
	for (int count = 0; count < m_numNodes - 1; count++) 
	{
		int posVeiAct = minDistance(dist, visitat);
		visitat[posVeiAct] = true;
		if (posVeiAct == node2) return;
		for (int posVei = 0; posVei < m_numNodes; posVei++)
			if (m_matriuAdj[posVeiAct][posVei] != 0)
				if (!visitat[posVei])
					if (dist[posVeiAct] + m_matriuAdj[posVeiAct][posVei] < dist[posVei])
					{
						dist[posVei] = dist[posVeiAct] + m_matriuAdj[posVeiAct][posVei];
						anterior[posVei] = posVeiAct;
					}
	}
}
int GrafSolucio::minDistance(vector<double>& dist, vector<bool>& visitat)
{
	const double DISTMAX = 1.79769313486231e308;
	double min = DISTMAX;
	int minIndex = -1;
	for (int posVei = 0; posVei < m_numNodes; posVei++)
		if (!visitat[posVei] && dist[posVei] <= min)
		{
			min = dist[posVei];
			minIndex = posVei;
		}
	return minIndex;

}
int GrafSolucio::buscaIndex(Coordinate cord)
{
	for (int i = 0; i < m_nodes.size(); i++)
	{
		if (cord.lat == m_nodes[i].lat && cord.lon == m_nodes[i].lon)
		{
			return i;
		}
	}
	return -1;
}
void GrafSolucio::inserirAresta(int posNode1, int posNode2, double pes)
{
	m_matriuAdj[posNode1][posNode2] = pes;
	if (!m_dirigit)
		m_matriuAdj[posNode2][posNode1] = pes;
}
void GrafSolucio::afegirNode(const Coordinate& node)
{
	//m_nodes.resize(m_numNodes);
	m_nodes.push_back(node);

	// add a row
	m_matriuAdj.push_back(std::vector<double>(m_numNodes));

	m_numNodes++;

	//m_matriuAdj.resize(m_numNodes);
	for (int i = 0; i < m_numNodes; i++) m_matriuAdj[i].push_back(0);
}
void GrafSolucio::crearMatriu(const vector<vector<int>>& parelles)
{
		m_matriuAdj.resize(m_numNodes);
		for (int i = 0; i < m_numNodes; i++)
		{
			m_matriuAdj[i].resize(m_numNodes, 0);
		}

		for (int i = 0; i < parelles.size(); i++)
		{
			m_matriuAdj[parelles[i][0]][parelles[i][1]] = 1;
			if (!m_dirigit)
				m_matriuAdj[parelles[i][1]][parelles[i][0]] = 1;
		}
}
void GrafSolucio::crearMatriu(const vector<vector<int>>& parelles, const vector<int>& pesos)
{

	m_matriuAdj.resize(m_numNodes);
	for (auto& it : m_matriuAdj)
	{
		it.resize(m_numNodes);
	}

	for (int i = 0; i < parelles.size(); i++)
	{
		m_matriuAdj[parelles[i][0]][parelles[i][1]] = pesos[i];
		if (!m_dirigit)
			m_matriuAdj[parelles[i][1]][parelles[i][0]] = pesos[i];
	}
}
int GrafSolucio::existeixNode(const Coordinate& c) const
{
	bool trobat = false;
	int i = 0; 
	while (i < m_numNodes && !trobat)
	{
		if (m_nodes[i].lat == c.lat && m_nodes[i].lon == c.lon)
			trobat = true;
		else
			i++;
	}
	if (trobat)
		return i;
	return -1;
}
vector<Coordinate>::iterator GrafSolucio::findIterator(vector<Coordinate>::iterator inicial, vector<Coordinate>::iterator final, Coordinate valor)
{
	vector<Coordinate>::iterator actual = inicial;
	while (actual != final)
	{
		if ((*actual).lat == valor.lat && (*actual).lon == valor.lon)
		{
			return actual;
		}
		else
			actual++;
	}
	return actual;
}
void GrafSolucio::camiMesCurt(const Coordinate& node1, const Coordinate& node2, stack<Coordinate>& cami)
{
	vector<Coordinate>::iterator itNode1 = findIterator(m_nodes.begin(), m_nodes.end(), node1);
	vector<Coordinate>::iterator itNode2 = findIterator(m_nodes.begin(), m_nodes.end(), node2);
	if ((itNode1 != m_nodes.end()) && (itNode2 != m_nodes.end()))
	{
		int pos1 = distance(m_nodes.begin(), itNode1);
		int pos2 = distance(m_nodes.begin(), itNode2);
		vector<int> anterior;
		vector<double> vDist;
		dijkstra(pos1, pos2, vDist, anterior);
		int it = pos2;
		cami.push(m_nodes[pos2]);
		while (it != pos1)
		{
			cami.push(m_nodes[anterior[it]]);
			it = anterior[it];
		}
	}
}