//
//  LinkedList.h
//  TestAmigo
//
//  Created by fengkai on 2017/7/25.
//  Copyright © 2017年 fengkai. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h
#include <assert.h>

template <typename T>
class LinkedList
{
private:
    class Node
    {
    public:
        Node* mPret; //前一个节点
        Node* mNext; //后一个节点
        T mData;
    public:
        Node(const T& element,Node*&pri,Node*& next):mData(element),mNext(next),mPret(pri){};
        Node():mData(mData){};
    };
    
    
public:
    Node* mHead;//指向第一个节点
    LinkedList():mHead(new Node())
    {
        mHead->mPret = mHead->mNext = mHead;
    }
    
    // 获取元素总数
    int size()const;
    // 判断是否为空链表
    bool isEmpty()const;
    // 将元素添加到最后
    void addToLast(const T& element);
    //获取最后一个元素
    T getLastElement()const;
    //删除最后一个元素
    void deleteLastEmlent();
    //修改最后一个元素
    void alterLastElement(const T& element);
    //插入元素
    void insertElement(const T& element,int position);
    //获取元素
    T GetElement(int index)const;
    //删除元素
    T delElement(int index);
    //修改元素
    void alterElement(const T& newELement,int index);
    //查找元素
    int findElement(const T& element)const;
//    //正序遍历
//    void Traverse(void (*visit)(T));
    
    //打印列表
    void print()const;
};

template <typename T>
int  LinkedList<T>::size( ) const
{
    int size = 0 ;
    for ( Node* p = mHead->mNext ; p != mHead; p=p->mNext)
        ++size ;
    
    return size;
    
}

template <typename T>
bool LinkedList<T>::isEmpty( ) const
{
    return mHead->mNext == mHead;
}

template <typename T>
void LinkedList<T>::addToLast(const T& element)
{
    Node* n = new Node(element,mHead->mPret,mHead);
    mHead->mPret = mHead->mPret->mNext = n;
}

template <typename T>
T LinkedList<T>::getLastElement( ) const
{
    assert(!isEmpty());
    return mHead->mPret->mData;
}

template <typename T>
void <#function name#>(<#function parameters#>) {
    <#statements#>
}

template <typename T>
void LinkedList<T>::print( ) const
{
    for ( Node* p = mHead->mNext ; p != mHead; p=p->mNext)
        std::cout<< p->mData<<" size = "<<size()<<std::endl;
}

#endif /* LinkedList_h */
