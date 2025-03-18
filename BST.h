#ifndef TREE_H
#define  TREE_H

#include <stdexcept>

namespace mine 
{
    template<typename T> class Node;

    template<typename T>
    class Tree
    {
    private:
        Node<T>* root;
        Node<T>& findMin(Node<T>*);
        Node<T>& findMax(Node<T>*);
        Node<T>& find(Node<T>*, T);
        void add(Node<T>*, T);
        void remove(Node<T>*, T);
    public:
        Tree(/* args */);
        ~Tree();
        Node<T>& min();
        Node<T>& max();
        Node<T>& search(T);
        void insert(T);
        void erase(T);
        bool is_empty();
    };

    template<typename T>
    Tree<T>::Tree(/* args */)
    {
        this->root = nullptr;
    }

    template<typename T>
    Tree<T>::~Tree()
    {
    }

    // private method
    template<typename T>
    Node<T>& Tree<T>::findMin(Node<T>* node)
    {
        if(node->rightChild)
            return findMin(node->leftChild);
        else
            return *node;
    }

    template<typename T>
    Node<T>& Tree<T>::findMax(Node<T>* node)
    {
        if(node->rightChild)
            return findMax(node->rightChild);
        else
            return *node;
    }

    template<typename T>
    Node<T>& Tree<T>::find(Node<T>* node, T value) 
    {
        if(!node) 
            throw std::runtime_error("value does'nt exist find");
        if(node->value < value) 
            return find(node->rightChild, value);
        else if(node->value < value)
            return find(node->leftChild, value);
        else
            return *node;
    }

    template<typename T>
    void Tree<T>::add(Node<T>* node, T value)
    {
        if(node->value < value)
            if(node->rightChild)
                add(node->rightChild, value);
            else
                node->rightChild = new Trie(node, value);
        else
            if(node->leftChild)    
                add(node->leftChild, value);
            else
                node->leftChild = new Trie(node, value);
        return ;
    }

    template<typename T>
    void Tree<T>::remove(Node<T>* node, T value)
    {
        if(!node)
            throw std::runtime_error("value does'nt exist to remove");
        
        if(node->value < value)
            remove(node->rightChild, value);
        else if(node->value > value)
            remove(node->leftChild, value);
        else
            if(node->leftChild && node->rightChild)
            {
                Trie minNode = findMin(node);
                node->value = minNode.value;
                remove(&minNode, minNode.value);
            }
            else
            {
                auto replaceNode = [&](Node<T>* oldNode, Node<T>* newNode) -> void
                {
                    if(root == oldNode) // oldNode is root
                    {
                        root = newNode;
                        delete oldNode;
                        oldNode = nullptr;
                    }
                        

                    if(oldNode->parent)
                    {
                        if(oldNode->parent->leftChild = oldNode)
                            oldNode->parent->leftChild = newNode;
                        else
                            oldNode->parent->rightChild = newNode;
                        newNode->parent = oldNode->parent;
                    }

                    oldNode->parent = nullptr;
                    oldNode->leftChild = nullptr;
                    oldNode->rightChild = nullptr;
                    delete oldNode;
                    oldNode = nullptr;
                };

                if(node->rightChild)
                    replaceNode(node, node->rightChild);
                else if(node->leftChild)
                    replaceNode(node, node->leftChild);
                else
                {
                    if(node->parent->rightChild == node)
                        node->parent->rightChild = nullptr;
                    else
                        node->parent->leftChild = nullptr;
                    delete node;
                    node = nullptr;
                }
            }
    }

    // public method
    template<typename T>
    Node<T>& Tree<T>::min()
    {
        return findMin(this->root);
    }

    template<typename T>
    Node<T>& Tree<T>::max()
    {
        return findMax(this->root);
    }

    template<typename T>
    Node<T>& Tree<T>::search(T value) 
    {
        return find(this->root, value);
    }

    template<typename T>
    void Tree<T>::insert(T value) 
    {
        if(root)
            add(this->root, value);
        else 
            root = new Node<T>(nullptr, value);
    }

    template<typename T>
    void Tree<T>::erase(T value) 
    {
        remove(this->root, value);
    }

    template<typename T>
    bool Tree<T>::is_empty()
    {
        return root == nullptr;
    }

    template<typename T>
    class Node
    {
        friend class Tree<T>;
    private:
        Node* rightChild;
        Node* leftChild;
        Node* parent;
        T value;
    public:
        Node(Node*, T);
        ~Node();
        T data();
    };

    template<typename T>
    Node<T>::Node(Node* parent, T value)
    {
        this->rightChild = nullptr;
        this->leftChild = nullptr;
        this->parent = parent;
        this->value = value;
    }

    template<typename T>
    Node<T>::~Node()
    {
    }

    template<typename T>
    T Node<T>::data()
    {
        return value;
    }
}

#endif