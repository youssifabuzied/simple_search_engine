#include "user_interface.h"
#include <windows.h>
#include <shellapi.h>
#include <iostream>
#include <string>
using namespace std;



void user_interface::welcome_window() {
	cout << "Welcome!" << endl;
	cout << "What would you like to do?" << endl;
	cout << "1. New search" << endl;
	cout << "2. Exit" << endl;
	cout << endl;
	cout << "Type in your choice:  ";
	char ans;
	cin >> ans;
	if (ans == '1') {
		search_counter++;
		search_window();
	}
	else {
		return;
	}
}
void user_interface::search_window() {
	cout << "What are you searching for? " << endl;
	string input;
	cin.ignore();
	getline(cin, input);
	Search_string s;
	s.search_statement = input;

	search.initialize(input);
	search.perform_search();
	cout << endl;	
	results.clear();
	for (int i = 0; i < search.results.size(); i++) {
		//cout <<i+1<<"."<<"\t"<< S.results[i].URL << endl;
		results.push_back(search.results[i]);
	}
	search_results_menu();
}
void user_interface::search_results_menu() {
	if (results.size() == 0) {
		cout << "No result match your search";
		cout << endl;
		cout << "Would you like to " << endl;
		cout << "1.  New Search" << endl;
		cout << "2.  Exit" << endl;
		cout << endl;
		cout << "Type in your choice:  ";
		char ans;
		cin >> ans;
		if (ans == '1') {
			search_window();
		}
		else {
			return;
		}
	}
	else {
		for (int i = 0; i < results.size(); i++) {
			cout << i+1 << "." << "\t" << results[results.size()-1-i].URL << endl;
			cout <<"Page Score:    "<<  results[results.size() - 1 - i].score << endl;
		}
		cout << endl;
		cout << "Would you like to " << endl;
		cout << "1.  Choose a webPage to open" << endl;
		cout << "2.  New Search" << endl;
		cout << "3.  Exit" << endl;
		cout << endl;
		cout << "Type in your choice:  ";
		search.update();
		char ans;
		cin >> ans;
		if (ans == '1') {
			cout << endl;
			cout << "Type in the number of the web page:  ";
			int index;
			cin >> index;
			viewing_website_window(results.size()  - index);
		}
		else if (ans == '2') {
			search_window();
		}
		else {
			return;
		}
	}
}
void user_interface::viewing_website_window(int index) {
	search.G.Pages[results[index].CSV_index].clicks++;
	string linkChar = results[index].URL;
	wstring temp = wstring(linkChar.begin(), linkChar.end());
	LPCWSTR wideString = temp.c_str();
	ShellExecute(0, 0, wideString, 0, 0, SW_SHOW);
	cout << "You are now viewing    " << results[index].URL << endl;
	cout << endl;
	cout << "Would you like to " << endl;
	cout << "1.  Back to search results" << endl;
	cout << "2.  New Search" << endl;
	cout << "3.  Exit" << endl;
	cout << endl;
	cout << "Type in your choice:  ";
	search.update();
	char ans;
	cin >> ans;
	if (ans == '1') {
		search_results_menu();
	}
	else if (ans == '2') {
		search_window();
	}
	else {
		return;
	}	
}