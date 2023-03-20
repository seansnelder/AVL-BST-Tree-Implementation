#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <algorithm>
#endif

#include "equal-paths.h"

using namespace std;


// You may add any prototypes of helper functions here


bool equalPaths(Node * root)
{
    if(root == NULL){
        return true; 
    }
    int leftheight = treeheight(root->left); //finds the height of left subtree
    int rightheight = treeheight(root->right); //finds the height of right subtree
    if(leftheight == rightheight || (leftheight == 0 && rightheight == 1) || (leftheight == 1 && rightheight == 0)){
        return true;
    }
    else{
        return false; 
    }

    //base case
    
    // Add your code below

}

int treeheight(Node * root){
    if(root == NULL){ //if an empty tree, no root
        return 0; 
    }
        int leftsubheight = treeheight(root->left); //using post-order, returning
        //max of left and right when returning
        int rightsubheight = treeheight(root->right); 
        return max(leftsubheight,rightsubheight) + 1;
    }


