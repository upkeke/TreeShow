#ifndef AVLTREE
#define AVLTREE
#pragma execution_character_set("utf-8")
#include "Tree.h"
#include<vector>

namespace w二叉树 {
	using std::vector;

	class AVLTree
	{
	public:
		Tree* head;
	private:
		enum class w状态
		{
			平衡后,
			插入后未平衡,
			删除后未平衡,
		};
		

		/*辅助数据, 为了方便演示 插入节点删除节点》》二叉搜索树》》平衡二叉树这个过程，将插入删除和平衡过程分开，
		* 插入完毕后立刻平衡即可不需要这些辅助数据
		*/
		w状态 state = w状态::平衡后;
		int m_val = 0;
		//int del_val = 0;
		Tree* del_front = nullptr;


		Tree* _初始化二叉查找树(const vector<int>& data, int lIndex, int rIndex);
		//平衡因子 左子节点的高度减右子节点的高度
		
		/*插入节点区域*/
		//只是添加节点，不进行平衡
		bool _添加节点(Tree* _head, int val);
		// 1）找到节点说明树不平衡, 此时 失衡点不等于nullptr
		// 2）不平衡点一定在根节点到插入这个点路径上
		// 仅限insert函数使用
		Tree* _获得最低失衡节点_insert(int val);
		

		/*删除节点区域*/
		bool _删掉节点(int val);
		void _删掉节点_平衡();

		void _sort_tree(vector<Tree*>& vt);
		Tree*& _获得指定值的节点(Tree*& p_head,int val);
		Tree* _获得指定值的父节点(Tree* _head, int val);

		//int _刷新每个节点的高度(Tree* _head);
		void _搜索树_平衡(Tree* _head);
		
		bool w单个节点是否平衡(Tree* p);
	public:
		explicit AVLTree(Tree* head = nullptr) :head(head){}
		explicit AVLTree(vector<int> data);

		AVLTree(AVLTree& ) = delete;
		AVLTree& operator=(AVLTree&) = delete;
		AVLTree(AVLTree&& tree);
		AVLTree& operator=(AVLTree&& tree);
		bool insert(int val);
		bool pop(int val);

		Tree* w失衡节点();
		bool w树是否平衡();
		void w保持平衡();
		~AVLTree();

	};
	AVLTree* 生成平衡树();

}

void 二叉树测试();



#endif