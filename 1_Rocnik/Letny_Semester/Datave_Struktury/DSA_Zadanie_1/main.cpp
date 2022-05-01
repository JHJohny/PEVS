#include <iostream>
#include <string_view>
#include <string>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

typedef std::map<string, string> wordDictionary; //Map works as dictionary in any other language
std::fstream file("./out.txt"); //this file will be used among functions to save console's output to this file

//Custom print, that will print output to the console but also save string to the file
void print(std::ostream &streamOne, std::ostream &streamTwo, const std::string &str)
{
    /* This function prints output to the console + the to file
     *
     * This function takes two stream parameters and one string.
     * Strings writes to the both stream - usually one stream is file and another is console.
     */
    streamOne << str;
    streamTwo << str;
}

string handleUserInput(const std::string& askingSentence)
{
    /* Abstract way how to ask user for his input and handle possible errors
     *
     * This function ask user for it's input with the asking sentence that was passed at the beginning.
     * This function does all checks that are usually done when we are asking user for his input.
     * Checks if the user input is empty or not.
     */
    std::string userInput;

    while (true)
    {
        print(file, cout, askingSentence);
        cin >> userInput;
        file << userInput+"\n";

        if(userInput == "" || userInput.length()==0)
        {
            print(file, cout, "Nevalidny vstup, prosim opakuj!\n");
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
    /* Takes a filepath as a input and return true/false whether file exist or not
     *
     * Self-explanatory
     */
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
    /* Checks whether given string start with the specific prefix
     *
     * Self-explanatory
     */
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
    /* Checks whether string ends with the specific postfix
     *
     * Self-explanatory
     */
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
    /* Checks whether given string contains a substring
     *
     * Self-explanatory
     */
    if (_string.find(substring) != std::string::npos) {
        return true;
    }
    else
    {
        return false;
    }
}

vector<string> split (string s, string delimiter) {
    /* Split - split string within two parts - based on the delimeter
     *
     * Split works as any other split in any other programming language. Take string as a input and split it's content into two parts based on the delimeter.
     */
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
    /* Custom dictionary class, that behave almost the same as a usual dictionary data structure
     *
     * This custom dictionary is almost the same as regular dictionary is, except it adds some functionality on the top of that.
     * It handles searching in the keys, based on: prefix, substring, postfix.
     */
    wordDictionary wordDict; //Dictionary for word and it's explanation

public:
    CustomDictionary(std::string fileNameWithPath)
    {
        /* Constructor - take filepath
         *
         * Constructor takes a filepath then read the file and finds word and it's meaning - with the ";" delimeter.
         * Delimeter cannot be changed - because this is very specific assignment oriented, so it makes no sense to give user change all that functionality
         */
        string line;
        ifstream myfile;
        myfile.open(fileNameWithPath);

        if(!myfile.is_open())
        {
            print(file, cout, "File failed to open.\n");
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
    /* Specific function that handles main logic behind the printing
     *
     * This function is very specific oriented. It describes the logic that was in describe in the assignment.
     * If the searched words are none - prints a note about it.
     * If the searched words are only one = prints the word + it's description
     * If the searched words are many - but one is exact match of the word - print only exact matched word + it's description
     * If the searched words are many - but NO exact matched is searched - prints only matched words - WITHOUT the description
     */
    int dictLength = wordDict.size();

    //Ak žiadne slovo v slovníku nesplňa daný dotaz, vypíšte príslušné hlásenie o tom.
    //If there was no match, print a note about it
    if(dictLength == 0)
    {
        print(file, cout, "No word was matched!\n");
        return; //Return because it makes no point to check for other things
    }

    //Ak iba jedno slovo spľňa daný dotaz, potom vypíšte toto slovo s jeho významom zo slovníka ako výstup.
    //If there is only one match
    if(dictLength == 1)
    {
        for (auto const& x : wordDict)
        {
            print(file, cout, x.first+":"+x.second+"\n");
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
        print(file, cout, tmpString+"\n");

        return; //Return because it makes no point to check for other things
    }

    //Ak viac ako jedno slovo spľňa daný dotaz, potom vypíšte zoznam všetkých
    //takýchto slov bez uvedenia ich významu (napr. slovo "knih").
    for (auto const& x : wordDict)
    {
        print(file, cout, x.first+"\n");
    }

}

int main()
{
    file << ""; //Clear the save console's output first
    const std::string fileNameWithPath = "./slovnik.txt"; //Better to use current working directory than asking user for input - because windows may have a problem with the folder that contains empty space

    //Handling if the slovnik.txt is not in the current working directory
    if(!doesFileExist(fileNameWithPath))
    {
        print(file, cout, "File doesn't exist!\nSlovnik sa nenachadza v momentalnom directory! Prosim presun slovnik.txt kde sa tento .cpp subor nachadza a opakuj.\n");
        exit(EXIT_FAILURE);
    }

    //Creating custom datastructure
    CustomDictionary customDic = CustomDictionary(fileNameWithPath);
    wordDictionary wordDict;

    while(true)
    {
        std::string usersInput = handleUserInput("\n####Prosim vyber si moznost####\n"
                                                 "1.) <starting> ......... najdi význam slova začínajúceho danými znakmi\n"
                                                 "2.) <containing> .......... najdi význam slova obsahujúceho dané znaky\n"
                                                 "3.) <ending> ......... najdi význam slova končiaceho danými znakmi\n"
                                                 "4.) <stop> .......... ukonči daný program\n");

        int userChoice = atoi(usersInput.c_str());

        //Switching between options that was presented to the user
        switch (userChoice)
        {
            case 1:
            {
                string prefix = handleUserInput("Please enter prefix\n");
                wordDict = customDic.wordsStartingWith(prefix);

                handleConsoleOutputWithDictionary(wordDict, prefix);
                break;
            }
            case 2:
            {
                string substring = handleUserInput("Please enter substring\n");
                wordDict = customDic.wordsContains(substring);

                handleConsoleOutputWithDictionary(wordDict, substring);
                break;
            }
            case 3:
            {
                string postfix = handleUserInput("Please enter postfix\n");
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
