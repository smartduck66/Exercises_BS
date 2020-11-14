// Book TCPL4 : chapitre X de l'ouvrage
// Commit initial : 30/08/2018 
// Commit en cours : 26/12/2019
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @

// Librairie indispensable sous Windows et VC++
#include "pch.h"

#include <iostream>
#include <thread>
#include <memory>
#include <algorithm>
#include <iterator>
#include <string>
#include <regex>
#include <limits>
#include <cstddef>
#include "MyHeader.h"

using namespace std;

auto print_char(int x) {
	  std::cout << "Le code ASCII décimal "<<std::dec << x << " (Hexa : "<< std::hex << x <<") correspond au caractère '" << char(x) << "'" << endl;
}


int main()
{
	try
	{
		// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
		std::locale::global(std::locale("fr-FR"));

		/*
		// X.6.2 et X.6.3
		cout << "Temps d'exécution de la boucle (x100) contenant 2 threads :" << endl;
		RunAndMeasure([&]() {
			for (int i = 0; i < 100; ++i) {
				thread th1([] {cout << "Hello "; });
				thread th2([] {cout << "world !" << endl; });

				th1.join();		// Wait for thread t1 to finish

				th2.join();		// Wait for thread t2 to finish
			}
		});
		
		// X.6.5 : check regex format in Tour of C++ pour être plus générique
		auto glambda = [](auto &s) { 
			regex pat{ R"(\d{1,10}.\d{1,10})" };
			return regex_match(s, pat); }
		;
		
		ifstream ist = open_file_read("numbers.txt");
		string s{};
		int count = 0;
		while (!ist.eof()) {					// Tant que la fin du fichier n'est pas atteinte, on continue à extraire de nouveaux enregistrements
			getline(ist, s);					// On lit une ligne terminée par un NEWLINE
			if (bool b = glambda(s)) ++count;				
			
		}
				
		ist.close();							// Fermeture du fichier

		cout << count << " nombres décimaux trouvés" << endl;

		// X.7.2 : sizeof
		if (alignment_of_v<signed char>) 
			cout << "plain chars are signed" << endl;
		else
			cout << "plain chars are UNsigned" << endl;

		// X.7.6
		struct X
		{
			enum direction { left = 'l', right = 'r' };
		};
		std::unique_ptr<X> x1 = std::make_unique<X>();
		struct C
		{
			C(int i) : i(i) {} //< constructor needed (until C++20)
			int i;
		};
		auto sp = std::make_shared<C>(12);
		cout << "size of INT : " << sizeof(int) << " - size of DOUBLE : " << sizeof(double) << " - size of ENUM : " << sizeof(X) <<
			" - size of unique PTR : " << sizeof(*x1) << " - size of shared PTR : " << sizeof(*sp)<< endl;

		// X.7.7
		
		for (int i = 97; i < 123;i++) {
			print_char(i);
		}
		for (int i = 48; i < 58; i++) {
			print_char(i);
		}
		
		// X.7.8 à X.7.10
		std::cout << "bool : " << std::dec<<std::numeric_limits<bool>::max() << " - taille : "<<sizeof(bool)<<'\n' <<
			"char : " << std::numeric_limits<char>::max() << '\n' <<
			"short : " << std::numeric_limits<short>::max() << '\n' <<
			"int : " << std::numeric_limits<int>::max() << '\n' <<
			"long : " << std::numeric_limits<long>::max() << '\n' <<
			"long long : " << std::numeric_limits<long long>::max() << '\n' <<
			"float : " << std::numeric_limits<float>::max() << '\n' <<
			"double : " << std::numeric_limits<double>::max() << '\n' <<
			"long double : " << std::numeric_limits<long double>::max() << '\n' <<
			"unsigned : " << std::numeric_limits<unsigned>::max() << '\n' <<
			"unsigned long : " << std::numeric_limits<unsigned long>::max() << " - alignment : "<< std::alignment_of_v<unsigned long><<'\n';
			
		// X.7.13
		for (int i = 4; i < 18; i++) {
			if (i == 4 or i == 5 or i == 9 or i == 12 or i == 17) cout << i << endl;
		
		}
		
		// X.8.1
		char a = 'a';
		auto p = std::make_unique<char>(a);
		int ax[10]{};
		auto p1 = &ax;
		string sx[20]{};
		auto p2 = std::make_unique<string>(sx[0]);
		auto p3 = std::make_unique<char>(*p);
		const int ci = 2;
		auto p4 = std::make_unique<int>(ci);
		int cpi = 2;
		auto p5 = std::make_unique<const int>(cpi);
		
		// X.8.3
		using UC = unsigned char;
		UC var_uc{'a'};
		using PtoI = unique_ptr<int>;
		PtoI p6 = std::make_unique<int>(ci);
		
		cout << "UC = " << var_uc << endl;
		cout << "PtoI = " << *p6 << endl;

		// X.8.4 (idem X.8.5)
		char ay[10]{"123456789"};
		auto p7 = std::make_unique<char>(ay[0]);
		auto p8 = std::make_unique<char>(ay[8]);
		cout << "Nombre de caractères : " << (*p8) - (*p7) << endl;

		// X.8.7
		int i1 = 1;
		int i2 = 2;
		auto p9 = std::make_unique<int>(i1);
		auto p10 = std::make_unique<int>(i2);

		// before
		std::cout << *p9 << ' ' << *p10 << '\n';

		std::swap(p9, p10);

		// after
		std::cout << *p9 << ' ' << *p10 << '\n';

		// X.8.8
		char str[] = "a short string";
		cout << "Taille lhs : " << sizeof(str) << endl;
		cout << "Taille rhs : " << sizeof("a short string") << endl;
		
		// X.8.10
		string months [12]{"Jan","Fév","Mars","Avril","Mai","Juin","Juillet","Août","Sept","Oct","Nov","Déc"};
		for (auto x:months) 
			cout << x << '-';
		cout << endl;

		// X.8.11
		vector <string> words{};
		cout << "Saisir des mots (quit pour stopper) :" << endl;
		for (;;) {
			string saisie{};
			cin >> saisie;
			if (saisie == "quit") break;
			words.push_back(saisie);
		}
		sort(words.begin(),words.end());
		for (auto x:words)
			cout << x << '-';
		cout << words.size() << " mots saisis"<< endl;
		

		// X.8.12
		const string word_to_analyse = "xfaxabaacbaxabb";
		const string n1 = "ab";
		int nb_occurences = 0;
		auto wb = std::begin(word_to_analyse);
		auto we = std::end(word_to_analyse);
		
		for (;;) {
			auto resultat = std::search(wb, we, n1.begin(), n1.end());
			if (resultat != we) {
				nb_occurences++;
				wb = resultat + n1.size();
			}
			else
				break;
		
		}
		
		cout << "Le mot " << word_to_analyse << " contient " << nb_occurences << " occurences de la chaîne " << n1 << endl;
 

		// Fin des exos
		keep_window_open();
		return 0;
	}


	catch (runtime_error& e)
	{	// this code is to produce error messages
		cout << e.what() << '\n';
		keep_window_open("q");	// For some Windows(tm) setups
	}


}

