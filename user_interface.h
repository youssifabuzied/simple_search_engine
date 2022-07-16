#pragma once
#include "search.h"
#include <vector>
class user_interface
{
public :
	void welcome_window();
	void search_window();
	void search_results_menu();
	void viewing_website_window(int index);
	vector <WebPage> results;
	Search search;
	int search_counter = 0;
};

