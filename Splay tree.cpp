#include <iostream>
#include <cstdlib>
#include <ctime>

class Node {
public:
    int ipAdd;
    int dataPacket;
    Node* left;
    Node* right;
    Node* parent;

    Node(int ipAdd) {
        this->ipAdd = ipAdd;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class SplayTree {
public:
    Node* root;

    SplayTree() {
        this->root = nullptr;
    }

    Node* maximum(Node* x) {
        while (x->right != nullptr) {
            x = x->right;
        }
        return x;
    }

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void splay(Node* n) {
        while (n->parent != nullptr) {
            if (n->parent == this->root) {
                if (n == n->parent->left) {
                    rightRotate(n->parent);
                } else {
                    leftRotate(n->parent);
                }
            } else {
                Node* p = n->parent;
                Node* g = p->parent;
                if (n->parent->left == n && p->parent->left == p) {
                    rightRotate(g);
                    rightRotate(p);
                } else if (n->parent->right == n && p->parent->right == p) {
                    leftRotate(g);
                    leftRotate(p);
                } else if (n->parent->right == n && p->parent->left == p) {
                    leftRotate(p);
                    rightRotate(g);
                } else if (n->parent->left == n && p->parent->right == p) {
                    rightRotate(p);
                    leftRotate(g);
                }
            }
        }
    }

    void insert(Node* n) {
        Node* y = nullptr;
        Node* temp = this->root;
        while (temp != nullptr) {
            y = temp;
            if (n->ipAdd < temp->ipAdd) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        n->parent = y;
        if (y == nullptr) {
            this->root = n;
        } else if (n->ipAdd < y->ipAdd) {
            y->left = n;
        } else {
            y->right = n;
        }
        splay(n);
    }

    Node* search(Node* n, int x) {
        if (n == nullptr || x == n->ipAdd) {
            if (n != nullptr) {
                splay(n);
            }
            return n;
        }
        if (x < n->ipAdd) {
            return search(n->left, x);
        } else {
            return search(n->right, x);
        }
    }

    void inorder(Node* n, std::string cmn) {
        if (n != nullptr) {
            inorder(n->left, cmn);
            std::cout << cmn << n->ipAdd << " -> " << n->dataPacket << std::endl;
            inorder(n->right, cmn);
        }
    }
};

int main() {
    std::string cmn = "192.168.3.";
    SplayTree t;
    Node* nodes[] = {
        new Node(104), new Node(112), new Node(117), new Node(124),
        new Node(121), new Node(108), new Node(109), new Node(111),
        new Node(122), new Node(125), new Node(129)
    };

    for (Node* node : nodes) {
        t.insert(node);
    }

    int find[] = {104, 112, 117, 124, 121, 108, 109, 111, 122, 125, 129};
    std::srand(std::time(0));
    for (int i = 0; i < sizeof(find) / sizeof(find[0]); i++) {
        int data = std::rand() % 200;
        Node* temp = t.search(nodes[i], find[i]);
        if (temp != nullptr) {
            temp->dataPacket = data;
        }
    }

    std::cout << "IP ADDRESS -> DATA PACKET" << std::endl;
    t.inorder(t.root, cmn);

    return 0;
}
