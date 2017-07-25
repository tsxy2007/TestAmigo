#pragma once
#include <stack>
#include <iostream>
using namespace std;
template<class T>
class BNode
{
public:
	T iValue;
	BNode<T>* pLeft;
	BNode<T>* pRight;
public:
	BNode();
	BNode(T value);
};


template<class T>
BNode<T>::BNode() : iValue(0), pRight(NULL), pLeft(NULL)
{

}
template<class T>
BNode<T>::BNode(T value) : iValue(value), pRight(NULL), pLeft(NULL)
{

}

template<class T>
class B_Tree
{
private:
	BNode<T>* pBase;
public:
	B_Tree();
	~B_Tree();
public:
	void add(T value);
	void travel();
	void travel(BNode<T>* pHead);
	void printTree();
	BNode<T>* find_t(T value);
	void qtravel();   // 前序遍历
	void ctravel(); // 中序遍历
	void htravel(); // 后序遍历
};

template<class T>
void B_Tree<T>::htravel()
{
	BNode<T>* pre = NULL;
	BNode<T>* cur = NULL;
	stack<BNode<T>*> s;
	s.push(pBase);
	while (!s.empty())
	{
		cur = s.top();
		if (
			(cur->pRight == NULL&& cur->pLeft) || // 叶子节点
			(pre != NULL &&
				(pre == cur->pLNext || pre == cur->pRNext))
			)
		{
			cout << cur->iData << " "; //如果当前结点没有孩子结点或者孩子节点都已被访问过   
			s.pop();
			pre = cur;
		}
		else
		{
			if (cur->pRight)
				s.push(cur->pRight);
			if (cur->pLeft)
				s.push(cur->pLeft);
		}
	}
}

template<class T>
void B_Tree<T>::ctravel()
{
	stack<BNode<T>*> s;
	s.push(pBase);
	BNode<T>* temp = pBase;
	while (!s.empty())
	{
		while (temp)
		{
			s.push(temp);
			temp = temp->pLeft;
		}
		cout << temp->iValue << " ";
		temp = s.top();
		s.pop();
		temp = temp->pRight;
	}
}

template<class T>
void B_Tree<T>::qtravel()
{
	stack<BNode<T>*> s;
	s.push(pBase);
	BNode<T>* temp = pBase;
	while (!s.empty())
	{
		while (temp)
		{
			s.push(temp);
			cout << temp->iValue << " ";
			temp = temp->pLeft;
		}
		temp = s.top();
		s.pop();
		temp = temp->pRight;
	}
}

template<class T>
void B_Tree<T>::add(T value)
{
	BNode<T>* temp = new BNode<T>(value);
	if (pBase == NULL)
	{
		pBase = temp;
	}
	else
	{
		BNode<T>* parent = NULL;
		BNode<T>* cur = pBase;
		while (cur)
		{
			if (value>cur->iValue)
			{
				parent = cur;
				cur = cur->pRight;
			}
			else if (value < cur->iValue)
			{
				parent = cur;
				cur = cur->pLeft;
			}
			else
				return;
		}
		if (parent)
		{
			if ( value > parent->iValue)
			{
				parent->pRight = temp;
			}
			else if (value < parent->iValue)
			{
				parent->pLeft = temp;
			}
			else
				return;
		}
	}
}

template<class T>
BNode<T>* B_Tree<T>::find_t(T value)
{
	BNode<T>* tmp = pBase;

	while (tmp)
	{
		if (tmp->iValue == value)
			return tmp;
		else if (value > tmp->iValue)
			tmp = tmp->pRight;
		else
			tmp = tmp->pLeft;
	}
	return NULL;
}

template<class T>
void B_Tree<T>::printTree()
{
	vector<BNode<T>*> s;
	s.push_back(pBase);
	int size = 0, cur = 0;
	while (cur < s.size())
	{
		size = s.size();
		while (cur < size)
		{
			BNode<T>* iter = s[cur];
			cout << iter->iValue << " ";
			if (iter->pLeft)
				s.push_back(iter->pLeft);
			if (iter->pRight)
				s.push_back(iter->pRight);
			cur++;
		}
		cout << endl;
	}
	s.clear();
}

template<class T>
void B_Tree<T>::travel(BNode<T>* pHead)
{
	if (pHead == NULL)
		return;
	cout << pHead->iValue << " ";
	travel(pHead->pLeft);
	travel(pHead->pRight);
}


template<class T>
void B_Tree<T>::travel()
{
	travel(pBase);
}

template<class T>
B_Tree<T>::B_Tree() : pBase(NULL)
{

}

template<class T>
B_Tree<T>::~B_Tree()
{

}

