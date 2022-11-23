#ifndef AVLTREE
#define AVLTREE
#pragma execution_character_set("utf-8")
#include "Tree.h"
#include<vector>

namespace w������ {
	using std::vector;

	class AVLTree
	{
	public:
		Tree* head;
	private:
		enum class w״̬
		{
			ƽ���,
			�����δƽ��,
			ɾ����δƽ��,
		};
		

		/*��������, Ϊ�˷�����ʾ ����ڵ�ɾ���ڵ㡷����������������ƽ�������������̣�������ɾ����ƽ����̷ֿ���
		* ������Ϻ�����ƽ�⼴�ɲ���Ҫ��Щ��������
		*/
		w״̬ state = w״̬::ƽ���;
		int m_val = 0;
		//int del_val = 0;
		Tree* del_front = nullptr;


		Tree* _��ʼ�����������(const vector<int>& data, int lIndex, int rIndex);
		//ƽ������ ���ӽڵ�ĸ߶ȼ����ӽڵ�ĸ߶�
		
		/*����ڵ�����*/
		//ֻ����ӽڵ㣬������ƽ��
		bool _��ӽڵ�(Tree* _head, int val);
		// 1���ҵ��ڵ�˵������ƽ��, ��ʱ ʧ��㲻����nullptr
		// 2����ƽ���һ���ڸ��ڵ㵽���������·����
		// ����insert����ʹ��
		Tree* _������ʧ��ڵ�_insert(int val);
		

		/*ɾ���ڵ�����*/
		bool _ɾ���ڵ�(int val);
		void _ɾ���ڵ�_ƽ��();

		void _sort_tree(vector<Tree*>& vt);
		Tree*& _���ָ��ֵ�Ľڵ�(Tree*& p_head,int val);
		Tree* _���ָ��ֵ�ĸ��ڵ�(Tree* _head, int val);

		//int _ˢ��ÿ���ڵ�ĸ߶�(Tree* _head);
		void _������_ƽ��(Tree* _head);
		
		bool w�����ڵ��Ƿ�ƽ��(Tree* p);
	public:
		explicit AVLTree(Tree* head = nullptr) :head(head){}
		explicit AVLTree(vector<int> data);

		AVLTree(AVLTree& ) = delete;
		AVLTree& operator=(AVLTree&) = delete;
		AVLTree(AVLTree&& tree);
		AVLTree& operator=(AVLTree&& tree);
		bool insert(int val);
		bool pop(int val);

		Tree* wʧ��ڵ�();
		bool w���Ƿ�ƽ��();
		void w����ƽ��();
		~AVLTree();

	};
	AVLTree* ����ƽ����();

}

void ����������();



#endif