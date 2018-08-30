// Book TCPL4 : chapitre X de l'ouvrage
// Commit initial : 30/08/2018 
// Commit en cours : 30/08/2018
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @

// Librairie indispensable sous Windows et VC++
#include "pch.h"

#include<iostream>
#include "MyHeader.h"

using namespace std;



int main()
{
	try
	{
		// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
		std::locale::global(std::locale("fr-FR"));

		cout << "Hello André" << endl;

		keep_window_open();

		return 0;
	}


	catch (runtime_error& e)
	{	// this code is to produce error messages
		cout << e.what() << '\n';
		keep_window_open("q");	// For some Windows(tm) setups
	}


}