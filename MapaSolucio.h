#pragma once
#include "MapaBase.h"
#include "PuntDeInteresBase.h"
#include "PuntDeInteresBotigaSolucio.h"
#include "PuntDeInteresRestaurantSolucio.h"
#include "CamiSolucio.h"
#include "Util.h"
#include "GrafSolucio.h"
#include "BallTree.h"
class MapaSolucio : public MapaBase
{
public:
	MapaSolucio() {}
	~MapaSolucio();
	void getPdis(std::vector<PuntDeInteresBase*>&);
	void getCamins(std::vector<CamiBase*>&);
	void parsejaXmlElements(std::vector<XmlElement>& xmlElements);
	void afegeixRestaurant(PuntDeInteresRestaurantSolucio r) { m_PuntInteres.push_back(r.clone()); }
	void afegeixBotiga(PuntDeInteresBotigaSolucio b) { m_PuntInteres.push_back(b.clone()); }
	Coordinate buscaCoordenadesenXML(const string& id, vector<XmlElement>& xmlElements); //PER PODER BUSCAR SEGONS UN ID PER ELS CAMINS.
	Coordinate buscaCoordenadesenNode(int index, vector<XmlElement>& xmlElements);
	string comprobaID(int indexXML, vector<XmlElement>& xmlElements);
	bool comprobaName(int i, vector<XmlElement>& xmlElements);
	Coordinate buscaCoordenades(int indexXML, vector<XmlElement>& xmlElements);
	string buscaNom(int indexXML, vector<XmlElement>& xmlElements);
	string buscaHores(int indexXML, vector<XmlElement>& xmlElements);
	bool buscaCadira(int indexXML, vector<XmlElement>& xmlElements);
	string buscaCuisine(int indexXML, vector<XmlElement>& xmlElements);
	void reiniciaParseig();
	bool esUnPuntName(int indexXML, vector<XmlElement>& xmlElements);
	CamiBase* buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a);
	void generaGraf();


private:
	std::vector<PuntDeInteresBase*> m_PuntInteres;
	std::vector<CamiBase*> m_cami;
	GrafSolucio m_graf;

};

