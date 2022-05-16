
#ifndef GAME_H
#define GAME_H

#include "BinTree.h"

class Game {
public:
    Game();
    void Start();

private:

    void print(BinTree *pTree);

    void playGame(BinTree *pTree);

    std::string getUserInputText(const std::string &consolePrintText) const;

    bool isLastNode(const BinTree *pTree) const;

    BinTree *makeRight(BinTree *pTree, std::string question);

    BinTree *makeLeft(BinTree *pTree, std::string question);

    BinTree *lostGame(BinTree *pTree);

    void Exit(BinTree *pTree);

    void createNodeInLeftCorner(BinTree *pTree, const std::string &animalName, const std::string &question);

    BinTree *createNodeInRightCorner(BinTree *pTree, const std::string &animalName, const std::string &question);
};


#endif