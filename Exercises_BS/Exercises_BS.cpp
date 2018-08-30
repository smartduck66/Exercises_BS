// Book TCPL4 : chapitre X de l'ouvrage
// Commit initial : 30/08/2018 
// Commit en cours : 30/08/2018
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @

// Librairie indispensable sous Windows et VC++
#include "pch.h"

#include <iostream>
#include <thread>
#include <iterator>
#include <string>
#include <regex>
#include "MyHeader.h"

using namespace std;

bool is_dec(string& s)
{
	// Vérification du format de la référence passée en paramètre
	// n.n (limités à 10 avant et après la virgule)
	regex pat{ R"(\d{1,10}.\d{1,10})" };
	return regex_match(s, pat);
}

int main()
{
	try
	{
		// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
		std::locale::global(std::locale("fr-FR"));

		// X.6.2 et X.6.3
		cout << "Temps d'exécution de la boucle (x100) contenant 2 threads :" << endl;
		RunAndMeasure([&]() {
			for (int i = 0; i < 100; ++i) {
				thread th1([] {cout << "Hello "; });
				thread th2([] {cout << "world !" << endl; });

				// Wait for thread t1 to finish
				th1.join();

				// Wait for thread t2 to finish
				th2.join();
			}
		});
		
		// X.6.5 : check regex format in Tour of C++ pour être plus générique
		ifstream ist = open_file_read("numbers.txt");
		string s{};
		int count = 0;
		regex pat{ R"(\d{1,10}.\d{1,10})" };
		while (!ist.eof()) {					// Tant que la fin du fichier n'est pas atteinte, on continue à extraire de nouveaux enregistrements
			getline(ist, s);					// On lit une ligne terminée par un NEWLINE
			if (is_dec(s)) ++count;				// Alternative : lambda
			
		}
				
		ist.close();							// Fermeture du fichier

		cout << count << " nombres décimaux trouvés" << endl;


		keep_window_open();

		return 0;
	}


	catch (runtime_error& e)
	{	// this code is to produce error messages
		cout << e.what() << '\n';
		keep_window_open("q");	// For some Windows(tm) setups
	}


}