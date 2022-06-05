#pragma once

#include <stdexcept>

#include <algorithm>

template<typename T>
class BTree
{
private:
    T fKey;                                         // T() for empty BTree
    BTree<T>* fLeft;
    BTree<T>* fRight;

    BTree() : fKey(T()), fLeft(&NIL), fRight()                                    // sentinel constructor
    {
    }

    // tree manipulator auxiliaries
    void attach(BTree<T>** aNode, const BTree<T>& aBTree)
    {
        if ((*aNode)->empty())
        {
            *aNode = const_cast<BTree<T>*>(&aBTree);
        }
        else
        {
            throw std::domain_error("Illegal subtreet operation.");
        }
    }
    const BTree<T>& detach(BTree<T>** aNode)
    {
        if (!(*aNode)->empty())
        {
            BTree<T>* Result = *aNode;
            *aNode = &NIL;
            return *Result;
        }
        else
        {
            throw std::domain_error("Illegal subtree operation.");
        }
    }

public:
    static BTree<T> NIL;                           

    BTree(const T& aKey) : 
        fKey(aKey), 
        fLeft(&NIL), 
        fRight(&NIL)                       
    {}

    BTree(T&& aKey) : 
        fKey(std::move(aKey)),
        fLeft(&NIL),
        fRight(&NIL)                             
    {}

    BTree(const BTree& aOtherBTree) : 
        BTree()           
    {
        *this = aOtherBTree;
    }

    BTree(BTree&& aOtherBTree) : 
        BTree()                
    {
        *this = std::move(aOtherBTree);
    }

    virtual ~BTree()           
    {
        if (!left().empty())
        {
            delete fLeft;
        }

        if (!right().empty())
        {
            delete fRight;
        }
    }

    BTree& operator=(const BTree& aOtherBTree) 
    {
        if (!aOtherBTree.empty())
        {
            if (this != &aOtherBTree)
            {
                fKey = aOtherBTree.fKey;

                fLeft = aOtherBTree.left().clone();
                fRight = aOtherBTree.right().clone();
            }
            return *this;
        }
        else
        {
            throw std::domain_error("Illegal binary treet operation.");
        }
    }

    BTree& operator=(BTree&& aOtherBTree)      
    {
        if (!aOtherBTree.empty())
        {
            if (this != &aOtherBTree)
            {
                this->~BTree();

                fKey = std::move(aOtherBTree.fKey);

                fLeft = const_cast<BTree<T>*>(&aOtherBTree.detachLeft());
                fRight = const_cast<BTree<T>*>(&aOtherBTree.detachRight());
            }
            return *this;
        }
        else
        {
            throw std::domain_error("Illegal binary treet operation.");
        }
    }

#ifdef Clone
    virtual BTree* clone() const                  
    {
        if (!empty())
        {
            return new BTree(*this);
        }
        else
        {
            return const_cast<BTree<T>*>(this);
        }
    }
#endif

    bool empty() const                        
    {
        return this == &NIL;
    }

    const T& operator*() const                
    {
        return fKey;
    }

    const BTree& left() const
    {
        return *fLeft;
    }

    const BTree& right() const
    {
        return *fRight;
    }

    
    void attachLeft(const BTree<T>& aBTree)
    {
        attach(&fLeft, aBTree);
    }

    void attachRight(const BTree<T>& aBTree)
    {
        attach(&fRight, aBTree);
    }

    const BTree& detachLeft()
    {
        return detach(&fLeft);
    }

    const BTree& detachRight()
    {
        return detach(&fRight);
    }
};
template<class T>
BTree<T> BTree<T>::NIL;