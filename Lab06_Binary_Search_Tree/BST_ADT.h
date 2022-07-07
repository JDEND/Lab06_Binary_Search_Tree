#ifndef BST_ADT_H
#define BST_ADT_H


#include<iostream>
#include <stdexcept>
#include <iostream>
#include <vector>

using namespace std;

template < typename DataType, class KeyType >    // DataType : tree data item
class BSTree                                     // KeyType : key field
{
public:

    BSTree() {
        clear();
    };                         // Default constructor
    BSTree(const BSTree<DataType, KeyType>& other) {
        copyHelper(root, other->root);
    };
    BSTree& operator= (const BSTree<DataType, KeyType>& other) {
        copyHelper(root, other->root);
    };
    ~BSTree() {
        clear();
    };
    void insert(const DataType& newDataItem);
    bool retrieve(const KeyType& searchKey, DataType& searchDataItem) const;
    bool remove(const KeyType& deleteKey);
    void writeKeys() const {
        writeKeysHelper(root);
    };                     // Output keys
    void clear();                               // Clear tree
    bool isEmpty() const {
        if (root == NULL)
            return true;
        else
            return false;
    };                       // Tree is empty
    void showStructure() const {
        if (root == 0)
            cout << "Empty tree" << endl;
        else
        {
            cout << endl;
            showHelper(root, 1);
            cout << endl;
        }
    };
    int getHeight() const {
        return getHeightHelper(root, 0);
    };                 // Height of tree
    int getCount() const {
        return getCountHelper(root);
    };		  // Number of nodes in tree
    void writeLessThan(const KeyType& searchKey) const {
        writeLessThanHelper(root, searchKey);
    };
    void writeGreaterThan(const KeyType& searchKey) const {
        writeGreaterThanHelper(root, searchKey);
    };
    
    void writePreorder() const {
        writePreorderHelper(root);
    };

protected:

    class BSTreeNode
    {
    public:

        // Constructor
        BSTreeNode(const DataType& newDataItem, BSTreeNode* leftPtr, BSTreeNode* rightPtr);

        DataType dataItem;         // Binary search tree data item
        BSTreeNode* left, * right;
    };

    void showHelper(BSTreeNode* p, int level) const;
    void insertHelper(BSTreeNode*& p, const DataType& newDataItem);
    bool retrieveHelper(BSTreeNode* p, const KeyType& searchKey, DataType& searchDataItem) const;
    bool removeHelper(BSTreeNode*& p, const KeyType& deleteKey);
    void writeKeysHelper(BSTreeNode* p) const;
    void clearHelper(BSTreeNode* p);
    int getHeightHelper(BSTreeNode* p, int level) const;
    int getCountHelper(BSTreeNode* p) const;
    void writeLessThanHelper(BSTreeNode* p, const KeyType& searchKey) const;
    void writeGreaterThanHelper(BSTreeNode* p, const KeyType& searchKey) const;
    void copyHelper(BSTreeNode* p, BSTreeNode* other);
    void writePreorderHelper(BSTreeNode* p) const;

    BSTreeNode* root;   // Pointer to the root node
};

template < typename DataType, typename KeyType >
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode(const DataType& nodeDataItem, BSTreeNode* leftPtr, BSTreeNode* rightPtr) : dataItem(nodeDataItem), left(leftPtr), right(rightPtr) {};

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::insert(const DataType& newDataItem) {
    insertHelper(root, newDataItem);
}

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::insertHelper(BSTreeNode*& p, const DataType& newDataItem) {
    if (p == 0) // Insert
        p = new BSTreeNode(newDataItem, 0, 0);
    else if (newDataItem.getKey() < p->dataItem.getKey())
        insertHelper(p->left, newDataItem);                  // Search left
    else if (newDataItem.getKey() > p->dataItem.getKey())
        insertHelper(p->right, newDataItem);                 // Search right
    else
        p->dataItem = newDataItem;                           // Update
}

template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& searchDataItem) const {
    return retrieveHelper(root, searchKey, searchDataItem);
}

template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::retrieveHelper(BSTreeNode* p, const KeyType& searchKey, DataType& searchDataItem) const {
    bool result;   // Result returned

    if (p == 0)
    {
        // Fell off the tree while searching. Item is not in tree.
        result = false;
    }
    else if (searchKey < p->dataItem.getKey())
    {
        // Key is smaller than current node. Search to left.
        result = retrieveHelper(p->left, searchKey, searchDataItem);
    }
    else if (searchKey > p->dataItem.getKey())
    {
        // Key is larger than current node. Search to right.
        result = retrieveHelper(p->right, searchKey, searchDataItem);
    }
    else
    {
        // Found the desired item
        searchDataItem = p->dataItem;
        result = true;
    }

    return result;
}

template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::remove(const KeyType& deleteKey) {
    return removeHelper(root, deleteKey);
}

template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::removeHelper(BSTreeNode*& p, const KeyType& deleteKey) {
    BSTreeNode* delPtr;  // Pointer to node to delete
    int result;                 // Result returned

    if (p == 0)
        result = false;                           // Search failed
    else if (deleteKey < p->dataItem.getKey())
        result = removeHelper(p->left, deleteKey);    // Search left
    else if (deleteKey > p->dataItem.getKey())
        result = removeHelper(p->right, deleteKey);   // Search right
    else
    {                                            // Found
        delPtr = p;
        if (p->left == 0)
        {
            p = p->right;                    // No left child
            delete delPtr;
        }
        else if (p->right == 0)
        {
            p = p->left;                     // No right child
            delete delPtr;
        }
        else
            // Node has both children: removing is more complex.
        {

            // ** Start implemtation option #1
            // Find node with largest key smaller than p's key.
            BSTreeNode* temp = p->left;
            while (temp->right) {
                temp = temp->right;
            }
            // Copy node data to p
            p->dataItem = temp->dataItem;
            // And remove the node whose data was copied to p.
            removeHelper(p->left, temp->dataItem.getKey());

            /*
            // ** Start implemtation option #2. Looks simpler here,
            // but there is all of cutRightmost to deal with.
                cutRightmost(p->left,delPtr);
            delete delPtr;
            */
        }
        result = true;
    }

    return result;
}

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::clear() {
    clearHelper(root);
    root = 0;
}

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode* p) {
    if (p != 0)
    {
        clearHelper(p->left);
        clearHelper(p->right);
        delete p;
    }
}

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::copyHelper(BSTreeNode* p, BSTreeNode* other) {
    if (p != 0)
    {
        p = new BSTreeNode(other->DataItem, 0, 0);
        copyTreeHelper(p->left, other->left);
        copyTreeHelper(p->right, other->right);
    }
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeKeysHelper(BSTreeNode* p) const {
    if (p != 0)
    {
        writeKeysHelper(p->left);
        cout << (p->dataItem).getKey() << " ";
        writeKeysHelper(p->right);
    }
}

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::showHelper(BSTreeNode* p, int level) const {
    int j;
    if (p != 0)
    {
        showHelper(p->right, level + 1); // Output right subtree
        for (j = 0; j < level; j++) // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem.getKey(); // Output key
        if ((p->left != 0) && // Output "connector"
            (p->right != 0))
            cout << "<";
        else if (p->right != 0)
            cout << "/";
        else if (p->left != 0)
            cout << "\\";
        cout << endl;
        showHelper(p->left, level + 1); // Output left subtree
    }
}

template<typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getHeightHelper(BSTreeNode* p, int currentLevel) const
{

    static int maxLevel = 0;
    if (p == 0)
    {
        if (currentLevel > maxLevel)
            maxLevel = currentLevel;
    }
    else
    {
        getHeightHelper(p->left, currentLevel + 1);
        getHeightHelper(p->right, currentLevel + 1);
    }
    return maxLevel;
}

template<typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getCountHelper(BSTreeNode* p) const
{
    if (p == 0)
        return 0;
    else
        return 1 + getCountHelper(p->left) + getCountHelper(p->right);
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeLessThanHelper(BSTreeNode* p, const KeyType& searchKey) const {
    if (p != 0) {
        writeLessThanHelper(p->left, searchKey);
        if(p->dataItem.getKey() < searchKey)
            cout << p->dataItem.getKey() << " ";

        writeLessThanHelper(p->right, searchKey);
    }
    
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeGreaterThanHelper(BSTreeNode* p, const KeyType& searchKey) const {
    if (p != 0) {
        writeGreaterThanHelper(p->left, searchKey);
        if (p->dataItem.getKey() > searchKey)
            cout << p->dataItem.getKey() << " ";

        writeGreaterThanHelper(p->right, searchKey);
    }
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writePreorderHelper(BSTreeNode* p) const {
    if (p != 0) {
        cout << p->dataItem.getKey() << " ";
        writePreorderHelper(p->left);
        writePreorderHelper(p->right);
    }


};

#endif // !BST_ADT_H
