
#define USER_ASKING_FOR_QUESTION "Co sa chces uzivatela pytat?"

#include <string>
#include <iostream>
#include <utility>

#include "Game.h"
#include "BinTree.h"
#include "StringUtils.h"

Game::Game() {
    Start();
}

std::string Game::getUserInputText(const std::string &askingSentence) const {

    std::cout << askingSentence << std::endl;
    std::string text;

    std::getline(std::cin, text, '\n');

    return text;
}

void Game::Exit(BinTree *pTree) {
    pTree = pTree->MoveToRoot(pTree);
    delete pTree;
}

void Game::Start() {

    std::string question;
    std::string userInput;
    auto *binaryTree = new BinTree();
    bool wasTreeAlreadyCreated = false;

    while (true) {
        std::cout << "a. Vytvorenie prázdneho stromu\n"
                     "b. Vytvorenie ľavého nasledovníka\n"
                     "c. Vytvorenie pravého nasledovníka\n"
                     "d. Nastavenie na root\n"
                     "e. Nastavenie na ľavé dieťa\n"
                     "f. Nastavenie na pravé dieťa\n"
                     "g. Nastavenie aktívneho prvku na rodiča\n"
                     "h. Vypíše hodnotu aktívneho vrcholu a jeho hodnoty ľavý a pravý (pripadne null ak nemajú dáta)\n"
                     "i. Spustenie hry\n"
                     "x. Ukonči program.\n";

        getline(std::cin, question);

        switch (*question.c_str()) {
            case 'a':
                question = getUserInputText("Ktoru otazku sa chces opytat uzivatela");
                binaryTree = new BinTree(question);
                wasTreeAlreadyCreated = true;
                break;
            case 'b':
                if(!wasTreeAlreadyCreated) {
                    makeLeft(binaryTree, "");
                }
                break;
            case 'c':
                if(!wasTreeAlreadyCreated) {
                    makeRight(binaryTree, "");
                }
                break;
            case 'd':
                binaryTree = binaryTree->MoveToRoot(binaryTree);
                break;
            case 'e':
                binaryTree = binaryTree->MoveLeft();
                break;
            case 'f':
                binaryTree = binaryTree->MoveRight();
                break;
            case 'g':
                binaryTree = binaryTree->MoveUp();
                break;
            case 'h':
                if(!wasTreeAlreadyCreated) {
                    print(binaryTree);
                }
                break;
            case 'i':
                if(!wasTreeAlreadyCreated) {
                    playGame(binaryTree);
                }
                break;
            case 'x':
                Exit(binaryTree);
                exit(EXIT_SUCCESS);
        }
    }

}

BinTree *Game::makeLeft(BinTree *pTree, std::string question="") {
    if(question == "") {
        question = getUserInputText(USER_ASKING_FOR_QUESTION);
    }

    return pTree->CreateLeft(std::move(question));
}

BinTree *Game::makeRight(BinTree *pTree, std::string question="") {
    if(question == "") {
        question = getUserInputText(USER_ASKING_FOR_QUESTION);
    }

    return pTree->CreateRight(std::move(question));
}

void Game::print(BinTree *pTree) {

    std::cout << "Question: " << pTree->GetQuestion() << std::endl << "Left: ";
    pTree->GetLeft() == nullptr ? std::cout << "Empty" << std::endl
                                : std::cout << pTree->GetLeft()->GetQuestion() << std::endl;
    std::cout << "Right: ";
    pTree->GetRight() == nullptr ? std::cout << "Empty" << std::endl
                                 : std::cout << pTree->GetRight()->GetQuestion() << std::endl;

}

void Game::playGame(BinTree *pTree) {

    pTree = pTree->MoveToRoot(pTree);
    std::string answer;

    while (true) {
            answer = getUserInputText(pTree->GetQuestion());
            if (answer == "y") {
                if (!isLastNode(pTree->GetLeft())) {
                    pTree = pTree->MoveLeft();
                    continue;
                }
                std::cout << "Vyhravam!" << std::endl;
                answer = getUserInputText("Hrat znova? (y/n)?");
                if (answer == "n") {
                    break;
                }
            } else if (answer == "n") {
                if (!isLastNode(pTree->GetRight())) {
                    pTree = pTree->MoveRight();
                    continue;
                }
                pTree = lostGame(pTree);

                answer = getUserInputText("Hrat znova? (y/n)?");
                if (answer == "n") {
                    break;
                }

            } else {
                perror("Something went wrong");
            }

        pTree = pTree->MoveToRoot(pTree);
    }

}

BinTree *Game::lostGame(BinTree *pTree) {
    const std::string animalName = getUserInputText("Vyhravas, nepodarilo sa mi uhadnut na ake zviera myslis. Na ake zviera si myslel?");
    const std::string question = getUserInputText("Napis otazku aby strom vedel nabuduce na ake zviera si myslel");

    if (nullptr != pTree->GetLeft()) {
        pTree = createNodeInRightCorner(pTree, animalName, question);
    } else {
        createNodeInLeftCorner(pTree, animalName, question);
    }
    return pTree;
}

BinTree *Game::createNodeInRightCorner(BinTree *pTree, const std::string &animalName, const std::string &question) {
    makeRight(pTree, question + "?");
    pTree = pTree->MoveRight();
    makeLeft(pTree, "Je to " + animalName + "?");
    return pTree;
}

void Game::createNodeInLeftCorner(BinTree *pTree, const std::string &animalName, const std::string &question) {
    makeLeft(pTree, pTree->GetQuestion());
    makeRight(pTree, "Je to " + animalName + "?");
    pTree->SetQuestion(question + "?");
}

bool Game::isLastNode(const BinTree *pTree) const {
    return nullptr == pTree;
}
