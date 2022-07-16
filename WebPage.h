#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "key_word.h"
#include <vector>
using namespace std;
class WebPage
{
public:
	int CSV_index;        //
	vector <string> keywords;  //
	double impressions; //
	double clicks;  //
	double CTR;
	double page_rank;
	//double previous_ratio;
	//int pagerank;
	double normalized_page_rank;
	double score;
	string URL;    //
	vector<WebPage> adjacency_list;
	vector<WebPage> reverse_adjacency_list;
	bool check_match(vector <key_word> keys);
	void calc_score();
};

