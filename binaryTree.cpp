#ifndef BINARY_TREE
#define BINARY_TREE

#include <stdexcept>
#include "smartPointer.cpp"

template <typename Object>
class BinaryTree
{
public:
    class BinaryTreeNode;

protected:
    BinaryTreeNode* root = nullptr;
    int size = 0;

    void _add(int key, Object* item, BinaryTreeNode*& root)
    {
        if(root == nullptr)
            root = new BinaryTreeNode(key, item);
        else if(key < root->getKey())
        {
            if(root->left_child == nullptr)
                root->left_child = new BinaryTreeNode(key, item);
            else
                _add(key, item, root->left_child);
        }
        else
        {
            if(root->right_child == nullptr)
                root->right_child = new BinaryTreeNode(key, item);
            else
                _add(key, item, root->right_child);
        }
    }
    SmartPtr<Object>* _remove(int key, BinaryTreeNode*& root)
    {
        if(root == nullptr)
            throw std::out_of_range("Get over here");
        if(key < root->getKey())
            return _remove(key, root->left_child);
        else if(key > root->getKey())
            return _remove(key, root->right_child);
        else
        {
            SmartPtr<Object>* res = root->item;
            if(root->left_child == nullptr && root->right_child == nullptr)
            {
                delete root;
                root = nullptr;
                size--;
            }
            else if(root->left_child == nullptr)
            {
                BinaryTreeNode* temp = root;
                root = root->right_child;
                delete temp;
                size--;
            }
            else if(root->right_child == nullptr)
            {
                BinaryTreeNode* temp = root;
                root = root->left_child;
                delete temp;
                size--;
            }
            else
            {
                BinaryTreeNode* temp = root->right_child;
                while(temp->left_child != nullptr) {
                    temp = temp->left_child;
                }
                root->setKey(temp->getKey());
                root->item = temp->item;
                _remove(root->getKey(), root->right_child);
            }
            return res;
        }
    }
    void _preOrder(SmartPtr<Object>** res, int& pos, BinaryTreeNode* root, int* keys = nullptr)
    {
        if(root == nullptr)
            return;
        if(keys != nullptr)
            keys[pos] = root->getKey();
        res[pos++] = root->item;
        if(root->left_child != nullptr)
            _preOrder(res, pos, root->left_child);
        if(root->right_child != nullptr)
            _preOrder(res, pos, root->right_child);
    }
    void _inOrder(SmartPtr<Object>** res, int& pos, BinaryTreeNode* root, int* keys = nullptr)
    {
        if(root == nullptr)
            return;
        if(root->left_child != nullptr)
            _inOrder(res, pos, root->left_child, keys);
        if(keys != nullptr)
            keys[pos] = root->getKey();
        res[pos++] = root->item;
        if(root->right_child != nullptr)
            _inOrder(res, pos, root->right_child, keys);
    }
    void _postOrder(SmartPtr<Object>** res, int& pos, BinaryTreeNode* root)
    {
        if(root == nullptr)
            return;
        if(root->left_child != nullptr)
            _postOrder(res, pos, root->left_child);
        if(root->right_child != nullptr)
            _postOrder(res, pos, root->right_child);
        res[pos++] = root->item;
    }
    SmartPtr<Object>* _search(int key, BinaryTreeNode* root)
    {
        if(root == nullptr)
            throw std::out_of_range("Out of range");
        if(key < root->getKey())
            return _search(key, root->left_child);
        else if(key > root->getKey())
            return _search(key, root->right_child);
        else
            return root->item;
    }
    void _deleteAll(BinaryTreeNode* root)
    {
        if(root == nullptr)
            return;
        if(root->left_child != nullptr)
            _deleteAll(root->left_child);
        if(root->right_child != nullptr)
            _deleteAll(root->right_child);
        delete root;
        root = nullptr;
    }
    void _balance(int* keys, SmartPtr<Object>** objs, int start, int end, BinaryTreeNode*& root)
    {
        int mid = (start + end) / 2;
        root = new BinaryTreeNode(keys[mid], objs[mid]);
        if(mid > start)
            _balance(keys, objs, start, mid - 1, root->left_child);
        if(mid < end)
            _balance(keys, objs, mid + 1, end, root->right_child);
    }
public:


    class BinaryTreeNode
    {
        int key;
    public:

        BinaryTreeNode* left_child = nullptr;
        BinaryTreeNode* right_child = nullptr;
        SmartPtr<Object>* item;

        BinaryTreeNode(int key, SmartPtr<Object>* item)
            : key(key)
        {
            this->item = item;
        }
        BinaryTreeNode(int key, Object* item)
            : key(key)
        {
            this->item = new SmartPtr<Object>(item);
        }

        ~BinaryTreeNode()
        {
        }

        int getKey()
        {
            return key;
        }
        void setKey(int key)
        {
            this->key = key;
        }
    };


    BinaryTree(int key, Object* item)
    {
        root = new BinaryTreeNode(key, item);
    }
    BinaryTree()
    {}

    void add(int key, Object* item)
    {
        _add(key, item, root);
        size++;
    }
    SmartPtr<Object>* remove(int key)
    {
        return _remove(key, root);
    }
    SmartPtr<Object>** getInfoArr(int type = 0, int* keys = nullptr)
    {
        SmartPtr<Object>** res = new SmartPtr<Object>*[size];
        int pos = 0;
        if(type == 0)
            _preOrder(res, pos, root, keys);
        else if(type == 1)
            _inOrder(res, pos, root, keys);
        else
            _postOrder(res, pos, root);
        return res;
    }
    SmartPtr<Object>* search(int key)
    {
        return _search(key, root);
    }
    void balance()
    {
        if(size == 0)
            return;
        int* keys = new int[size];
        int pos = 0;
        SmartPtr<Object>** objs = new SmartPtr<Object>*[size];
        _inOrder(objs, pos, root, keys);
        _deleteAll(root);
        _balance(keys, objs, 0, size - 1, root);
        delete[] keys;
    }
    int getSize()
    {
        return size;
    }
    BinaryTreeNode* getRoot()
    {
        return root;
    }
};

#endif
