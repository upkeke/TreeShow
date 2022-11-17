#ifndef AVTREE
#define AVTREE
#pragma execution_character_set("utf-8")

#include<vector>

namespace 二叉树 {
	using std::vector;
	struct Pos
	{
		int row;
		int col;
		Pos(int x = 0, int y = 0) :row(x), col(y){}
	};
	struct Tree:public Pos
	{
		int val;
		Tree* left;
		Tree* right;
		Tree(int val = 0,
			Tree* left = nullptr,
			Tree* right = nullptr) :Pos(),
			val(val), left(left), right(right) {}
		void 层级遍历();
		void 中序遍历();
		void 释放树节点(Tree* head);
		int 节点个数();
		~Tree();

	private:
		int _节点个数(Tree* head);
	};
	class AVLTree
	{
	private:
		Tree* head;
		Tree* 失衡点 = nullptr;
		Tree 中转点; // 辅助
		int row_index = 0; //_修正节点横坐标函数的辅助变量

		Tree* _初始化二叉查找树(const vector<int>& data, int lIndex, int rIndex);
		//平衡因子 左子节点的高度减右子节点的高度
		int _节点高度(Tree* _head);
		// 二叉查找树，左<中<右
		bool _insert(Tree* _head, int val);
		// 1）找到节点说明树不平衡, 此时 失衡点不等于nullptr
		// 2）不平衡点一定在根节点到插入这个点路径上
		void _获得失衡节点(Tree* _head, int val);
		// 中序遍历
		void _修正节点横坐标(Tree* head);
		void _修正节点纵坐标(Tree* head);
		
		void _后序遍历收集节点(Tree* head, vector<Tree*>& vt);

		void 保持平衡();
	public:
		explicit AVLTree(Tree* head = nullptr) :head(head), 中转点() {}
		explicit AVLTree(vector<int> data);

		AVLTree(AVLTree& ) = delete;
		AVLTree& operator=(AVLTree& ) = delete;
		AVLTree(AVLTree&& tree);
		AVLTree& operator=(AVLTree&& tree);
		bool insert(int val);
		int 深度();
		int 节点个数();

		// 测试项
		void 层级遍历();
		void 中序遍历();
		Tree* 失衡节点();

		vector<Tree*> 节点集合();
		~AVLTree();

	};

}

void 二叉树测试();



#endif