#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

string newPassword(string a, string b) {
	int len = min(a.size(), b.size());
	string newStr, biggerStr = (a.size() > b.size()) ? a : b;

	for (int i = 0; i < len; i++){
		newStr += a[i];
		newStr += b[i];
	}

	if(biggerStr.size() - newStr.size() != 0)
		newStr += biggerStr.substr(len);	
	return newStr;
}

vector<string> processLogs(vector<string> logs, int threshold) {
	unordered_map<string, int> data;

	for (size_t i = 0; i < logs.size(); i++){
		int firstSpace = logs[i].find(' '), secondSpace = logs[i].find(' ', firstSpace + 1);
		string sender = logs[i].substr(0, firstSpace);
		string receiver = logs[i].substr(firstSpace + 1, secondSpace - firstSpace - 1 );
		
		//cout << "sender: " << sender << "ls and receiver: " << receiver << "ls" << endl;
		if(sender == receiver)
		    data[sender]++;
		else{
		    data[sender]++;
		    data[receiver]++;
		}
 	}

	vector<string> result;
	vector<pair<string, int>> sortedOccurences;
	int currentIndex = 0;
	for (auto i = data.begin(); i != data.end(); i++){

		//Only add the key-value pair if the value is >= to the threshold
		if (i->second >= threshold) {
			sortedOccurences.push_back(*i);
			result.push_back(i->first);		
			currentIndex = result.size() - 1;
		}

		while (currentIndex > 0 and sortedOccurences[currentIndex].second > sortedOccurences[currentIndex - 1].second){
			swap(sortedOccurences[currentIndex], sortedOccurences[currentIndex - 1]);
			swap(result[currentIndex], result[currentIndex - 1]);
			currentIndex--;
		}
	}
	

	/*for (size_t i = 0; i  < result.size(); i++){
		cout << result[i] << " num occurences: " << sortedOccurences[i].second << endl;
	}*/
		

	return result;
}


int main() {
	//cout << newPassword("ab", "zsd") << endl;
	auto res = processLogs({ "88 70 200", "88 12 100", "12 12 900", "88 99 250", "99 70 50", "60 700 210",
		"2 7 700", "22 60 100" }, 2);
	for (auto& num : res)
		cout << num << endl;
}