/**
 * @file rbapp.cpp 
 *
 * Instantiates a RBTree and adds elements into it.
 *
 * @author Joshua Salcido 
 * @date 4/22/16
 */

#include "rbtree.h" 
#include "rbapp.h"
#include <string> 
#include <iostream> 
using namespace std; 

RBapp::RBapp(){
    done = false; 
}

/*
 * Initializes a RBapp then call's mainLoop(); 
 *
 * @return int
*/

int main(){
    RBapp myRBapp;
    myRBapp.mainLoop();
    
    return 0; 
}

/*
 * Reads input until none is given. 
*/
void RBapp::mainLoop(){
    while(!cin.eof() && !done){
        processCommand(); 
    } 
}

/*
 * Reads in commands and data from input calls from
 * functions in rbTree.cpp. 
*/
void RBapp::processCommand(){
    string cmd, key, data;
    while (cin >> cmd){
        if(cmd == "insert"){
            getline(cin, data); 
            processInsert(data);
        }
        else if(cmd == "find"){
            cin >> key; 
            processFind(key); 
        }
        else if(cmd == "delete"){
            getline(cin, data);
            processDelete(data);
        }
        else if(cmd == "print"){
            processPrint(); 
        }
        else {
            if(cmd == "quit"){
                processQuit(); 
            } 
        }
    }
}

/*
 * Seperates data into to strings (key and value) and then inserts 
 * them into tree. 
 *
 * @param string
*/
void RBapp::processInsert(string& data){
    //string::size_t pos; 
    string::size_type pos;
    string key, value;

    pos = data.find(' ', 1);
    key = data.substr(1, pos-1); 
    value = data.substr(pos+1);

    myRBT.rbInsert(key, value); 

}

/*
 * Calls print function in rbTree.cpp. 
 *
 * @param Node 
*/
void RBapp::processPrint(){
    myRBT.rbPrintTree();
}

/*
 * Calls search function in rbTree.cpp to find
 * a specified node.  
 *
 * @param string
*/
void RBapp::processFind(string& key){
    vector<const string*> data;
    vector<const string*>::iterator it;

    data = myRBT.rbFind(key); 
    for(it = data.begin(); it != data.end(); it++){
        cout << key << " " << *(*it) << endl;     
    }

}

/*
 * Calls delete function in rbTree.cpp to delete
 * a specified node.  
 *
 * @param string
*/
void RBapp::processDelete(string& data){
    string::size_type pos; 
    string key, value;

    pos = data.find(' ', 1);
    key = data.substr(1, pos-1); 
    value = data.substr(pos+1);

    myRBT.rbDelete(key, value); 

}

// Just switches a bool, assits mainLoop() to
// determine whether "quit" command was read.
void RBapp::processQuit(){
    if(!done){
        done = true; 
    }
}
