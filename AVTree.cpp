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

namespace ������
{
	void Tree::�㼶����()
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
	void Tree::�������()
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
	void Tree::�ͷ����ڵ�(Tree* head)
	{
		if (head == nullptr)return;
		�ͷ����ڵ�(head->left);
		�ͷ����ڵ�(head->right);
		free(head);
	}
	int Tree::�ڵ����()
	{
		return _�ڵ����(this);
	}
	Tree::~Tree()
	{
		�ͷ����ڵ�(left);
		�ͷ����ڵ�(right);
	}
	int Tree::_�ڵ����(Tree* head)
	{
		if (head == nullptr)return 0;
		int x = _�ڵ����(head->left);
		int y = _�ڵ����(head->right);
		return x + y + 1;
	}
}
namespace
{

}
namespace ������
{
	Tree* AVLTree::_��ʼ�����������(const vector<int>& data, int lIndex, int rIndex)
	{
		if (lIndex > rIndex) return nullptr;
		int mIndex = (lIndex + rIndex) / 2;
		Tree* head = new Tree(data[mIndex]);
		head->row = mIndex;
		head->left = _��ʼ�����������(data, lIndex, mIndex - 1);
		head->right = _��ʼ�����������(data, mIndex + 1, rIndex);
		return head;
	}
	int AVLTree::_�ڵ�߶�(Tree* _head)
	{
		if (_head == nullptr) return 0;
		int left_h = _�ڵ�߶�(_head->left);
		int right_h = _�ڵ�߶�(_head->right);
		return std::max(left_h, right_h) + 1;
	}
	bool AVLTree::_insert(Tree* _head, int val)
	{
		if (_head->val == val)
		{
			return false;// ��������Ҫƽ��
		}
		Tree** temp = nullptr;
		if (_head->val > val)
			temp = &_head->left;
		else
			temp = &_head->right;
		if (*temp == nullptr)
		{
			*temp = new Tree(val);
			return true; //������Ҫ����ƽ��
		}
		else
			_insert(*temp, val);
	}
	// 1���ҵ��ڵ�˵������ƽ��, ��ʱ ʧ��㲻����nullptr
	// 2����ƽ���һ���ڸ��ڵ㵽���������·����
	void AVLTree::_���ʧ��ڵ�(Tree* _head, int val)
	{
		if (_head->val == val)return;
		if (_head == nullptr) return;
		if (_head->val > val) //��ǰֵ���ڲ���ڵ㣬����ڵ�����ߣ�
			_���ʧ��ڵ�(_head->left, val);
		else
			_���ʧ��ڵ�(_head->right, val);
		if (ʧ��� == nullptr) //�������ʧ���
		{
			int left_h = _�ڵ�߶�(_head->left);
			int right_h = _�ڵ�߶�(_head->right);
			if (abs(left_h - right_h) > 1)
				ʧ��� = _head;
		}
	}

	void AVLTree::_�����ڵ������(Tree* head)
	{
		if (head == nullptr) return;
		_�����ڵ������(head->left);
		head->row = row_index++;
		_�����ڵ������(head->right);
	}
	void AVLTree::_�����ڵ�������(Tree* head)
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
	void AVLTree::_��������ռ��ڵ�(Tree* head, vector<Tree*>& vt)
	{
		if (head == nullptr)
			return;
		_��������ռ��ڵ�(head->left, vt);
		_��������ռ��ڵ�(head->right, vt);
		vt.push_back(head);
	}
	void AVLTree::����ƽ��()
	{

	}
	AVLTree::AVLTree(vector<int> data):AVLTree()
	{
		std::sort(data.begin(), data.end());
		int rIndex = data.size() - 1;
		head = _��ʼ�����������(data, 0, rIndex); //��һ���Ѿ��ռ��˺�����
		_�����ڵ�������(head);
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
		bool flag = _insert(head, val);
		if (flag)
		{
			ʧ��� = nullptr;
			_���ʧ��ڵ�(head, val);
			row_index = 0;
			_�����ڵ������(head);
			_�����ڵ�������(head);
			//�ҵ����ʧ����Ȼ���������������ķ����ռ��������ڵ�
			if (ʧ��� != nullptr)
				qDebug() << "ʧ����ֵ��" << ʧ���->val;
			else
				qDebug() << "������������Ȼƽ��";
		}
		else
		{
			qDebug() << "���������Ѿ������ֵ�ˣ�����Ҫ����";
		}
		return flag;
	}
	void AVLTree::�㼶����()
	{
		head->�㼶����();
	}
	void AVLTree::�������()
	{
		head->�������();
	}
	Tree* AVLTree::ʧ��ڵ�()
	{
		return ʧ���;
	}
	int AVLTree::���()
	{
		return _�ڵ�߶�(head);
	}
	int AVLTree::�ڵ����()
	{
		return head->�ڵ����();
	}
	vector<Tree*> AVLTree::�ڵ㼯��()
	{
		vector<Tree*> vt; //��������� �ռ�ÿһ���ڵ�
		_��������ռ��ڵ�(head, vt);
		return vt;
	}
	AVLTree::~AVLTree()
	{
		if (head != nullptr)
			delete head;
	}



	AVLTree* ����ƽ����()
	{
		//vector<int> ����������ظ���(int size);
		//vector<int> arr = ����������ظ���(10); // ���һ��sizeΪ11��vector

		vector<int> arr{ 5,40,43,51,55,65,70,83,96,100 };

		AVLTree* head = new AVLTree(arr);
		qDebug() << "�������";
		head->�������();
		return head;
		//delete head;
	}
}

void ����������()
{
	using namespace ������;

	AVLTree* av = ����ƽ����();
	av->insert(1);
	av->�㼶����();
	qDebug() << "���� 50 ��" ;
	av->insert(50);
	av->�㼶����();
	qDebug() << "++++++++++++++++";
}