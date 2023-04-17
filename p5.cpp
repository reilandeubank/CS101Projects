#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <vector>

using namespace std;
int ioArr[3000];
int poArr[3000];
string encoded;
int poRoot;

class Node {
    public:
    Node *left;
    Node *right;
    int val;

    Node() {
        val = 0;
        left = right = nullptr;
    }
    Node(int num) {
        val = num;
        left = right = nullptr;
    }
};

class Tree {
    public:
    Node *root; 

    Tree() {
        this->root = nullptr;
    }

    int searchIO(int arr[], int start, int end, int val) {
        int i;
        for(i = start; i <= end; i++) {
            if (arr[i] == val) {
                break;
            }
        }
        return i;
    }

    Node* buildFunction (int iArr[], int pArr[], int start, int end, int *rootIndex) {
        if (start > end) {
            return nullptr;
        }

        Node *n = new Node(pArr[*rootIndex]);
        (*rootIndex)--;

        if (start == end) {
            return n;
            cout << "return n" << endl;
        }

        int IOIndex = searchIO(iArr, start, end, n->val);

        n->right = buildFunction(iArr, pArr, IOIndex + 1, end, rootIndex);
        n->left = buildFunction(iArr, pArr, start, IOIndex - 1, rootIndex);
        return n;
    }

    Node* buildTree(int iArr[], int pArr[], int n) {
        poRoot = n-1;
        return buildFunction(iArr, pArr, 0, n-1, &poRoot);
    }

    void traverseCall(string encodedString, Node *rootNode) {
        int traversal = 0;
        while (traversal < encodedString.size()) {
            traverse(encodedString, rootNode, &traversal);
            traversal++;
        }
    }

    void traverse(string encodedString, Node *rootNode, int *t) {
        bool done = false;
        Node *curr = new Node();
        curr = rootNode;
        while (!done) {
            if (encodedString[*t] == '1') {
                curr = curr->right;
            }
            else if (encodedString[*t] == '0') {
                curr = curr->left;
            }
            else {
                break;
            }
            if(curr == nullptr) {
                break;
            }
            if (curr->val < 128) {
                cout << char(curr->val);
                done = true;
                break;
            }
            (*t)++;
        }
        done = false;
    }

};

int main(int argc, char** argv) {
    if (argc != 4) {
        cout << "Usage: ./a.out inorder.txt postorder.txt encoded.txt" << endl;
        return 1;
    }

    string inOrderFile = argv[1];
    string postOrderFile = argv[2];
    string encodedFile = argv[3];
    ifstream iof(inOrderFile);
    ifstream pof(postOrderFile);
    ifstream ef(encodedFile);

    if (!iof) {
        cout << "Unable to open " << inOrderFile << endl;
        return 2;
    }
    if (!pof) {
        cout << "Unable to open " << postOrderFile << endl;
        return 2;
    }
    if (!ef) {
        cout << "Unable to open " << encodedFile << endl;
        return 2;
    }

    int x = 0;
    while (!(iof.eof())) {
        iof >> ioArr[x];
        x++;
    }
    x = 0;
    while (!(pof.eof())) {
        pof >> poArr[x];
        x++;
    }
    string current;
    while (!(ef.eof())) {
        getline(ef, current);
        encoded.append(current);
    }

    x--;
    Tree t;
    t.root = t.buildTree(ioArr, poArr, x);
    t.traverseCall(encoded, t.root);
    
    return 0;
}