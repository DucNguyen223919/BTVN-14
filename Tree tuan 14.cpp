#include <iostream>
#include <string>
#include <queue>

using namespace std;

// Dinh nghia node
struct Node {
    string value; // Gia tri tai node (toan hang hoac toan tu)
    Node* left;   // Con trai
    Node* right;  // Con phai
    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

// Lop bieu dien cay bieu thuc
class ExpressionTree {
private:
    Node* root;

    // Duyet trung to (Infix)
    void duyetInfix(Node* node) {
        if (node == nullptr) return;
        if (!isOperator(node->value)) cout << node->value << " ";
        else {
            cout << "( ";
            duyetInfix(node->left);
            cout << node->value << " ";
            duyetInfix(node->right);
            cout << ") ";
        }
    }

    // Duyet tien to (Prefix)
    void duyetPrefix(Node* node) {
        if (node == nullptr) return;
        cout << node->value << " ";
        duyetPrefix(node->left);
        duyetPrefix(node->right);
    }

    // Duyet hau to (Postfix)
    void duyetPostfix(Node* node) {
        if (node == nullptr) return;
        duyetPostfix(node->left);
        duyetPostfix(node->right);
        cout << node->value << " ";
    }

    // Kiem tra toan tu
    bool isOperator(const string& value) {
        return value == "+" || value == "-" || value == "*" || value == "/" || value == "^";
    }

    // Tim node trong cay theo gia tri
    Node* findNode(Node* node, const string& value) {
        if (node == nullptr) return nullptr;
        if (node->value == value) return node;
        Node* leftResult = findNode(node->left, value);
        if (leftResult != nullptr) return leftResult;
        return findNode(node->right, value);
    }

public:
    // Ham khoi tao
    ExpressionTree() : root(nullptr) {}
    bool isEmpty() {
        return root == nullptr;
    }
    Node* getRoot() {
        return root;
    }
    void insertRoot(const string& value, Node* left = nullptr, Node* right = nullptr) {
        root = new Node(value);
        root->left = left;
        root->right = right;
    }

    // Bo sung phan tu vao cay tai 1 vi tri cu the
    void insertNode(const string& parentValue, const string& value, bool leftChild) {
        if (isEmpty()) {
            cout << "Cay rong, khoi tao goc cay truoc!" << endl;
            return;
        }

        Node* parent = findNode(root, parentValue);
        if (parent == nullptr) {
            cout << "Ko tim thay node co gia tri: " << parentValue << endl;
            return;
        }

        if (leftChild) {
            if (parent->left == nullptr) {
                parent->left = new Node(value);
            } else {
                cout << "Node nay da co con trai!" << endl;
            }
        } else {
            if (parent->right == nullptr) {
                parent->right = new Node(value);
            } else {
                cout << "Node nay da co con phai!" << endl;
            }
        }
    }

    void printInfix() {
        duyetInfix(root);
        cout << endl;
    }

    void printPrefix() {
        duyetPrefix(root);
        cout << endl;
    }

    void printPostfix() {
        duyetPostfix(root);
        cout << endl;
    }
};

int main() {
    ExpressionTree tree;

    // Xây dung cay bieu thuc ban dau
    Node* a = new Node("a");
    Node* b = new Node("b");
    Node* c = new Node("c");
    Node* d = new Node("d");
    Node* h = new Node("h");
    Node* f = new Node("f");
    Node* e = new Node("e");

    Node* five = new Node("5");
    Node* six = new Node("6");
    Node* oneHalf = new Node("1/2");

    Node* c6 = new Node("^");
    c6->left = c;
    c6->right = six;

    Node* bc6 = new Node("*");
    bc6->left = b;
    bc6->right = c6;

    Node* div = new Node("/");
    div->left = bc6;
    div->right = d;

    Node* a5 = new Node("*");
    a5->left = a;
    a5->right = five;

    Node* leftSubtree = new Node("-");
    leftSubtree->left = a5;
    leftSubtree->right = div;

    Node* hf = new Node("-");
    hf->left = h;
    hf->right = f;

    Node* eHalf = new Node("^");
    eHalf->left = e;
    eHalf->right = oneHalf;

    Node* rightSubtree = new Node("*");
    rightSubtree->left = hf;
    rightSubtree->right = eHalf;

    tree.insertRoot("+", leftSubtree, rightSubtree);

    // In ket qua ban dau
    cout << "Bieu thuc ban dau:\n";
    cout << "Trung to (Infix): ";
    tree.printInfix();

    cout << "Tien to (Prefix): ";
    tree.printPrefix();

    cout << "Hau to (Postfix): ";
    tree.printPostfix();

    // Bo sung phan tu nguoi dung
    string parentValue, newValue;
    bool leftChild;

    cout << "\Nhap gia tri cau node cha: ";
    cin >> parentValue;
    cout << "Nhap gia tri cua node moi: ";
    cin >> newValue;
    cout << "Them vao con trai (1) hay con phai (0): ";
    cin >> leftChild;

    tree.insertNode(parentValue, newValue, leftChild);

    // In lai cay sau khi bo sung
    cout << "\Nhap bieu thuc sau khi bo sung:\n";
    cout << "Trung to (Infix): ";
    tree.printInfix();

    cout << "Tien to (Prefix): ";
    tree.printPrefix();

    cout << "Hau to (Postfix): ";
    tree.printPostfix();

    return 0;
}
