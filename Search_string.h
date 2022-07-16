#pragma once
#include <iostream>
#include "key_word.h"
#include <map>
#include <vector>
#include <iterator>
#include <stack>
using namespace std;


class Search_string
{
public:
	string search_statement;
	vector <key_word> keywords;
	void populate_keywords();
};

