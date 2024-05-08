#pragma once
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <string>
#include <cstdio>
#include "Common.h"
using namespace std;

/*Construirem un graf que tindrà com a nodes les 
coordenades dels camins que carregueu a través de MapaSolucio i com arestes les connexions entre aquests 
nodes donades pels camins i ponderades per la distància Haversineentre els nodes.*/
class GrafSolucio
{
public:

	GrafSolucio() : m_numNodes(0) {}
	GrafSolucio(const vector<Coordinate>& nodes, const vector<vector<int>>& parellesNodes, bool dirigit);
	GrafSolucio(const vector<Coordinate>& nodes, const vector<vector<int>>& parellesNodes, const vector<int>& pesos, bool dirigit);
	~GrafSolucio();
	int minDistance(vector<double>& dist, vector<bool>& visitat);
	void camiMesCurt(const Coordinate& node1, const Coordinate& node2, stack<Coordinate>& cami);
	inline vector<Coordinate> getCoordinates() const { return m_nodes; };
	void dijkstra(int node, int node2, vector<double>& dist, vector<int>& anterior);
	int buscaIndex(Coordinate cord);
	int getNumNodes() { return m_numNodes; }
	void inserirAresta(int posNode1, int posNode2, double pes);
	void afegirNode(const Coordinate& node);
	Coordinate buscaNode(int i) { return m_nodes[i]; }
	vector<Coordinate>::iterator findIterator(vector<Coordinate>::iterator inicial, vector<Coordinate>::iterator final, Coordinate valor);
	int existeixNode(const Coordinate& c) const;
private:
	vector<Coordinate> m_nodes;
	vector<vector<double>> m_matriuAdj;
	int m_numNodes;
	int m_numArestes;
	bool m_dirigit;
	void crearMatriu(const vector<vector<int>>& parelles);
	void crearMatriu(const vector<vector<int>>& parelles, const vector<int>& pesos);
	
};

