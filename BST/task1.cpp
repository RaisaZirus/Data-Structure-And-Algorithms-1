 #include <iostream>
#include <fstream>
#include "listBST.hpp"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file)
    {
        cerr << "Unable to open file\n";
        return 2;
    }
    char c, str[5];
    int val;
    BST<int, int> *bst = new ListBST<int, int>();
    if (!bst)
    {
        cerr << "Memory allocation failed\n";
        return 3;
    }
    while (in_file >> c)
    {
        // TODO: Implement the logic to read commands from the file and output accordingly
        // After every insertion and removal, print the BST in nested parentheses format
        // Handle exceptions where necessary and print appropriate error messages

        // Start your code here
        switch (c)
        {
        case 'F':
        {
            in_file >> val;
            if (bst->find(val))cout << "Key " << val << " found in BST." << endl;
            else cout << "Key " << val << " not found in BST." << endl;
            break;
        }
        case 'E':
        {
            if (bst->empty())cout << "Empty" << endl;
            else cout << "Not empty"<< endl; 
            break;
        }
        case 'I':
        {
            in_file >> val;
            if (bst->insert(val, val))cout << "Key " << val << " inserted into BST, ";
            else{
                cout << "Insertion failed! Key " << val << " already exists in BST, ";
            }
            
            bst->print('D');
            break;
        }
        case 'M':
        {
            in_file >> str;
            if (str[2] == 'n')cout << "Minimum value: " << bst->find_min() << endl;
            else if (str[2] == 'x')
            {
                cout << "Maximum value: " << bst->find_max() << endl;
            }
            break;
        }
        case 'D':
        {
            in_file >> val;
            if (bst->remove(val))cout << "Key " << val << " removed from BST, ";
            else cout << "Removal failed! Key " << val << " not found in BST, ";
            
            bst->print();
            break;
        }
        case 'S':{
            cout << "Size: " << bst->size() << endl;
            break;
        }
        case 'T':{
            in_file >> str;
            if(str[1]=='n') bst->print('i');
            else if(str[1]=='r') bst->print('p');
            else if(str[1]=='o') bst->print('o');
            break;
        }
        }
        // End your code here
    }
    in_file.close();
    delete bst;
    return 0;
}
