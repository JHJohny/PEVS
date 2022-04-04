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

//Custom print, that will print output to the console but also save string to the file
void print(std::ostream &streamOne, std::ostream &streamTwo, const std::string &str)
{
    streamOne << str;
    streamTwo << str;
}

string handleUserInput(const std::string& askingSentence)
{
    std::string userInput;

    while (true)
    {
        cout << askingSentence << endl;
        cin >> userInput;

        if(userInput == "" || userInput.length()==0)
        {
            cout << "Nevalidny vstup, prosim opakuj!" << endl;
        }
        else
        {
            break;
        }
    }

    return userInput;
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

void handleConsoleOutputWithDictionary(wordDictionary wordDict, std::string searchingWord) //Matching word for the case when we are checking if the match is whole searching word
{
    int dictLength = wordDict.size();

    //Ak žiadne slovo v slovníku nesplňa daný dotaz, vypíšte príslušné hlásenie o tom.
    //If there was no match, print a note about it
    if(dictLength == 0)
    {
        print(file, cout, "No word was matched!");
        return; //Return because it makes no point to check for other things
    }

    //Ak iba jedno slovo spľňa daný dotaz, potom vypíšte toto slovo s jeho významom zo slovníka ako výstup.
    //If there is only one match
    if(dictLength == 1)
    {
        for (auto const& x : wordDict)
        {
            std::cout << x.first  // string (key)
                      << ':'
                      << x.second // string's value
                      << std::endl;
        }

        return; //Return because it makes no point to check for other things
    }

    //Ak existuje dotaz v slovníku ako celé slovo, ale pritom je aj časť iného slova, vypíš
    //slovo s jeho významom (napr. "kniha", vypíše len slovo kniha s významom)
    //Basically checking whether searching word was complete match

    //First check for complete match word itself
    bool wasSearchingCompleteWordMatch = false;
    for (auto const& x : wordDict)
    {
        if(x.first == searchingWord)
        {
            wasSearchingCompleteWordMatch = true;
        }
    }
    //Printing only the exact match only
    if(wasSearchingCompleteWordMatch)
    {
        string tmpString = searchingWord+":"+wordDict[searchingWord];
        print(file, cout, tmpString);

        return; //Return because it makes no point to check for other things
    }

    //Ak viac ako jedno slovo spľňa daný dotaz, potom vypíšte zoznam všetkých
    //takýchto slov bez uvedenia ich významu (napr. slovo "knih").
    for (auto const& x : wordDict)
    {
        std::cout << x.first  // string (key)
                  << std::endl;
    }

}

int main()
{
    const std::string fileNameWithPath = "/Users/johny/CLionProjects/untitled/something.txt";

    if(!doesFileExist(fileNameWithPath))
    {
        perror("File doesn't exist!");
        exit(EXIT_FAILURE);
    }

    CustomDictionary customDic = CustomDictionary(fileNameWithPath);
    wordDictionary wordDict;

    while(true)
    {
        std::string usersInput = handleUserInput("\n####Prosim vyber si moznost####\n"
                                                 "1.) <starting> ......... najdi význam slova začínajúceho danými znakmi\n"
                                                 "2.) <containing> .......... najdi význam slova obsahujúceho dané znaky\n"
                                                 "3.) <ending> ......... najdi význam slova končiaceho danými znakmi\n"
                                                 "4.) <stop> .......... ukonči daný program");

        int userChoice = atoi(usersInput.c_str());

        switch (userChoice)
        {
            case 1:
            {
                string prefix = handleUserInput("Please enter prefix");
                wordDict = customDic.wordsStartingWith(prefix);

                handleConsoleOutputWithDictionary(wordDict, prefix);
                break;
            }
            case 2:
            {
                string substring = handleUserInput("Please enter substring");
                wordDict = customDic.wordsContains(substring);

                handleConsoleOutputWithDictionary(wordDict, substring);
                break;
            }
            case 3:
            {
                string postfix = handleUserInput("Please enter postfix");
                wordDict = customDic.wordsEndingWith(postfix);

                handleConsoleOutputWithDictionary(wordDict, postfix);
                break;
            }
            case 4:
            {
                exit(EXIT_SUCCESS);
                break;
            }
            default:
            {
                print(file, cout, "Nespravna volba, prosim opakuj\n");
                break;
            }
        }
    }

}
