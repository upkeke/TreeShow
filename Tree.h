#pragma once
#include <vector>
using std::vector;

#ifndef NODECOLOR
#define NODECOLOR
enum class NodeColor
{
	yellow,
	green,
	red,
	black,
};
#endif

namespace w二叉树
{

	struct Pos
	{
		int row;
		int col; //也是节点的深度
		int height = 0;// 节点的高度
		NodeColor color = NodeColor::yellow; // 红黑树专用

		Pos() :row(0), col(0) {}
		Pos(NodeColor color) :row(0), col(0),color(color) {}
		
		/*红黑树*/
		//Pos(NodeColor color):color(color),row(0),col(0){}
		void setPos(int x, int y);
		bool isRedn(Pos* head);
		void setColor(NodeColor _color);
		virtual ~Pos()
		{
			;
		}
	};

	struct Tree :public Pos
	{
		int val;
		Tree* left;
		Tree* right;
		Tree(int val = 0,
			Tree* left = nullptr,
			Tree* right = nullptr) :val(val), left(left), right(right) {}
		bool operator<(const Tree& t);
		void w层级遍历();
		void w中序遍历();
		void w释放树节点(Tree* head);
		int w节点个数();
		/*红黑树*/
		//Pos(NodeColor::):
		Tree(int val, NodeColor color):Pos(color),val(val), left(nullptr), right(nullptr) {}
		virtual ~Tree();
	private:
		int _节点个数(Tree* head);


	};

	//对外开放函数区域
	inline bool isRed(Pos* head)
	{
		if (head == nullptr)
			return false;
		return head->color == NodeColor::red;
	}

	int w刷新每个节点的高度(Tree* _head);
	//void 修正坐标(Tree* head);
	vector<Tree*> w节点集合(Tree* _head);

}

