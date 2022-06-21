#ifndef SPELLCHECKER
#define SPELLCHEKCER

#include <iosfwd>
#include <vector>
#include <map>
#include <unordered_map>

long hashFunction(std::string word);
void spellCheck(std::map<long, std::vector<std::string>>& dict, std::vector<std::string>& text, std::unordered_map<std::string, double>& results);
bool compareWords(std::string word1, std::string word2);
std::string formatWord(std::string word);
bool isWord(std::string word);

#endif // SPELLCHECKER 