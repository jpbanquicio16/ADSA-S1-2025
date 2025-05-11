#include <iostream>
#include <sstream>
#include <vector>
#include <string>

class Node {
public:
    int data, height;
    Node* lChild;
    Node* rChild;

    Node(int v) : data(v), height(1), lChild(nullptr), rChild(nullptr) {}
};

class AVLTree {
private:
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? getHeight(node->lChild) - getHeight(node->rChild) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->lChild;
        Node* T2 = x->rChild;
        x->rChild = y;
        y->lChild = T2;
        y->height = 1 + std::max(getHeight(y->lChild), getHeight(y->rChild));
        x->height = 1 + std::max(getHeight(x->lChild), getHeight(x->rChild));
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->rChild;
        Node* T2 = y->lChild;
        y->lChild = x;
        x->rChild = T2;
        x->height = 1 + std::max(getHeight(x->lChild), getHeight(x->rChild));
        y->height = 1 + std::max(getHeight(y->lChild), getHeight(y->rChild));
        return y;
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->data) node->lChild = insert(node->lChild, key);
        else if (key > node->data) node->rChild = insert(node->rChild, key);
        else return node; // duplicates not allowed

        node->height = 1 + std::max(getHeight(node->lChild), getHeight(node->rChild));
        int balance = getBalance(node);

        if (balance > 1 && key < node->lChild->data) return rightRotate(node);
        if (balance < -1 && key > node->rChild->data) return leftRotate(node);
        if (balance > 1 && key > node->lChild->data) {
            node->lChild = leftRotate(node->lChild);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->rChild->data) {
            node->rChild = rightRotate(node->rChild);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->lChild) current = current->lChild;
        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (!root) return root;
        if (key < root->data) root->lChild = deleteNode(root->lChild, key);
        else if (key > root->data) root->rChild = deleteNode(root->rChild, key);
        else {
            if (!root->lChild || !root->rChild) {
                Node* temp = root->lChild ? root->lChild : root->rChild;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else *root = *temp;
                delete temp;
            } else {
                Node* temp = minValueNode(root->rChild);
                root->data = temp->data;
                root->rChild = deleteNode(root->rChild, temp->data);
            }
        }

        if (!root) return root;

        root->height = 1 + std::max(getHeight(root->lChild), getHeight(root->rChild));
        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->lChild) >= 0) return rightRotate(root);
        if (balance > 1 && getBalance(root->lChild) < 0) {
            root->lChild = leftRotate(root->lChild);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->rChild) <= 0) return leftRotate(root);
        if (balance < -1 && getBalance(root->rChild) > 0) {
            root->rChild = rightRotate(root->rChild);
            return leftRotate(root);
        }

        return root;
    }

    void inOrder(Node* node) {
        if (!node) return;
        inOrder(node->lChild);
        std::cout << node->data << " ";
        inOrder(node->rChild);
    }

    void preOrder(Node* node) {
        if (!node) return;
        std::cout << node->data << " ";
        preOrder(node->lChild);
        preOrder(node->rChild);
    }

    void postOrder(Node* node) {
        if (!node) return;
        postOrder(node->lChild);
        postOrder(node->rChild);
        std::cout << node->data << " ";
    }

public:
    Node* root = nullptr;

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    void print(std::string order) {
        if (!root) {
            std::cout << "EMPTY" << std::endl;
            return;
        }
        if (order == "IN") inOrder(root);
        else if (order == "PRE") preOrder(root);
        else if (order == "POST") postOrder(root);
        std::cout << std::endl;
    }
};

int main() {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    std::string token;
    AVLTree tree;
    std::vector<std::string> commands;

    while (iss >> token) {
        commands.push_back(token);
    }

    for (size_t i = 0; i < commands.size() - 1; ++i) {
        if (commands[i][0] == 'A') {
            int val = std::stoi(commands[i].substr(1));
            tree.insert(val);
        } else if (commands[i][0] == 'D') {
            int val = std::stoi(commands[i].substr(1));
            tree.remove(val);
        }
    }

    tree.print(commands.back());
    return 0;
}
