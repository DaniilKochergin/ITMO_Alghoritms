#include <iostream>
#include <string>

using namespace std;

int inf = 1e9 + 31;
struct Node {
    Node() : value(inf), left(nullptr), right(nullptr), parent(nullptr) {
    }
    int value;
    Node *left;
    Node *right;
    Node *parent;
};

Node *root = new Node();

Node *find(Node *v, int x) {
    if (v->value == inf || v->value == x) {
        return v;
    }
    if (v->value < x) {
        return find(v->right, x);
    } else {
        return find(v->left, x);
    }
}

bool search(int x) {
    return find(root, x)->value == x;
}

void insert(int x) {
    if (search(x)) return;
    Node *a = find(root, x);
    if (a->value != inf) exit(-1);
    a->value = x;
    Node *c = new Node();
    c->parent = a;
    a->left = c;
    Node *d = new Node();
    d->parent = a;
    a->right = d;
}

Node *go_left(Node *v) {
    if ((v->left)->value == inf) {
        return v;
    }
    return go_left(v->left);
}

Node *go_up(Node *v) {
    if (v->parent == nullptr) {
        return nullptr;
    }
    if ((v->parent)->left == v) {
        return v->parent;
    }
    return go_up(v->parent);
}

Node *next(int x) {
    Node *a = find(root, x);
    if (a->value != inf && (a->right)->value != inf) {
        a = go_left(a->right);
        return a;
    } else {
        a = go_up(a);
        return a;
    }
}

Node *go_right(Node *v) {
    if ((v->right)->value == inf) {
        return v;
    }
    return go_right(v->right);
}

Node *go_up1(Node *v) {
    if (v->parent == nullptr) {
        return nullptr;
    }
    if ((v->parent)->right == v) {
        return v->parent;
    }
    return go_up1(v->parent);
}

Node *prev(int x) {
    Node *a = find(root, x);
    if (a->value != inf && (a->left)->value != inf) {
        a = go_right(a->left);
        return a;
    } else {
        a = go_up1(a);
        return a;
    }
}
bool have_one_sun(Node *a) {
    if ((a->left)->value == inf && (a->right)->value == inf) {
        Node *p = a->parent;
        *a = *(new Node());
        a->parent = p;
        return true;
    }
    if ((a->left)->value == inf && (a->right)->value != inf) {
        Node *p = a->parent;
        if (p != nullptr) {
            if (p->right == a) {
                p->right = a->right;
            } else {
                p->left = a->right;
            }
        } else {
            root = a->right;
        }
        (a->right)->parent = p;
        delete a;
        return true;
    }
    if ((a->right)->value == inf && (a->left)->value != inf) {
        Node *p = a->parent;
        if (p != nullptr) {
            if (p->right == a) {
                p->right = a->left;
            } else {
                p->left = a->left;
            }
        } else {
            root = a->left;
        }
        (a->left)->parent = p;
        delete a;
        return true;
    }
    return false;
}
void erase(int x) {
    if (!search(x)) return;
    Node *a = find(root, x);
    if (a->value != x) exit(-1);
    if (have_one_sun(a)) {
        return;
    }
    Node *b = next(a->value);
    a->value = b->value;
    have_one_sun(b);
}
int main() {
#ifndef _KOCH
    // freopen("read.txt", "r", stdin);
#endif
    string s;
    while (cin >> s) {
        int a;
        cin >> a;
        if (s[0] == 'i') {
            insert(a);
            continue;
        }
        if (s[0] == 'e') {
            if (search(a)) {
                cout << "true" << endl;
            } else {
                cout << "false" << endl;
            }
            continue;
        }
        if (s == "next") {
            Node *ans = next(a);
            if (ans == nullptr) {
                cout << "none" << "\n";
            } else {
                cout << ans->value << "\n";
            }
        }
        if (s == "prev") {
            Node *ans = prev(a);
            if (ans == nullptr) {
                cout << "none" << "\n";
            } else {
                cout << ans->value << "\n";
            }
        }
        if (s[0] == 'd') {
            erase(a);
        }
    }
    return 0;
}