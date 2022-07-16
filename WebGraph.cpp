#include "WebGraph.h"
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iterator>

using namespace std;
void WebGraph::populate_URL_impressions() {
	WebPage temp_page;
	fstream fin;
	fin.open("Number of impressions.csv", ios::in);
	int row_number = 0;
	string temp, line, word;
	while (fin>>temp)
	{
		stringstream S(temp);
		int counter = 0;
		while (getline(S, word, ',')) {
			if (counter == 0) {
				temp_page.CSV_index = row_number;
				temp_page.URL = word;
			}
			else {
				temp_page.impressions = stoi(word);
			}
			counter++;
		}
		Pages.push_back(temp_page);
		row_number++;
	}
}
void WebGraph::populate_key_words() {
	fstream fin;
	fin.open("Keywords.csv", ios::in);
	int row_number = 0;
	string temp, line, word;
	while (getline(fin, temp))
	{
		stringstream S(temp);
		int counter = 0;
		while (getline(S, word, ',')) {
			if (counter != 0) {
				Pages[row_number].keywords.push_back(word);
			}
			counter++;
		}
		row_number++;
	}
}
void WebGraph::populate_clicks() {

	fstream fin;
	fin.open("Clicks.csv", ios::in);
	int row_number = 0;
	string temp, word;
	while (fin>>temp)
	{
		stringstream S(temp);
		int counter = 0;
		while (getline(S, word, ','))
		{
			if (counter != 0) {
				Pages[row_number].clicks = stoi(word);
			}
			counter++;
		}
		row_number++;
	}
}
void WebGraph::populate_Pages_adjacency_list() {
	fstream fin;
	fin.open("Web graph file.csv", ios::in);
	string temp, word;
	while (fin >> temp) {
		stringstream S(temp);
		int counter = 0;
		int srcindex = 0;
		int desindex = 0;
		while (getline(S, word, ',')) {
			if (counter == 0) {
				for (int i = 0; i < Pages.size(); i++) {
					if (Pages[i].URL == word) {
						srcindex = i;
						break;
					}
				}
			}
			else {
				for (int i = 0; i < Pages.size(); i++) {
					if (Pages[i].URL == word) {
						desindex = i;
						
						break;
					}
				}
				Pages[srcindex].adjacency_list.push_back(Pages[desindex]);
				Pages[desindex].reverse_adjacency_list.push_back(Pages[srcindex]);
			}
			
			counter++;
		}
	}
}
void WebGraph::populate_graph_adjacency_list() {
	for (int i = 0; i < Pages.size(); i++) {
		vector<WebPage> temp = Pages[i].adjacency_list;
		WebPage Page = Pages[i];
		adjacencyList[i].push_back(Pages[i]);
		adjacencyList[i].insert(adjacencyList[i].end(), Pages[i].adjacency_list.begin(), Pages[i].adjacency_list.end());	
	}
}
void WebGraph::compute_initial_page_ranks() {
	double n = Pages.size();
	vector <double> last_iteration;
	for (int i = 0; i < n; i++) {
		Pages[i].page_rank = 1 / (n) ;
		last_iteration.push_back(1 / (n) );
	}
	for (int i = 0; i < 200; i++) {
		double sum = 0;
		for (int j = 0; j < n; j++) {
			double ratio = 0;
			for (int k = 0; k < Pages[j].reverse_adjacency_list.size(); k++) {
				int liti = Pages[j].reverse_adjacency_list[k].CSV_index;
				ratio += last_iteration[liti] / Pages[liti].adjacency_list.size();
			}
				Pages[j].page_rank = 0.85*ratio + 0.15/n;
				sum += Pages[j].page_rank;
		}
		for (int j = 0; j < n; j++) {
			Pages[j].normalized_page_rank = Pages[j].page_rank / sum;
			last_iteration[j] = Pages[j].normalized_page_rank;
		}
	}
}
