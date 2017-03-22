#pragma once

#include <iostream>
//#include <stirng>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

template<class KEY , class U>
class RB_Tree
{
private:
	RB_Tree( const RB_Tree& input ) {};
	const RB_Tree& operator= (const RB_Tree& input) {}
private:
	enum COLOR { RED, BLACK };
private:
	class RB_Node
	{
	public:
		RB_Node()
		{
			right = NULL;
			left = NULL;
			parent = NULL;
		};
		COLOR RB_COLOR;
		RB_Node* right;
		RB_Node* left;
		RB_Node* parent;
		KEY key;
		U   data;
	};
private:
	RB_Node* m_root;
	RB_Node* m_nullNode;
public:
		RB_Tree()
		{
			this->m_nullNode = new RB_Node;
			this->m_root = m_nullNode;
			this->m_nullNode->right = this->m_root;
			this->m_nullNode->left = this->m_root;
			this->m_nullNode->parent = this->m_root;
			this->m_nullNode->RB_COLOR = BLACK;
		}
		bool empty()
		{
			return this->m_root == this->m_nullNode;
		}
		//����key
		RB_Node* find(KEY key)
		{
			RB_Node* index = m_root;
			while (index != m_nullNode)
			{
				if (key < index->key)
					index = index->left;
				else if (key > index->right)
					index = index->right;
				else
					return index;
			}
			return NULL;
		}

		//�������
		bool Insert(KEY key, U data)
		{
			RB_Node* insert_point = m_nullNode;
			RB_Node* index = m_root;
			while (index != m_nullNode)
			{
				insert_point = index;
				if (key < index->key)
					index = index->left;
				else if (key > index->key)
					index = index->right;
				else
					return false;
			}

			RB_Node* insert_node = new RB_Node;
			insert_node->key = key;
			insert_node->RB_COLOR = RED;
			insert_node->data = data;
			insert_node->right = m_nullNode;
			insert_node->left = m_nullNode;

			if (insert_point == m_nullNode)
			{
				m_root = insert_node;
				m_root->parent = m_nullNode;
				m_nullNode->left = m_root;
				m_nullNode->right = m_root;
				m_nullNode->parent = m_root;
			}
			else
			{
				if (key > insert_point->key)
					insert_point->right = insert_node;
				else
					insert_point->left = insert_node;
				insert_node->parent = insert_point;
			}

			InsertFixUp(insert_node);
		}

		// �����޸������
		void InsertFixUp(RB_Node* node)
		{
			while (node->parent->RB_COLOR == RED)
			{
				if (node->parent == node->parent->parent->left)   //    
				{
					RB_Node* uncle = node->parent->parent->right;
					if (uncle->RB_COLOR == RED)   //�������1��z������y�Ǻ�ɫ�ġ�    
					{
						node->parent->RB_COLOR = BLACK;
						uncle->RB_COLOR = BLACK;
						node->parent->parent->RB_COLOR = RED;
						node = node->parent->parent;
					}
					else if (uncle->RB_COLOR == BLACK)  //�������2��z������y�Ǻ�ɫ�ģ���    
					{
						if (node == node->parent->right) //��z���Һ���    
						{
							node = node->parent;
							RotateLeft(node);
						}
						//else                 //�������3��z������y�Ǻ�ɫ�ģ���z�����ӡ�    
						//{    
						node->parent->RB_COLOR = BLACK;
						node->parent->parent->RB_COLOR = RED;
						RotateRight(node->parent->parent);
						//}  
					}
				}
				else //�ⲿ�������Ϊ�������1�У�z�ĸ���������Ϊ�游���Һ����˵��������д�ġ�    
					 //15 else (same as then clause with "right" and "left" exchanged)    
				{
					RB_Node* uncle = node->parent->parent->left;
					if (uncle->RB_COLOR == RED)
					{
						node->parent->RB_COLOR = BLACK;
						uncle->RB_COLOR = BLACK;
						uncle->parent->RB_COLOR = RED;
						node = node->parent->parent;
					}
					else if (uncle->RB_COLOR == BLACK)
					{
						if (node == node->parent->left)
						{
							node = node->parent;
							RotateRight(node);     //������������ȣ�������Ϊ����    
						}
						//else    
						//{    
						node->parent->RB_COLOR = BLACK;
						node->parent->parent->RB_COLOR = RED;
						RotateLeft(node->parent->parent);   //������Ϊ���������ɡ�    
															//}    
					}
				}
			}
			m_root->RB_COLOR = BLACK;
		}
		// ����
		bool RotateLeft(RB_Node* node)
		{
			if (node == m_nullNode || node->right == m_nullNode)
				return false;
			RB_Node* lower_right = node->right;
			lower_right->parent = node->parent;
			node->right = lower_right->left;
			if (lower_right->left != m_nullNode) // �Һ��ӵ����Ӵ���
				lower_right->left->parent = node;
			if (node->parent == m_nullNode) 
			{
				m_root = lower_right;
				m_nullNode->left = m_root;
				m_nullNode->right = m_root;
			}
			else
			{
				if (node == node->parent->left)
					node->parent->left = lower_right;
				else
					node->parent->right = lower_right;
			}
			node->parent = lower_right;
			lower_right->left = node;
		}
		// ����
		bool RotateRight(RB_Node* node)
		{
			if (node == m_nullNode || node->left == m_nullNode)
				return false;
			RB_Node* lower_left = node->left; // �ýڵ����Ҷ��
			lower_left->parent = node->parent; // �ýڵ�ĸ��ڵ㸳ֵ����Ҷ�ӽڵ�ĸ��ڵ�
			node->left = lower_left->left;
			if (lower_left->right != m_nullNode)
				lower_left->right->parent = node;
			if ( node->parent == m_nullNode )
			{
				m_root = lower_left;
				m_nullNode->left = m_root;
				m_nullNode->right = m_root;
			}
			else
			{
				if (node->parent->left == node)
					node->parent->left = lower_left;
				else
					node->parent->right = lower_left;
			}
			node->parent = lower_left;
			lower_left->right = node;
		}
		
		void printTree()
		{
			RB_Node* iter = NULL;
			vector<RB_Node*> s;
			s.push_back(m_root);
			int cur = 0, size = s.size();
			while(cur < size)
			{ 
				while (cur < size)
				{
					iter = s[cur];
					cout << iter->key << " ";
					if (iter->right != m_nullNode)
						s.push_back(iter->right);
					if (iter->left != m_nullNode)
						s.push_back(iter->left);
					cur++;
				}
				size = s.size();
				cout << endl;
			}
		}
};
