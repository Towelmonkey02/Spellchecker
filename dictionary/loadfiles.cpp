#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>
#include <sstream>
#include "loadfiles.h"
#include "spellchecker.h"
using namespace std;

bool loadDictionary(ifstream& dictFile, string dictPath, map<long, vector<string>>& dict) {

    auto t1 = chrono::high_resolution_clock::now();

    dictFile.open(dictPath);

    if (dictFile.is_open() == false) {
        return false;
    }

        // A naive use of vectors takes around 120ms to load the entirety of large.txt.
        // For more information on how C++ timers work, look at https://en.cppreference.com/w/cpp/chrono/duration
            // A time point can simply be declared as an "auto" variable. Use chrono::high_resolution_clock, and use its 
            // member function ::now().
            // A time duration is defined using chrono::duration<variable type, ratio>. You can use the inbuilt ratio types 
            // std::micro, std::milli, or just use ratio<1, 1> for seconds. Use .count() to print out its actual value.
            // You can also use chrono::duration_cast<duration type> https://en.cppreference.com/w/cpp/chrono/duration/duration_cast
            // to obtain the duration rounded to the nearest integer.

    string line;
    while (getline(dictFile, line)) {
        long dictKey = hashFunction(line);
        dict[dictKey].emplace_back(line);
    }

    auto t2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tD = t2 - t1;
    cout << "Loading the dictionary took " << tD.count() << " milliseconds.\n";

    // for (const auto & [key, value] : dict) {
    //     cout << key << " : ";
    //     for (string value1 : dict[key]) {cout << value1 << ", ";}
    //     cout << '\n';
    // }

    return true;
}


bool loadTextFile(ifstream& textFile, string textPath, vector<string>& text) {

    auto t1 = chrono::high_resolution_clock::now();
    textFile.open(textPath);
    if (textFile.is_open() == false) {return false;}
    string s, line;
    while (getline(textFile, line)) {
        istringstream ss(line);             // The istringstream here allows text to be parsed
        while (ss >> s) {                   // word by word.
            if (isWord(s)) {
                text.emplace_back(s);
            }
                                            // Alternatively, the C way would be to use textFile.seekp(0, ios::end), followed by
                                            // int x = textFile.tellp(), to obtain an integer representing the position of the pointer.

                                            // The file can also be opened in binary using .open(textPath, ios::ate), wherein the pointer
                                            // will return the no. of bytes that were iterated (and hence the size in bytes of the file).
                                            // https://cplusplus.com/reference/istream/istream/tellg/
        }
    }
    auto t2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tD = t2 - t1;
    cout << "Loading the text took " << tD.count() << " milliseconds.\n";

    // for (string element : text) {
    //     cout << element << "_";
    // }

    return true;

}