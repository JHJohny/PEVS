
#ifndef BIN_TREE_H
#define BIN_TREE_H

#include <vector>
#include <string>
#include <fstream>

class BinTree {

public:
    BinTree *GetParent() const;

    void SetParent(BinTree *parent);

private:
    std::string file;

    BinTree *left;
    BinTree *parent;
    BinTree *right;
    std::string question;

    void PreOrderTraverse(BinTree *tree, std::ofstream &ofstream, int index);

public:
    virtual ~BinTree();

    explicit BinTree(BinTree *tree);

public:
    void SetQuestion(const std::string &question);

    BinTree *MoveUp();
    BinTree *MoveLeft();
    BinTree *MoveRight();
    BinTree *CreateLeft(std::string text);
    BinTree *CreateRight(std::string text);

public:

    BinTree *GetLeft() const;
    BinTree *GetRight() const;
    void SetRight(BinTree *right);
    void SetLeft(BinTree *left);
    const std::string &GetQuestion() const;

public:
    BinTree();
    BinTree(const std::string &question);

    void FindNodeDirections(const std::string &index, std::vector<std::string> &nodeDirections) const;
    void LoadFromFile(BinTree *pTree, std::string filePath) const;
    void SetRootNode(BinTree *pTree, const std::vector<std::string> &nodeDirections, const std::string &question) const;
    BinTree *MoveToRoot(BinTree *pTree);
    BinTree *MoveToPlaceAndCreateNode(BinTree *pTree,
                                      const std::vector<std::string> &nodeDirections,
                                      std::string &currentQuestion) const;
};

#endif