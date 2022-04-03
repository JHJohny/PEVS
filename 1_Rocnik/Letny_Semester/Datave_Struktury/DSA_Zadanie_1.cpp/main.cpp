#include <iostream>
#include <string_view>
#include <string>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;
typedef std::map<string, string> wordDictionary; //Map works as dictionary in any other language
std::fstream file("/Users/johny/CLionProjects/untitled/out.txt");

void print(std::ostream &streamOne, std::ostream &streamTwo, const std::string &str)
{
    //Custom print, that will print output to the console but also save string to the file
    streamOne << str;
    streamTwo << str;
}

inline bool doesFileExist(const std::string& fileNameWithPath)
{
    ifstream fileToOpen;
    fileToOpen.open(fileNameWithPath);

    if(fileToOpen)
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline bool doesStringStartsWith(const std::string _string, const std::string prefix)
{
    if (_string.rfind(prefix, 0) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline bool doesStringEndsWith(const std::string _string, const std::string postfix)
{
    if(_string.size() >= postfix.size() &&
            _string.compare(_string.size() - postfix.size(), postfix.size(), postfix) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline bool doesStringContains(const std::string _string, const std::string substring)
{
    if (_string.find(substring) != std::string::npos) {
        return true;
    }
    else
    {
        return false;
    }
}

vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos)
    {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

class CustomDictionary
{
    wordDictionary wordDict; //Dictionary for word and it's explanation

public:
    CustomDictionary(std::string fileNameWithPath)
    {
        string line;
        ifstream myfile;
        myfile.open(fileNameWithPath);

        if(!myfile.is_open())
        {
            perror("File failed to open.");
            exit(EXIT_FAILURE);
        }

        while(getline(myfile, line))
        {
            string word = split(line, ";")[0];
            string wordExplanation = split(line, ";")[1];

            wordDict[word] = wordExplanation;
        }
    }

public:
    wordDictionary wordsStartingWith(std::string prefix)
    {
        wordDictionary wordDictStartingWith;

        //Looping trough the whole dictionary from the file
        for (auto const& x : wordDict)
        {
            if(doesStringStartsWith(x.first, prefix))
            {
                wordDictStartingWith[x.first] = x.second;
            }
        }
        return wordDictStartingWith;
    }

public:
    wordDictionary wordsEndingWith(std::string postfix)
    {
        wordDictionary wordDictEndingWith;

        //Looping trough the whole dictionary from the file
        for (auto const& x : wordDict)
        {
            if(doesStringEndsWith(x.first, postfix))
            {
                wordDictEndingWith[x.first] = x.second;
            }
        }
        return wordDictEndingWith;
    }

public:
    wordDictionary wordsContains(std::string substring)
    {
        wordDictionary wordDictEndingWith;

        //Looping trough the whole dictionary from the file
        for (auto const& x : wordDict)
        {
            if(doesStringContains(x.first, substring))
            {
                wordDictEndingWith[x.first] = x.second;
            }
        }
        return wordDictEndingWith;
    }

};


int main()
{
    const std::string fileNameWithPath = "/Users/johny/CLionProjects/untitled/something.txt";

    if(!doesFileExist(fileNameWithPath))
    {
        perror("File doesn't exist!");
        exit(EXIT_FAILURE);
    }

    CustomDictionary customDic = CustomDictionary(fileNameWithPath);
    wordDictionary wordDictionaryContains;
    wordDictionaryContains = customDic.wordsEndingWith("ro");

    for (auto const& x : wordDictionaryContains)
    {
        std::cout << x.first  // string (key)
                  << ':'
                  << x.second // string's value
                  << std::endl;
    }

    /* CONTAINS

    */

}
