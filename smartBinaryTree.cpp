#ifndef SMARTBINARYTREE
#define SMARTBINARYREE

#include "binaryTree.cpp"

template <typename Object>
class SmartBinaryTree : public BinaryTree<Object>
{
public:
    SmartBinaryTree(int key, Object* item)
        : BinaryTree<Object>(key, item)
    {}
    SmartBinaryTree()
    {}

    SmartPtr<Object>* findMiddliest()
    {
        if(BinaryTree<Object>::size == 0)
            return nullptr;
        SmartPtr<Object>** objs = new SmartPtr<Object>*[BinaryTree<Object>::size];
        int* keys = new int[BinaryTree<Object>::size];
        int tmp = 0;
        BinaryTree<Object>::_inOrder(objs, tmp, BinaryTree<Object>::root, keys);
        int middle = 0, best_res = keys[0], pos = 0;
        typename BinaryTree<Object>::BinaryTreeNode* temp = BinaryTree<Object>::root;
        while(temp->left_child != nullptr)
            temp = temp->left_child;
        middle += temp->getKey();
        temp = BinaryTree<Object>::root;
        while(temp->right_child != nullptr)
            temp = temp->right_child;
        middle += temp->getKey();
        middle /= 2;
        for(int i = 1; i < BinaryTree<Object>::size; i++)
            if(abs(middle - keys[i]) < abs(middle - best_res)) {
                best_res = keys[i];
                pos = i;
            }
        return objs[pos];
    }
};
#endif
