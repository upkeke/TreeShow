#include"AVLTree.h"
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


namespace
{
	using w二叉树::Tree;
	inline bool 没有子树(Tree* top)
	{
		return top->left == nullptr && top->right == nullptr;
	}
	inline bool 是否只有左子(Tree* top)
	{
		return top->left != nullptr && top->right == nullptr;
	}
	inline bool 是否只有右子(Tree* top)
	{
		return top->left == nullptr && top->right != nullptr;
	}
	inline bool 左右子树都有(Tree* top)
	{
		return top->left != nullptr && top->right != nullptr;
	}
	bool 有一个子节点(Tree* top)
	{
		return 是否只有左子(top) || 是否只有右子(top);
	}
}
namespace w二叉树
{
	Tree* AVLTree::_初始化二叉查找树(const vector<int>& data, int lIndex, int rIndex)
	{
		if (lIndex > rIndex) return nullptr;
		int mIndex = (lIndex + rIndex) / 2;
		Tree* head = new Tree(data[mIndex]);
		//head->row = mIndex;
		head->left = _初始化二叉查找树(data, lIndex, mIndex - 1);
		head->right = _初始化二叉查找树(data, mIndex + 1, rIndex);
		return head;
	}


	bool AVLTree::_添加节点(Tree* _head, int val)
	{
		if (_head->val == val)
		{
			state = w状态::平衡后;
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
			w刷新每个节点的高度(head);
			state = w状态::插入后未平衡;
			return true; //后续需要进行平衡
		}
		else
			_添加节点(*temp, val);
	}
	// 1）找到节点说明树不平衡, 此时 失衡点不等于nullptr
	// 2）不平衡点一定在根节点到插入这个点路径上
	// 这个函数只适合插入数据的后，参看二叉树是否平衡，专为insert函数服务，其他函数不能调用

	/// <summary>
	/// 
	/// </summary>
	/// <param name="val">承当索引，失衡节点一定在根节点和val之间</param>
	/// <returns>返回nullptr说明当前已经是平衡树</returns>
	Tree* AVLTree::_获得最低失衡节点_insert(int val)
	{

		Tree* re = nullptr;
		function<void(Tree*)> func = [&](Tree* _head)
		{
			if (_head->val > val)
				_head = _head->left;
			else if (_head->val < val)
				_head = _head->right;
			else
				return;
			func(_head);
			if (re == nullptr && !w单个节点是否平衡(_head))
				re = _head;
		};
		func(head);
		return re;
	}

	bool AVLTree::w单个节点是否平衡(Tree* p)
	{
		if (没有子树(p))
			return true;
		if (左右子树都有(p))
		{
			int leftH = p->left->height;
			int rightH = p->right->height;
			if (abs(leftH - rightH) > 1)
				return false;
			return true;
		}
		int cha = p->left != nullptr ? p->left->height : p->right->height;
		if (cha > 1)
			return false;
		return true;
		
	}

	// 这是通用版，插入数据有复杂度更低的方法，但是需要索引，也就是插入值val，失衡节点朝着val走
	//对于
	
	/// <summary>
	/// 调用之前需要调用_刷新每个节点的高度
	/// </summary>
	/// <param name="_head">高度最低的失衡节点</param>
	void AVLTree::_搜索树_平衡(Tree* _head)
	{
		if (state == w状态::平衡后)
			return;
		//Tree* _head = _获得失衡节点_insert(val);
		if (_head == nullptr) return;
		Tree* temp = _head;
		vector<Tree*> vt1(3, nullptr);
		vector<Tree*> vt2;
		vt1[0] = temp;
		size_t i = 1;
		//_刷新每个节点的高度(head);
		for (; i < 3; i++)
		{
			if (左右子树都有(temp))
			{
				int lefth = temp->left->height;
				int righth = temp->right->height;
				if (lefth > righth)
				{
					vt1[i] = temp->left;
					vt2.push_back(temp->right);
				}
				else
				{
					vt1[i] = temp->right;
					vt2.push_back(temp->left);
				}
			}
			else if (temp->left == nullptr)
				vt1[i] = temp->right;
			else if (temp->right == nullptr)
				vt1[i] = temp->left;
			// 如果有失衡节点，当前循环种，不会出现temp为叶子的情况
			temp = vt1[i];
		}
		if (temp->left != nullptr)
			vt2.push_back(temp->left);
		if (temp->right != nullptr)
			vt2.push_back(temp->right);

		for (auto ptr : vt1)
		{
			ptr->left = nullptr;
			ptr->right = nullptr;
		}
		//对vt1进行排序
		_sort_tree(vt1);
		// *失衡点 等于 vt1中间的value
		std::swap(_head->val, vt1[1]->val); //此时vt1又被打乱
		_sort_tree(vt1);
		_head->left = vt1[0];
		_head->right = vt1[2];

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
		w刷新每个节点的高度(head);
	}

	/// <summary>
	/// 只管删，不管平衡，表现为二叉搜索树，某些特殊情况这个二叉搜索树需要2次平衡，
	/// 1）找不到节点，返回false
	/// 
	/// </summary>
	/// <param name="val">删除的值</param>
	/// <param name="father_ptr">这个是第二个返回值，在平衡树的时候使用，如果为nullptr，不进行后续平衡</param>
	/// <returns>是否插入成功</returns>
	bool AVLTree::_删掉节点(int val)
	{
		//Tree*& _head = _获得指定值的节点(head, val); //_head是要的删除节点
		Tree* father = _获得指定值的父节点(head, val);
		if (father == nullptr)
		{
			qDebug() << "没有找到要删除的节点";
			del_front = nullptr;
			state = w状态::平衡后;
			return false; //没有找到节点
		}

		if (father == head)
		{
			if (没有子树(father))//究极特殊情况，如果要删除的正好是头节点，且整棵树只有一个节点
			{
				free(head);
				head = nullptr;
				qDebug() << "删除的是头节点，已经删除，树不存在节点了";
				state = w状态::平衡后;
				del_front = nullptr;
				return true;
			}
		}
		state = w状态::删除后未平衡;
		// _head 是要删除的节点 这之后每个节点的高度会发生变换
		Tree*& _head = father->val > val ? father->left : father->right;
		//节点 没有子节点
		if (没有子树(_head)) 
		{
			free(_head);
			_head = nullptr;
		}
		else if (左右子树都有(_head)) //左右子节点都有
		{
			int leftH = _head->left->height;
			int rightH = _head->right->height;
			if (leftH - rightH >= 0) //左边大于于右边，取左边最大，左边最大的节点必然没有右子节点
			{						//因为这个树是二叉搜索树，找到这个树，把它的val交给_head，把						//它的左子树交给它的父节点的右子树
				father = _head;
				Tree* current = _head->left;
				if (current->right == nullptr)
				{
					_head->val = current->val;
					_head->left = current->left;
					free(current);
				}
				else
				{
					while (current->right != nullptr)
					{
						father = current;
						current = current->right;
					}
					_head->val = current->val;
					father->right = current->left;
					free(current);
				}
			}
			else //右子树深度更深 找右边最小的节点
			{
				father = _head;
				Tree* current = _head->right;
				if (current->left == nullptr)
				{
					_head->val = current->val;
					_head->right = current->right;
					free(current);
				}
				else
				{
					while (current->left != nullptr)
					{
						father = current;
						current = current->left;
					}
					_head->val = current->val;
					father->left = current->right;
					free(current);
				}
			}

		}
		else // 移出点有一颗子树,由于是平衡树，这颗子树不会有子节点，直接free调子树即可
		{
			if (_head->left != nullptr)
			{
				*_head = *_head->left;
				free(_head->left);
			}
			else
			{
				*_head = *_head->right;
				free(_head->right);
			}
		}
		del_front = father; // 第二个返回值
		w刷新每个节点的高度(head);
		return true;
	}

	void AVLTree::_删掉节点_平衡()
	{

		if (state != w状态::删除后未平衡)
			return;
		//如果有失衡节点，del_front
		if (w单个节点是否平衡(del_front))
		{
			state = w状态::平衡后;
			return;
		}
		_搜索树_平衡(del_front);
		//获得del_front的父节点
		 Tree* ptr = _获得指定值的父节点(head, del_front->val);
		//一次后不一定平衡，如果不平衡，最低平衡点就是根节点
		if (!w单个节点是否平衡(ptr))
		{
			_搜索树_平衡(ptr);
		}
		state = w状态::平衡后;
	}



	void AVLTree::_sort_tree(vector<Tree*>& vt1)
	{
		if (vt1[0]->val > vt1[1]->val) std::swap(vt1[0], vt1[1]);
		if (vt1[1]->val > vt1[2]->val) std::swap(vt1[1], vt1[2]);
		if (vt1[0]->val > vt1[1]->val) std::swap(vt1[0], vt1[1]);
	}

	Tree*& AVLTree::_获得指定值的节点(Tree*& _head, int val)
	{
		if (_head == nullptr)
			return _head;
		if (_head->val == val)
			return _head;
		if (_head->val > val)
			_获得指定值的节点(_head->left, val);
		else
			_获得指定值的节点(_head->right, val);
	}

	/// <summary>
	/// 这是辅助函数，_删掉节点有调用，特殊情况，根节点没有父节点，返回head，调用地方也必须进行特殊处理
	/// </summary>
	/// <param name="_head">外部调用只能传入head，</param>
	/// <param name="val">指定的值</param>
	/// <returns>返回nullptr说明整棵树没有val，返回head说明val在头节点，其他情况正常</returns>
	Tree* AVLTree::_获得指定值的父节点(Tree* _head, int val)
	{
		if (_head == nullptr) return _head;
		Tree** child = nullptr;
		if (_head->val > val)
			child = &_head->left;
		else if (_head->val < val)
			child = &_head->right;
		else
			return _head; //到这一行，根节点的值就是val，根节点没有父节点，返回根节点
		if (*child != nullptr)
		{
			if ((*child)->val == val)
			{
				qDebug("%d 的父节点的值是 %d", val,_head->val);
				return _head;
			}
			else
			{
				return _获得指定值的父节点(*child, val);
			}
		}
		return nullptr;
	}

	void AVLTree::w保持平衡()
	{
		Tree* ptr = nullptr;
		switch (state)
		{
		case w二叉树::AVLTree::w状态::平衡后:
			break;
		case w二叉树::AVLTree::w状态::插入后未平衡:
			ptr = _获得最低失衡节点_insert(m_val);
			_搜索树_平衡(ptr);
			break;
		case w二叉树::AVLTree::w状态::删除后未平衡:
			_删掉节点_平衡();
			break;
		default:
			break;
		}
		//_修正坐标
		state = w状态::平衡后;
	}
	AVLTree::AVLTree(vector<int> data):AVLTree()
	{
		std::sort(data.begin(), data.end());
		int rIndex = data.size() - 1;
		head = _初始化二叉查找树(data, 0, rIndex); //这一步已经收集了横坐标
		//_修正节点纵坐标(head);
		state = w状态::平衡后;
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
		state = tree.state;
		tree.head = nullptr;
		return *this;
	}

	//没有进行平衡
	bool AVLTree::insert(int val)
	{
		m_val = val;
		bool flag = _添加节点(head, val);
		//state = 状态::插入后未平衡;
		if (flag)
		{
			qDebug() << "二叉树插入成功";
		}
		else
		{
			qDebug() << "二叉树中已经有这个值了，不需要插入";
		}
		return flag;
	}

	// 只有删除，没有平衡
	bool AVLTree::pop(int val)
	{
		m_val = val;
		bool flag = _删掉节点(val);
		return flag;
	}

	Tree* AVLTree::w失衡节点()
	{
		Tree* ptr = nullptr;
		//_修正坐标(head);
		switch (state)
		{
		case w二叉树::AVLTree::w状态::平衡后:
			break;
		case w二叉树::AVLTree::w状态::插入后未平衡:
			ptr =_获得最低失衡节点_insert(m_val);
			break;
		case w二叉树::AVLTree::w状态::删除后未平衡:
			if (!w单个节点是否平衡(del_front))
				ptr = del_front;
			break;
		default:
			break;

		}
		return ptr;
	}

	bool AVLTree::w树是否平衡()
	{
		
		switch (state)
		{
		case w二叉树::AVLTree::w状态::平衡后:
			return true;
		case w二叉树::AVLTree::w状态::插入后未平衡:
			//auto ptr = _获得最低失衡节点(m_val);
			if (_获得最低失衡节点_insert(m_val) == nullptr)
			{
				state = w状态::平衡后;
				return true;
			}
			return false;
		case w二叉树::AVLTree::w状态::删除后未平衡:
			if (w单个节点是否平衡(del_front))
			{
				state = w状态::平衡后;
				return true;
			}
			return false;
		default:
			break;
		}
		return true;
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

		AVLTree* _head = new AVLTree(arr);
		qDebug() << "中序遍历";
		_head->head->w中序遍历();
		return _head;
		//delete head;
	}
}

void 二叉树测试()
{
	using namespace w二叉树;

	AVLTree* av = 生成平衡树();
	av->insert(1);
	av->head->w层级遍历();
	qDebug() << "插入 50 后" ;
	av->insert(50);
	av->head->w层级遍历();
	qDebug() << "++++++++++++++++";
}