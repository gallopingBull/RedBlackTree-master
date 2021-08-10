 /**
 * @file rbtree.cpp Red-Black Tree Functions
 *
 * @brief
 *    Implementation of the  red-black tree member functions.
 *
 * @author Joshua Salcido
 * @date 4/22/16
 */

#include <iostream>
#include <iomanip>
#include "rbtree.h"

using std::cout;
using std::setw;
using std::endl;

/*
 * Red-Black Tree Constructor, initializes member variables.
*/
RBTree::RBTree(){
    nil = new Node();
    root = nil; 
}

/*
 * Red-Black Tree Destructor
*/
RBTree::~RBTree(){
    nodeDestroy(root);
    delete nil; 
}

/*
 * Node Constructor, initializes Node member variables.
*/
RBTree::Node::Node(){
    parent = NULL;
    left = NULL;
    right = NULL;
    color = 'B'; 
}

/*
 * Node Destructor
*/
RBTree::Node::~Node(){
    delete key;
    delete value;
}

/*
 * Node constructor 
 *
 * @param const 
 * @param const 
 * @param Node node
*/
RBTree::Node::Node(const string& _key, const string& _value, Node* node){
    parent = node;
    left = node;
    right = node; 
    key = new string(_key);
    value = new string(_value);
}

/*
 * Insert helper function. Initializes new node for 
 * each element that'll be inserted into tree. 
 *
 * @param const string key 
 * @param const string value
*/
void RBTree::rbInsert(const string& key, const string& value){
    Node *tmp;
    tmp = new Node(key, value, nil); 
    tmp->left = nil;
    tmp->right = nil; 

    rbInsert(tmp); 

}

/*
 * Inserts node into tree.
 *
 * @param Node z 
*/
void RBTree::rbInsert(Node* z){
    Node *y = nil; 
    Node *x = root;

    while(x != nil){
        y = x; 
        if(*(z->key) < *(x->key)){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    z->parent = y;
    if(y == nil){
        root = z;
    }
    else if(*(z->key) < *(y->key)){
        y->left = z;
    }
    else{
        y->right = z; 
    }

    z->left = nil;
    z->right = nil; 
    z->color = 'R';

    rbInsertFixup(z); 
}

/*
 * Rebalances tree after node is inserted. 
 *
 * @param Node z
*/
void RBTree::rbInsertFixup(Node* z){
    Node *y;

    while(z->parent->color == 'R'){
        if(z->parent == z->parent->parent->left){
            y = z->parent->parent->right;
            if(y->color == 'R'){
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R'; 
                z = z->parent->parent; 
            }
            else{
                if(z == z->parent->right){
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(z->parent->parent);
            }
        }
        else{
            y = z->parent->parent->left;
            if(y->color == 'R'){
                z->parent->color = 'B';
                y->color = 'B'; 
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->left){
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = 'B'; 
                z->parent->parent->color = 'R';
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = 'B';
}

/*
 * Rotates part of subtree to assist rbInsertFixup and rbDeeteFixup. 
 *
 * @param Node x
*/
void RBTree::leftRotate(Node* x){
    Node *y = x->right;
    x->right = y->left;

    if(y->left != nil){
        y->left->parent = x; 
    }
    
    y->parent = x->parent; 

    if(x->parent == nil){
        root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y; 
}

/*
 * Rotates part of subtree to assist rbInsertFixup and rbDeeteFixup. 
 *
 * @param Node x
*/
void RBTree::rightRotate(Node* x){
    Node *y = x->left;
    x->left = y->right;

    if(y->right != nil){
        y->right->parent = x; 
    }
    
    y->parent = x->parent; 

    if(x->parent == nil){
        root = y;
    }
    else if(x == x->parent->right){
        x->parent->right = y;
    }
    else{
        x->parent->left = y;
    }
    
    y->right = x;
    x->parent = y; 
}

/*
 * Finds key using rbTreeSearch(). Then looks for any duplicates 
 * using rbTreeSuccessor() and rbTreePredessor(). 
 *
 * @param string
 * @return vector 
*/
vector<const string*> RBTree::rbFind(const string& key){
    vector<const string*> data;
    Node *x = nil;
    x = rbTreeSearch(root, key); 

    if(x != nil && *(x->key) == key){
        data.push_back(x->value);

        Node *succ_Node;
        Node *r_Succ_Node = x;
        succ_Node = rbTreeSuccessor(r_Succ_Node);

        while(succ_Node != nil && *(succ_Node->key) == key){
            data.push_back(succ_Node->value);
            r_Succ_Node = succ_Node;
            succ_Node = rbTreeSuccessor(r_Succ_Node);
        }

        Node *pre_Node;
        Node *r_Pre_Node = x; 
        pre_Node = rbTreePredecessor(r_Pre_Node);

        while(pre_Node != nil && *(pre_Node->key) == key){
            data.push_back(pre_Node->value);
            r_Pre_Node = pre_Node;
            pre_Node = rbTreePredecessor(r_Pre_Node); 
        }
    }
    return data; 
}

/*
 * Loops through the tree unitl it finds user declared key. 
 *
 * @param Node
 * @param string 
 * @return Node 
*/
RBTree::Node* RBTree::rbTreeSearch(Node *x, const string& key){
    if(x == nil || key == *(x->key)){
        return x;
    }
    if(key < *(x->key)){
        return rbTreeSearch(x->left, key); 
    }
    else{
        return rbTreeSearch(x->right, key); 
    }
}

/*
 *Helper function for rbDelete(). 
 *
 * @param string 
 * @param string  
*/
void RBTree::rbDelete(const string& key, const string& value){
    Node *z = nil;
    z = rbTreeSearch(root, key);

    if(z == nil){
        return; 
    }
    else{
        if(*(z->value) == value){
            Node *tmp = z;
            rbDelete(tmp);
            rbDelete(key, value);
            return;
        }
        
        Node *succ_Node;
        Node *r_Succ_Node = z;
        succ_Node = rbTreeSuccessor(r_Succ_Node);
        while(succ_Node != nil && *(succ_Node->key) == key){
            if(*(succ_Node->value) == value){
                rbDelete(succ_Node);
                rbDelete(key, value);
                succ_Node = nil; 
            }
            else{
                r_Succ_Node = succ_Node;
                succ_Node = rbTreeSuccessor(r_Succ_Node);
            }
        }
        
        Node *pre_Node;
        Node *r_Pre_Node = z;
        pre_Node = rbTreePredecessor(r_Pre_Node);
        while(pre_Node != nil && *(pre_Node->value) == key){
            if(*(pre_Node->value) == value){
                rbDelete(pre_Node);
                rbDelete(key,value);
                pre_Node = nil;
            }
            else{
                r_Pre_Node = pre_Node;
                pre_Node = rbTreePredecessor(r_Pre_Node); 
            }
        }
    }
} 

/*
 * Deletes node from tree.  
 *
 * @param Node
*/
void RBTree::rbDelete(Node* z){
    Node *y;
    Node *x; 
    char y_OGColor; 

    y = z; 
    y_OGColor = y->color;
    if(z->left == nil){
        x = z->right;
        rbTransplant(z, z->right);
    }
    else if(z->right == nil){
        x = z->left;
        rbTransplant(z, z->left); 
    }
    else{
        y = rbTreeMaximum(z->left);
        y_OGColor = y->color;
        x = y->left;
        
        if(y->parent == z){
            x->parent = y;
        }
        else{
            rbTransplant(y, y->left);
            y->left = z->left; 
            y->left->parent = y; 
        }
        rbTransplant(z, y);
        y->right = z->right; 
        y->right->parent = y;
        y->color = z->color; 
    }

    if(y_OGColor == 'B'){
        rbDeleteFixup(x);
    }
    delete z; 
}

/*
 * Rebalances tree at the end of rbDelete() when it's called. 
 *
 * @param Node
*/
void RBTree::rbDeleteFixup(Node* x){
    Node *w;

    while(x != root && x->color == 'B'){
        if(x == x->parent->left){
            w = x->parent->right;
            if(w->color == 'R'){
                w->color = 'B'; 
                x->parent->color = 'R';
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if(w->left->color == 'B' && w->right->color == 'B'){
                w->color = 'R'; 
                x = x->parent;
            }
            else{
                if(w->right->color == 'B'){
                    w->left->color = 'B'; 
                    w->color = 'R'; 
                    rightRotate(w);
                    w = x->parent->right; 
                }
                w->color = x->parent->color;
                x->parent->color = 'B'; 
                w->right->color = 'B';
                leftRotate(x->parent);
                x = root; 
            }
        }
        else{
            w = x->parent->left;
            if(w->color == 'R'){
                w->color = 'B';
                x->parent->color = 'R';
                rightRotate(x->parent);
                w = x->parent; 
            }
            w->color = x->parent->color; 
            x->parent->color = 'B'; 
            w->left->color = 'B';
            rightRotate(x->parent); 
            x = root;
        }
    }
    x->color = 'B'; 
}

/*
 * Moves subtree, called during rbDelete(). 
 *
 * @param Node 
 * @param Node
*/
void RBTree::rbTransplant(Node* u, Node* v){
    if(u->parent == nil){
        root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v; 
    }
    else{
        u->parent->right = v; 
    }
    v->parent = u->parent; 
}

/*
 * Finds the minimum node and return it.   
 *
 * @param Node 
 * @return Node
*/
RBTree::Node* RBTree::rbTreeMinimum(Node* x){
    while(x->left != nil){
        x = x->left;
    }
    return x;
}

/*
 * Finds the maximum node and return it.   
 *
 * @param Node 
 * @return Node
*/
RBTree::Node* RBTree::rbTreeMaximum(Node* x){
    while(x->right != nil){
        x = x->right;
    }
    return x;
}

/*
 * Finds a node's successor and returns it. 
 *
 * @param Node 
 * @return Node
*/
RBTree::Node* RBTree::rbTreeSuccessor(Node* x){
    Node *y;

    if(x->right != nil){
        return rbTreeMinimum(x->right);
    }
    
    y = x->parent;
    while(y != nil && x == y->right){
        x = y;
        y = y->parent;
    }
    return y; 
}

/*
 * Finds a node's predecssor and returns it. 
 *
 * @param Node 
 * @return Node
*/
RBTree::Node* RBTree::rbTreePredecessor(Node* x){
    Node *y;

    if(x->left != nil){
        return rbTreeMaximum(x->left);
    }
    
    y = x->parent;
    while(y != nil && x == y->left){
        x = y;
        y = y->parent;
    }
    return y; 
}

/*
 * Recursively destorys all nodes. 
 *
 * @param Node 
 * @return Node
*/
void RBTree::nodeDestroy(Node* n){
    
    if(n != nil){
        nodeDestroy(n->left);
        nodeDestroy(n->right); 
        delete n; 
    }
}

/*
 * Calls reverseInOrderPrint(), starts at 
 * root with depth of 0.  
*/
void RBTree::rbPrintTree(){
    reverseInOrderPrint(root, 0); 
}

/*
 * Prints out elements in tree. Dr. Challinger wrote this. 
 *
 * @param Node 
 * @param int
*/
void RBTree::reverseInOrderPrint(Node *x, int depth) {
   if ( x != nil ) {
      reverseInOrderPrint(x->right, depth+1);
      cout << setw(depth*4+4) << x->color << " ";
      cout << *(x->key) << " " << *(x->value) << endl;
      reverseInOrderPrint(x->left, depth+1);
   }
}
 
