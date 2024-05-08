#ifndef _BALL_H
#define _BALL_H

#include "Util.h"
#include <list>
#include <algorithm>
#include <vector>

class BallTree {

public:
	BallTree() {
		m_left = nullptr;
		m_right = nullptr;
		m_radi = 0.001;
		m_pivot = Coordinate { 0.0, 0.0 };
        m_root = nullptr;
    }
    BallTree* getArrel() 
	{
	    return m_root;
	}
    Coordinate getPivot() {
		return m_pivot;
	}
	double getRadi() 
	{
		return m_radi;
	}
	BallTree* getDreta() {
		return m_right;
	}
	BallTree* getEsquerre() {
		return m_left;
	}
	std::vector<Coordinate>& getCoordenades() 
	{
		return m_coordenades;
	}
    void setArrel(BallTree* root) {
        m_root = root;
    }
	void setPivot(Coordinate pivot) {
		m_pivot = pivot;
	}
	void setRadius(double radi) 
	{
		m_radi = radi;
	}
	void setDreta(BallTree* right) {
		m_right = right;
	}
	void setEsquerre(BallTree* left) {
		m_left = left;
	}
	void setCoordenades(std::vector<Coordinate>& coordenades) 
	{
		m_coordenades = coordenades;
	}
    Coordinate nodeMesProper(Coordinate targetQuery, Coordinate& Q, BallTree* ball);
	Coordinate nodeMesProperRec(Coordinate targetQuery, Coordinate& Q, BallTree* ball);
    void construirArbre(const std::vector<Coordinate>& coordenades);
	void inOrdre(std::vector<std::list<Coordinate>>& out);
    void preOrdre(std::vector<std::list<Coordinate>>& out);
    void postOrdre(std::vector<std::list<Coordinate>>& out);
	double calculaDistancia(Coordinate cord, BallTree coordenades);
	Coordinate buscaCentral(std::vector<Coordinate> coordenades);
	Coordinate buscaMaxima(Coordinate cord, std::vector<Coordinate> coordenades);
	void eliminaCord(Coordinate cord, std::vector<Coordinate>& coordenades);
	Coordinate calculaMesProper(Coordinate pdi, std::vector<Coordinate> coordenades);
	void construirArbreRec(std::vector<Coordinate>& coordenades, const std::vector<Coordinate>& coord, bool rootControl);
	void buscaPosicio(Coordinate valor);
	void mostra();
    ~BallTree() = default;

private:
    BallTree* m_root; // PARE
    BallTree* m_left; //ESQUERRA
	BallTree* m_right; //DRET
	double m_radi; // RADI RESPECTE EL PIVOT (CENTRAL)
	Coordinate m_pivot; // Coordenades centre.
	std::vector<Coordinate> m_coordenades;

};


#endif

