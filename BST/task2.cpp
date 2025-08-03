#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include "listBST.hpp"
using namespace std;
/*
g++ -std=c++11 task2.cpp -o  task2
./task2 in_task2.txt > myout_task2.txt
*/

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file) {
        cerr << "Unable to open file\n";
        return 1;
    }
    
    BST<string, int> *bst1 = new ListBST<string, int>();
    if (!bst1) {
        cerr << "Memory allocation failed\n";
        return 2;
    }
    BST<string, int> *bst2 = new ListBST<string, int>();
    if (!bst2) {
        cerr << "Memory allocation failed\n";
        delete bst1; // Clean up previously allocated memory
        return 3;
    }

    int n;
    in_file >> n;
    string word;
    for (int i = 0; i < n; ++i) {
        // TODO: Implement the logic to read Phil's words
        // Start your code here
        in_file >> word;
        if(bst1->find(word)){
            bst1->update(word,bst1->get(word)+1);
        }else bst1->insert(word, 1);
        // End your code here
    }cout << "\n";
    for (int i = 0; i < n; ++i) {
        // TODO: Implement the logic to read Claire's words
        // Start your code here
        in_file >> word;
        if(bst2->find(word)){
            bst2->update(word,bst2->get(word)+1);
        }else bst2->insert(word, 1);
        // End your code here
    }
    
    // TODO: Implement the logic to print the initial state of both hands
    cout << "Phil's words:\n";
    bst1->print('I');
    cout << "Claire's words:\n";
    bst2->print('I');
    // Start your code here

    // End your code here
    cout << "\nGame starts!\n\n";
    cout << "==============================\n";
        
        // TODO: Implement the logic to process the game turn and print both hands after each turn
        // Start your code here
        bool game_over = false;
        string drawn_word;
        while(!game_over){
            in_file >> drawn_word;
            //cout << "Drawn word: " << drawn_word << endl;
            if (bst1->find(drawn_word)) {
                if(bst1->get(drawn_word)==1){
                    bst1->remove(drawn_word);
                }else{
                    bst1->update(drawn_word,bst1->get(drawn_word)-1);
                }
                cout << "Phil has " << drawn_word << endl;
                
            } else {
                //cout << "Phil does not have the word: " << drawn_word << endl;
            }
            if (bst2->find(drawn_word)) {
                if(bst2->get(drawn_word)==1){
                    bst2->remove(drawn_word);
                }else{
                    bst2->update(drawn_word,bst2->get(drawn_word)-1);
                }
                cout << "Claire has " << drawn_word << endl;
            } else {
                //cout << "Claire does not have the word: " << drawn_word << endl;
            }
            if (bst1->empty()){
                cout << "Phil wins!" << endl;
                game_over = true;
                break;
            } else if (bst2->empty()) {
                cout << "Claire wins!" << endl;
                game_over = true;
                break;
            }
            cout << "\n";
            cout << "Phil's remaining words: \n";
            bst1->print('I');
            cout << "\n";
            cout << "Claire's remaining words: \n";
            bst2->print('I');
            cout << "\n";
            cout << "==============================\n";
        }
        // End your code here


    in_file.close();
    delete bst1;
    delete bst2;
    return 0;
}