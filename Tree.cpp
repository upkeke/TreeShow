#include "Tree.h"
#include <queue>
#include<functional>

using std::queue;
using std::function;
namespace w二叉树
{

	bool Tree::operator<(const Tree& t)
	{
		return val < t.val;
	}
	void Tree::w层级遍历()
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
	void Tree::w中序遍历()
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
	void Tree::w释放树节点(Tree* head)
	{
		if (head == nullptr)return;
		w释放树节点(head->left);
		w释放树节点(head->right);
		free(head);
	}
	int Tree::w节点个数()
	{
		return _节点个数(this);
	}
	Tree::~Tree()
	{
		w释放树节点(left);
		w释放树节点(right);
	}
	int Tree::_节点个数(Tree* head)
	{
		if (head == nullptr)return 0;
		int x = _节点个数(head->left);
		int y = _节点个数(head->right);
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
	using w二叉树::Tree;
	void _修正节点横坐标(Tree* head, int& index)
	{
		if (head == nullptr) return;
		_修正节点横坐标(head->left, index);
		head->row = index++;
		_修正节点横坐标(head->right, index);
	}
	void _修正节点纵坐标(Tree* head)
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
	void _修正坐标(Tree* head)
	{
		int index = 0;
		_修正节点横坐标(head, index);
		_修正节点纵坐标(head);
	}
	void _后序遍历收集节点(Tree* head, vector<Tree*>& vt)
	{
		if (head == nullptr)
			return;
		_后序遍历收集节点(head->left, vt);
		_后序遍历收集节点(head->right, vt);
		vt.push_back(head);
	}
}

/*公共函数区域*/
namespace w二叉树
{
	int w刷新每个节点的高度(Tree* _head)
	{
		if (_head == nullptr) return 0;
		int left_h = w刷新每个节点的高度(_head->left);
		int right_h = w刷新每个节点的高度(_head->right);
		_head->height = std::max(left_h, right_h) + 1;
		
		return _head->height;
	}

	vector<Tree*> w节点集合(Tree* head)
	{
		//这一步会修正所有节点的坐标，
		_修正坐标(head);
		vector<Tree*> vt; //按后序遍历 收集每一个节点
		_后序遍历收集节点(head, vt);
		return vt;
	}
}