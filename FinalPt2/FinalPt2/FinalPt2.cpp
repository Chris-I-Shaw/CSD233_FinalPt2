/*
Chris Shaw
Final Part 2
3/18/20
C++ Programming
*/

#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace::std;

map<string, int> get_counts(string file_name) {

	//map to store the values to be returned
	map<string, int> temp;

	//store name of file to be searched
	string text_file_name = file_name.c_str();

	//store each word from file
	string word;

	//create and open input file stream
	ifstream file;
	file.open(text_file_name);

	//check to see if file opened. ending program if not open
	if (!file.is_open()) {
		cout << "File not found";
		exit(1);
	}

	//while loop to gather each strig from the file
	while (file >> word) {

		//for loop to check for and remove punctuation and capitals using iswpunct() and transform
		int len = word.size();
		for (int i = 0; i < len; i++) {
			//check for punctuation
			if (iswpunct(word.at(i))) {
				word.erase(i--, 1);
				len = word.size();
			}

			transform(word.begin(), word.end(), word.begin(), ::tolower);
		}

		//word is added to the map
		++temp[word];
	}
	//close file
	file.close();

	//return the temp map holding the words and their counts
	return temp;

}

string get_suggestion(map<string, int> counts, string input) {

	//iterator for the counts map for value comparisons
	map<string, int>::iterator it;

	//verification variables
	int found;
	string match;

	//stored at -1 to verify the substring is the beginning of a match
	int testValue = -1;

	//for loop to iterate through counts map
	for (it = counts.begin(); it != counts.end(); it++) {

		//check to see if input exists as a subsring inside counts string values
		//stores first occurance index in found
		found = it->first.find(input);

		//verify the substring is the start of a match in counts
		//modifies counts second pair(int values) for the return statements
		if (found == 0)

			if (testValue < it->second) {

				testValue = it->second;
				match = it->first;

			}

	}

	//return statments for if a match was found or not
	if (testValue != -1)  return match;

	else  return(input + " does not exist in chosen file.");

}

int main()
{
	map<string, int> r = get_counts("C:\\Users\\subno\\source\\repos\\FinalPt1\\LOTR.txt");

	vector<string> input =
	{
	"t", "th", "the",
	"l", "lo", "lor", "lord",
	"o", "of",
	"r", "ri", "rin", "ring", "rings",
	"f", "fe", "fel", "fell", "fello", "fellow", "fellows", "fellowsh", "fellowshi", "fellowship"
	};

	for (string s : input)
	{
		cout << s << ": " << get_suggestion(r, s) << endl;
	}
}



/*
int main()
{
	map<string, int> r = get_counts("C:\\Users\\subno\\source\\repos\\FinalPt1\\LOTR.txt");
	cout << "the: " << r["the"] << endl;
	cout << "lord: " << r["lord"] << endl;
	cout << "of: " << r["of"] << endl;
	cout << "rings: " << r["rings"] << endl;
	cout << "fellowship: " << r["fellowship"] << endl;

	cin.get();
}

*/