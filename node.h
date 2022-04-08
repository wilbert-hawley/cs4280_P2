#include <string>
#include "token.h"
using namespace std;

struct Node {
    string label;
    Node* child1;
    Node* child2;
    Node* child3;
    Node* child4;
    token tok1;
    token tok2;
    token tok3;
    token tok4;
    token tok5;
};

Node* getNode(string);