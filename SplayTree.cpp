#include <iostream>

using namespace std;

struct Node {
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
  int key = -1;
};

struct TwoTrees {
  Node* leftTree = nullptr;
  Node* rightTree = nullptr;
};

void SetParent(Node* v, Node* p) {
  if (v != nullptr) {
    v->parent = p;
  }
}

void SetParents(Node* p) {
  if (p == nullptr) {
    return;
  }
  if (p->left != nullptr) {
    p->left->parent = p;
  }
  if (p->right != nullptr) {
    p->right->parent = p;
  }
}

void Rotate(Node* p, Node* v) {
  Node* g = p->parent;
  if (g != nullptr) {
    if (g->left == p) {
      g->left = v;
    }
    if (g->right == p) {
      g->right = v;
    }
  }
  if (p->left == v) {
    Node* r = v->right;
    v->right = p;
    p->left = r;
  } else if (p->right == v) {
    Node* l = v->left;
    v->left = p;
    p->right = l;
  }
  SetParents(v);
  SetParents(p);
  v->parent = g;
}

Node* Splay(Node* v) {
  if (v->parent == nullptr) {
    return v;
  }
  Node* p = v->parent;
  if (p->parent == nullptr) {
    Rotate(p, v);
    return v;
  }
  Node* g = p->parent;
  if ((g->left == p && p->left == v) || (g->right == p && p->right == v)) {
    Rotate(g, p);
    Rotate(p, v);
  } else {
    Rotate(p, v);
    Rotate(g, v);
  }
  return Splay(v);
}

Node* Find(Node* root, int key) {
  if (root == nullptr) {
    return nullptr;
  }
  if (root->key < key && root->right != nullptr) {
    return Find(root->right, key);
  }
  if (root->key > key && root->left != nullptr) {
    return Find(root->left, key);
  }
  if (root->key == key) {
    return Splay(root);
  }
  return Splay(root);
}

TwoTrees Split(Node* root, int key) {
  if (root == nullptr) {
    return {nullptr, nullptr};
  }
  root = Find(root, key);
  if (root->key == key) {
    SetParent(root->left, nullptr);
    SetParent(root->right, nullptr);
    Node* l = root->left;
    Node* r = root->right;
    delete root;
    return {l, r};
  }
  if (root->key < key) {
    Node* right = root->right;
    root->right = nullptr;
    SetParent(right, nullptr);
    return {root, right};
  }
  Node* left = root->left;
  root->left = nullptr;
  SetParent(left, nullptr);
  return {left, root};
}

Node* Insert(Node* root, int key) {
  TwoTrees tmp = Split(root, key);
  Node* rootNew = new Node{tmp.leftTree, tmp.rightTree, nullptr, key};
  SetParents(rootNew);
  return rootNew;
}

int next(Node* root, int x) {
  int next = -1;
  while (true) {
    if (root == nullptr) {
      break;
    }
    if (root->key > x && root->left != nullptr) {
      next = root->key;
      root = root->left;
      continue;
    }
    if ((root->key > x && root->left == nullptr) || root->key == x) {
      return root->key;
    }
    root = root->right;
  }
  return next;
}

void Clear(Node* root) {
  if (root != nullptr) {
    Clear(root->left);
    Clear(root->right);
    delete root;
  }
}

int main() {
  Node* tree = nullptr;
  int N, last_answer;
  cin >> N;
  char last_command = '0';
  for (; N > 0; N--) {
    int key;
    char command = '0';
    cin >> command >> key;
    if (last_command != '?' && command == '+') {
      tree = Insert(tree, key);
    }
    if (command == '?') {
      last_answer = next(tree, key);
      cout << last_answer << endl;
    }
    if (last_command == '?' && command == '+') {
      key = (key + last_answer) % 1000000000;
      tree = Insert(tree, key);
    }
    last_command = command;
  }
  Clear(tree);
  return 0;
}