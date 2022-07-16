#include "Search_string.h"
#include "key_word.h"
#include <iostream>
using namespace std;

void Search_string::populate_keywords() {
	key_word keyW;
	bool quote = false;
	bool quote_closed = false;
	string key = "";
	bool And = false;
	bool Or = false;
	int index = 0;
	string natural_key = "";
	for (int i = 0; i < search_statement.size(); i++) {
		if (search_statement[i] == ' ') {
			if (i > 0 && search_statement[i] == ' ' && search_statement[i - 1] == ' ' && !quote) {
				continue;
			}
			if (i > 0 && search_statement[i - 1] != '\"' && !quote) {
				if (natural_key == "AND") {
					keywords[index - 1].priority = 1;
					And = true;
				}
				else if (natural_key == "OR") {
					if (keywords[index - 1].priority != 1) {
						keywords[index - 1].priority = 0;
					}
					else {
						keywords[index - 1].priority = 0.5;
					}
					Or = true;
				}else if (And && key != "AND") {
					keyW.keyword = key;
					keyW.priority = 1;
					keywords.push_back(keyW);
					index++;
					And = false;
				}else if (Or && key != "OR") {
					keyW.keyword = key;
					keyW.priority = 0;
					keywords.push_back(keyW);
					index++;
					Or = false;
				}
				else {
					keyW.keyword = key;
					if (index > 0 &&  keywords[index - 1].priority != 1) {
						keywords[index - 1].priority = 0;
					}
					else if (index > 0) {
						keywords[index - 1].priority = 0.5;
					}
					keyW.priority = 0;
					keywords.push_back(keyW);
					index++;
				}
				key = "";
				natural_key = "";
				keyW.keyword = "";
			}if (quote) {
				key += ' ';
			}
		}
		else if (search_statement[i] == '\"') {
			if (quote) {
				if (search_statement[i - 1] != '\"') {
					keyW.keyword = key;
					if (And) {
						keyW.priority = 1;
						And = false;
					}
					else if (Or) {
						keyW.priority = 0;
					}
					else {
						if (index > 0 && keywords[index - 1].priority != 1) {
							keywords[index - 1].priority = 0;
						}
						else if (index > 0) {
							keywords[index - 1].priority = 0.5;
						}
						keyW.priority = 0;
						keywords.push_back(keyW);
						index++;
					}
					keywords.push_back(keyW);
					index++;
					key = "";
					natural_key = "";
					keyW.keyword = "";
					quote_closed = true;
					quote = false;
				}
			}
			else {
				quote = true;
				quote_closed = false;
			}
		}
		else {
			if (quote) {
				key += search_statement[i];
				quote_closed = false;
			}
			else {
				natural_key += search_statement[i];
				if (search_statement[i] <= 90) {
					search_statement[i] += 32;
					key += search_statement[i];
					quote_closed = false;
					
				}
				else {
					key += search_statement[i];
					quote_closed = false;
				}
			}
			
			if (i == search_statement.size() - 1) {
				if (And) {
					keyW.keyword = key;
					keyW.priority = 1;
					keywords.push_back(keyW);
					index++;
				}
				else if (Or) {
					keyW.keyword = key;
					keyW.priority = 0;
					keywords.push_back(keyW);
					index++;
				}
				else {
					keyW.keyword = key;
					keyW.priority = 0;
					keywords.push_back(keyW);
					index++;
				}
			}
		}
	}

}
