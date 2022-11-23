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

namespace w������
{

	struct Pos
	{
		int row;
		int col; //Ҳ�ǽڵ�����
		int height = 0;// �ڵ�ĸ߶�
		NodeColor color = NodeColor::yellow; // �����ר��

		Pos() :row(0), col(0) {}
		Pos(NodeColor color) :row(0), col(0),color(color) {}
		
		/*�����*/
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
		void w�㼶����();
		void w�������();
		void w�ͷ����ڵ�(Tree* head);
		int w�ڵ����();
		/*�����*/
		//Pos(NodeColor::):
		Tree(int val, NodeColor color):Pos(color),val(val), left(nullptr), right(nullptr) {}
		virtual ~Tree();
	private:
		int _�ڵ����(Tree* head);


	};

	//���⿪�ź�������
	inline bool isRed(Pos* head)
	{
		if (head == nullptr)
			return false;
		return head->color == NodeColor::red;
	}

	int wˢ��ÿ���ڵ�ĸ߶�(Tree* _head);
	//void ��������(Tree* head);
	vector<Tree*> w�ڵ㼯��(Tree* _head);

}

