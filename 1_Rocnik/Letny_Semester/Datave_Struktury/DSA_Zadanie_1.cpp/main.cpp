#include <iostream>
#include <string_view>
#include <string>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

bool endsWith(const std::string &mainStr, const std::string &toMatch)
{
    if(mainStr.size() >= toMatch.size() &&
       mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
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
    typedef std::map<string, string> wordDictionary; //Map works as dictionary in any other language

public:
    CustomDictionary(std::string fileNameWithPath)
    {
        wordDictionary wordDict;

        string line;
        ifstream myfile;
        myfile.open(fileNameWithPath);

        if(!myfile.is_open())
        {
            printf("Subor sa nepodarilo otvorit! Prosim over ci nie je poskodeny, alebo nie je otvoreny inym programom.");
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
};


int main()
{
    const std::string fileNameWithPath = "/Users/johny/CLionProjects/untitled/something.txt";

    if(doesFileExist(fileNameWithPath))
    {
        CustomDictionary dictionary = CustomDictionary(fileNameWithPath);
    }
    else
    {
        printf("File doesn't exist");
    }

    /* CONTAINS
    auto hello  = std::string("hello");
    auto el = std::string("el");

    if (hello.find(el) != std::string::npos) {
        std::cout << "found!" << '\n';
    }
    */

    /* PREFIX
    std::string str = "C++17";
    std::string prefix = "C++";

    if (str.rfind(prefix, 0) == 0) {
        std::cout << "String starts with the given prefix" << std::endl;
    } else {
        std::cout << "String doesn't starts with prefix" << std::endl;
    }
    */

    /* POSTFIX
    std::string normalString = "Helloworld";
    std::string postfix = "rld";

    if(endsWith(normalString, postfix))
    {
        printf("Yes it contains");
    }
    */
}
