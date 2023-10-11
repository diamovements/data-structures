#include <iostream>
#include <queue>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* parent;
    Node* left;
    Node* right;
};

class RedBlackTree {
private:
    Node* root;
    Node* nil;

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != nil) {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nil) {
            root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;

        if (x->right != nil) {
            x->right->parent = y;
        }

        x->parent = y->parent;

        if (y->parent == nil) {
            root = x;
        }
        else if (y == y->parent->left) {
            y->parent->left = x;
        }
        else {
            y->parent->right = x;
        }

        x->right = y;
        y->parent = x;
    }

    void insertFixup(Node* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else {
                Node* y = z->parent->parent->left;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }

        root->color = BLACK;
    }

    void inorderTraversal(Node* x) {
        if (x != nil) {
            inorderTraversal(x->left);
            std::cout << x->data << " ";
            inorderTraversal(x->right);
        }
    }

    void breadthFirstTraversal(Node* x) {
        if (x == nil)
            return;

        std::queue<Node*> q;
        q.push(x);

        while (!q.empty()) {
            Node* node = q.front();
            q.pop();

            std::cout << node->data << " ";

            if (node->left != nil)
                q.push(node->left);

            if (node->right != nil)
                q.push(node->right);
        }
    }

    int sumLeafValues(Node* x) {
        if (x == nil)
            return 0;

        if (x->left == nil && x->right == nil)
            return x->data;

        return sumLeafValues(x->left) + sumLeafValues(x->right);
    }

    int findHeight(Node* x) {
        if (x == nil)
            return 0;

        int leftHeight = findHeight(x->left);
        int rightHeight = findHeight(x->right);

        return std::max(leftHeight, rightHeight) + 1;
    }

public:
    RedBlackTree() {
        nil = new Node;
        nil->color = BLACK;
        root = nil;
    }

    ~RedBlackTree() {
        // TODO: Implement deletion and free memory.
    }

    void insert(int data) {
        Node* z = new Node;
        z->data = data;
        z->left = nil;
        z->right = nil;
        z->color = RED;

        Node* y = nil;
        Node* x = root;
        while (x != nil) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        z->parent = y;

        if (y == nil) {
            root = z;
        }
        else if (z->data < y->data) {
            y->left = z;
        }
        else {
            y->right = z;
        }

        insertFixup(z);
    }

    void inorderTraversal() {
        inorderTraversal(root);
    }

    void breadthFirstTraversal() {
        breadthFirstTraversal(root);
    }

    int sumLeafValues() {
        return sumLeafValues(root);
    }

    int findHeight() {
        return findHeight(root);
    }
};

int main() {
    RedBlackTree tree;
    int values[] = { 10, 20, 5, 6, 12, 30, 7 };

    for (int value : values) {
        tree.insert(value);
    }

    cout << "Inorder traversal: ";
    tree.inorderTraversal();
    cout << endl;

    cout << "Breadth-first traversal: ";
    tree.breadthFirstTraversal();
    cout << endl;

    cout << "Sum of leaf values: " << tree.sumLeafValues() << endl;
    cout << "Height of the tree: " << tree.findHeight() << endl;

    return 0;
}