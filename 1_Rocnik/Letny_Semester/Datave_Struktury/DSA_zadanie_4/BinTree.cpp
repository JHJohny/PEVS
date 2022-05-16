
#define PATH_TO_TREE_FILE "./game.txt"

#include <iostream>
#include <vector>

#include "BinTree.h"
#include "StringUtils.h"

BinTree::BinTree() {
    std::cout << "Bintree start" << std::endl;
    file = PATH_TO_TREE_FILE;

    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->question = "";

    LoadFromFile(this, file);
}

BinTree::BinTree(const std::string &question) : question(question) {
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

void BinTree::LoadFromFile(BinTree *pTree, std::string filePath) const {
    std::string line;
    std::ifstream myfile;
    myfile.open(filePath);

    if(!myfile.is_open()) {
        perror("Subor sa nepodarilo otvorit!");
        return;
    }

    while(getline(myfile, line)) {
        std::vector<std::string> splittedText = StringUtils::split(line, " ");

        std::string index = splittedText[splittedText.size() - 1];
        std::string currentQuestion;

        for (int i = 0; i < splittedText.size() - 1; i++) {
            currentQuestion += " " + splittedText[i];
        }

        std::vector<std::string> nodeDirections;

        FindNodeDirections(index, nodeDirections);
        SetRootNode(pTree, nodeDirections, currentQuestion);

        pTree = MoveToPlaceAndCreateNode(pTree, nodeDirections, currentQuestion);
        pTree = pTree->MoveToRoot(pTree);
    }
}

BinTree::~BinTree() {
    std::ofstream openedFile;
    openedFile.open(file);

    if (!openedFile) {
        std::cout << "Strom sa nepodarilo zapisat do suboru" << std::endl;
    }

    PreOrderTraverse(this, openedFile, 1);
}

BinTree *BinTree::MoveToPlaceAndCreateNode(BinTree *pTree, const std::vector<std::string> &nodeDirections,
                                           std::string &currentQuestion) const {
    for (int i = 0; i < nodeDirections.size(); ++i) {
        if (i == nodeDirections.size() - 1) {
            "r" == nodeDirections[i] ? pTree->CreateRight(currentQuestion)
                                     : pTree->CreateLeft(currentQuestion);
            break;
        }
        pTree = "r" == nodeDirections[i] ? pTree->MoveRight()
                                         : pTree->MoveLeft();

    }
    return pTree;
}

BinTree *BinTree::MoveToRoot(BinTree *pTree) {
    while (pTree->GetParent() != nullptr) {
        pTree = pTree->MoveUp();
    }
    return pTree;
}

void BinTree::SetRootNode(BinTree *pTree, const std::vector<std::string> &nodeDirections,
                          const std::string &question) const {
    if (0 == nodeDirections.size()) {
        pTree->SetQuestion(question);
    }
}

void BinTree::FindNodeDirections(const std::string &index, std::vector<std::string> &nodeDirections) const {
    for (int i = std::stoi(index); i > 1; i /= 2) {
        if (i % 2 == 0) {
            nodeDirections.insert(nodeDirections.begin(), "l");
            continue;
        }
        nodeDirections.insert(nodeDirections.begin(), "r");
    }
}

BinTree::BinTree(BinTree *tree) {
    parent = tree->parent;
    left = tree->left;
    right = tree->right;
    question = tree->question;
}

const std::string &BinTree::GetQuestion() const {
    return question;
}

void BinTree::SetQuestion(const std::string &question) {
    BinTree::question = question;
}

BinTree *BinTree::GetLeft() const {
    return left;
}

void BinTree::SetLeft(BinTree *left) {
    BinTree::left = left;
}

BinTree *BinTree::GetRight() const {
    return right;
}

void BinTree::SetRight(BinTree *right) {
    BinTree::right = right;
}

void BinTree::PreOrderTraverse(BinTree *tree, std::ofstream &ofstream, int index) {
    if (nullptr == tree) {
        return;
    }

    ofstream << tree->GetQuestion() << " " << index << std::endl;

    PreOrderTraverse(tree->GetLeft(), ofstream, index * 2);
    PreOrderTraverse(tree->GetRight(), ofstream, index * 2 + 1);
}

BinTree *BinTree::MoveRight() {
    if (nullptr == GetRight()) {
        return this;
    } else {
        return GetRight();
    }
}

BinTree *BinTree::MoveLeft() {
    if (nullptr == GetLeft()) {
        return this;
    } else {
        return GetLeft();
    }
}

BinTree *BinTree::MoveUp() {
    if (nullptr == GetParent()) {
        return this;
    } else {
        return GetParent();
    }
}

BinTree *BinTree::GetParent() const {
    return parent;
}

void BinTree::SetParent(BinTree *parent) {
    BinTree::parent = parent;
}

BinTree *BinTree::CreateLeft(std::string text) {
    BinTree *newNode = new BinTree(text);
    newNode->SetQuestion(text);

    newNode->SetParent(this);
    SetLeft(newNode);

    return newNode->GetLeft();
}

BinTree *BinTree::CreateRight(std::string text) {
    BinTree *newNode = new BinTree(text);
    newNode->SetQuestion(text);

    newNode->SetParent(this);
    SetRight(newNode);

    return newNode->GetRight();
}