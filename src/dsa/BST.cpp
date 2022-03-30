#include <stack>
#include <iostream>
#include <vector>
#include "Structures.h"

using namespace _structures;

BSTNode *createNode(int key)
{
    struct BSTNode *node = new struct BSTNode;
    node->key = 0;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

BST ::BST()
{
    this->numNode = 0;
    this->root = nullptr;
}

BST::~BST()
{
    deleteTree(root);
}

void BST::insert(int key)
{
    if (this->root == nullptr)
    {
        root = createNode(key);
        this->numNode++;
        return;
    }
    struct BSTNode *temp = this->root;
    while (true)
    {
        if (key < temp->key)
        {
            if (temp->left == nullptr)
            {
                temp->left = createNode(key);
#ifdef DEBUG
                std::cout << key << "\n";
#endif
                this->numNode++;
                return;
            }
            else
            {
                temp = temp->left;
                continue;
            }
        }
        else if (key > temp->key)
        {
            if (temp->right == nullptr)
            {
                temp->right = createNode(key);
#ifdef DEBUG
                std::cout << key << "\n";
#endif

                this->numNode++;
                return;
            }
            else
            {
                temp = temp->right;
                continue;
            }
        }
        else
        {
#ifdef DEBUG
            std::cerr << "Duplicate Entry Found\n";
#endif
            return;
        }
    }
}
void BST::remove(int key)
{
}
void preOrder(struct BSTNode *node)
{
    if (node)
    {
        std::cout << " " << node->key << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
}
void inOrder(struct node *node)
{
    if (node)
    {
        preOrder(node->left);
        std::cout << " " << node->key << " ";
        preOrder(node->right);
    }
}
void postOrder(struct BSTNode *node)
{
    if (node)
    {
        preOrder(node->left);
        preOrder(node->right);
        std::cout << " " << node->key << " ";
    }
}
void BST::preOrderRec() const
{
    preOrder(this->root);
}
void BST::inOrderRec() const
{
    inOrder(this->root);
}
void BST::postOrderRec() const
{
    postOrder(this->root);
}
void deleteTree(BSTNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->left == nullptr && node->right == nullptr)
    {
        delete node;
    }
    else
    {
        deleteTree(node->left);
        deleteTree(node->right);
    }
}
void BST::preOrderItr() const
{

    this->traversal(1);
}
void BST::inOrderItr() const
{
    this->traversal(2);
}
void BST::postOrderItr() const
{
    this->traversal(3);
}
void BST::traversal(int type) const
{
    std::stack<BSTNode *> node;
    std::stack<int> state;
    std::vector<int> pre(this->numNode);
    std::vector<int> in(this->numNode);
    std::vector<int> post(this->numNode);
    if (root == nullptr)
    {
        return;
    }
    BSTNode *curr = this->root;
    BSTNode.push(curr);
    state.push(1);
    while (!node.empty())
    {
        if (state.top() == 3)
        {
            post.push_back(node.top()->key);
            std::cout << "\n"
                      << curr->key;
            state.pop();
            node.pop();
            curr = node.top();
            continue;
        }
        else if (state.top() == 1)
        {
            pre.push_back(curr->key);
            std::cout << "\n"
                      << curr->key;
            state.pop();
            state.push(2);
            if (curr->left)
            {
                curr = curr->left;
                state.push(1);
                node.push(curr);
                continue;
            }
            else if (curr->right)
            {
                curr = curr->right;
                state.push(2);
                node.push(curr);
                continue;
            }
        }
        else if (state.top() == 2)
        {
            in.push_back(curr->key);
            std::cout << "\n"
                      << curr->key;
            state.pop();
            state.push(3);
            if (curr->right)
            {
                curr = curr->right;
                state.push(2);
                node.push(curr);
                continue;
            }
        }
    }
    for (int i = 0; i < this->numNode; i++)
    {
        switch (type)
        {
        case 1:
            std::cout << " " << pre[i] << " ";
            break;
        case 2:
            std::cout << " " << in[i] << " ";
            break;
        case 3:
            std::cout << " " << post[i] << " ";
            break;
        default:
            std::cout << "Error !";
            break;
        }
    }
}
void BST::print() const
{
    print(this->root, 0);
}
void print(struct BSTNode *curr, int depth)
{
    if (curr)
    {
        for (int i = 0; i < depth; i++)
        {
            std::cout << "|";
        }
    }
}

struct node *BST::getRoot() const
{
    return this->root;
}