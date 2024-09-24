//=======================================================================
// Nom      : 	test.cpp
//
// But      : 	Programme de test de la classe string
//
// Création : 	18/09/2019
// Modififié:   24/11/2020
//
// Auteur	:	Christian Raymond
//=======================================================================

#include "string.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
//using std::string; //pour tester la string de la STL
using mystring::string; //pour utiliser une string à vous si elle se trouve dans un namespace mystring


string eval(const bool val, const bool obtenu)
{
	if (val == obtenu)
		return "OK";
	return "TEST NON REUSSI";
}

int main(int argc, char* argv[]) {

	//test des constructeurs
	string vide; //constructeur sans argument: on veux un chaine vide
	string TPC("TP de C++"); //appel explicite du constructeur
	string tpc="tp de c++"; //appel implcite du même constructeur
	string copie_tpc(tpc); // constructeur par copie (se génère tout seul mais ici il sera défecteux, il faut le réécrire explicitement)
	string progname(argv[0]);
	string *pcopie_tpc=new string("tp de c++"); //on fait de l'allocation dynamique, bien sûr c'est un peu ridicule dans ce cas de figure

	//test contenu et taille
	std::cout << "chaine vide:\""<<vide<<"\"  doit avoir une taille de 0:" << eval(true,vide.size()==0) << endl;
	std::cout << "chaine TPC:\""<<TPC<<"\" doit avoir une taille de 9:" << eval(true,TPC.size()==9) << endl;
	std::cout << "chaine tpc:\""<<tpc<<"\"  doit avoir une taille de 9:" << eval(true,tpc.size()==9) << endl;
	std::cout << "chaine copie_tpc:\""<<copie_tpc<<"\" doit avoir une taille de 9:" << eval(true,copie_tpc.size()==9) << endl;
	std::cout << "chaine pcopie_tpc:\""<<vide<<"\"  doit avoir une taille de 9:" << eval(true,pcopie_tpc->size()==9) << endl;
	std::cout << "chaine progname:\""<<progname<<"\"" << endl;

	//test getters et setters simples
	std::cout << "le second caractère de la chaine "<<TPC<< " est P -> "<<TPC[1]<<" "<< eval(true,TPC[1]=='P')<<endl;
	progname[0]='F';
	std::cout << "le premier caractère de la chaine "<<progname<< " est désormais F -> "<<progname[0]<<" "<< eval(true,progname[0]=='F')<<endl;

	//test operator= (cette méthode est générée automatiquement mais comme le constructeur par copie sera défectueuse (pas de copie profonde mais seulement du pointeur) à réécrire explicitement dans ce cas)
	string affectation;
	affectation= TPC;
	cout << affectation << "=" << TPC << "\n";
	cout << endl;

	//test iterateurs (la fonction générique std::find, fonctionne sur votre string si vous avez défini les méthodes begin() et end())
	//la fonction begin() renvoi un iterateur sur le premier élément du conteneur: ici un pointeur sur le premier caractère
	//la fonction end() renvoi un iterateur invalide sur le dernier élément +1 du conteneur: ici un pointeur sur la case contenant l' '\0'
	//il peut exister 2 versions de ces méthodes, une version const (iterateurs permettant le parcours en lecture seule) et une non-const permettant le parcours en lecture-écriture
	auto it=std::find(TPC.begin(),TPC.end(),'d');
	if(it!=TPC.end())
		cout<< "d found in position:"<<it-TPC.begin()<<endl;

	//test comparateurs
	cout << TPC << ">" << tpc << " doit donner FAUX:" << eval(false,TPC > tpc) << endl;
	cout << TPC << "<" << tpc << " doit donner VRAI:" << eval(true,TPC < tpc) << endl;
	cout << TPC << "==" << TPC << " doit donner VRAI:" << eval(true,TPC == TPC) << endl;
	cout << tpc << "==" << copie_tpc << " doit donner VRAI:" << eval(true,tpc == copie_tpc) << endl;
	cout << TPC << "==" << copie_tpc << " doit donner FAUX:" << eval(false,TPC == copie_tpc) << endl;
	cout << endl;

	//test operator+=
	string cat = "cat";
	cat += "dog";
	cout << cat  << " doit donner 'catdog':" << eval(true, cat == "catdog") << endl;

	string contenu("trouve moi la dedans toto");
	auto cherche1 = contenu.find("dedans");		
	cout << "sous chaine 'dedans' trouvée à position=" << cherche1 << " :" << eval(true,cherche1==14) << endl;
	auto cherche2 = contenu.find("titi");
	cout << "sous chaine 'titi' pas trouvée=" << cherche2 << " :" << eval(true, cherche2 >= contenu.size()) << endl;
	string cherche3 = contenu.substr(cherche1,4);
	cout << "sous chaine 'deda' =" << cherche3 << " :" << eval(true, cherche3 == "deda") << endl;

    //test istream operator>>	
	string libre, libre2, libre3;
	cout << "Entrez deux strings au clavier :"; //séparées par une espace et un seul "entrée"
	cin >> libre >> libre2;
	cout << "La string libre  vaut " << '"' << libre << '"' << " de taille:" << libre.size() << endl;
	cout << "La string libre2 vaut " << '"' << libre2 << '"' << " de taille:" << libre2.size() << endl;
	cout << "puis une troisième :"<<std::endl;
	cin >> libre2;
	cout << "La string libre2 vaut " << '"' << libre2 << '"' << " de taille:" << libre2.size() << endl;

	//test lecture dans un fichier d'une chaine un peu longue
	try 
	{
		constexpr const char* name="../fichier.txt";
		std::ifstream file(name);
		if(file)
		{
			string tmp;
			string res;
			while(file>>tmp)
			{
				//std::cerr<< tmp<<endl;
				res+=tmp+" ";
			}
			std::cout<< "\n------------------------------------\n"<< res << "\n------------------------------------\n";
		}
		else
		{
			std::cerr << "Fichier " << name<<" pas trouvé\n";
		}
		
	
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}


	//test constructeur par déplacement
	string vole_tpc(std::move(tpc)); //illustration de la "sémantique de déplacement" vole_tpc s'approprie le contenu de tpc ici qui est considéré mort après
	cout << "vole_tpc=" << vole_tpc << " et tpc doit etre mort" << endl;



	delete pcopie_tpc;
	return 0;

}
