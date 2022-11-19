#ifndef AVTREE
#define AVTREE
#pragma execution_character_set("utf-8")

#include<vector>

namespace ������ {
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
		bool operator<(const Tree& t);
		void �㼶����();
		void �������();
		void �ͷ����ڵ�(Tree* head);
		int �ڵ����();
		~Tree();

	private:
		int _�ڵ����(Tree* head);
	};
	class AVLTree
	{
	private:
		Tree* head;
		Tree* ʧ��� = nullptr;
		Tree ��ת��; // ����
		int insert_val = 0; // �����ֵ

		Tree* _��ʼ�����������(const vector<int>& data, int lIndex, int rIndex);
		//ƽ������ ���ӽڵ�ĸ߶ȼ����ӽڵ�ĸ߶�
		int _�ڵ�߶�(Tree* _head);
		// �������������<��<��
		bool _insert(Tree* _head, int val);
		// 1���ҵ��ڵ�˵������ƽ��, ��ʱ ʧ��㲻����nullptr
		// 2����ƽ���һ���ڸ��ڵ㵽���������·����
		void _���ʧ��ڵ�(Tree* _head, int val);
		// �������
		void _�����ڵ������(Tree* head, int& index);
		void _�����ڵ�������(Tree* head);
		void _��������(Tree* head);
		
		void _��������ռ��ڵ�(Tree* head, vector<Tree*>& vt);

		void _sort_tree(vector<Tree*>& vt);
		
	public:
		explicit AVLTree(Tree* head = nullptr) :head(head), ��ת��() {}
		explicit AVLTree(vector<int> data);

		AVLTree(AVLTree& ) = delete;
		AVLTree& operator=(AVLTree& ) = delete;
		AVLTree(AVLTree&& tree);
		AVLTree& operator=(AVLTree&& tree);
		bool insert(int val);
		bool pop(int val);
		int ���();
		int �ڵ����();

		// ������
		void �㼶����();
		void �������();
		Tree* ʧ��ڵ�();
		void ����ƽ��();
		vector<Tree*> �ڵ㼯��();
		~AVLTree();

	};

}

void ����������();



#endif