#pragma once
#include "Tree.h"
#include <vector>
using std::vector;

namespace w¶þ²æÊ÷
{
	class RBTree
	{
	private:
		void _insert(Tree* &_head, int val);

	public:
		Tree* head;
		explicit RBTree(Tree* _head=nullptr):head(_head){}
		explicit RBTree(const vector<int>& arr);
		RBTree(RBTree&) = delete;
		RBTree& operator=(RBTree&) = delete;
		RBTree& operator=(RBTree&&);
		RBTree(RBTree&&);
		void insert(int val);
		~RBTree();
	};

}
