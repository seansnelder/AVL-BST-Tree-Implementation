#ifndef BST_H
#define BST_H


#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <iostream>



/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
        parent_ = parent;
    
    
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree //
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    static Node<Key, Value>* successor(Node <Key, Value>* current); 
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.


    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void PostOrder(Node<Key, Value>* node);
    bool balancechecker(Node <Key, Value> *nodeptr) const; 
//above, helper function for clear function, remove nodes

    int treeheight(const Node<Key,Value> * node) const; 
protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::PostOrder(Node<Key, Value>* node)
{
  if(node != NULL){ 
    PostOrder(node->getLeft()); 
    PostOrder(node->getRight());
    delete node;  
   } 
  
   
   
   
 
   
}


/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/

template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr): current_(ptr)
{
    // TODO
    
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator():current_(NULL) 
{
    // TODO


}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{ //iterator through the tree values, smallest to largest, therefore succ.,succ.,succ.
    // TODO
    //we defined current_ as an iterator
    return this->current_ == rhs.current_; 
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return this->current_ != rhs.current_; 

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    this->current_ = successor(this->current_); 
    return *this; 

}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = NULL; 

}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear(); 


}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
     
   // Node<Key, Value>* node = internalFind(keyValuePair.first); //returns a node of found key
    Node<Key, Value>* current = root_; //set current to point to root, we don't want to change where root is pointing to
    if(root_ == NULL){ //check if empty tree, insert "just root"
        Node<Key, Value> *nullNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        root_ = nullNode; 
        return; 
      }

    //override value
    // else if(node != NULL && (keyValuePair.first) == node->getKey()){ 
    //     node->setValue(keyValuePair.second); 
    // }

    else{ //enters if it doesn't find the key, so we insert
        while(current != NULL){

        if(current->getKey() > keyValuePair.first){ //if "curr parent" key is  greater than "insert's" key
            if(current->getLeft() != NULL){
                current = current->getLeft();
                // Node<Key, Value> *newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current_);
                // current_->setLeft(newNode); 
                // break; 

            }
            else{
              Node<Key, Value> *newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current);
                current->setLeft(newNode); 
                break; 
            } 
        }

        else if(current->getKey() < keyValuePair.first){ //if "curr parent" key is  less than "insert's" key
            if(current->getRight() != NULL){
                current = current->getRight(); 
                // Node<Key, Value> *newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current_);
                // current_->setRight(newNode);
                // break; 
            }
            else{
              Node<Key, Value> *newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current);
                current->setRight(newNode);
                break; 
            }
        }


        else if(current->getKey() == keyValuePair.first){
            current->setValue(keyValuePair.second);
            return;
        }
         
        
        }
        //Node<Key, Value> *newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current_);
        //allocate storage for a new node
        //  if(current_->getKey() > newNode->getKey()){
        //      current_->setLeft(newNode); 
        //  }
        //  else if(current_->getKey() < newNode->getKey()){
        //      current_->setRight(newNode); 
    }
      }
         







/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key) //finished?
{
    Node<Key, Value> *keysnode = internalFind(key); 
    // TODO
    Node<Key, Value> *current = keysnode;
   if(internalFind(key) == NULL){ //if we can't find the key to remove, return NULL
        return; 
    }
    else if(current->getRight() == NULL && current->getLeft() == NULL && current->getParent() == NULL){ //check if one element
        delete root_; 
        root_ = NULL; 
        return;
        
    }
    else if(current->getRight() != NULL && current->getLeft() == NULL && current->getParent() == NULL){
        current->getRight()->setParent(NULL); 
        root_ = current->getRight(); 
        delete current; 
        return;
    }
    else if(current->getRight() == NULL && current->getLeft() != NULL && current->getParent() == NULL){
        current->getLeft()->setParent(NULL); 
        root_ = current->getLeft(); 
        delete current; 
        return;
    }
    


    //case 1: key to remove has no children
    if(keysnode->getLeft() == NULL && keysnode->getRight() == NULL){ //if key to remove has no children 
        
        if((keysnode->getParent())->getRight() == keysnode){ //if it is RIGHT child, deallocate
            keysnode->getParent()->setRight(NULL);  
            delete keysnode;
            return;
            
        }
        else if((keysnode->getParent())->getLeft() == keysnode) //if it is left child, deallocate
        {
            keysnode->getParent()->setLeft(NULL);
            delete keysnode;
            return;
            

        }
    }

    //case 2:key to remove has one child, either left or right, 
    else if(keysnode->getLeft() != NULL && keysnode->getRight() == NULL){ //if it has a left child
        
        if((keysnode->getParent())->getRight() == keysnode){ //if key to remove is a right child
            keysnode->getParent()->setRight(keysnode->getLeft()); //sets parent to point to removal's right child
          (keysnode->getLeft())->setParent(keysnode->getParent()); 
            delete keysnode;//deallocate
            
        }
        else if((keysnode->getParent())->getLeft() == keysnode){ //if key to remove is left child
            keysnode->getParent()->setLeft(keysnode->getLeft()); //sets parent to point to removal's left child
            (keysnode->getLeft())->setParent(keysnode->getParent());
            delete keysnode;
        }
    }
    else if(keysnode->getLeft() == NULL && keysnode->getRight() != NULL){ //same logic as above, but reversed
        if((keysnode->getParent())->getRight() == keysnode){
            keysnode->getParent()->setRight(keysnode->getRight()); 
            (keysnode->getRight())->setParent(keysnode->getParent());
            delete keysnode;
            
        }
        else if((keysnode->getParent())->getLeft() == keysnode){
            keysnode->getParent()->setLeft(keysnode->getRight()); 
            (keysnode->getRight())->setParent(keysnode->getParent());
            delete keysnode;
        }
    }
    

    //Node<Key, Value>* 
    //BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
     
    //case 3: removal has two children, utilise pred/successor methodrecursion?
    else if(keysnode->getLeft() != NULL && keysnode->getRight() != NULL){
        Node<Key,Value>* prednode = predecessor(keysnode);
        nodeSwap(prednode, keysnode); 
         //now we have swapped pred node and key to remove node
        //now, key, which is swapped with pred, can only have 1 child or 0 children
        
        
        //remove(key); 
        
        //SAME PROCESS, BROUGHT IT DOWN TO CASE 1 OR 2: 0 OR 1 children
        //case one: 0 children
        if(keysnode->getLeft() == NULL && keysnode->getRight() == NULL){ //if key to remove has no children 
            
            if((keysnode->getParent())->getRight() == keysnode){ //if it is RIGHT child, deallocate
            keysnode->getParent()->setRight(NULL);  
            delete keysnode;
            return;
            
            }
            else if((keysnode->getParent())->getLeft() == keysnode) //if it is left child, deallocate
            {
                keysnode->getParent()->setLeft(NULL);
                delete keysnode;
                return;
                

            }
        }
        // predecessor of node with 2 children cannot have right child.
        //case 2:key to remove has one child, either left or right, 
        else if(keysnode->getLeft() != NULL){ //if it has a left child
            
            if((keysnode->getParent())->getRight() == keysnode){ //if key to remove is a right child
                keysnode->getParent()->setRight(keysnode->getLeft()); //sets parent to point to removal's right child
              (keysnode->getLeft())->setParent(keysnode->getParent()); 
                delete keysnode;//deallocate
                return;
                
            }
            else if((keysnode->getParent())->getLeft() == keysnode){ //if key to remove is left child
                keysnode->getParent()->setLeft(keysnode->getLeft()); //sets parent to point to removal's left child
                (keysnode->getLeft())->setParent(keysnode->getParent());
                delete keysnode;
                return;
            }

        }
    

    }

}


template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    if(current->getRight() != NULL){ 
        current = current->getRight(); 
        while(current->getLeft() != NULL){
            current = current->getLeft(); 
        }
        return current; 
    }
    else{
        while(current->getParent() != NULL && current != (current->getParent())->getLeft()){
            current = current->getParent(); 
        }
        return current->getParent(); 
    }
    return current; 

}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    if(current->getLeft() != NULL){
        current = current->getLeft(); 
        while(current->getRight() != NULL){
            current = current->getRight(); 
        }
        return current; 
    }
    else{ 
        while(current->getParent() != NULL && current != (current->getParent())->getRight()){
            current = current->getParent(); 
        }
        return current->getParent(); 
    }
    return current; 
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
//

   PostOrder(root_); 
   root_ = NULL; 

    // TODO

}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    //How would I find smallest node?
    // TODO 
    Node <Key, Value>* newnode = root_; 
    while(newnode->getLeft() !=NULL){
        newnode = newnode->getLeft(); 
    }
    return newnode; //ez
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TO do
    Node <Key, Value>* newnode = root_; 
    while(newnode != NULL){
        if(newnode->getKey() > key){
            newnode = newnode->getLeft(); 
        }
        else if(newnode->getKey() < key){
            newnode = newnode->getRight(); 
        }
        else if(newnode->getKey() == key){
            return newnode; //we return the value
        }
        

    }
    return NULL; 
    

    // std::pair<const Key, Value> item_;
    // Node<Key, Value>* parent_;
    // Node<Key, Value>* left_;
    // Node<Key, Value>* right_;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    return balancechecker(root_); 
}


template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::treeheight(const Node<Key,Value> * node) const{
    if(node == NULL){ //if an empty tree, no root
        return 0; 
    }
        int leftsubheight = treeheight(node->getLeft()); //using post-order, returning
        //max of left and right when returning
        int rightsubheight = treeheight(node->getRight()); 

        if(rightsubheight > leftsubheight){
          return rightsubheight + 1; 
        }
        else{
          return leftsubheight + 1; 
        }
    }

template<typename Key, typename Value>
bool BinarySearchTree<Key,Value>::balancechecker(Node <Key, Value> * nodeptr) const{
    if(nodeptr == NULL){
      return true; 
    }
    int leftheight = this->treeheight(nodeptr->getLeft());
    int rightheight = this->treeheight(nodeptr->getRight());
  if(abs(leftheight - rightheight) <= 1 && balancechecker(nodeptr->getRight()) && balancechecker(nodeptr->getLeft())){
        return true;
  }
  return 0; 

  
} 




template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
