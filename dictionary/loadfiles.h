#ifndef LOADFILES
#define LOADFILES

#include <iosfwd>
#include <vector>
#include <map>
#include <fstream>

bool loadDictionary(std::ifstream& dictFile, std::string dictPath, std::map<long, std::vector<std::string>>& dict);
bool loadTextFile(std::ifstream& textFile, std::string textPath, std::vector<std::string>& text);

#endif // LOADFILES