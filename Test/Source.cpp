#include <iostream>
#include <windows.h>  
#include <stdio.h>  
#include <Mmsystem.h> //声明的头文件  
#include <algorithm>
#include <random>
#include <queue>
#include <vector>
#include <stack>
#include "AVLTree.h"
#include "RB_Tree.h"
#define random(x) (rand()%x)
using namespace std;
class X{ };
class Y : public virtual X {};
class Z : public virtual X {};
class A : public Y, public Z {};
class M
{
public:
	int i;
	string str;
	M() {};
	M(int it) { i = it; }
	M(const M& m) {};
	const M& operator= (const M& m) 
	{
		if (this != &m)
			this->i = m.i;
		return *this;
	};
	~M() {};
protected:
private:
};

int sum(int n)
{
	if (n > 1)
		return n + sum(n - 1);
	return n;
}

int rank1(int key , int* a,int lenght)
{
	int lo = 0;
	int lh = lenght - 1;
	while (lo < lh)
	{
		int mid = lo + (lh - lo) / 2;
		if (key < a[mid]) lh = mid - 1;
		else if (key>a[mid]) lo = mid + 1;
		else return mid;
	}
	return -1;
}

bool less1(int a, int b)
{
	return a < b;
}

void exch(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//把大于tmp
void AdJustArray(int* data,int lengh,int tmp)
{
	if (lengh <= 1)
		return;

	int* arr_tmp_low = new int[lengh];
	int* arr_tmp_high = new int[lengh];
	int k = 0,h = 0;
	for (int i = 0; i < lengh;i++)
	{
		if (data[i] < tmp)
		{
			arr_tmp_low[k++] = data[i];
		}
		else
		{
			arr_tmp_high[h++] = data[i];
		}
	}
	for (int i = 0; i < k+1;i++)
	{
		data[i] = arr_tmp_low[i];
	}
	for (int i = k + 1; i < h+k+2; i++)
	{
		data[i] = arr_tmp_high[i];
	}


}


//合并序列
void merge(int* data, int low, int mid, int high)
{
	int i = low; // 第一段序列的下标
	int j = mid + 1; // 第二段序列的下标
	int k = 0;   // 临时存放序列的下标
	int* arr_tmp = new int[high - low + 1];
	//扫描第一段和第二段序列
	while (i <= mid&& j <= high)
	{
		if (less1(data[i],data[j]))
		{
			arr_tmp[k] = data[i];
			i++;
		}
		else
		{
			arr_tmp[k] = data[j];
			j++;
		}
		k++;
	}
	while (i <= mid)
	{
		arr_tmp[k] = data[i];
		i++;
		k++;
	}

	while (j <= high)
	{
		arr_tmp[k] = data[j];
		j++;
		k++;
	}

	for (k = 0, i = low; i <= high;i++,k++)
	{
		data[i] = arr_tmp[k];
		cout << arr_tmp[k]<<",";
	}
	cout << endl;
	delete []arr_tmp;
	
}

// 自底向上归并排序
void MergePass(int* array, int gap, int length)
{
	int i = 0;
	//归并gap长度的两个相邻子表
	for (i = 0; i + 2 * gap - 1 < length; i = i + 2 * gap)
	{
		merge(array, i, i + gap - 1, i + 2 * gap - 1);
	}
	//余下两个子表，后者长度小于gap
	if (i + gap - 1 < length)
	{
		merge(array, i, i + gap - 1, length - 1);
	}
}
int iiii = 0;
// 自上向下归并排序
void MergePassM(int *arr, int low, int high)
{
	if (high <= low)
		return;
	int mid = low + (high - low) / 2;
	//iiii++;
	cout << "mid ==================" << mid <<"iii==="<<iiii<< endl;
	MergePassM(arr, low, mid);
	MergePassM(arr, mid+1, high);
	merge(arr, low, mid, high);
}

struct node
{
	int priority;
	int value;
	friend bool operator<(node n1, node n2)
	{
		return n1.priority > n2.priority;
	}
};

class cNode
{
public:
	int priority;
	int value;
	friend bool operator<(cNode n1, cNode n2)
	{
		return n1.priority > n2.priority;
	}
};

void quickSort(int* data,int low ,int high)
{
	if (high <= low)
		return;
	int i = low ;
	int j = high;
	int tmpData = data[low];
	while (i != j)
	{
		while (i<j&& data[j] >= tmpData )
			j--;
		while (i < j&& data[i] <= tmpData)
			i++;
		//cout << "data[" << j << "] = " << data[j] << " ;data[" << i << "] = " << data[i] << endl;
		if (i<j)
		{
			int t = data[i];
			data[i] = data[j];
			data[j] = t;
		}
	}
	data[low] = data[i];
	data[i] = tmpData;

	quickSort(data, low, i -1 );
	quickSort(data, i+1, high);
}

void sort(int* arr,int lenght)
{

	LARGE_INTEGER freq_;
	QueryPerformanceFrequency(&freq_);

	LARGE_INTEGER begin_time;
	LARGE_INTEGER end_time;
	QueryPerformanceCounter(&begin_time);
	
	
	// 冒泡排序
	/*for (int i = 0; i < lenght;i++)
	{
		for (int j = i; j < lenght;j++)
		{
			int tmpj = arr[j];
			if (less1(arr[i], arr[j]))
			{
				exch(&arr[i], &arr[j]);
			}
				
		}
	}*/
	//插入排序
	/*for (int i = 1; i < lenght;i++)
	{
		for (int j = i; j > 0 && less1(arr[j], arr[j - 1]);j--)
		{
			exch(&arr[j], &arr[j-1]);
		}
	}*/
	//选择排序
	/*for (int i = 0; i < lenght;i++)
	{
		int min = i;
		for (int j = i+1; j < lenght;j++)
		{
			if (less1(arr[j], arr[min]))
				min = j;
		}
		exch(&arr[min], &arr[i]);
	}*/
	//希尔排序
	/*for (int div = lenght / 2; div >= 1; div /= 2)
	{
		for (int i = div; i < lenght; i++)
		{
			for (int j = i; less1(arr[j], arr[j - div]) && j >= 0; j -= div)
				exch(arr + j, arr + j - div);
		}

	}*/

	// 归并排序
	/*for (int gap = 1; gap < lenght;gap = 2	* gap	)
	{
		MergePass(arr, gap, lenght);
	}*/

	//MergePassM(arr, 0, lenght-1);

	// 快速排序
	quickSort(arr, 0, lenght - 1);


	QueryPerformanceCounter(&end_time);

	double ns_time = (end_time.QuadPart - begin_time.QuadPart) * 1000000.0 / freq_.QuadPart;

	cout << "ns_time = " << ns_time << endl;


}


void ShellSort(int*data, unsigned int len)
{
	if (len <= 1 || data == NULL)
		return;
	for (int div = len / 2; div >= 1; div /= 2)
	{
		for (int i = div; i < len; i++)
		{
			for (int j = i; (data[j] < data[j - div]) && j >= 0; j -= div)
			{
				exch (data + j, data + j - div);
			}
		}
	}
}


void show(int* arr,int lenght)
{
	for (int i = 0; i < lenght; i++)
		cout << "arr[" << i << "] = " << arr[i] << "; " << endl;
}

void MoveQueue(int *a, int l, int times)//将首元素移动到队尾  
{
	for (int i = 0; i < times; ++i)
	{
		int temp = a[0];
		for (int j = 0; j < l - 1; ++j)
			a[j] = a[j + 1];
		a[l - 1] = temp;
	}
}

void DequeueSort(int *a, int l)
{
	for (int i = 1; i < l; ++i)//执行l-1次冒泡  
	{
		for (int j = 0; j < l - i; ++j)
		{
			if (a[0] > a[1]) exch(&a[0], &a[1]);
			MoveQueue(a, l, 1);
		}
		MoveQueue(a, l, i);
	}

}

typedef struct queue
{
	int queuesize; //数组大小
	int head, tail;//头和尾下标
	int* q;//数组指针；
} Queue;

void InitQueue(Queue* q)
{
	q->queuesize = 8;
	q->q = (int*)malloc(sizeof(int)* q->queuesize);
	q->tail = 0;
	q->head = 0;
}

int IsQueueEmpty(Queue *Q)
{
	if (Q->head == Q->tail)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int IsQueueFull(Queue *Q)
{
	if (Q->tail == Q->queuesize)
		return true;
	else
		return false;
	/*if ((Q->tail + 1) % Q->queuesize == Q->head)
	{
	return 1;
	}
	else
	{
	return 0;
	}*/
}

int binarySearch(int* data , int low , int high,int value)
{
	/*if (high < low)
		return -1;
	int mid = low + (high - low) / 2;
	if (data[mid] == value)
		return mid;
	else if (data[mid] > value)
		return binarySearch(data, low, mid - 1, value);
	else
		return binarySearch(data, mid + 1, high, value);*/
	/*while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (data[mid] == value)
			return mid;
		else if (data[mid] > value)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;*/

	while (low<=high)
	{
		int mid = low + (value - data[low]) / (data[high] - data[low]) * (high - low);
		if (data[mid] == value)
			return mid;
		else if (data[mid] > value)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}

int find_m( int* data,int length, int value)
{
	return binarySearch(data,0,length - 1, value);
}

void EnQueue(Queue* Q, int key)
{
	int tail = (Q->tail + 1);// % Q->queuesize;
	if (IsQueueFull(Q))
	{
		cout<<"the queue has been filled full!"<<endl;
		Q->queuesize *= 2;
		int* tmp = Q->q;
		Q->q = (int*)malloc(sizeof(int)* Q->queuesize);
		memcpy(Q->q, tmp, sizeof(int)* Q->queuesize / 2 );
		free(tmp);
	}
	Q->q[Q->tail] = key;
	Q->tail = tail;
}

int DeQueue(Queue* Q)
{
	int tmp;
	if (IsQueueEmpty(Q))
	{
		printf("the queue is NULL\n");
	}
	else
	{
		tmp = Q->q[Q->head];
		Q->head = (Q->head + 1) % Q->queuesize;
	}
	return tmp;
}

template <class T>
class MNode
{
public:
	MNode() { pNext = nullptr; };
	T      pData;
	MNode* pNext;
};

template<class T>
class MList
{
private:
	unsigned int iLen;
	MNode<T>* pNode; //temp Node;
	MNode<T>* pLastNode; // firstNode
	MNode<T>* pHeadNode;// lastNode
public:
	MList();
	unsigned int size();
	void add(T x); 
	void traversal();//遍历
	bool isEmpty();
	MNode<T>* find(T x);
	void Delete(T x);
	void insert(T x, MNode<T>* p);
	void insertHead(T x);
};

template<class T>
void MList<T>::insertHead(T x)
{
	pNode = new MNode<T>;
	pNode->pData = x;
	pNode->pNext = pHeadNode;
	pHeadNode = pNode;
	iLen++;
}

template<class T>
void MList<T>::insert(T x, MNode<T>* p)
{
	if (p == NULL) return;
	pNode = new MNode<T>();//申请一个新的空间
	pNode->pData = x;//如图5
	pNode->pNext = p->pNext;
	p->pNext = pNode;
	if (pNode->pNext == NULL)//如果node为尾节点
		pLastNode = pNode;
	iLen++;
}

template<class T>
void MList<T>::Delete(T x)
{
	MNode<T>* tmp = pHeadNode;
	if (tmp == NULL)
		return;
	if (tmp->pData == x)
	{
		pHeadNode = tmp->pNext;
		if (tmp->pNext == NULL)
			pLastNode = NULL;
		delete(tmp);
		iLen--;
		return;
	}
	while (tmp->pNext != NULL && tmp->pNext->pData != x)
	{
		tmp = tmp->pNext;
	}
	if (tmp->pNext == NULL)
		return;
	if (tmp->pNext == pLastNode)
	{
		iLen--;
		pLastNode = tmp;
		delete(tmp->pNext);
		tmp->pNext = NULL;
	}
	else
	{
		pNode = tmp->pNext;
		tmp->pNext = pNode->pNext;
		delete(pNode);
		pNode = NULL;
		iLen--;
	}
}

template<class T>
MNode<T>* MList<T>::find(T x)
{
	pNode = pHeadNode;
	while (pNode != NULL && pNode->pData != x)
	{
		pNode = pNode->pNext;
	}
	return pNode;
}

template<class T>
bool MList<T>::isEmpty()
{
	return iLen == 0;
}

template<class T>
void MList<T>::traversal()
{
	pNode = pHeadNode;
	while (pNode != NULL)
	{
		cout << pNode->pData<<" ";
		pNode = pNode->pNext;
	}
	cout << endl;
}

template<class T>
void MList<T>::add(T x)
{
	pNode = new MNode<T>();
	pNode->pData = x;
	if (pHeadNode == NULL)
	{
		pHeadNode = pNode;
		pLastNode = pNode;
	}
	else
	{
		pLastNode->pNext = pNode;
		pLastNode = pNode;
	}
	iLen++;
}

template<class T>
unsigned int MList<T>::size()
{
	return iLen;
}

template<class T>
MList<T>::MList()
{
	iLen = 0;
	pNode = NULL;
	pLastNode = NULL;
	pHeadNode = NULL;
}




template<class T>
class PNode1
{
public:
	T  iData;
	PNode1* pNext;
public:
	PNode1():iData(0),
		pNext(NULL) 
	{

	};
};

template<class T>
class PList
{
public:
	int iLen;
	PNode1<T>* pHNode;
	PNode1<T>* pLNode;
	PNode1<T>* pNode;
public:
	PList();
	void add(T x);
	int  size();
	void traversal();
	bool isEmpty();
	PNode1<T>* find(T x);
	void Delete(T x);
	void insert(T x, PNode1<T>* p);
	void insertHead(T x);
	void sort();
	PNode1<T>* mergeList(PNode1<T>* pHead, PNode1<T>* pMid);
	PNode1<T>* mergePassN(PNode1<T>* pHead);
	bool less(PNode1<T>*a, PNode1<T>* b);
	void exch(PNode1<T>*a, PNode1<T>* b);
	PNode1<T>* getMid(PNode1<T>* pHead);
	void quickSort(PNode1<T>* pHead, PNode1<T>* pEnd);
};

template<class T>
void PList<T>::quickSort(PNode1<T>* pBegin, PNode1<T>* pEnd)
{
	if (NULL == pBegin
		|| NULL == pEnd
		|| pBegin == pEnd)
	{
		return;
	}

	PNode1<T>* pFirst = pBegin;
	PNode1<T>* pSecond = pFirst->pNext;

	int nMidValue = pBegin->iData;

	//开始排序
	while (pSecond != pEnd->pNext && pSecond != NULL)
	{
		if (pSecond->iData > nMidValue)
		{
			pFirst = pFirst->pNext;
			std::swap(pFirst->iData, pSecond->iData);
		}

		pSecond = pSecond->pNext;
	}

	//更换支点后完成1轮排序
	std::swap(pBegin->iData, pFirst->iData);

	quickSort(pBegin, pFirst);
	quickSort(pFirst->pNext, pEnd);//此处的next很重要,不然将导致死循环

}

template<class T>
PNode1<T>* PList<T>::mergePassN(PNode1<T>* pHead)
{
	
	if (pHead == NULL) return pHead;
	if (pHead->pNext == NULL) return pHead;
	PNode1<T>* pMid = getMid(pHead);
	
	PNode1<T>* pMid_Next = NULL;
	if (pMid)
	{
		pMid_Next = pMid->pNext;
		pMid->pNext = NULL;
	}
	return mergeList(mergePassN(pHead), mergePassN(pMid_Next) );
	
}

template<class T>
PNode1<T>* PList<T>::getMid(PNode1<T>* pHead)
{
	if (pHead == NULL) return NULL;
	if (pHead->pNext == NULL) return pHead;
	PNode1<T>* slow = pHead;
	PNode1<T>* fast = pHead->pNext;

	while ( fast && fast->pNext )
	{
		slow = slow->pNext;
		fast = fast->pNext->pNext;
	}
	return slow;
}

template<class T>
void PList<T>::exch(PNode1<T>*a, PNode1<T>* b)
{
	T tmp = a->iData;
	a->iData = b->iData;
	b->iData = tmp;
}

template<class T>
bool PList<T>::less(PNode1<T>*a, PNode1<T>* b)
{
	return a->iData > b->iData;
}

template<class T>
PNode1<T>* PList<T>::mergeList(PNode1<T>* pHead, PNode1<T>* pMid )
{
	if (pHead == NULL) return pMid;
	if (pMid == NULL) return pHead;
	PNode1<T>* L = pHead;
	PNode1<T>* R = pMid;
	PNode1<T>* tmp = new PNode1<T>;
	PNode1<T>* ret = tmp;
	while (L  && R )
	{
		if (less(L,R))
		{
			ret->pNext = L;
			ret = ret->pNext;
			L = L->pNext;
		}
		else
		{
			
			ret->pNext = R;
			ret = ret->pNext;
			R = R->pNext;
		}
	}

	
	if (L)
		ret->pNext = L;
	if (R)
		ret->pNext = R;

	PNode1<T>* del = tmp;
	tmp = tmp->pNext;
	delete del;

	return tmp;

}

template<class T>
void PList<T>::sort()
{
	/*pNode = pHNode;
	if (pNode == NULL || pNode->pNext == NULL)
		return;
	while (pNode)
	{
		PNode1<T>* temp = pNode->pNext;
		while (temp && pNode->iData > temp->iData)
		{
			int m = pNode->iData;
			pNode->iData = temp->iData;
			temp->iData = m;
			temp = temp->pNext;
		}
		pNode = pNode->pNext;
	}*/
	//pHNode =  mergePassN(pHNode);
	quickSort(pHNode, pLNode);

}

template<class T>
void PList<T>::insertHead(T x)
{
	pNode = new PNode1<T>;
	pNode->iData = x;
	pNode->pNext = pHNode;
	pHNode = pNode;
	iLen++;
}

template<class T>
void PList<T>::insert(T x, PNode1<T>* p)
{
	pNode = new PNode1<T>;
	pNode->iData = x;
	pNode->pNext = p->pNext;
	p->pNext = pNode;
	if (pNode->pNext == NULL)//如果node为尾节点
		pLastNode = pNode;
	iLen++;
}

template<class T>
void PList<T>::Delete(T x)
{
	PNode1<T>* temp = pHNode;
	if (temp == NULL)
		return;
	if (temp->iData == x)
	{
		pHNode = temp->pNext;
		if (temp->pNext == NULL)
			pLNode = NULL;
		delete(temp);
		iLen--;
		return;
	}
	while (temp->pNext && temp->pNext->iData != x)
	{
		temp = temp->pNext;
	}
	if (temp->pNext == NULL) return;
	if (temp->pNext == pLNode)
	{
		pLNode = temp;
		delete(temp->pNext);
		temp->pNext = NULL;
	}
	else
	{
		pNode = temp->pNext;
		temp->pNext = pNode->pNext;
		delete(pNode);
		pNode = nullptr;
	}
	iLen--;
}

template<class T>
PNode1<T>* PList<T>::find(T x)
{
	pNode = pHNode;
	while (pNode && pNode->iData != x)
	{
		pNode = pNode->pNext;
	}
	return pNode;
}

template<class T>
bool PList<T>::isEmpty()
{
	return iLen == 0;
}

template<class T>
void PList<T>::traversal()
{
	pNode = pHNode;
	while (pNode)
	{
		cout << pNode->iData << " ";
		pNode = pNode->pNext;
	}
	cout << endl;
}

template<class T>
int PList<T>::size()
{
	return iLen;
}

template<class T>
void PList<T>::add(T x)
{
	pNode = new PNode1<T>;
	pNode->iData = x;
	if (pHNode == NULL)
	{
		pHNode = pNode;
		pLNode = pNode;
	}
	else
	{
		pLNode->pNext = pNode;
		pLNode = pNode;
	}
	iLen++;
}

template<class T>
PList<T>::PList() : iLen(0),pHNode(NULL),pLNode(NULL),pNode(NULL)
{

}

template <class T>
class TNode
{
public:
	T iData;
	TNode<T>* pLNext;
	TNode<T>* pRNext;
public:
	TNode() :iData(0), pLNext(NULL), pRNext(NULL) {};
};

template<class T>
class TList
{
public:
	TNode<T>* pBNode;
public:
	TList();
	void add(T value);
	void travel();
	void travel(TNode<T>* pHead);
	void printTree();
	TNode<T>* find_t(T value);
	void qtravel();   // 前序遍历
	void ctravel(); // 中序遍历
	void htravel(); // 后序遍历
	void Delete(TNode<T>* n );
};

template<class T>
void TList<T>::Delete(TNode<T>* n)
{
	if (n == NULL)
		return;
	if (n->pLNext == NULL && n->pRNext)
	{
		delete(n);
	}
	else if (n->pLNext != NULL && n->pRNext == NULL)
	{
		TNode<T>* p = n;
		n = n->pLNext;
		delete(p);
	}
	else if (n->pLNext == NULL && n->pLNext != NULL)
	{
		TNode<T>* p = n;
		n = n->pRNext;
		delete(p);
	}
	else
	{
		TNode<T>* q = n;
		TNode<T>* s = q->pLNext;
		while (s->pRNext)
		{
			q = s;
			s = s->pRNext;
		}
		n->iData = s->iData;
		if (q != n)
			q->pRNext = s->pLNext;
		else
			q->pLNext = s->pLNext;
		delete(s);
	}
}

template<class T>
void TList<T>::htravel()
{
	stack<TNode<T>*> s;
	TNode<T> *cur; //当前结点   
	TNode<T> *pre=NULL; //前一次访问的结点   
	s.push(pBNode); 
	while(!s.empty())
	{
		cur = s.top(); 
		if (
			(cur->pLNext == NULL && cur->pRNext == NULL) || // 左右叶子节点
			(pre != NULL && 
				(pre == cur->pLNext || pre == cur->pRNext) // 父节点
				)
			)
		{
			cout << cur->iData << " "; //如果当前结点没有孩子结点或者孩子节点都已被访问过   
			s.pop();
			pre = cur;
		} 
		else 
		{
			if (cur->pRNext != NULL)
				s.push(cur->pRNext); 
			if (cur->pLNext != NULL)
				s.push(cur->pLNext);
		}
	}

	cout << endl;
}

template<class T>
void TList<T>::ctravel()
{
	if (pBNode == NULL)
		return;
	stack<TNode<T>*> s_tree;
	TNode<T>* p_tmp = pBNode;
	while (s_tree.size() || p_tmp)
	{

		while (p_tmp)
		{
			s_tree.push(p_tmp);
			p_tmp = p_tmp->pLNext;
		}

		p_tmp = s_tree.top();
		s_tree.pop();
		cout << p_tmp->iData << " ";
		p_tmp = p_tmp->pRNext;
	}
	cout << endl;
}

template<class T>
void TList<T>::qtravel()
{
	if (pBNode == NULL)
		return;
	stack<TNode<T>*> s_tree;
	TNode<T>* p_tmp = pBNode;
	while (s_tree.size() || p_tmp)
	{
			
		while (p_tmp)
		{
			s_tree.push(p_tmp);
			cout << p_tmp->iData << " ";
			p_tmp = p_tmp->pLNext;
		}

		p_tmp = s_tree.top();
		
		s_tree.pop();
		
		p_tmp = p_tmp->pRNext;
	}
	cout << endl;
}

template<class T>
void TList<T>::printTree()
{
	if (pBNode == NULL)
		return;
	
	vector<TNode<T>*> t_v;
	int cur = 0 , last = 0 ;
	t_v.push_back(pBNode);
	while (cur < t_v.size())
	{
		last = t_v.size();
		while (cur < last)
		{
			TNode<T>* cur_t = t_v[cur];
			
			
			if (cur_t->pLNext != NULL)
			{
				t_v .push_back(cur_t->pLNext);
			}
			if (cur_t->pRNext != NULL)
			{
				t_v.push_back(cur_t->pRNext);
			}
			cout << cur_t->iData << " ";
			cur++;
		}
		cout << endl;
	}
	t_v.clear();
}

template<class T>
TNode<T>* TList<T>::find_t(T value)
{
	TNode<T>* tmp = pBNode;
	while (tmp)
	{
		if (value == tmp->iData)
			return tmp;
		else if (value > tmp->iData)
			tmp = tmp->pRNext;
		else
			tmp = tmp->pLNext;
	}
	return NULL;
}

template<class T>
void TList<T>::travel()
{
	travel(pBNode);
}

template<class T>
void TList<T>::travel(TNode<T>* pHead)
{
	if (pHead == NULL)
		return;
	
	travel(pHead->pLNext);
	travel(pHead->pRNext);
	cout << pHead->iData << " ";
	
}

template<class T>
void TList<T>::add(T value)
{
	if (pBNode == NULL)
	{
		pBNode = new TNode<T>();
		pBNode->iData = value;
	}
	else
	{
		TNode<T>* tmp = new TNode<T>;
		tmp->iData = value;
		TNode<T>* p = pBNode ,*parent = NULL;
		while (p)
		{
			if (value < p->iData)
			{
				parent = p;
				p = p->pLNext;
			}
			else if (value > p->iData)
			{
				parent = p;
				p = p->pRNext;
			}
			else
				return;
		}
		if (parent)
		{
			if (value < parent->iData)
				parent->pLNext = tmp;
			else if (value > parent->iData)
				parent->pRNext = tmp;
			else
				return;
		}
	}
}

template<class T>
TList<T>::TList():pBNode(NULL)
{

}

void main() 
{

	/*int x = sizeof(X);
	int y = sizeof(Y);
	int z = sizeof(Z);
	int a = sizeof(A);
	cout << "x = " << x << "; y = " << y << "; z = " << z << "; z = " << z << " ; a = " << a << ";" << endl;


	M* m1 = new M;
	M* m2 = new M;
	M* m3 = m1;
	m3 = m2;
	cout << "m1 = " << &m1<<endl;
	cout << "m2 =" << &m2 << endl;
	cout << "m3 =" << &m3 << endl;

	cout << "sum n = " << sum(5) << endl;*/

	//int aArr[6] = {1,2,3,4,6,7};
	//int temp = rank1(1, aArr, 6);

	//cout << "temp = " << temp << endl;

	//int tmpArr[6] = { 4,2,6,3,1,5 };

	//sort(tmpArr, 6);
	////show(tmpArr, 6);

	int len = 10;
	RB_Tree<int,int> rbTree;
	for (int i = 0; i < len;i++)
	{
		rbTree.Insert( i,i );
	}
	rbTree.printTree();
	//int len = 10;
	//AvlTree<int> avlTree;
	//for (int i = 0; i < len;i++)
	//{
	//	avlTree.insert(avlTree.root, i);
	//	avlTree.c_travl();
	//}
	//avlTree.printTree();

	//AVLNode<int>* vNode = avlTree.find_t(31);
	//if (vNode)
	//	cout << vNode->iValue << " " << vNode->height << endl;
	//else
	//	cout << "vnode is NULL" << endl;

	//avlTree.travl_c();
	////avlTree.c_travl();
	//avlTree.h_travl();
	//avlTree.c_travl();
	//avlTree.Delete(3);
	//avlTree.c_travl();

	//std::default_random_engine e;
	//std::uniform_int_distribution <> u(0, len);
	//TList<int> list;
	//for (int i = 0; i < len;i++)
	//{
	//	int a = u( e );
	//	cout << a << " ";
	//	list.add( a );
	//}

	////list.travel();
	//TNode<int>* p = list.find_t(10);
	//if (p)
	//	cout << "p = " << p->iData << endl;
	//else
	//	cout << "p is NULL" << endl;

	//list.printTree();
	//list.travel();
	//cout << endl;
	//list.ctravel(); // 中序遍历 左中右
	//list.qtravel(); // 前序遍历 中左右
	//list.htravel(); // 后序遍历 左右中
	//int arr[100];
	//for (int i = 0; i < 100; i++)
	//	arr[i] = 100 - i;
	//show(arr, 100);
	//sort(arr, 100);
	//////DequeueSort(arr, 100);
	//show(arr, 100);

	//int index = find_m(arr, 100, 100);
	//cout << "index = " << index << endl;


	//const int len = 100;
	////int i;
	//int a[len] = {3,5,9,6,2};
	//int n[len] = {2,3,5,4,1 };

	//PList<int> list;
	//for (int i = 0; i < len; i++)
	//{
	//	list.add( i + 1);
	//}
	//list.Delete( 10 );
	//list.Delete(99);
	//list.Delete(0);
	//list.Delete(99);
	//list.insertHead(99);
	//list.insertHead(100);
	//list.traversal();
	/*list.sort();
	list.traversal();*/
	//cout << list.size() << endl;
	//MList<int> list;
	//for (int i = 0; i < len;i++)
	//{
	//	list.add(i);
	//}

	//cout << list.size() << endl;
	//list.insertHead(1000);
	//MNode<int>* p = list.find(10);
	//cout << p->pData<<"---" << endl;

	//list.insert(1001, p);

	//cout << list.size() << endl;
	//list.traversal();
	/*Queue q;
	InitQueue(&q);

	for (int i = 0; i < len;i++)
	{
		EnQueue(&q, i);
	}

	for (int i = 0; i < len; i++)
	{
		int value = DeQueue(&q);
		cout << value << " ";
	}
	cout << endl;*/

	////示例1
	//priority_queue<int> qi;
	//for (i = 0; i < len; i++)
	//	qi.push(a[i]);
	//for (i = 0; i < len; i++)
	//{
	//	cout << qi.top() << " ";
	//	qi.pop();
	//}
	//cout << endl;

	//priority_queue<cNode> qCn;
	//cNode b[len];
	//for (int i = 0; i < len;i++)
	//{
	//	cNode b;
	//	b.priority = n[i];
	//	b.value = a[i];
	//	qCn.push(b);
	//}

	//for (int i = 0; i < len;i++)
	//{
	//	cout << qCn.top().value << " ";
	//	qCn.pop();
	//}
	//cout << endl;
	/*priority_queue<node> qn;
	node b[len];
	for (int i = 0; i < len;i++)
	{
		b[i].priority = n[i];
		b[i].value = a[i];
	}

	for (int i = 0; i < len; i++)
		qn.push(b[i]);

	for (i = 0; i < len; i++)
	{
		cout << qn.top().value << " ";
		qn.pop();
	}
	cout << endl;*/

	/*int arr1[100],arr2[100],arr3[200];
	for (int i = 0; i < 100; i++)
	{
		arr1[i] = i;
		arr2[i] = i + 1;
	}

	int low = 0;
	int mid = 0;
	int high = 200;
	for (int i = 0; i < high;i++)
	{
		if (arr1[low] < arr2[mid])
		{
			arr3[i] = arr1[low];
			low++;
		}
		else
		{
			arr3[i] = arr2[mid];
			mid++;
		}

	}
	show(arr3, high);*/


	system("pause");
}