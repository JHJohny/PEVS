#include <iostream>
#include "stack.h"
#include <fstream>

std::ofstream file("./out.txt"); //this file will be used among functions to save console's output to this file
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

int main() {
    file << ""; //Clear the save console's output first

    Stack firstStack;
    Stack secondStack;

    bool wereStacksCreated = false;

    std::string input;
    std::string firstStackContent;
    std::string secondStackContent;

    while (true)
    {
        print(cout, file, "a) Vytvor dva nové a prázdne zásobníky.\n"
                          "b) Vyprázdni obsah v oboch zásobníkoch.\n"
                          "c) Načítaj nový reťazec z klávesnice do prvého zásobníka a vytvor aj druhý zásobník.\n"
                          "d) Vypíš obsah prvého zásobníka.\n"
                          "e) Vypíš obsah druhého zásobníka.\n"
                          "f) Určí, či daný reťazec je palindrómom. \n"
                          "x) Ukonči program.\n");

        char usersChoice;
        print(file, cout, "Prosim, vyber si moznost \n");
        std::cin >> usersChoice;
        file << usersChoice;
        file << "\n";

        switch (usersChoice) {
            case 'a':
                firstStack.Create();
                secondStack.Create();
                wereStacksCreated = true;
                break;
            case 'b':
                if(!wereStacksCreated)
                {
                    print(file, cout, "#First you need to create stacks, please choose option A first\n\n");
                    break;
                }

                while(!firstStack.IsEmpty())
                {
                    firstStack.Pop();
                }

                while(!secondStack.IsEmpty())
                {
                    secondStack.Pop();
                }
                break;
            case 'c':
                if(!wereStacksCreated)
                {
                    print(file, cout, "#First you need to create stacks, please choose option A first\n\n");
                    break;
                }

                std::cin >> input;
                print(file, cout, input);
                print(file, cout, "\n");

                // filling first stack
                for(int i = 0; i < input.length(); i++)
                {
                    firstStack.Push(input[i]);
                    firstStackContent += input[i];
                }

                // filling another stack in reverse order from the first one
                while(!firstStack.IsEmpty())
                {
                    secondStack.Push(firstStack.Pop());
                    secondStackContent += secondStack.Top();
                }

                // filling first stack again, because poping emptied it
                for(int i = 0; i < input.length(); i++)
                {
                    firstStack.Push(input[i]);
                }
                break;
            case 'd':
                if(!wereStacksCreated)
                {
                    print(file, cout, "#First you need to create stacks, please choose option A first\n\n");
                    break;
                }
                print(file, cout, firstStackContent+"\n");
                break;
            case 'e':
                if(!wereStacksCreated)
                {
                    print(file, cout, "#First you need to create stacks, please choose option A first\n\n");
                    break;
                }
                print(file, cout, secondStackContent+"\n");
                break;
            case 'f':
                if(!wereStacksCreated)
                {
                    print(file, cout, "First you need to create stacks, please choose option A first\n");
                    break;
                }

                if(firstStack.IsEmpty() && secondStack.IsEmpty())
                {
                    print(file, cout, "Stacks are empty, you need to fill them first\n");
                    break;
                }

                while (!firstStack.IsEmpty() && !secondStack.IsEmpty())
                {
                    if(tolower(firstStack.Pop()) != tolower(secondStack.Pop()))
                    {
                        print(file, cout, "No it's not a palindrom\n");
                        break;
                    }
                }

                if(firstStack.IsEmpty() && secondStack.IsEmpty())
                {
                    print(file, cout, "\n\n##### Yes it is palindrom\n\n");
                    break;
                }

                break;
            case 'x':
                exit(EXIT_SUCCESS);
                break;
            default:
                print(file, cout, "Nespravny vstup, prosim opakuj!\n");
                break;
        }
    }

    return 0;
}
