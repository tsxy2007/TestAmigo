#pragma once
#include <vector>
#include <stdio.h>  
#include <iostream>
using namespace std;
template <class T>
class AVLNode
{
public:
	int height;
	T iValue;
	AVLNode<T>* pLeft;
	AVLNode<T>* pRight;
	AVLNode<T>(const T theData) : iValue(theData), pLeft(NULL), pRight(NULL), height(0) {};
};

template < typename T>
class AvlTree
{
public:
	AVLNode<T>* root;
public:
	AvlTree<T>() {};
	~AvlTree<T>() {};
public:
	//����
	void insert(AVLNode<T>* &t, T x);
	// ��ӡÿ��
	void printTree();
	// ����ĳһ��ֵ
	AVLNode<T>* find_t(T x);
	// �ݹ�ǰ�����
	void travl_c();
	// �ǵݹ�ǰ�����
	void c_travl();
	// �ǵݹ��������
	void h_travl();
	//ɾ��
	void Delete(T value);
	//��Сֵ���
	 AVLNode<T> *FindMin(AVLNode<T> *t) const;
	//���ֵ���
	AVLNode<T> *FindMax(AVLNode<T> *t) const;
private:
	//ɾ��
	void Delete(AVLNode<T>* &p,T value);
	void travl_c(AVLNode<T>* t);
	int GetHeight(AVLNode<T>* t);
	AVLNode<T>* LL(AVLNode<T>* t);
	AVLNode<T>* LR(AVLNode<T>* t);
	AVLNode<T>* RR(AVLNode<T>* t);
	AVLNode<T>* RL(AVLNode<T>* t);
};

template < typename T>
AVLNode<T> * AvlTree<T>::FindMax(AVLNode<T> *t) const
{
	AVLNode<T>* cur = t , * pre = NULL;

	while (cur)
	{
		pre = cur;
		cur = cur->pRight;
	}
	return pre;
}

template < typename T>
AVLNode<T> * AvlTree<T>::FindMin(AVLNode<T> *t) const
{
	AVLNode<T>* cur = t, *pre = NULL;

	while (cur)
	{
		pre = cur;
		cur = cur->pLeft;
	}
	return pre;
}

template < typename T>
void AvlTree<T>::Delete(AVLNode<T>* &p, T value)
{
	if (p == NULL)
		return;
	else if ( p->iValue == value )
	{
		
		if (p->pLeft != NULL && p->pRight != NULL)
		{
			//�������߶ȴ�ɾ����������ֵ���Ľ�㣬���丳�������
			if (GetHeight(p->pLeft) > GetHeight(p->pRight))
			{
				p->iValue = FindMax(p->pLeft)->iValue;
				Delete(p->pLeft, p->iValue);
			}
			else//�������߶ȸ���ɾ����������ֵ��С�Ľ�㣬���丳�������
			{
				p->iValue = FindMin(p->pRight)->iValue;
				Delete(p->pRight, p->iValue);
			}
		}
		else//����������һ����Ϊ�գ�ֱ������Ҫɾ���Ľ����ӽ���滻����
		{
			AVLNode<T>* old = p;

			p = p->pLeft ? p->pLeft : p->pRight;
			delete old;
			old = NULL;
		}
	}
	else if ( value < p->iValue) // ɾ���Ľڵ�����������
	{
		//�ݹ�ɾ���������ϵĽڵ�
		Delete(p->pLeft, value);
		//�ж��Ƿ���Ȼ����ƽ������
		 if ( GetHeight(p->pRight) - GetHeight(p->pLeft) > 1 )
		 {
			 if (GetHeight(p->pRight->pLeft) > GetHeight(p->pRight->pRight))
				 p = RL(p);
			 else
				 p = RR(p);
		 }
		 else //����ƽ������ �����߶�
		 {
			 p->height = max(GetHeight(p->pLeft), GetHeight(p->pRight)) + 1;
		 }
	}
	else // ɾ���Ľڵ�����������
	{
		//�ݹ�ɾ��������
		Delete(p->pRight, value);
		//ɾ��֮���ж�ƽ�����
		if ( GetHeight(p->pLeft) - GetHeight(p->pRight) > 1 )
		{
			if (GetHeight(p->pLeft->pRight) > GetHeight(p->pLeft->pLeft))
				p = LR(p);
			else
				p = LL(p);
		}
		else //����ƽ��
		{
			p->height = max(GetHeight(p->pLeft), GetHeight(p->pRight)) + 1;
		}
	}
	return;
}

template < typename T>
void AvlTree<T>::Delete(T value)
{
	Delete( root, value);
}

template < typename T>
void AvlTree<T>::h_travl()
{
	std::stack<AVLNode<T>*> s;
	AVLNode<T>* itr = root,*pre = NULL;
	s.push(root);
	while (!s.empty())
	{
		itr = s.top();
		if ( ( itr->pRight == NULL && itr->pLeft == NULL ) ||
		( pre != NULL && ( pre == itr->pRight || pre == itr->pLeft ))
			)
		{
			cout << itr->iValue << " ";
			pre = itr;
			s.pop();

		}
		else
		{
			if (itr->pRight)
				s.push(itr->pRight);
			if (itr->pLeft)
				s.push(itr->pLeft);
		}
	}
	cout << endl;
}

template < typename T>
void AvlTree<T>::c_travl()
{
	stack<AVLNode<T>*> s;
	AVLNode<T>* itr = root;
	while (s.size() || itr)
	{
		while (itr)
		{
			s.push(itr);
			cout << itr->iValue << " ";
			itr = itr->pLeft;
			
		}
		itr = s.top();
		s.pop();
		itr = itr->pRight;
	}
	cout <<""<< endl;
}

template < typename T>
void AvlTree<T>::travl_c(AVLNode<T>* t)
{
	if (t==NULL)
		return;
	
	travl_c(t->pLeft);
	travl_c(t->pRight);
	cout << t->iValue << " ";
}

template < typename T>
void AvlTree<T>::travl_c()
{
	travl_c(root);
	cout << endl;
}

template < typename T>
AVLNode<T>* AvlTree<T>::find_t(T x)
{
	AVLNode<T>* temp = root;
	while (temp)
	{
		if (temp->iValue == x)
			return temp;
		else if (x > temp->iValue)
			temp = temp->pRight;
		else if (x < temp->iValue)
			temp = temp->pLeft;
	}
	return NULL;
}

template < typename T>
void AvlTree<T>::printTree()
{
	AVLNode<T>* itr = root;
	int cur = 0, size = 0; 
	vector<AVLNode<T>*> s;
	s.push_back( root );
	size = s.size();
	while (cur < size)
	{
		
		while (cur < size)
		{
			AVLNode<T>* temp = s[cur];
			cout << temp->iValue << " ";
			if (temp->pLeft)
				s.push_back(temp->pLeft);
			if (temp->pRight)
				s.push_back(temp->pRight);
			cur++;
		}
		size = s.size();
		cout << ";" << endl;
	}
}

template < typename T>
void AvlTree<T>::insert(AVLNode<T>* &t, T x)
{
	if (t== NULL)
	{
		t = new AVLNode<T>(x);
	}
	else if ( x < t->iValue )
	{
		insert(t->pLeft, x);
		if (GetHeight(t->pLeft) - GetHeight(t->pRight) > 1)
		{
			if (x > t->pLeft->iValue)
				t = LL(t);
			else
				t = LR(t);
		}
	}
	else if (x > t->iValue)
	{
		insert(t->pRight, x);
		if (GetHeight(t->pRight) - GetHeight(t->pLeft) > 1)
		{
			if (x > t->pRight->iValue)
				t = RR(t);
			else
				t = RL(t);
		}
	}
	else
		return;
	t->height = max(GetHeight(t->pLeft), GetHeight(t->pRight)) + 1;

}

template < typename T>
AVLNode<T>* AvlTree<T>::RL(AVLNode<T>* t)
{
	LL(t->pRight);
	return RR(t);
}

template < typename T>
AVLNode<T>* AvlTree<T>::LR(AVLNode<T>* t)
{
	// �Ƚ�������ת �ٽ�������ת
	RR(t->pLeft);
	return LL(t);
}

template < typename T>
AVLNode<T>* AvlTree<T>::RR(AVLNode<T>* t)
{
	AVLNode<T>* q = t->pRight;
	t->pRight = q->pLeft;
	q->pLeft = t;

	t->height = max(GetHeight(t->pLeft), GetHeight(t->pRight)) + 1;
	q->height = max(GetHeight(q->pRight), t->height) + 1;

	return q;
}

template < typename T>
AVLNode<T>* AvlTree<T>::LL(AVLNode<T>* t)
{
	AVLNode<T>* q = t->pLeft;
	t->pLeft = q->pRight;
	q->pRight = t;

	t->height = max(GetHeight(t->pLeft), GetHeight(t->pRight)) + 1;
	q->height = max(GetHeight(q->pLeft), t->height) + 1;

	return q;
}

template < typename T>
int AvlTree<T>::GetHeight(AVLNode<T>* t)
{
	if (t)
		return t->height;
	return -1;
}
