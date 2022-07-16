#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "WebPage.h"
using namespace std;
class WebGraph
{
public:
	vector <WebPage> Pages;
	vector<vector<WebPage>> adjacencyList;
	void populate_URL_impressions();
	void populate_key_words();
	void populate_clicks();
	void populate_Pages_adjacency_list();
	void populate_graph_adjacency_list();
	void compute_initial_page_ranks();
};

