#include "Tree.h"
#include <queue>
#include<functional>

using std::queue;
using std::function;
namespace w������
{

	bool Tree::operator<(const Tree& t)
	{
		return val < t.val;
	}
	void Tree::w�㼶����()
	{
		////http://520it.com/binarytrees/
		queue<Tree*> qu;
		qu.push(this);
		while (!qu.empty())
		{
			auto h = qu.front();
			//cout << h->val << ',';
			qu.pop();
			if (h->left != nullptr)
				qu.push(h->left);
			if (h->right != nullptr)
				qu.push(h->right);
		}
		//cout << " ";
	}
	void Tree::w�������()
	{
		function<void(Tree*)> func = [&](Tree* head)
		{
			if (head == nullptr) return;
			func(head->left);
			//cout << head->val << '\t';
			func(head->right);
		};
		func(this);
		//cout << endl;
	}
	void Tree::w�ͷ����ڵ�(Tree* head)
	{
		if (head == nullptr)return;
		w�ͷ����ڵ�(head->left);
		w�ͷ����ڵ�(head->right);
		free(head);
	}
	int Tree::w�ڵ����()
	{
		return _�ڵ����(this);
	}
	Tree::~Tree()
	{
		w�ͷ����ڵ�(left);
		w�ͷ����ڵ�(right);
	}
	int Tree::_�ڵ����(Tree* head)
	{
		if (head == nullptr)return 0;
		int x = _�ڵ����(head->left);
		int y = _�ڵ����(head->right);
		return x + y + 1;
	}

	void Pos::setPos(int x, int y)
	{
		row = x;
		col = y;
	}

	bool Pos::isRedn(Pos* head)
	{
		if (head == nullptr)
			return true;
		return head->color == NodeColor::red;
	}

	void Pos::setColor(NodeColor _color)
	{
		color = _color;
	}



}

namespace
{
	using w������::Tree;
	void _�����ڵ������(Tree* head, int& index)
	{
		if (head == nullptr) return;
		_�����ڵ������(head->left, index);
		head->row = index++;
		_�����ڵ������(head->right, index);
	}
	void _�����ڵ�������(Tree* head)
	{
		queue<Tree*> Q;
		Q.push(head);
		Q.push(0);
		int index = 0;
		do {
			Tree* node = Q.front();
			Q.pop();
			if (node) {
				node->col = index;
				//cout << node->val << " ";
				if (node->left)
					Q.push(node->left);
				if (node->right)
					Q.push(node->right);
			}
			else if (!Q.empty()) {
				Q.push(0);
				++index;
				//cout << endl;
			}
		} while (!Q.empty());
	}
	void _��������(Tree* head)
	{
		int index = 0;
		_�����ڵ������(head, index);
		_�����ڵ�������(head);
	}
	void _��������ռ��ڵ�(Tree* head, vector<Tree*>& vt)
	{
		if (head == nullptr)
			return;
		_��������ռ��ڵ�(head->left, vt);
		_��������ռ��ڵ�(head->right, vt);
		vt.push_back(head);
	}
}

/*������������*/
namespace w������
{
	int wˢ��ÿ���ڵ�ĸ߶�(Tree* _head)
	{
		if (_head == nullptr) return 0;
		int left_h = wˢ��ÿ���ڵ�ĸ߶�(_head->left);
		int right_h = wˢ��ÿ���ڵ�ĸ߶�(_head->right);
		_head->height = std::max(left_h, right_h) + 1;
		
		return _head->height;
	}

	vector<Tree*> w�ڵ㼯��(Tree* head)
	{
		//��һ�����������нڵ�����꣬
		_��������(head);
		vector<Tree*> vt; //��������� �ռ�ÿһ���ڵ�
		_��������ռ��ڵ�(head, vt);
		return vt;
	}
}