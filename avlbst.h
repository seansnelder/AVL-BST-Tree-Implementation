#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/



template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here

    //an insertfix function

    void insertfix(AVLNode<Key,Value>* current_, AVLNode<Key,Value>* newAVLNode);
    void removefix(AVLNode<Key,Value>* current_, int8_t diff); 
    void rotateright(AVLNode<Key,Value> *grandparent);
    void rotateleft(AVLNode<Key,Value> *grandparent);  

     


    //Node<Key, Value>* internalFind(const Key& k) const; // TODO
    //Node<Key, Value> *getSmallestNode() const;  // TODO
    //static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    //static Node<Key, Value>* successor(Node <Key, Value>* current); 
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    
    
   

    
    
//above, helper function for clear function, remove nodes
   

     


};

//removefix function

template<class Key, class Value>
void AVLTree<Key, Value>::removefix(AVLNode<Key,Value>* current_, int8_t diff){
 
if(current_ == NULL){
  return; 
} //base case, traverse to top
int8_t nextdiff = 0;

AVLNode<Key, Value>* parent = current_->getParent(); 
if(parent != NULL){
  if(current_ = parent->getLeft()){ //if current node is a left child of parent, set
    //let ndiff(nextdiff) = +1
    nextdiff = 1; 
  }
  else if(current_ = parent->getRight()){
    //letndiff(nextdiff) = -1
    nextdiff = -1; 
  }
}


//CASE 1: we are assuming that diff = -1, node we are removing is a left child

if(diff == -1){
AVLNode<Key, Value>* leftchild = current_->getLeft();

if(current_->getBalance() + diff == -2){ //case 1

if(leftchild->getBalance() == -1){ //zig zig case

rotateright(current_); 
current_->setBalance(0);
leftchild->setBalance(0);  
removefix(parent, nextdiff); 
}
else if(leftchild->getBalance() == 0){
  rotateright(current_); 
  current_->setBalance(-1);
  leftchild->setBalance(1);
  return;  
}
else if(leftchild->getBalance() == 1){
 AVLNode<Key, Value>* grandchild = leftchild->getRight();
rotateleft(leftchild); 
rotateright(current_);  


 if(grandchild->getBalance() == 1) //now 3 cases
{
 current_->setBalance(0);
leftchild->setBalance(-1);
grandchild->setBalance(0); 

}
else if(grandchild->getBalance() == 0){
  current_->setBalance(0);
  leftchild->setBalance(0);
  grandchild->setBalance(0);  
}
else if(grandchild->getBalance() == -1){
  current_->setBalance(1);
  leftchild->setBalance(0);
  grandchild->setBalance(0);
   
}
removefix(parent, nextdiff);
}


}
else if(current_->getBalance() + diff == -1){ //case 2, no need to recurse up anymore
  current_->setBalance(-1); 
  return; 
}
else if(current_->getBalance() + diff == 0){
  current_->setBalance(0); 
  removefix(parent, nextdiff); 
}


}


if(diff == 1){

//CASE 2: we are assuming that diff = 1, node we are removing is a right child
AVLNode<Key, Value>* rightchild = current_->getRight();
if(current_->getBalance() + diff == 2){ //case 1

if(rightchild->getBalance() == 1){ //zig zig case

rotateleft(current_); 
current_->setBalance(0);
rightchild->setBalance(0);  
removefix(parent, nextdiff); 
}
else if(rightchild->getBalance() == 0){
  rotateleft(current_); 
  current_->setBalance(1);
  rightchild->setBalance(-1);
  return;  
}

else if(rightchild->getBalance() == -1){
 AVLNode<Key, Value>* grandchild = rightchild->getLeft(); //zig zag case for diff = 1
rotateright(rightchild); 
rotateleft(current_); 
 if(grandchild->getBalance() == -1) //now 3 cases
{
 current_->setBalance(0);
rightchild->setBalance(1);
grandchild->setBalance(0); 

}
else if(grandchild->getBalance() == 0){
  current_->setBalance(0);
  rightchild->setBalance(0);
  grandchild->setBalance(0);  
}
else if(grandchild->getBalance() == 1){
  current_->setBalance(-1);
  rightchild->setBalance(0);
  grandchild->setBalance(0);
   
}
removefix(parent, nextdiff);
}


}

else if(current_->getBalance() + diff == 1){ //case 2, no need to recurse up anymore
  current_->setBalance(1); 
  return; 
}
else if(current_->getBalance() + diff == 0){
  current_->setBalance(0); 
  removefix(parent, nextdiff); 
}


}
}

// Rotate right implementation
template<class Key, class Value>
void AVLTree<Key, Value>::rotateright(AVLNode<Key,Value> *grandparent){

AVLNode<Key,Value> *parent = grandparent->getLeft(); 

AVLNode<Key,Value> *parentrc = NULL;
    if (parent != NULL) {
        parentrc = parent->getRight(); 
    }

AVLNode<Key,Value> *greatgrand = grandparent->getParent();




//is grand = root
if(grandparent == this->root_){
  this->root_ = parent; 


}

//if greatgrand val is greater than grandparent
else if(grandparent->getParent() != NULL && grandparent->getParent()->getKey() > grandparent->getKey()){
   
  
  // gg set left p 
  greatgrand->setLeft(parent); 
  
  
  

}
//if great grandparent is less than grandparents value
else if(grandparent->getParent() != NULL && grandparent->getParent()->getKey() < grandparent->getKey()){
 
  // gg set right p
  greatgrand->setRight(parent); 
  
    
}

parent->setParent(greatgrand); 
parent->setRight(grandparent);
grandparent->setParent(parent); 

grandparent->setLeft(parentrc);

if(parentrc != NULL){
  parentrc->setParent(grandparent); 
}
}






// rotate left implementation
template<class Key, class Value>
void AVLTree<Key, Value>::rotateleft(AVLNode<Key,Value> *grandparent){

AVLNode<Key,Value> *parent = grandparent->getRight(); 

AVLNode<Key,Value> *parentlc = parent->getLeft(); 


AVLNode<Key,Value> *greatgrand = grandparent->getParent();

if(grandparent->getParent() == NULL){ //no great grandparent
  this->root_ = parent; 
  
  
}

//if great grandparent is greater than grandparents
else if(grandparent->getParent() != NULL && grandparent->getParent()->getKey() > grandparent->getKey()){
  
  //gg set left p 
  greatgrand->setLeft(parent);



}
//if great grandparent is less than grandparents value
else if(grandparent->getParent() != NULL && grandparent->getParent()->getKey() < grandparent->getKey()){
  
  //gg set right p
  greatgrand->setRight(parent); 
  

}

parent->setLeft(grandparent); 
grandparent->setParent(parent);
parent->setParent(greatgrand);
grandparent->setRight(parentlc);

if(parentlc != NULL){
  parentlc->setParent(grandparent); 
}

}
 














template<class Key, class Value>
void AVLTree<Key, Value>::insertfix(AVLNode<Key,Value>* current_ /*parent*/, AVLNode<Key,Value>* newNode /*child*/){
  
if((current_ == NULL) || current_->getParent() == NULL){ //if p is null or parent(p) is null
  return;  //base case
}

//let g = parent(p);  = current_;
AVLNode<Key,Value>* grandparent = current_->getParent(); 


//assume parent is left child of grandparent, CASE 1:

if(current_->getKey() < grandparent->getKey()){
  int bal =  grandparent->getBalance(); 
  grandparent->setBalance(bal-1); //balance is now subtracted 1

  if(grandparent->getBalance() == 0){ //grandparent is balanced, get out
    return; 
  }
  else if(grandparent->getBalance() == -1){
    //we  recurse up, grandparent, and parent
    insertfix(grandparent, current_); 
  }
  else if(grandparent->getBalance() == -2){ 
    //we have to make our rotations, either zig-zig or zig-zag

//zig zig case below,if parent left child of grandparent
      if(current_->getLeft() == newNode){
      rotateright(grandparent); 
      current_->setBalance(0); 
      grandparent->setBalance(0); 
    }

      else{
//zig zag case below, if parent left child of grandparent, inserted child is right of parent
        rotateleft(current_);
        rotateright(grandparent);
        if(newNode->getBalance() == -1){
         
        current_->setBalance(0); 
        grandparent->setBalance(1); 
        newNode->setBalance(0); 
      }
        else if(newNode->getBalance() == 0){
        
         
        current_->setBalance(0); 
        grandparent->setBalance(0); 
        newNode->setBalance(0); 
      }
       else if(newNode->getBalance() == 1){
        
        current_->setBalance(-1); 
        grandparent->setBalance(0); 
        newNode->setBalance(0); 

      }

    }
    
  }


}

////assume parent is right child of grandparent, CASE 2:

else if(current_->getKey() > grandparent->getKey()){ 
  int bal =  grandparent->getBalance(); 
  grandparent->setBalance(bal + 1);

  if(grandparent->getBalance() == 0){ //grandparent is balanced, get out
    return; 
  }
  else if(grandparent->getBalance() == 1){
    //we  recurse up, grandparent, and parent
    insertfix(grandparent, current_); 
  }
  else if(grandparent->getBalance() == 2){ //we have to make our rotations, either zig-zig or zig-zag
    //zig zig case below,if parent left child of grandparent
    if((grandparent->getKey() < current_->getKey()) && (current_->getKey() < newNode->getKey())){
      rotateleft(grandparent); 
      current_->setBalance(0); 
      grandparent->setBalance(0); 
    }

    else{
//zig zag case below, if parent left child of grandparent, child right of parent
      rotateright(current_); //correct
      rotateleft(grandparent); 
      if(newNode->getBalance() == 1){ //depends on child's initial balance cases
         
        current_->setBalance(0); 
        grandparent->setBalance(-1); 
        newNode->setBalance(0); 
      }
      else if(newNode->getBalance() == 0){
        
        current_->setBalance(0); 
        grandparent->setBalance(0); 
        newNode->setBalance(0); 
      }
      else if(newNode->getBalance() == -1){
        
        current_->setBalance(1); 
        grandparent->setBalance(0); 
        newNode->setBalance(0); 
      }

    }
    
  }


}



}


 






/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)//not a node yet
{
    // TODO
    Key key = new_item.first;
    Value value = new_item.second;
    AVLNode<Key, Value>* keynode = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));  
    AVLNode<Key, Value>* current_ = static_cast<AVLNode<Key,Value>*>(this->root_);
    //AVLNode<Key, Value>


    //If there is not a single element in tree
    if(this->root_ == NULL){ //set n as root, b(n) = 0, 
    //create a new node
    AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
    this->root_ = newNode; 
    newNode->setParent(NULL); 
    newNode->setBalance(0); //balance of that specific pointer, root is 0
    return;  //first case is covered, empty tree


    }
    
    //if we found the element, we override value
    else if(keynode != NULL){
      //override the current value if we find it
      keynode->setValue(value); 
      return;
     
    }
    

    else{ //we now need to insert a new item
   
    AVLNode<Key, Value> *newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, current_);
  

  while(current_ != NULL){ //walk down the tree
      if(current_->getKey() > new_item.first){ //if "curr parent" key is  greater than "insert's" key
            if(current_->getLeft() != NULL){
                current_ = current_->getLeft();
                // Node<Key, Value> *newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current_);
                // current_->setLeft(newNode); 
                // break; 

            }
            else{
              //Node<Key, Value> *newNode = new Node<Key, Value>(new_item.first, new_item.second, current_);
                current_->setLeft(newNode); //allocate for a new node as left
                newNode->setBalance(0);
                break; 
            } 
        }

        else if(current_->getKey() < new_item.first){ //if "curr parent" key is  less than "insert's" key
            if(current_->getRight() != NULL){
                current_ = current_->getRight(); 
                // Node<Key, Value> *newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current_);
                // current_->setRight(newNode);
                // break; 
            }
            else{
              //Node<Key, Value> *newNode = new Node<Key, Value>(new_item.first, new_item.second, current_);
                current_->setRight(newNode); //allocate for a new node as left
                newNode->setBalance(0);
                break; 
            }
        }


        else if(current_->getKey() == new_item.first){
            current_->setValue(new_item.second);
            return;
        }
         
    }
      //NOW, we have officially inserted the new node, where inserted node has a balance of 0 
    newNode->setParent(current_); 
       
      //3 cases (with 1 subcase): if parent balance was -1, now parent balance is 0

      if(current_->getBalance() == -1){
        current_->setBalance(0); 
        return; 
      }
      else if(current_->getBalance() == 1){ //if parent balance was 1, it is now 0
        current_->setBalance(0); 
        return; 
      }
      else if(current_->getBalance() == 0){ //else if parent's initial balance was initially 0
        //need to check if new node is left child or right child

         //now, two cases, assume p is left child, assume p is right child
         
        if(newNode->getKey() < current_->getKey()){ //if the insert's key is less than parent, it is a left child
          current_->setBalance(-1); //parent's balance is -1
        }
        else{
          current_->setBalance(1); 
        }

        insertfix(current_, newNode); 
        return; 
        }
        }
      }




    
    



/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    
    AVLNode <Key,Value> * keytoremove = static_cast<AVLNode<Key,Value>*>(this->internalFind(key)); 

    
    //case: if you can't find key to remove, return
    if(keytoremove == NULL){
      return; 
    }


    else{


      if(keytoremove->getLeft() != NULL && keytoremove->getRight() != NULL){
        //if key to remove has two children, swap with predecessor
          AVLNode <Key,Value> *prednode = static_cast<AVLNode<Key,Value>*>(this->predecessor(keytoremove));
          
           
          nodeSwap(keytoremove, prednode); 
      }

      int8_t diff = 0; 
      

      AVLNode<Key,Value>* parent = keytoremove->getParent(); 

      if(parent != NULL){ //if there is a parent
        

        // CASE 1: if key to remove is a right child of parent
        if(keytoremove == parent->getRight()){
          
          diff -= 1;  
        }
        else if(keytoremove == parent->getLeft()){ //else if left child, difference update
          diff += 1; 
        }
      }


      //case for if the key to remove has no child
      if(keytoremove->getRight() == NULL && keytoremove->getLeft() == NULL){
        
        if(keytoremove->getParent() == NULL){
          delete keytoremove; 
          this->root_ = NULL; 
        }
        else if(keytoremove == parent->getRight()){
          parent->setRight(NULL); 
          delete keytoremove; 
        }
        else if(keytoremove == parent->getLeft()){
          parent->setLeft(NULL); 
          delete keytoremove; 
        }
        
      }

      //case for if the key to remove has one child
      else if(keytoremove->getRight() != NULL && keytoremove->getLeft() == NULL || keytoremove->getRight() == NULL && keytoremove->getLeft() != NULL){
        
        AVLNode<Key,Value>* nodechild = NULL; 
      
        
        if(keytoremove->getRight() == NULL && keytoremove->getLeft() != NULL){ //if leftchild exists
          nodechild = keytoremove->getLeft(); 
        }
        else if(keytoremove->getRight() != NULL && keytoremove->getLeft() == NULL){
          nodechild = keytoremove->getRight(); 
        }


        if(keytoremove->getParent() == NULL){ //ROOT
          nodechild->setParent(NULL); 
          this->root_ = nodechild; 
          delete keytoremove; 
        }

        else if(keytoremove->getParent() != NULL){

          if(keytoremove == parent->getRight()){
            parent->setRight(nodechild); 
            nodechild->setParent(parent); 
            delete keytoremove; 
          }
          else if(keytoremove == parent->getLeft()){
            parent->setLeft(nodechild); 
            nodechild->setParent(parent);
            delete keytoremove;  

          }

        }
        
        }

removefix(parent, diff);
      }
       


}
   
          
    // TODO




template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
