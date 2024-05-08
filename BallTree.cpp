#include "BallTree.h"
#include <iostream>
using namespace std;

void BallTree::construirArbre(const std::vector<Coordinate>& coordenades) {
//TODO: Utilitza aquest metode per construir el teu BallTree.
//TODO: Amb les coordenades que se us passen per parametre.
//BUSQUEM PUNT CENTRAL.
//FEM LA MITJANA DE LES DISTÀNCIES, EL QUE TINGUI LA MINIMA ÉS EL PUNT CENTRAL (HARVERSINE).
//BUSQUEM DISTANCIA MÉS LLUNYANA AL CENTRE (ESQUERRA).
    
    std::vector<Coordinate> valors(coordenades);
    construirArbreRec(valors, coordenades, true);
    //mostra();
}
void BallTree::construirArbreRec(std::vector<Coordinate>& coordenades, const std::vector<Coordinate>& coord, bool rootControl)
{
    if (coordenades.size() > 0)
    {
        for (int i = 0; i < coordenades.size(); i++) //COPIEM LES COORDENADES DE TOTS ELS PUNTS QUE HI HA.
        {
            m_coordenades.push_back(coordenades[i]);
        }
        if (rootControl)
        {
            m_root = this;
        }
            m_pivot = buscaCentral(coordenades);
            double d1, d2;
            m_radi = 0;

            if (coordenades.size() > 1)
            {
                Coordinate posA = buscaMaxima(m_pivot, coordenades);
                m_radi = Util::DistanciaHaversine(m_pivot, posA);
                eliminaCord(posA, coordenades);

                if (coordenades.size() > 0)
                {
                    Coordinate posB = buscaMaxima(posA, coordenades);
                    eliminaCord(posB, coordenades);
                    std::vector <Coordinate> cordRight;
                    std::vector <Coordinate> cordLeft;
                    cordRight.push_back(posA);
                    cordLeft.push_back(posB);

                    if (coordenades.size() > 0)
                    {
                        m_left = new BallTree;
                        m_left->m_root = m_root;

                        m_right = new BallTree;
                        m_right->m_root = m_root;

                        for (int i = 0; i < coordenades.size(); i++)
                        {
                            d1 = Util::DistanciaHaversine(posA, coordenades[i]);
                            d2 = Util::DistanciaHaversine(posB, coordenades[i]);

                            if (d1 > d2)
                            {

                                //m_left->m_coordenades.push_back(coordenades[i]);
                                cordLeft.push_back(coordenades[i]);

                            }
                            else
                            {
                                //m_right->m_coordenades.push_back(coordenades[i]);
                                cordRight.push_back(coordenades[i]);
                            }
                        }

                        m_left->construirArbreRec(cordLeft, coord, false);
                        m_right->construirArbreRec(cordRight, coord, false);
                    }
                    else
                    {
                        m_left = new BallTree;
                        m_left->m_root = m_root;
                        m_left->m_coordenades.push_back(posB);

                        m_right = new BallTree;
                        m_right->m_root = m_root;
                        m_right->m_coordenades.push_back(posA);
                    }

                }
                else
                {
                    m_left = new BallTree;
                    m_left->m_root = m_root;
                    m_left->m_coordenades.push_back(posA);
                }

            }


    }

  
}
void BallTree::inOrdre(std::vector<std::list<Coordinate>>& out) 
{

    if (m_left != nullptr)
    {
        m_left->inOrdre(out);
    }

    std::list<Coordinate> llista;
    for (int i = 0; i < m_coordenades.size(); i++)
    {
        llista.push_back(m_coordenades[i]);
    }
    out.push_back(llista);

    if (m_right != nullptr)
    {
        m_right->inOrdre(out);
    }

}
void BallTree::preOrdre(std::vector<std::list<Coordinate>>& out) 
{
    std::list<Coordinate> llista;
    for (int i = 0; i < m_coordenades.size(); i++)
    {
        llista.push_back(m_coordenades[i]);
    }
    out.push_back(llista);

    if (m_left != nullptr)
    {
        m_left->preOrdre(out);
    }

    if (m_right != nullptr)
    {
        m_right->preOrdre(out);
    }
}
void BallTree::postOrdre(std::vector<std::list<Coordinate>>& out) 
{
    if (m_left != nullptr)
    {
        m_left->postOrdre(out);
    }

    if (m_right != nullptr)
    {
        m_right->postOrdre(out);
    }
    std::list<Coordinate> llista;
    for (int i = 0; i < m_coordenades.size(); i++)
    {
        llista.push_back(m_coordenades[i]);
    }
    out.push_back(llista);
}
double BallTree::calculaDistancia(Coordinate cord, BallTree ball)
{
    return Util::DistanciaHaversine(cord, ball.m_pivot);
}
Coordinate BallTree::buscaCentral(std::vector<Coordinate> coordenades)
{
    /*Coordinate central;
    float min = 0;
    for (int i = 0; i < coordenades.size(); i++)
    {
        int mit = 0;
        for (int s = 0; s < coordenades.size(); s++)
        {
            if(i != s)
                mit = mit + Util::DistanciaHaversine(coordenades[i], coordenades[s]);
        }

        mit = mit / coordenades.size() - 1;
        if (mit < min || i == 0)
        {
            min = mit;
            central = coordenades[i];
        }
    }
    return central;
    */
    double sumLat = 0;
    double sumLon = 0;
    for (int i = 0; i < coordenades.size(); i++)
    {
        sumLat += coordenades[i].lat;
        sumLon += coordenades[i].lon;
    }
    Coordinate centre;
    centre.lat = (sumLat / (coordenades.size()));
    centre.lon = (sumLon / (coordenades.size()));
    return centre;
}
Coordinate BallTree::buscaMaxima(Coordinate cord, std::vector<Coordinate> coordenades)
{
    Coordinate maxCord;
    double max = 0;
    double dist = 0;
    for (int i = 0; i < coordenades.size(); i++)
    {
        if (coordenades[i].lat != cord.lat || coordenades[i].lon != cord.lon)
        {
            dist = Util::DistanciaHaversine(cord, coordenades[i]);
            if (dist > max || i == 0)
            {
                max = dist;
                maxCord = coordenades[i];
            }
        }
    }

    return maxCord;
}
void BallTree::eliminaCord(Coordinate cord, std::vector<Coordinate>& coordenades)
{
    std::vector<Coordinate>::iterator actual;
    for (actual = coordenades.begin(); actual != coordenades.end(); actual++)
    {
        if (cord.lat == actual->lat && cord.lon == actual->lon)
        {
            coordenades.erase(actual);
            break;
        }
    }
}
Coordinate BallTree::calculaMesProper(Coordinate pdi, std::vector<Coordinate> coordenades)
{
    double min = Util::DistanciaHaversine(pdi, coordenades[0]); ;
    Coordinate minCord = coordenades[0];
    for (int i = 0; i < coordenades.size(); i++)
    {
        double d1 = Util::DistanciaHaversine(pdi, coordenades[i]);
        if (d1 <= min)
        {
            min = d1;
            minCord = coordenades[i];
        }
    }
    return minCord;
}
void BallTree::buscaPosicio(Coordinate valor)
{
    
}
void BallTree::mostra()
{

    for (int i = 0; i < m_coordenades.size(); i++)
    {
        cout << "lat: " << m_coordenades[i].lat << "lon: " << m_coordenades[i].lon << endl;
    }
    cout << "----------------- PASO ----------------" << endl;
    
    if (m_left != nullptr)
    {
        cout << "ESQUERRA" << endl;
        m_left->mostra();
    }

    if (m_right != nullptr)
    {
        cout << "DRETA" << endl;
        m_right->mostra();
    }
}
Coordinate BallTree::nodeMesProper(Coordinate targetQuery, Coordinate& Q, BallTree* ball) 
{
    Q.lat = 0;
    Q.lon = 0;
    return nodeMesProperRec(targetQuery, Q, ball);
}
Coordinate BallTree::nodeMesProperRec(Coordinate targetQuery, Coordinate& Q, BallTree* ball)
{
    //INICIALITZACIÓ DE Q EN UN PUNT MOOOLT LLUNY (0,0) SEGONS L'ENUNCIAT FUNCIONA.
   
    double D1 = calculaDistancia(targetQuery, *ball);
    double D2 = calculaDistancia(Q, *ball);

    if (D1 - ball->m_radi >= D2)
    {
        return Q;
    }

    else
    {
        if (ball->m_left == nullptr && ball->m_right == nullptr)
        {
            Q = calculaMesProper(targetQuery, m_coordenades);
            if (Util::DistanciaHaversine(Q, targetQuery) == 0)
            {
                return Q;
            }
        }
        else
        {
            double Da = Util::DistanciaHaversine(targetQuery, ball->m_left->m_pivot);
            double Db = Util::DistanciaHaversine(targetQuery, ball->m_right->m_pivot);

            if (Da < Db)
            {
                double control1 = Util::DistanciaHaversine(nodeMesProperRec(targetQuery, Q, ball->m_left), targetQuery);
                    if (control1 == 0)
                        return Q;
                    else
                    {
                        control1 = Util::DistanciaHaversine(nodeMesProperRec(targetQuery, Q, ball->m_right), targetQuery);
                        if (control1 == 0)
                            return Q;
                    }

            }
            else
            {
                double control1 = Util::DistanciaHaversine(nodeMesProperRec(targetQuery, Q, ball->m_right), targetQuery);
                if (control1 == 0)
                    return Q;
                else
                {
                    control1 = Util::DistanciaHaversine(nodeMesProperRec(targetQuery, Q, ball->m_left), targetQuery);
                    if (control1 == 0)
                        return Q;
                }
            }
        }

    }
    return Q;

}




