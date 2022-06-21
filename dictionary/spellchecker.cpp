#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <chrono>
#include "spellchecker.h"
using namespace std;

long hashFunction(string word) {
    int wordLen = word.length();
    long result = 0;
    if (wordLen > 4) {wordLen = 4;}
    for (int i=0; i<wordLen; i++) {
        int a = word[i];
        if (65 <= a && a <= 90) {a -= 64;} else if (97 <= a && a <= 122) {a -= 96;}
        result = 27*result + a;
    }

    return result;
}

void spellCheck(map<long, vector<string>>& dict, vector<string>& text, unordered_map<string, double>& results) {

    auto t1 = chrono::high_resolution_clock::now();

    double totalWords = 0, wrongWords = 0, percentCorrect = 0;
    totalWords = text.size();
    for (string rawWord : text) {
        bool wordCorrect = false;
        string word = formatWord(rawWord);      // Ensures all words from the raw text are formatted first.
        long targetHash = hashFunction(word);
        map<long, vector<string>>::iterator dict_it = dict.find(targetHash);        // https://stackoverflow.com/questions/1939953/how-to-find-if-a-given-key-exists-in-a-c-stdmap
                                                                                    // Use map.find(key value) to return an iterator to the 
                                                                                    // key/value pair if the key exists. Remember that you can
                                                                                    // use iterator->first to access the key, and iterator->second
                                                                                    // to access the value.
        if (dict_it == dict.end()) {
            // Hash not found
            // cout << "Hash " << targetHash << " not found for word " << word << "\n";
        } else {
            // Hash found, look in vector for word
            vector<string> vect = dict_it->second;
            vector<string>::iterator vect_it = vect.begin();
            while (vect_it != vect.end() && wordCorrect == false) {
                if (compareWords(*vect_it, word)) {
                    wordCorrect = true;
                    // cout << "There is a match between the words " << *vect_it << " and " << word << ";\n";
                }
                vect_it++;
            }
        }
        if (wordCorrect == false) {
            // cout << "The word " << word << " was not found.\n";
            wrongWords += 1;
        }
    }

    results["Total no. of words"] = totalWords;
    results["No. of misspelled words"] = wrongWords;
    results["Percentage of words misspelled"] = (wrongWords / totalWords * 100);

    auto t2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tD = t2 - t1;
    cout << "Spell-check took " << tD.count() << " miliseconds.\n";

}

bool compareWords(string word1, string word2) {
    string newWord1 = formatWord(word1);    // The target word is word2 and is formatted beforehand.
                                            // The dictionary word is word1, which has not been formatted.
    if (newWord1 == word2) {return true;} else {return false;}
}

string formatWord(string word) {
    int wordLen = word.size();
    string newWord = "";
    for (int i=0; i<wordLen; i++) {
        int currentChar = word[i];

        // The spell-checker is sensitive to apostrophes ' and dashes -, but not sensitive to case, punctuation and numbers.
        // Pure numbers and dashes are also all removed.

        if ((33 <= currentChar && currentChar <= 38) || (40 <= currentChar && currentChar <= 44)
        || (46 <= currentChar && currentChar <= 64) || (91 <= currentChar && currentChar <= 96) || (123 <= currentChar && currentChar <= 126)) {
        } else {
            if (65 <= currentChar && currentChar <= 90) {
                currentChar += 32;
            }
            newWord += char(currentChar);
        }
    }
    return newWord;
}

bool isWord(string word) {
    for (int i=0; i<word.size(); i++) {
        int a = word[i];
        if ((65 <= a && a <= 90) || (97 <= a && a <= 122)) {
            return true;
        }
    }
    return false;
}
