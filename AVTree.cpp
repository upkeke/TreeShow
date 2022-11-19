#include"AVTree.h"
#include<queue>
#include<qdebug.h>
#include<vector>
#include<functional>
#include<iostream>
using std::function;
using std::queue;
using std::vector;
using std::cout;
using std::endl;

namespace 二叉树
{

	bool Tree::operator<(const Tree& t)
	{
		return val < t.val;
	}

	void Tree::层级遍历()
	{
		////http://520it.com/binarytrees/
		queue<Tree*> qu;
		qu.push(this);
		while (!qu.empty())
		{
			auto h = qu.front();
			cout << h->val << ',';
			qu.pop();
			if (h->left != nullptr)
				qu.push(h->left);
			if (h->right != nullptr)
				qu.push(h->right);
		}
		cout << " ";
	}
	void Tree::中序遍历()
	{
		function<void(Tree*)> func = [&](Tree* head)
		{
			if (head == nullptr) return;
			func(head->left);
			cout << head->val << '\t';
			func(head->right);
		};
		func(this);
		cout << endl;
	}
	void Tree::释放树节点(Tree* head)
	{
		if (head == nullptr)return;
		释放树节点(head->left);
		释放树节点(head->right);
		free(head);
	}
	int Tree::节点个数()
	{
		return _节点个数(this);
	}
	Tree::~Tree()
	{
		释放树节点(left);
		释放树节点(right);
	}
	int Tree::_节点个数(Tree* head)
	{
		if (head == nullptr)return 0;
		int x = _节点个数(head->left);
		int y = _节点个数(head->right);
		return x + y + 1;
	}
}
namespace
{

}
namespace 二叉树
{
	Tree* AVLTree::_初始化二叉查找树(const vector<int>& data, int lIndex, int rIndex)
	{
		if (lIndex > rIndex) return nullptr;
		int mIndex = (lIndex + rIndex) / 2;
		Tree* head = new Tree(data[mIndex]);
		head->row = mIndex;
		head->left = _初始化二叉查找树(data, lIndex, mIndex - 1);
		head->right = _初始化二叉查找树(data, mIndex + 1, rIndex);
		return head;
	}
	int AVLTree::_节点高度(Tree* _head)
	{
		if (_head == nullptr) return 0;
		int left_h = _节点高度(_head->left);
		int right_h = _节点高度(_head->right);
		return std::max(left_h, right_h) + 1;
	}
	bool AVLTree::_insert(Tree* _head, int val)
	{
		if (_head->val == val)
		{
			return false;// 后续不需要平衡
		}
		Tree** temp = nullptr;
		if (_head->val > val)
			temp = &_head->left;
		else
			temp = &_head->right;
		if (*temp == nullptr)
		{
			*temp = new Tree(val);
			return true; //后续需要进行平衡
		}
		else
			_insert(*temp, val);
	}
	// 1）找到节点说明树不平衡, 此时 失衡点不等于nullptr
	// 2）不平衡点一定在根节点到插入这个点路径上
	void AVLTree::_获得失衡节点(Tree* _head, int val)
	{

		// 虽然输入更快，有漏洞，val是最后插入的数，这个这个数不一定插入成功，等待后序修正
		// 同时插入这个数可能被 pop调，这时候val已经不在了
		if (_head->val == val)return;
		if (_head == nullptr) return;
		if (_head->val > val) //当前值大于插入节点，插入节点在左边，
			_获得失衡节点(_head->left, val);
		else
			_获得失衡节点(_head->right, val);
		if (失衡点 == nullptr) //到最深处的失衡点
		{
			int left_h = _节点高度(_head->left);
			int right_h = _节点高度(_head->right);
			if (abs(left_h - right_h) > 1)
				失衡点 = _head;
		}
	}

	void AVLTree::_修正节点横坐标(Tree* head,int &index)
	{
		if (head == nullptr) return;
		_修正节点横坐标(head->left,index);
		head->row = index++;
		_修正节点横坐标(head->right,index);
	}
	void AVLTree::_修正节点纵坐标(Tree* head)
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
				cout << node->val << " ";
				if (node->left)
					Q.push(node->left);
				if (node->right)
					Q.push(node->right);
			}
			else if (!Q.empty()) {
				Q.push(0);
				++index;
				cout << endl;
			}
		} while (!Q.empty());
	}
	void AVLTree::_修正坐标(Tree* head)
	{
		int index = 0;

		_修正节点横坐标(head,index);
		_修正节点纵坐标(head);
	}
	void AVLTree::_后序遍历收集节点(Tree* head, vector<Tree*>& vt)
	{
		if (head == nullptr)
			return;
		_后序遍历收集节点(head->left, vt);
		_后序遍历收集节点(head->right, vt);
		vt.push_back(head);
	}

	void AVLTree::_sort_tree(vector<Tree*>& vt1)
	{
		if (vt1[0]->val > vt1[1]->val) std::swap(vt1[0], vt1[1]);
		if (vt1[1]->val > vt1[2]->val) std::swap(vt1[1], vt1[2]);
		if (vt1[0]->val > vt1[1]->val) std::swap(vt1[0], vt1[1]);
	}
	void AVLTree::保持平衡()
	{

		Tree* temp = 失衡节点();
		if (失衡点 == nullptr) return;
		vector<Tree*> vt1(3, nullptr);
		vector<Tree*> vt2;
		vt1[0] = temp;
		for (size_t i = 1; i < 3; i++)
		{
			if (temp->val > insert_val)
			{
				vt1[i] = temp->left;
				if (temp->right != nullptr)
				{
					vt2.push_back(temp->right);
				}
			}
			else
			{
				vt1[i] = temp->right;
				if (temp->left != nullptr)
				{
					vt2.push_back(temp->left);
				}
			}
			temp = vt1[i];
		}
		if(temp->left!=nullptr)vt2.push_back(temp->left);
		if(temp->right !=nullptr)vt2.push_back(temp->right);
		for (auto ptr : vt1)
		{
			ptr->left = nullptr;
			ptr->right = nullptr;
		}
		//对vt1进行排序
		_sort_tree(vt1);
		// *失衡点 等于 vt1中间的value
		std::swap(失衡点->val, vt1[1]->val); //此时vt1又被打乱
		_sort_tree(vt1);
		失衡点->left = vt1[0];
		失衡点->right = vt1[2];

		for (auto ptr : vt2)
		{
			int val = ptr->val;
			if (val > vt1[2]->val)
				vt1[2]->right = ptr;
			else if (val > vt1[1]->val)
				vt1[2]->left = ptr;
			else if (val > vt1[0]->val)
				vt1[0]->right = ptr;
			else
				vt1[0]->left = ptr;
		}
		qDebug() << "修正平衡完毕";
		失衡点 = nullptr;
		_修正坐标(head);
	}
	AVLTree::AVLTree(vector<int> data):AVLTree()
	{
		std::sort(data.begin(), data.end());
		int rIndex = data.size() - 1;
		head = _初始化二叉查找树(data, 0, rIndex); //这一步已经收集了横坐标
		_修正节点纵坐标(head);
	}
	AVLTree::AVLTree(AVLTree&& tree)
	{
		*this = std::move(tree);
	}

	AVLTree& AVLTree::operator=(AVLTree&& tree)
	{
		if (head == tree.head) return *this;
		delete head;
		head = tree.head;
		tree.head = nullptr;
		return *this;
	}
	bool AVLTree::insert(int val)
	{
		insert_val = val;
		bool flag = _insert(head, val);
		if (flag)
		{
			失衡点 = nullptr;
			_获得失衡节点(head, val);
			_修正坐标(head);
			//找到这个失衡点后，然后沿着它往插入点的方向收集三个树节点
			if (失衡点 != nullptr)
				qDebug() << "失衡点的值：" << 失衡点->val;
			else
				qDebug() << "插入后二叉树依然平衡";
		}
		else
		{
			qDebug() << "二叉树中已经有这个值了，不需要插入";
		}
		return flag;
	}

	bool AVLTree::pop(int val)
	{
		function<void(Tree*)> func = [&](Tree* top) {
			if (top == nullptr) return;
			Tree** tp = nullptr;
			if (top->val > val)
				tp = &top->left;
			else
				tp = &top->right;
			if (*tp != nullptr)
			{
				if ((*tp)->val == val)
				{
					delete (*tp);
					*tp = nullptr;
				}
				else
					func(*tp);
			}
		};
		func(head);
		_修正坐标(head);
		return true;
	}

	void AVLTree::层级遍历()
	{
		head->层级遍历();
	}
	void AVLTree::中序遍历()
	{
		head->中序遍历();
	}
	Tree* AVLTree::失衡节点()
	{
		失衡点 = nullptr;
		_获得失衡节点(head, insert_val);
		return 失衡点;
	}
	int AVLTree::深度()
	{
		return _节点高度(head);
	}
	int AVLTree::节点个数()
	{
		return head->节点个数();
	}
	vector<Tree*> AVLTree::节点集合()
	{
		vector<Tree*> vt; //按后序遍历 收集每一个节点
		_后序遍历收集节点(head, vt);
		return vt;
	}
	AVLTree::~AVLTree()
	{
		if (head != nullptr)
			delete head;
	}



	AVLTree* 生成平衡树()
	{
		//vector<int> 获得数组无重复数(int size);
		//vector<int> arr = 获得数组无重复数(10); // 获得一个size为11的vector

		vector<int> arr{ 5,40,43,51,55,65,70,83,96,100 };

		AVLTree* head = new AVLTree(arr);
		qDebug() << "中序遍历";
		head->中序遍历();
		return head;
		//delete head;
	}
}

void 二叉树测试()
{
	using namespace 二叉树;

	AVLTree* av = 生成平衡树();
	av->insert(1);
	av->层级遍历();
	qDebug() << "插入 50 后" ;
	av->insert(50);
	av->层级遍历();
	qDebug() << "++++++++++++++++";
}