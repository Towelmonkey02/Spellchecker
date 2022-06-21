#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <chrono>
#include <sstream>
#include "spellchecker.h"
#include "loadfiles.h"
using namespace std;



int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Usage: ./dictionary [path of dictionary] [path of text]\n";
        return 0;
    }

    ifstream dictFile; ifstream textFile;
    map<long, vector<string>> dict; vector<string> text; unordered_map<string, double> results;

    if (loadDictionary(dictFile, argv[1], dict) == false) {
        cout << "Failed to load dictionary!\n";
        return 0;
    }

    if (loadTextFile(textFile, argv[2], text) == false) {
        cout << "Failed to load text file!\n";
        return 0;
    }

    spellCheck(dict, text, results);
    cout.precision(10);
    for (auto& [ss, dd] : results) {
        cout << ss << ": " << dd << '\n';
    }

    // SPELLCHECK RESULTS:
    // Holmes:
        // Dictionary loading (large.txt, 143091 words): 89.1131ms
        // Text loading: 282.048ms
        // Spellchecking: 4342.48ms
        // No. of misspelled words: 36762
        // Total no. of words: 1133014
    // Lalaland:
        // Dictionary loading: 90.7184ms
        // Text loading: 11.3883ms
        // Spellchecking: 60.5495ms
        // No. of misspelled words: 1050
        // Total no. of words: 17595

}