#pragma once
#include"WebGraph.h"
#include "Search_string.h"
class Search
{
public:
	Search(string statement);
	Search();
	WebGraph G;
	Search_string S;
	vector <WebPage> results;
	void rank_pages();
	void perform_search();
	void build_heap(vector<WebPage>& Pages, int n);
	void heapify(vector<WebPage>& Pages,int n, int i);
	void heap_sort_results(vector<WebPage>& Pages);
	void initialize(string statement);
	void update();
};

