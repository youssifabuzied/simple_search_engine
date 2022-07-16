#include "Search.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
Search::Search(string statement) {
	S.search_statement = statement;
	S.populate_keywords();
	G.populate_URL_impressions();
	G.populate_key_words();
	G.populate_clicks();
	G.populate_Pages_adjacency_list();
	G.compute_initial_page_ranks();
	vector<WebPage> Pages = G.Pages;
}
Search::Search() {
	G.populate_URL_impressions();
	G.populate_key_words();
	G.populate_clicks();
	G.populate_Pages_adjacency_list();
	G.compute_initial_page_ranks();
	vector<WebPage> Pages = G.Pages;
}
void Search::initialize(string statement) {
	S.search_statement = statement;
	S.keywords.clear();
	S.populate_keywords();
}
void Search::update() {
	fstream fout_clisks;
	fstream fout_impressions;
	fout_impressions.open("Number of impressions.csv", ios::out);
	fout_clisks.open("Clicks.csv", ios::out);
	for (int i = 0; i < G.Pages.size(); i++) {
		fout_impressions << G.Pages[i].URL << "," << G.Pages[i].impressions<<endl;
		fout_clisks << G.Pages[i].URL << "," << G.Pages[i].clicks << endl;
	}
}
void Search::perform_search() {
	results.clear();
	for (int i = 0; i < G.Pages.size(); i++) {
		if (G.Pages[i].check_match(S.keywords)) {
			G.Pages[i].calc_score();
			G.Pages[i].impressions++;
			results.push_back(G.Pages[i]);
		}
	}
	heap_sort_results(results);
}
void Search::heapify(vector<WebPage>& Pages,int n, int i) {
	int largest = i; 
	int left = 2 * i + 1; 
	int right = 2 * i + 2; 

	if (left < n && Pages[left].score > Pages[largest].score) {
		largest = left;
	}
	if (right < n && Pages[right].score > Pages[largest].score) {
		largest = right;
	}
	if (largest != i) {
		swap(Pages[i], Pages[largest]);
		heapify(Pages,n,  largest);
	}
}
void Search::build_heap(vector<WebPage> & Pages, int n) {
	for (int i = Pages.size() / 2 - 1; i >= 0; i--) {
		heapify(Pages,n, i);
	}
}
void Search::heap_sort_results(vector <WebPage>& Pages) {
	build_heap(Pages, Pages.size());
	for (int i = Pages.size() - 1; i > 0; i--) {
		swap(Pages[0], Pages[i]);
		heapify(Pages, i, 0);
	}
}

