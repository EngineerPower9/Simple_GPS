#include "MapaSolucio.h"

MapaSolucio::~MapaSolucio()
{
	vector<PuntDeInteresBase*>::iterator actual = m_PuntInteres.begin();
	for (actual; actual != m_PuntInteres.end(); actual++)
	{

		m_PuntInteres.pop_back();

	}
}
void MapaSolucio::getPdis(std::vector<PuntDeInteresBase*>& vec)
{
	for (int i = 0; i < m_PuntInteres.size(); i++)
	{
		vec.push_back(m_PuntInteres[i]);
	}

}
void MapaSolucio::getCamins(std::vector<CamiBase*>& cami)
{
	for (int i = 0; i < m_cami.size(); i++)
	{
		cami.push_back(m_cami[i]);
	}

}
void MapaSolucio::parsejaXmlElements(vector<XmlElement>& xmlElements)
{
	reiniciaParseig();

	//PUNTS DE INTERES BASE
	for (int i = 0; i < xmlElements.size(); i++)
	{
		//IDENTIFIQUEM SI ÉS UN NODE

		if (xmlElements[i].id_element == "node" && xmlElements[i].fills.size() > 0)
		{
			bool trobatName = esUnPuntName(i, xmlElements);
			bool trobat = false;
			if (trobatName && xmlElements[i].fills[0].first == "tag")
			{
				//BOTIGA

				int s = 0;

				while (!trobat && s < xmlElements[i].fills.size())
				{
					//BOTIGA

					if (xmlElements[i].fills[s].second[0].second == "shop")
					{
						trobat = true;

						string name = "unknown";
						string botiga = "unknown";
						Coordinate cord;
						string hores = "unknown";
						string opening_hours = "unknown";
						bool cadiraRodes = false;

						//BUSQUEM TIPUS DE BOTIGA
						botiga = xmlElements[i].fills[s].second[1].second;

						//BUSQUEM COORDENADES
						cord = buscaCoordenades(i, xmlElements);

						//BUSQUEM NOM
						name = buscaNom(i, xmlElements);

						//BUSQUEM HORES
						hores = buscaHores(i, xmlElements);

						//BUSQUEM CADIRA DE RODES
						cadiraRodes = buscaCadira(i, xmlElements);


						//AFEGIM BOTIGA
						PuntDeInteresBotigaSolucio p(cord, name, botiga, hores, cadiraRodes);
						afegeixBotiga(p);
					}


					//RESTAURANT
					else
					{
						if (xmlElements[i].fills[s].second[0].second == "amenity" && xmlElements[i].fills[s].second[1].second == "restaurant")
						{
							trobat = true;
							Coordinate cord;
							string name = "unknown";
							string openingHours = "unknown";
							bool cadiraRodes = false;
							string cuisine = "unknown";

							//BUSQUEM COORDENADES
							cord = buscaCoordenades(i, xmlElements);

							//BUSQUEM NOM
							name = buscaNom(i, xmlElements);

							//BUSQUEM HORES
							openingHours = buscaHores(i, xmlElements);

							//BUSQUEM CUISINE
							cuisine = buscaCuisine(i, xmlElements);

							//BUSQUEM CADIRA DE RODES
							cadiraRodes = buscaCadira(i, xmlElements);

							//CREEM RESTAURANT
							PuntDeInteresRestaurantSolucio rest(cord, name, openingHours, cadiraRodes, cuisine);
							afegeixRestaurant(rest);
						}
						else
							s++;
					}
				}

			}
			if (!trobat && trobatName)
			{
				//SI NO ÉS NI BOTIGA NI RESTAURANT ES SIMPLEMENT UN PUNT D'INTERÈS

				trobat = true;
				Coordinate cord;
				string name = "unknown";
				int r = 0;

				//BUSQUEM COORDENADES
				cord = buscaCoordenades(i, xmlElements);

				//BUSQUEM NOM
				name = buscaNom(i, xmlElements);

				//AFEGIM PUNT
				m_PuntInteres.push_back(new PuntDeInteresBase(cord, name));
			}

		}


	}

	//CAMINS
	for (int i = 0; i < xmlElements.size(); i++)
	{

		if (xmlElements[i].id_element == "way" && xmlElements[i].fills.size() > 0)
		{
			int r = 0;
			bool trobat = false;
			while (r < xmlElements[i].fills.size() && !trobat)
			{
				if (xmlElements[i].fills[r].first == "tag")
				{
					//MIREM SI ÉS HIGHWAY
					if (xmlElements[i].fills[r].second[0].second == "highway")
					{
						CamiSolucio cami;
						//MIREM COORDENADES
						int l = 0;
						while (l < xmlElements[i].fills.size() && !trobat)
						{
							if (xmlElements[i].fills[l].first == "nd")
							{

								string id = xmlElements[i].fills[l].second[0].second;
								Coordinate cord1 = buscaCoordenadesenXML(id, xmlElements);
								cami.afegeixPunt(cord1);
								l++;
							}
							else
								trobat = true;

						}

						m_cami.push_back(new CamiSolucio(cami));

					}
					else
					{
						r++;
					}

				}
				else
					r++;
			}
		}

	}
}
Coordinate MapaSolucio::buscaCoordenadesenXML(const string& id, vector<XmlElement>& xmlElements)
{
	bool trobat = false;
	int i = 0;
	Coordinate co;
	co.lat = 0;
	co.lon = 0;

	while (!trobat && i < xmlElements.size())
	{

		if (comprobaID(i, xmlElements) == id)
		{
			co = buscaCoordenadesenNode(i, xmlElements);
			trobat = true;
		}
		else
		{
			i++;
		}
	}




	return co;
}
Coordinate MapaSolucio::buscaCoordenadesenNode(int i, vector<XmlElement>& xmlElements)
{

	Coordinate cord;
	cord.lat = 0;
	cord.lon = 0;
	bool trobatCord1 = false;
	bool trobatCord2 = false;
	int r = 0;
	while (!trobatCord1 && !trobatCord2 && r < xmlElements[i].atributs.size())
	{
		if (xmlElements[i].atributs[r].first == "lat")
		{
			cord.lat = stod(xmlElements[i].atributs[r].second);
			trobatCord1 = true;
			r++;
			cord.lon = stod(xmlElements[i].atributs[r].second);
			trobatCord2 = true;
		}
		else
			r++;

	}
	return cord;
}
string MapaSolucio::comprobaID(int indexXML, vector<XmlElement>& xmlElements)
{
	int s = 0;
	bool trobat = false;
	while (!trobat && s < xmlElements[indexXML].atributs.size())
	{
		if (xmlElements[indexXML].atributs[s].first == "id")
			trobat = true;
		else
			s++;
	}

	return xmlElements[indexXML].atributs[s].second;
}
bool MapaSolucio::comprobaName(int i, vector<XmlElement>& xmlElements)
{
	bool interes = true;
	int s = 0;
	int r = 0;
	while (s < xmlElements[i].fills.size() && interes)
	{
		while (r < xmlElements[i].fills[s].second.size() && interes)
		{
			string valor = xmlElements[i].fills[s].second[r].second;
			if (valor == "highway" || valor == "public_transport" || valor == "access" || valor == "entrance")
			{
				interes = false;
			}
			else
			{
				r++;
			}
		}
		s++;
		r = 0;
	}


	return interes;
}
Coordinate MapaSolucio::buscaCoordenades(int i, vector<XmlElement>& xmlElements)
{
	Coordinate cord;
	bool trobatCord1 = false;
	bool trobatCord2 = false;
	int r = 0;
	while (!trobatCord1 && !trobatCord2 && r < xmlElements[i].atributs.size())
	{
		if (xmlElements[i].atributs[r].first == "lat")
		{
			cord.lat = stod(xmlElements[i].atributs[r].second);
			trobatCord1 = true;
			r++;
			cord.lon = stod(xmlElements[i].atributs[r].second);
			trobatCord2 = true;
		}
		else
			r++;

	}
	return cord;
}
string MapaSolucio::buscaNom(int i, vector<XmlElement>& xmlElements)
{
	int r = 0;
	string name;
	bool trobatNom = false;

	while (!trobatNom && r < xmlElements[i].fills.size())
	{
		if (xmlElements[i].fills[r].second[0].second == "name")
		{
			name = xmlElements[i].fills[r].second[1].second;
			trobatNom = true;
		}
		else
			r++;
	}
	return name;
}
string MapaSolucio::buscaHores(int i, vector<XmlElement>& xmlElements)
{
	int r = 0;
	string hores;
	bool trobatHores = false;
	r = 0;
	while (!trobatHores && r < xmlElements[i].fills.size())
	{
		if (xmlElements[i].fills[r].second[0].second == "opening_hours")
		{
			hores = xmlElements[i].fills[r].second[1].second;
			trobatHores = true;
		}
		else
			r++;
	}
	return hores;
}
bool MapaSolucio::buscaCadira(int i, vector<XmlElement>& xmlElements)
{
	bool trobatRodes = false;
	int r = 0;
	bool cadiraRodes = false;
	while (!trobatRodes && r < xmlElements[i].fills.size())
	{

		if (xmlElements[i].fills[r].second[0].second == "wheelchair")
		{
			trobatRodes = true;
			if (xmlElements[i].fills[r].second[1].second == "yes")
				cadiraRodes = true;
			else
				cadiraRodes = false;

		}
		else
			r++;
	}

	return cadiraRodes;
}
string MapaSolucio::buscaCuisine(int i, vector<XmlElement>& xmlElements)
{
	int r = 0;
	bool trobatCuisine = false;
	string cuisine;
	while (!trobatCuisine && r < xmlElements[i].fills.size())
	{
		if (xmlElements[i].fills[r].second[0].second == "cuisine")
		{
			cuisine = xmlElements[i].fills[r].second[1].second;
			trobatCuisine = true;
		}
		else
			r++;
	}
	return cuisine;
}
void MapaSolucio::reiniciaParseig()
{
	while (m_PuntInteres.size() > 0)
	{
		m_PuntInteres.pop_back();
	}
	while (m_cami.size() > 0)
	{
		m_cami.pop_back();
	}
}
bool MapaSolucio::esUnPuntName(int i, vector<XmlElement>& xmlElements)
{
	bool trobatName = false;
	int control = 0;
	while (!trobatName && control < xmlElements[i].fills.size())
	{
		if (xmlElements[i].fills[control].second[0].second == "name")
		{
			if (comprobaName(i, xmlElements))
				trobatName = true;
			else
				control++;

		}
		else
			control++;
	}
	return trobatName;
}
CamiBase* MapaSolucio::buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a)
{
	generaGraf();
	BallTree busca;
	busca.construirArbre(m_graf.getCoordinates());
	Coordinate from = busca.calculaMesProper(desde->getCoord(), m_graf.getCoordinates());
	Coordinate to = busca.calculaMesProper(a->getCoord(), m_graf.getCoordinates());
	std::vector<double> dist;
	std::vector<int>distAnterior;
	stack<Coordinate>cami;
	m_graf.camiMesCurt(from, to, cami);
	CamiBase* solucio = new CamiSolucio();
	while(!cami.empty())
	{
		solucio->afegeixPunt(cami.top());
		cami.pop();
	}
	return solucio;
}
void MapaSolucio::generaGraf()
{

	for (int i = 0; i < m_cami.size(); i++)
	{
		vector<Coordinate> aux = m_cami[i]->getCamiCoords();
		for (int j = 0; j < aux.size(); j++)
		{
			int pos = m_graf.existeixNode(aux[j]);
			if (pos == -1)
			{
				m_graf.afegirNode(aux[j]);
			}
	
		}

		for (int j = 0; j < aux.size()-1; j++)
		{
			int pos1 = m_graf.existeixNode(aux[j]);
			int pos2 = m_graf.existeixNode(aux[j + 1]);
			double distance = Util::DistanciaHaversine(aux[j], aux[j + 1]);

			m_graf.inserirAresta(pos1, pos2, distance);

		}
	}

}

