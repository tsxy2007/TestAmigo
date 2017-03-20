#pragma once

#include <iostream>
#include <stirng>
#include <sstream>
#include <fstream>
using namespace std;

template<class KEY , class U>
class RB_Tree
{
private:
	RB_Tree( const RB_Tree& input ) {};
	const RB_Tree& operator= (const RB_Tree& input) {}
private:
	enum COLOR { RED,BLACK };
	class RB_Node
	{
	public:
		RB_Node()
		{
			right = NULL;
			left = NULL;
			parent = NULL;
		}
		COLOR RB_COLOR;
		RB_Node* right;
		RB_Node* left;
		RB_Node* parent;
		KEY key;
		U   data;
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
		//查找key
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

		//插入操作
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
			insert_node->RB_COLOR = BLACK;
			insert_node->data = data;
			insert_node->right = m_nullNode;
			insert_node->left = m_nullNode;

			if (insert_point == m_nullNode)
			{
				m_root = insert_node;
				m_root->parent = m_nullNode;
				m_root->left = m_root;
				m_root->right = m_root;
				m_root->parent = m_root;
			}
			else
			{
				if (key > insert_node->key)
					insert_point->right = insert_node;
				else
					insert_point->left = insert_node;
				insert_node->parent = insert_point;
			}

			InsertFixup(insert_node);
		}

		// 插入修复红黑树
		void InsertFixup(RB_Node* node)
		{
			while (node->parent->RB_COLOR == RED)
			{
				if (node->parent == node->parent->parent->left)
				{
					RB_Node* uncle = node->parent->parent->right;
					if (uncle->RB_COLOR == RED)
					{
						node->parent->RB_COLOR = BLACK;
						uncle->RB_COLOR = BLACK;
						uncle->parent->parent->RB_COLOR = RED;
						node = node->parent->parent;
					}
					else if (uncle->RB_COLOR == BLACK)
					{
						if (node == node->parent->right)
						{
							node = node->parent;
							RoateLeft(node);//左旋
						}
						node->parent->RB_COLOR = BLACK;
						node->parent->parent->RB_COLOR = RED;
						RotateRight(node->parent->parent) //右旋
					}
				}
				else
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
							RotateRight(node);
						}
						node->parent->RB_COLOR = BLACK;
						node->parent->parent->RB_COLOR = RED;
						RoateLeft(node->parent->parent);
					}
				}

			}
			m_root->RB_COLOR = BLACK;
		}
		// 左旋
		bool RoateLeft(RB_Node* node)
		{
			if (node == m_nullNode || node->right == m_nullNode)
				return false;
			RB_Node* lower_right = node->right;
			lower_right->parent = node->parent;
			node->right = lower_right->left;
			if (lower_right->left != m_nullNode) // 右孩子的左孩子存在
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
		// 右旋
		bool RotateRight(RB_Node* node)
		{
			if (node == m_nullNode || node->left == m_nullNode)
				return false;
			RB_Node* lower_left = node->left; // 该节点的左叶子
			lower_left->parent = node->parent; // 该节点的父节点赋值给左叶子节点的父节点
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
		

	};
};