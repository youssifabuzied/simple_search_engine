#include "WebPage.h"
#include <iostream>
using namespace std;
bool WebPage::check_match(vector <key_word> keys) {
	bool result = true;
	int last_priority;
	bool last_result;
	for (int i = 0; i < keys.size(); i++) {
		bool temp_result = false;
		if (i == 0) {
			for (int j = 0; j < keywords.size(); j++) {
				if (keys[i].keyword == keywords[j]) {
					temp_result = true;
					break;
				}
			}
			if (!temp_result) {
				last_result = false;
				last_priority = keys[i].priority;
			}
			else {
				if (keys[i].priority == 0 ) {
					return true;
				}
				last_result = true;
				last_priority = keys[i].priority;
			}
		}
		else {
			if (keys[i].priority != 0)
			{
				if (last_priority == 1 && !last_result) {
					last_priority = keys[i].priority;
					continue;
				}
				else if (last_priority == 1 && last_result) {
					for (int j = 0; j < keywords.size(); j++) {
						if (keys[i].keyword == keywords[j]) {
							temp_result = true;
							break;
						}
					}
					if (!temp_result) {
						last_result = false;
						last_priority = keys[i].priority;
					}
					else {
						last_result = true;
						last_priority = keys[i].priority;
						if (i == keys.size() - 1) {
							return true;
						}
						if (keys[i].priority == 0.5) {
							return true;
						}
					}
				
				}
				else if (last_priority == 0.5) {
					for (int j = 0; j < keywords.size(); j++) {
						if (keys[i].keyword == keywords[j]) {
							temp_result = true;
							break;
						}
					}
					last_result = temp_result;
					last_priority = keys[i].priority;
				}
				else if (last_priority == 0) {
					for (int j = 0; j < keywords.size(); j++) {
						if (keys[i].keyword == keywords[j]) {
							temp_result = true;
							break;
						}
					}
					if (!temp_result) {
						last_result = false;
						last_priority = keys[i].priority;
					}
					else {
						last_result = true;
						last_priority = keys[i].priority;
					}
				}
			}
			else {
				if (last_priority == 1 && last_result) {
					return true;
				}
				for (int j = 0; j < keywords.size(); j++) {
					if (keys[i].keyword == keywords[j]) {
						temp_result = true;
						break;
					}
				}if (temp_result) {
					return true;
				}
				else {
					last_priority = keys[i].priority;
					last_result = false;
				}
			}
		}
	}
	return false;		
}
void WebPage::calc_score() {
	CTR = clicks / impressions;
	score = 0.4 * normalized_page_rank + ((1 - (0.1 * impressions) / (1 + 0.1 * impressions)) * normalized_page_rank + ((0.1 * impressions) / (1 + 0.1 * impressions)) * CTR) * 0.6;
}