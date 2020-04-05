#include "iostream"
#include "stack"
#include "queue"
#include <map>

using namespace std;

//Node class
class Node {
public:
    int data;
    Node *left;
    Node *right;

    explicit Node(int d) {
        data = d;
        left = nullptr;
        right = nullptr;
    }
};


//Structure for Diameter and Height
class DiaHei {
public:
    int height;
    int diameter;

    DiaHei(int h, int d) {
        height = h;
        diameter = d;
    }
};

//PLR
//preOrder Recursive Function
void preOrderRecursive(Node *root) {
    if (!root) return;
    cout << root->data << " ";
    preOrderRecursive(root->left);
    preOrderRecursive(root->right);
}

//LRP
//postOrder Recursive Function
void postOrderRecursive(Node *root) {
    if (!root) return;
    postOrderRecursive(root->left);
    postOrderRecursive(root->right);
    cout << root->data << " ";
}

//LPR
//inOrder Recursive Function
void inOrderRecursive(Node *root) {
    if (!root) return;
    inOrderRecursive(root->left);
    cout << root->data << " ";
    inOrderRecursive(root->right);
}

//PLR
//preOrder Iterative Function
void preOrderIterative(Node *root) {
    stack<Node *> s;
    s.push(root);
    while (!s.empty()) {

        Node *temp = s.top();
        s.pop();

        cout << temp->data << " ";
        if (temp->right) s.push(temp->right);
        if (temp->left) s.push(temp->left);

    }
}

//LRP
//postOrder Iterative Function
void postOrderIterative(Node *root) {
    stack<Node *> s;
    Node *cur = root;

    do {

        while (cur != nullptr) {
            if (cur->right) s.push(cur->right);
            s.push(cur);
            cur = cur->left;
        }

        cur = s.top();
        s.pop();

        if (cur->right && !s.empty() && cur->right == s.top()) {
            Node *temp = s.top();
            s.pop();
            s.push(cur);
            cur = temp;
        } else {
            cout << cur->data << " ";
            cur = nullptr;
        }

    } while (!s.empty());
}

//LPR
//ineOrder Iterative Function
void inOrderIterative(Node *root) {
    stack<Node *> s;
    Node *cur = root;

    while (!s.empty() || cur) {

        while (cur != nullptr) {
            s.push(cur);
            cur = cur->left;
        }

        cur = s.top();
        s.pop();
        cout << cur->data << " ";
        cur = cur->right;
    }

}

//Height of the Tree
int height(Node *root) {
    if (!root) return 0;
    return max(height(root->left), height(root->right)) + 1;
}

//LevelOrder Recursive Helper Function
void levelOrderRecursiveUtil(Node *root, int level) {
    if (!root) return;
    if (level == 1) {
        cout << root->data << " ";
        return;
    }
    levelOrderRecursiveUtil(root->left, level - 1);
    levelOrderRecursiveUtil(root->right, level - 1);
}

//LevelOrder Recursive Function
void levelOrderRecursive(Node *root) {
    int x = height(root);
    for (int i = 1; i <= x; ++i) {
        levelOrderRecursiveUtil(root, i);
    }
}

//LevelOrder Iterative Function
void levelOrderIterative(Node *root) {
    queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        int x = q.size();
        for (int i = 0; i < x; ++i) {
            Node *temp = q.front();
            q.pop();
            cout << temp->data << " ";
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
    }
}

//LeftView Recursive Helper Function
void leftViewRecursiveUtil(Node *root, int level, int &count) {
    if (!root) return;
    if (level == 1 && count == 0) {
        count = 1;
        cout << root->data << " ";
        return;
    }
    leftViewRecursiveUtil(root->left, level - 1, count);
    leftViewRecursiveUtil(root->right, level - 1, count);
}

//LeftView Recursive Function
void leftViewRecursive(Node *root) {
    int x = height(root);
    for (int i = 1; i <= x; i++) {
        int count = 0;
        leftViewRecursiveUtil(root, i, count);
    }
}

//LeftView Iterative Function
void leftViewIterative(Node *root) {
    queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        int x = q.size();
        for (int i = 0; i < x; i++) {
            Node *temp = q.front();
            q.pop();
            if (i == 0) cout << temp->data << " ";
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
    }
}

//RightView Recursive Helper Function
void rightViewRecursiveUtil(Node *root, int level, int &count) {
    if (!root) return;
    if (level == 1 && count == 0) {
        count = 1;
        cout << root->data << " ";
        return;
    }
    rightViewRecursiveUtil(root->right, level - 1, count);
    rightViewRecursiveUtil(root->left, level - 1, count);
}

//RightView Recursive Function
void rightViewRecursive(Node *root) {
    int x = height(root);
    for (int i = 1; i <= x; i++) {
        int count = 0;
        rightViewRecursiveUtil(root, i, count);
    }
}

//RightView Iterative Function
void rightViewIterative(Node *root) {
    queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        int x = q.size();
        for (int i = 0; i < x; i++) {
            Node *temp = q.front();
            q.pop();
            if (i == x - 1) cout << temp->data << " ";
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
    }
}

//TopView Recursive Helper Function
void topViewRecursiveUtil(Node *root, map<int, Node *> &hdMap, int hd) {
    if (!root) return;
    if (hdMap.find(hd) == hdMap.end()) hdMap.insert({hd, root});
    topViewRecursiveUtil(root->left, hdMap, hd - 1);
    topViewRecursiveUtil(root->right, hdMap, hd + 1);
}

//TopView Recursive Function
void topViewRecursive(Node *root) {
    map<int, Node *> hdMap;
    topViewRecursiveUtil(root, hdMap, 0);
    for (auto f : hdMap) {
        cout << f.second->data << " ";
    }
}

//BottomView Recursive Helper Function
void bottomViewRecursiveUtil(Node *root, map<int, Node *> &hdMap, int hd) {
    if (!root) return;
    if (hdMap.find(hd) == hdMap.end()) hdMap.insert({hd, root});
    else hdMap[hd] = root;
    bottomViewRecursiveUtil(root->left, hdMap, hd - 1);
    bottomViewRecursiveUtil(root->right, hdMap, hd + 1);
}

//BottomView Recursive Function
void bottomViewRecursive(Node *root) {
    map<int, Node *> hdMap;
    bottomViewRecursiveUtil(root, hdMap, 0);
    for (auto f : hdMap) {
        cout << f.second->data << " ";
    }
}

bool lowestCommonAncestor(Node *root, int v1, int v2) {
    if (!root) return false;
    bool l = lowestCommonAncestor(root->left, v1, v2);
    bool r = lowestCommonAncestor(root->right, v1, v2);
    if ((root->data == v1) || (root->data == v2)) return true;
    if (l && r) {
        cout << root->data;
    }
    return (l || r);
}

int max(int a, int b, int c) {
    if (a > b && a > c) return a;
    if (b > a && b > c) return b;
    else return c;
}

int diameter(Node *root, int *height) {
    if (!root) return 0;
    int lh = 0;
    int rh = 0;
    int ld = diameter(root->left, &lh);
    int rd = diameter(root->right, &rh);
    *height = 1 + max(lh, rh);
    return max(rd, ld, (1 + lh + rh));
}


DiaHei *diameterStructure(Node *root, DiaHei *res) {
    if (!root) return new DiaHei(0, 0);

    DiaHei *ld = diameterStructure(root->left, res);

    DiaHei *rd = diameterStructure(root->right, res);

    res->height = 1 + max(ld->height, rd->height);

    return new DiaHei(res->height, max(rd->height, ld->height, 1 + ld->height + rd->height));
}


pair<int, int> diameterPair(Node *root, pair<int, int> res) {
    if (!root) return make_pair<int, int>(0, 0);
    pair<int, int> ld = diameterPair(root->left, res);
    pair<int, int> rd = diameterPair(root->right, res);
    res.first = 1 + max(ld.first, rd.first);
    return make_pair(res.first, max(rd.second, ld.second, (1 + ld.first + rd.first)));
}

int searchId(vector<int> arr, int s, int e, int v) {
    int i;
    for (i = s; i <= e; i++) {
        if (arr[i] == v)
            break;
    }
    return i;
}

Node *makeTreePreOrderInOrder(vector<int> pre, const vector<int> &in, int s, int e, int &i) {

    if (s > e || i > pre.size()) {
        return nullptr;
    }

    Node *root = new Node(pre[i++]);

    int id = searchId(in, s, e, root->data);

    root->left = makeTreePreOrderInOrder(pre, in, s, id - 1, i);
    root->right = makeTreePreOrderInOrder(pre, in, id + 1, e, i);

    return root;
}


Node *toPostOrder(vector<int> post, const vector<int> &in, int s, int e, int *j) {

    if (s > e)
        return nullptr;

    Node *node = new Node(post[*j]);
    (*j)--;

    if (s == e)
        return node;

    int id = searchId(in, s, e, node->data);

    node->right = toPostOrder(post, in, id + 1, e, j);
    node->left = toPostOrder(post, in, s, id - 1, j);

    return node;
}

void verticalViewRecursiveUtil(Node *root, map<int, vector<Node *>> &hdMap, int hd) {
    if (!root) return;
    if (hdMap.find(hd) == hdMap.end()) {
        vector<Node *> a;
        a.push_back(root);
        hdMap.insert({hd, a});
    } else {
        vector<Node *> a = hdMap[hd];
        a.push_back(root);
        hdMap[hd] = a;
    }
    verticalViewRecursiveUtil(root->left, hdMap, hd - 1);
    verticalViewRecursiveUtil(root->right, hdMap, hd + 1);
}

void verticalViewRecursive(Node *root) {
    map<int, vector<Node *>> hdMap;
    verticalViewRecursiveUtil(root, hdMap, 0);
    for (const auto &f : hdMap) {
        for (auto k:f.second) {
            cout << k->data << " ";
        }
    }
}

map<int, Node *> leftOrderUtil(Node *root) {
    queue<Node *> q;
    map<int, Node *> map;
    q.push(root);
    int j = 0;
    map.insert({j++, root});
    while (!q.empty()) {

        int x = q.size();
        for (int i = 0; i < x; ++i) {
            Node *temp = q.front();
            q.pop();

            if (temp->left) {
                q.push(temp->left);
                map.insert({j++, temp->left});
            }
            if (temp->right) q.push(temp->right);
        }

    }
    return map;
}

void leftOrder(Node *root) {
    map<int, Node *> map = leftOrderUtil(root);
    for (auto f:map) {
        cout << f.second->data << " ";
    }
}

map<int, Node *> rightOrderUtil(Node *root) {
    queue<Node *> q;
    map<int, Node *> map;
    q.push(root);
    int j = 0;
    map.insert({j++, root});
    while (!q.empty()) {

        int x = q.size();
        for (int i = 0; i < x; ++i) {
            Node *temp = q.front();
            q.pop();

            if (temp->left) q.push(temp->left);
            if (temp->right) {
                q.push(temp->right);
                map.insert({j++, temp->right});
            }
        }

    }
    return map;
}

void rightOrder(Node *root) {
    map<int, Node *> map = rightOrderUtil(root);
    for (auto f:map) {
        cout << f.second->data << " ";
    }
}

Node *resolve(Node *root, int v) {
    if (!root) return nullptr;
    if (root->data == v) return root;
    Node *l = resolve(root->left, v);
    Node *r = resolve(root->right, v);
    return l ? l : r;
}


bool isPerfectTree(Node *root) {
    if (!root) return true;
    if ((root->left && !root->right) || (root->right && !root->left)) return false;
    else return isPerfectTree(root->left) && isPerfectTree(root->right);
}

bool isCompleteTreeBad(Node *root) {
    queue<Node *> q;
    q.push(root);
    int c = 0;
    while (!q.empty()) {
        int x = q.size();
        for (int i = 0; i < x; i++) {
            Node *temp = q.front();
            q.pop();
            if (temp->left) {
                if (c == 1)
                    return false;
                q.push(temp->left);
            } else c = 1;
            if (temp->right) {
                if (c == 1)
                    return false;
                q.push(temp->right);
            } else c = 1;
        }
    }
    return true;
}

int count(Node *root) {
    if (!root) return 0;
    return (1 + count(root->left) + count(root->right));
}

bool isCompleteTree(Node *root, int index, int count) {
    if (!root) return true;
    if (index >= count)
        return false;
    return isCompleteTree(root->left, (2 * index) + 1, count) && isCompleteTree(root->right, (2 * index) + 2, count);
}

void flipTreeNode(Node *v) {
    Node *temp = v->left;
    v->left = v->right;
    v->right = temp;
}

void flipTreeIndex(Node *root, int i, int v) {
    if (i > v) return;
    if (i == v) {
        flipTreeNode(root);
    }
    flipTreeIndex(root->left, 2 * i + 1, v);
    flipTreeIndex(root->right, 2 * i + 2, v);
}

//Mirror/Inverse a Tree
void mirror(Node *root) {
    if (!root) return;

    mirror(root->left);
    mirror(root->right);
    flipTreeNode(root);
}


int main() {

    //make a tree
    Node *root = new Node(1);

    root->left = new Node(2);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    root->right = new Node(3);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    root->right->right->right = new Node(8);

    //preOrder
    cout << "preOrderRecursive :";
    preOrderRecursive(root);
    cout << endl << "preOrderIterative :";
    preOrderIterative(root);
    cout << endl;

    //postOrder
    cout << endl << "postOrderRecursive :";
    postOrderRecursive(root);
    cout << endl << "postOrderIterative :";
    postOrderIterative(root);
    cout << endl;

    //inOrder
    cout << endl << "inOrderRecursive :";
    inOrderRecursive(root);
    cout << endl << "inOrderIterative :";
    inOrderIterative(root);
    cout << endl;

    //height
    cout << endl << "height :";
    cout << height(root) << endl;
    cout << endl;

    //levelOrder
    cout << "levelOrderRecursive :";
    levelOrderRecursive(root);
    cout << endl << "levelOrderIterative :";
    levelOrderIterative(root);
    cout << endl;

    //leftView
    cout << endl << "leftViewRecursive :";
    leftViewRecursive(root);
    cout << endl << "leftViewIterative :";
    leftViewIterative(root);
    cout << endl;

    //rightView
    cout << endl << "rightViewRecursive :";
    rightViewRecursive(root);
    cout << endl << "rightViewIterative :";
    rightViewIterative(root);
    cout << endl;

    //topView
    cout << endl << "topViewRecursive :";
    topViewRecursive(root);
    cout << endl;

    //bottomView
    cout << endl << "bottomViewRecursive :";
    bottomViewRecursive(root);
    cout << endl;

    //lowestCommonAncestor
    cout << endl << "lowestCommonAncestor: ";
    lowestCommonAncestor(root, 8, 6);
    cout << endl;

    //Diameter
    //using pointer
    cout << endl << "Diameter using pointers:";
    int h = 0;
    cout << diameter(root, &h) << endl;
    //using structure
    auto *res = new DiaHei(0, 0);
    cout << "Diameter using structure: ";
    cout << diameterStructure(root, res)->diameter << endl;
    //using pair
    pair<int, int> resultPair;
    resultPair.second = 0;
    resultPair.first = 0;
    cout << "Diameter using pair: ";
    cout << diameterPair(root, resultPair).second << endl;
    cout << endl;


    vector<int> pre = {1, 2, 4, 5, 3, 6, 7, 8};
    vector<int> in = {4, 2, 5, 1, 6, 3, 7, 8};
    vector<int> post = {4, 5, 2, 6, 8, 7, 3, 1};

    //make tree using PreOrder and InOrder
    cout << endl << "Making tree using PreOrder and InOrder";
    int i = 0;
    Node *head = makeTreePreOrderInOrder(pre, in, 0, (int) pre.size() - 1, i);
    cout << endl << "preOrder ";
    preOrderRecursive(head);
    cout << endl << "inOrder ";
    inOrderRecursive(head);
    cout << endl << "postOrder ";
    postOrderRecursive(head);
    cout << endl;


    //make tree using PostOrder and InOrder
    cout << endl << "Making tree using PostOrder and InOrder";
    int j = (int) pre.size() - 1;
    int s = 0;
    int e = (int) pre.size() - 1;
    head = toPostOrder(post, in, s, e, &j);
    cout << endl << "pre ";
    preOrderRecursive(head);
    cout << endl << "in ";
    inOrderRecursive(head);
    cout << endl << "post ";
    postOrderRecursive(head);
    cout << endl;

    //Vertical View of the tree
    cout << endl << "Vertical View: ";
    verticalViewRecursive(root);
    cout << endl;

    //Right Order of the tree
    cout << endl << "Right Order : ";
    rightOrder(root);
    cout << endl;

    //Left Order of the tree
    cout << endl << "Left Order : ";
    leftOrder(root);
    cout << endl;


    root->right->right->right = nullptr;
    //PerfectTree
    cout << endl;
    inOrderRecursive(root);
    if (isPerfectTree(root)) cout << endl << "Tree is Perfect";
    else cout << endl << "Tree is not Perfect";



    //PerfectTree
    cout << endl;
    inOrderRecursive(root);
    if (isPerfectTree(root)) cout << endl << "Tree is Perfect";
    else cout << endl << "Tree is not Perfect";


    Node *incompleteTree = new Node(5);
    incompleteTree->left = new Node(2);
    incompleteTree->left->left = new Node(4);
    incompleteTree->right = new Node(7);
    incompleteTree->right->left = new Node(6);
    //Complete Tree
    cout << endl << "Complete Tree: ";
    cout << isCompleteTree(root, 0, count(root));

    cout << endl << "Complete Tree: ";
    cout << isCompleteTree(root, 0, count(incompleteTree));
    cout << endl;


    //Flipping Tree across a Node
    cout << endl;
    cout << "Flipping Tree using Node 1" << endl;
    flipTreeNode(resolve(root, 1));
    inOrderRecursive(root);


    //Flipping Tree across a index
    cout << endl << "Flipping Tree using index 0";
    flipTreeIndex(root, 0, 0);
    cout << endl;
    inOrderRecursive(root);
    cout << endl;


    //Mirror/Invert a Tree
    cout << endl << "Mirror/Invert a Tree";
    root = new Node(5);
    root->left = new Node(2);
    root->right = new Node(7);
    root->right->left = new Node(6);
    root->right->right = new Node(8);
    cout << endl << "InOrder before mirror: ";
    inOrderRecursive(root);
    cout << endl;
    mirror(root);
    cout << "InOrder after mirror: ";
    inOrderRecursive(root);
    cout << endl << endl;

}