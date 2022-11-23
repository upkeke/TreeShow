#include "RBTree.h"

namespace
{
	using w������::Tree;
	/*
	 1
  a     2
       b  c

	VVV

	 2
  1    c
 a b  
	*/
	void _����(Tree*& _head)
	{
		//Tree* temp = _head->left;

		Tree* temp = _head->right;
		_head->right = temp->left;
		temp->left = _head;

		temp->color = _head->color;
		_head->color = NodeColor::red;
		_head = temp;


	}
	void _����(Tree*& _head)
	{
		Tree* temp = _head->left; 
		_head->left = temp->right;
		temp->right = _head;

		temp->color = _head->color;
		_head->color = NodeColor::red;

		_head = temp;
	}
}
namespace w������
{
	void RBTree::_insert(Tree* &_head, int val)
	{
		if (_head == nullptr)
		{
			_head = new Tree(val, NodeColor::red);
			return;
		}
		if (_head->val > val)
		{
			_insert(_head->left, val);
		}
		else if (_head->val < val)
		{
			_insert(_head->right, val);
		}
		else
			return;
		//��ǰ�ڵ�Ϊ�죬�ҽڵ�Ϊ�죬����
		if ((!isRed(_head->left)) && isRed(_head->right))
		{
			_����(_head);
		}
		//��ڵ�Ϊ�죬��ڵ����ڵ�Ϊ�죬����
		if (isRed(_head->left) && isRed(_head->left->left))
		{
			_����(_head);
		}
		if (isRed(_head->right) && isRed(_head->left))
		{
			_head->left->color  = NodeColor::black;
			_head->right->color = NodeColor::black;
			_head->color = NodeColor::red;
		}
	}




	RBTree::RBTree(const vector<int>& arr) :RBTree()
	{
		for (auto val : arr)
		{
			insert(val);
		}
	}

	RBTree& RBTree::operator=(RBTree&& bt)
	{
		if (head != nullptr)
			delete head;
		head = bt.head;
		bt.head = nullptr;
		return *this;
	}
	RBTree::RBTree(RBTree&&bt)
	{
		*this = std::move(bt);
	}

	void RBTree::insert(int val)
	{
		if (head == nullptr)
		{
			head = new Tree(val,NodeColor::black);
			return;
		}
		_insert(head,val);
		head->color = NodeColor::black;
	}

	RBTree::~RBTree()
	{
		if (head != nullptr)
		{
			delete head;
			head = nullptr;
		}
	}

}


