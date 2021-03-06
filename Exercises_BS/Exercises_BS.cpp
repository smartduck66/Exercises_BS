// Book TCPL4 : chapitre X de l'ouvrage
// Commit initial : 30/08/2018 
// Commit en cours : 16/01/2021
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @

// Librairie indispensable sous Windows et VC++
#include "pch.h"

#include <iostream>
#include <sstream>
#include <thread>
#include <memory>
#include <algorithm>
#include <iterator>
#include <string>
#include <regex>
#include <limits>
#include <cstddef>
#include <vector>
#include <array>
#include <cmath>
#include <numeric>
#include "MyHeader.h"

using namespace std;

auto print_char(int x) {
	  std::cout << "Le code ASCII décimal "<<std::dec << x << " (Hexa : "<< std::hex << x <<") correspond au caractère '" << char(x) << "'" << endl;
}

// X.9.5
enum Season { spring, summer, autumn, winter };
ostream& operator<<(ostream& os, const Season& s)
{
	vector<string>season_names = { "printemps", "été", "automne", "hiver" };
	return os << '(' << season_names[s] << ')';
}

inline Season operator++ (Season const& s) {
	if (s == winter)
		return spring; // on revient à 0
	else
		return static_cast<Season>((static_cast<int>(s) + 1));
}

inline Season operator-- (Season const& s) {
	if (s == spring)
		return winter; // on revient à 3
	else
		return static_cast<Season>((static_cast<int>(s) - 1));
}
// -----------------

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
		 

		// X.9.1 (reprise des exos le 19/12/2020)
		struct X91
		{
			bool a;
			char b;
			int c;
			long d;
			double e;
			long double f;
		};
		X91 x91{};
		cout << "Taille struc X91 : " << sizeof(x91) << endl<<endl;

		// X.9.2
		std::array<char[10], 12> months = { "Janvier", "février","mars","avril","mai","juin","juillet","août","septembre","octobre","novembre","décembre" };
		std::array<int, 12> nbdays = { 31, 28,31,30,31,30,31,31,30,31,30,31 };
		for (int i = 0; i < 12;++i) cout << months[i] << " : " << nbdays[i]<< endl;
		cout << endl;

		struct s_months { string m; int d;};
		s_months months2[12] = { {"Janvier",31}, {"février",28},{"mars",31},{"avril",30},{"mai",31},{"juin",30},{"juillet",31},{"août",31},{"septembre",30},{"octobre",31},{"novembre",30},{"décembre",31} };
		for (auto x : months2) cout <<x.m<< " : "<<x.d << endl;
		cout << endl;

		// X.9.4
		struct s_date { int day; int month; int year; };
		s_date date_now = {19,12,2020};
		auto const output_date = [](s_date const date) {cout << "La date est : " << date.day << "/" << date.month << "/" << date.year << endl; };
		output_date(date_now);
		auto const input_date = []() {
			int d = 0, m = 0, y = 0;
			cout << "jour :";
			cin >> d;
			cout << "mois :";
			cin >> m;
			cout << "année :";
			cin >> y;
			s_date date{d,m,y};
			return date;
		};
		output_date(input_date());

		// X.9.5
		Season s = spring;
		cout << --s << endl;
		cout << ++s << endl;
		
		// X.10.1
		string input_line{"?Andromede?"};
		size_t max_length = input_line.size();
		int quest_count{};

		// Boucle type 1
		for (int i = 0; i != max_length; ++i)
			if (input_line[i] == '?') ++quest_count;
		cout << "for classique - quest_count: " << quest_count << endl;

		// Boucle type 2
		int compteur = 0;
		quest_count = 0;
		while (compteur != max_length)
		{
			if (input_line[compteur] == '?') ++quest_count;
			++compteur;
		}
		cout << "while - quest_count: " << quest_count << endl;

		// Boucle type 3
		quest_count = 0;
		char input_line1[12]= "?Andr?mede?";
		 
		for (int i = 0; i != max_length; ++i) {
			auto p = std::make_unique<char>(input_line1[i]);
			if (*p == '?') ++quest_count;
		}
		cout << "For avec pointeur - quest_count: " << quest_count << endl;

		// X.10.4
		auto atoi = [](const char* s) {
			int i{};
			int t = std::strlen(s)-1;
			string digits{ "0123456789" };
			for (int r = t; r >= 0; --r) {
				std::string s1(1, s[r]);
				int p = digits.find(s1);
				i += p * (t==r ? 1 : pow(10, t - r));
				
			}
			return i;};
		
		cout << atoi("985941") << endl;

		// X.10.5
		auto itoa = [](const float i) {
			string c{};
			float d = i;

			while (trunc(d) != 0) {
				d = trunc(d) / 10;
				float whole{};
				c += std::to_string(lround(std::modf(d, &whole) * 10));
				
			}

			return c; };

		float i = 4985;
		std::string c;
		string sx = itoa(i);
		std::copy(sx.crbegin(), sx.crend(), std::back_inserter(c));
		std::cout << c << endl;
		
		// X.11.2
		cout << "Saisir des séquences 'nom valeur' (quit pour stopper) :" << endl;
		vector <string> nomX112{};
		vector <double> valX112{};
		for (;;) {
			string nom{};
			double valeur{};
			cin >> nom >> valeur;
			if (nom == "quit") break;
			nomX112.push_back(nom);
			valX112.push_back(valeur);
		}
		double sum = std::accumulate(valX112.begin(), valX112.end(), 0);
		cout << "Somme des valeurs : " << sum << " - Moyenne des valeurs : " << sum / valX112.size() << endl;
		
		// X.11.3 : and, and_eq, bitand, bitor, compl, not, not_eq, or, or_eq, xor, xor_eq (logical operations keywords)
		// Test pour xor
		bool x1 = 0 xor 0;
		cout << "0 xor 0 : " << x1 << endl;
		bool x2 = 1 xor 1;
		cout << "1 xor 1 : " << x2 << endl;
		bool x3 = 0 xor 1;
		cout << "0 xor 1 : " << x3 << endl;
		bool x4 = 1 xor 0;
		cout << "1 xor 0 : " << x4 << endl;
		
		// X.11.7 : new strlen, strcpy, strcmp
		const char* s2 = "hello";
		const char* p = &s2[0];
		int compteur = 0;
		while (*p!='\0')
		{
			++compteur;
			++p;

		}
		cout << "nb caractères : "<< compteur << endl;	// strlen
		char* s3 = new char[compteur + 1];
		int compteur2 = 0;
		while (compteur2 != compteur)
		{
			s3[compteur2] = s2[compteur2];
			++compteur2;
		}
		s3[compteur2] = '\0';
		cout << "La nouvelle C-style string copiée : " << s3 << endl; // strcpy
		int compteur3 = 0;
		// s3[0] = 'd';
		bool identique = true;
		while (compteur3 != compteur)
		{
			if (s2[compteur3] != s3[compteur3]) { identique = false; break; }
			++compteur3;
		}
		cout << "Les deux chaînes sont-elles identiques (0=false ; 1 = true) ? " << identique << endl; // strcmp

		// X.11.9 : cat()
		string cat{};
		int compteur4 = 0;
		while (compteur4 != compteur)
		{
			cat +=s2[compteur4];
			++compteur4;
		}
		int compteur5 = 0;
		while (compteur5 != compteur)
		{
			cat += s3[compteur5];
			++compteur5;
		}
		cout << "Nouvelle string issue de la concaténation de deux C-style string : " << cat << endl;

		// X.11.10 : rev()
		char* s4 = new char[compteur + 1];
		int compteur6 = compteur-1;
		int compteur7 = 0;
		while (compteur6 >= 0)
		{
			s4[compteur7] = s2[compteur6];
			--compteur6;
			++compteur7;
		}
		s4[compteur7] = '\0';
		cout << "C-style string inversée : " << s4 << endl;
		*/

		// X.12.5 : count a given keyword through this code source
		auto in = open_file_read("CodeSourceQIF2.txt");
		int occurences = 0;
		string keyword = "db.exec";
		std::string::size_type n;
		for (string s; getline(in, s);) {
			n = s.find(keyword);
			if (n != std::string::npos) ++occurences;

		}
		cout << "Le mot-clé '" << keyword << "' a été trouvé " << occurences << " fois dans le code source" << endl;


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

