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
	using w������::Tree;
	inline bool û������(Tree* top)
	{
		return top->left == nullptr && top->right == nullptr;
	}
	inline bool �Ƿ�ֻ������(Tree* top)
	{
		return top->left != nullptr && top->right == nullptr;
	}
	inline bool �Ƿ�ֻ������(Tree* top)
	{
		return top->left == nullptr && top->right != nullptr;
	}
	inline bool ������������(Tree* top)
	{
		return top->left != nullptr && top->right != nullptr;
	}
	bool ��һ���ӽڵ�(Tree* top)
	{
		return �Ƿ�ֻ������(top) || �Ƿ�ֻ������(top);
	}
}
namespace w������
{
	Tree* AVLTree::_��ʼ�����������(const vector<int>& data, int lIndex, int rIndex)
	{
		if (lIndex > rIndex) return nullptr;
		int mIndex = (lIndex + rIndex) / 2;
		Tree* head = new Tree(data[mIndex]);
		//head->row = mIndex;
		head->left = _��ʼ�����������(data, lIndex, mIndex - 1);
		head->right = _��ʼ�����������(data, mIndex + 1, rIndex);
		return head;
	}


	bool AVLTree::_��ӽڵ�(Tree* _head, int val)
	{
		if (_head->val == val)
		{
			state = w״̬::ƽ���;
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
			wˢ��ÿ���ڵ�ĸ߶�(head);
			state = w״̬::�����δƽ��;
			return true; //������Ҫ����ƽ��
		}
		else
			_��ӽڵ�(*temp, val);
	}
	// 1���ҵ��ڵ�˵������ƽ��, ��ʱ ʧ��㲻����nullptr
	// 2����ƽ���һ���ڸ��ڵ㵽���������·����
	// �������ֻ�ʺϲ������ݵĺ󣬲ο��������Ƿ�ƽ�⣬רΪinsert�������������������ܵ���

	/// <summary>
	/// 
	/// </summary>
	/// <param name="val">�е�������ʧ��ڵ�һ���ڸ��ڵ��val֮��</param>
	/// <returns>����nullptr˵����ǰ�Ѿ���ƽ����</returns>
	Tree* AVLTree::_������ʧ��ڵ�_insert(int val)
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
			if (re == nullptr && !w�����ڵ��Ƿ�ƽ��(_head))
				re = _head;
		};
		func(head);
		return re;
	}

	bool AVLTree::w�����ڵ��Ƿ�ƽ��(Tree* p)
	{
		if (û������(p))
			return true;
		if (������������(p))
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

	// ����ͨ�ð棬���������и��Ӷȸ��͵ķ�����������Ҫ������Ҳ���ǲ���ֵval��ʧ��ڵ㳯��val��
	//����
	
	/// <summary>
	/// ����֮ǰ��Ҫ����_ˢ��ÿ���ڵ�ĸ߶�
	/// </summary>
	/// <param name="_head">�߶���͵�ʧ��ڵ�</param>
	void AVLTree::_������_ƽ��(Tree* _head)
	{
		if (state == w״̬::ƽ���)
			return;
		//Tree* _head = _���ʧ��ڵ�_insert(val);
		if (_head == nullptr) return;
		Tree* temp = _head;
		vector<Tree*> vt1(3, nullptr);
		vector<Tree*> vt2;
		vt1[0] = temp;
		size_t i = 1;
		//_ˢ��ÿ���ڵ�ĸ߶�(head);
		for (; i < 3; i++)
		{
			if (������������(temp))
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
			// �����ʧ��ڵ㣬��ǰѭ���֣��������tempΪҶ�ӵ����
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
		//��vt1��������
		_sort_tree(vt1);
		// *ʧ��� ���� vt1�м��value
		std::swap(_head->val, vt1[1]->val); //��ʱvt1�ֱ�����
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
		qDebug() << "����ƽ�����";
		wˢ��ÿ���ڵ�ĸ߶�(head);
	}

	/// <summary>
	/// ֻ��ɾ������ƽ�⣬����Ϊ������������ĳЩ����������������������Ҫ2��ƽ�⣬
	/// 1���Ҳ����ڵ㣬����false
	/// 
	/// </summary>
	/// <param name="val">ɾ����ֵ</param>
	/// <param name="father_ptr">����ǵڶ�������ֵ����ƽ������ʱ��ʹ�ã����Ϊnullptr�������к���ƽ��</param>
	/// <returns>�Ƿ����ɹ�</returns>
	bool AVLTree::_ɾ���ڵ�(int val)
	{
		//Tree*& _head = _���ָ��ֵ�Ľڵ�(head, val); //_head��Ҫ��ɾ���ڵ�
		Tree* father = _���ָ��ֵ�ĸ��ڵ�(head, val);
		if (father == nullptr)
		{
			qDebug() << "û���ҵ�Ҫɾ���Ľڵ�";
			del_front = nullptr;
			state = w״̬::ƽ���;
			return false; //û���ҵ��ڵ�
		}

		if (father == head)
		{
			if (û������(father))//����������������Ҫɾ����������ͷ�ڵ㣬��������ֻ��һ���ڵ�
			{
				free(head);
				head = nullptr;
				qDebug() << "ɾ������ͷ�ڵ㣬�Ѿ�ɾ�����������ڽڵ���";
				state = w״̬::ƽ���;
				del_front = nullptr;
				return true;
			}
		}
		state = w״̬::ɾ����δƽ��;
		// _head ��Ҫɾ���Ľڵ� ��֮��ÿ���ڵ�ĸ߶Ȼᷢ���任
		Tree*& _head = father->val > val ? father->left : father->right;
		//�ڵ� û���ӽڵ�
		if (û������(_head)) 
		{
			free(_head);
			_head = nullptr;
		}
		else if (������������(_head)) //�����ӽڵ㶼��
		{
			int leftH = _head->left->height;
			int rightH = _head->right->height;
			if (leftH - rightH >= 0) //��ߴ������ұߣ�ȡ������������Ľڵ��Ȼû�����ӽڵ�
			{						//��Ϊ������Ƕ������������ҵ��������������val����_head����						//�����������������ĸ��ڵ��������
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
			else //��������ȸ��� ���ұ���С�Ľڵ�
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
		else // �Ƴ�����һ������,������ƽ��������������������ӽڵ㣬ֱ��free����������
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
		del_front = father; // �ڶ�������ֵ
		wˢ��ÿ���ڵ�ĸ߶�(head);
		return true;
	}

	void AVLTree::_ɾ���ڵ�_ƽ��()
	{

		if (state != w״̬::ɾ����δƽ��)
			return;
		//�����ʧ��ڵ㣬del_front
		if (w�����ڵ��Ƿ�ƽ��(del_front))
		{
			state = w״̬::ƽ���;
			return;
		}
		_������_ƽ��(del_front);
		//���del_front�ĸ��ڵ�
		 Tree* ptr = _���ָ��ֵ�ĸ��ڵ�(head, del_front->val);
		//һ�κ�һ��ƽ�⣬�����ƽ�⣬���ƽ�����Ǹ��ڵ�
		if (!w�����ڵ��Ƿ�ƽ��(ptr))
		{
			_������_ƽ��(ptr);
		}
		state = w״̬::ƽ���;
	}



	void AVLTree::_sort_tree(vector<Tree*>& vt1)
	{
		if (vt1[0]->val > vt1[1]->val) std::swap(vt1[0], vt1[1]);
		if (vt1[1]->val > vt1[2]->val) std::swap(vt1[1], vt1[2]);
		if (vt1[0]->val > vt1[1]->val) std::swap(vt1[0], vt1[1]);
	}

	Tree*& AVLTree::_���ָ��ֵ�Ľڵ�(Tree*& _head, int val)
	{
		if (_head == nullptr)
			return _head;
		if (_head->val == val)
			return _head;
		if (_head->val > val)
			_���ָ��ֵ�Ľڵ�(_head->left, val);
		else
			_���ָ��ֵ�Ľڵ�(_head->right, val);
	}

	/// <summary>
	/// ���Ǹ���������_ɾ���ڵ��е��ã�������������ڵ�û�и��ڵ㣬����head�����õط�Ҳ����������⴦��
	/// </summary>
	/// <param name="_head">�ⲿ����ֻ�ܴ���head��</param>
	/// <param name="val">ָ����ֵ</param>
	/// <returns>����nullptr˵��������û��val������head˵��val��ͷ�ڵ㣬�����������</returns>
	Tree* AVLTree::_���ָ��ֵ�ĸ��ڵ�(Tree* _head, int val)
	{
		if (_head == nullptr) return _head;
		Tree** child = nullptr;
		if (_head->val > val)
			child = &_head->left;
		else if (_head->val < val)
			child = &_head->right;
		else
			return _head; //����һ�У����ڵ��ֵ����val�����ڵ�û�и��ڵ㣬���ظ��ڵ�
		if (*child != nullptr)
		{
			if ((*child)->val == val)
			{
				qDebug("%d �ĸ��ڵ��ֵ�� %d", val,_head->val);
				return _head;
			}
			else
			{
				return _���ָ��ֵ�ĸ��ڵ�(*child, val);
			}
		}
		return nullptr;
	}

	void AVLTree::w����ƽ��()
	{
		Tree* ptr = nullptr;
		switch (state)
		{
		case w������::AVLTree::w״̬::ƽ���:
			break;
		case w������::AVLTree::w״̬::�����δƽ��:
			ptr = _������ʧ��ڵ�_insert(m_val);
			_������_ƽ��(ptr);
			break;
		case w������::AVLTree::w״̬::ɾ����δƽ��:
			_ɾ���ڵ�_ƽ��();
			break;
		default:
			break;
		}
		//_��������
		state = w״̬::ƽ���;
	}
	AVLTree::AVLTree(vector<int> data):AVLTree()
	{
		std::sort(data.begin(), data.end());
		int rIndex = data.size() - 1;
		head = _��ʼ�����������(data, 0, rIndex); //��һ���Ѿ��ռ��˺�����
		//_�����ڵ�������(head);
		state = w״̬::ƽ���;
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

	//û�н���ƽ��
	bool AVLTree::insert(int val)
	{
		m_val = val;
		bool flag = _��ӽڵ�(head, val);
		//state = ״̬::�����δƽ��;
		if (flag)
		{
			qDebug() << "����������ɹ�";
		}
		else
		{
			qDebug() << "���������Ѿ������ֵ�ˣ�����Ҫ����";
		}
		return flag;
	}

	// ֻ��ɾ����û��ƽ��
	bool AVLTree::pop(int val)
	{
		m_val = val;
		bool flag = _ɾ���ڵ�(val);
		return flag;
	}

	Tree* AVLTree::wʧ��ڵ�()
	{
		Tree* ptr = nullptr;
		//_��������(head);
		switch (state)
		{
		case w������::AVLTree::w״̬::ƽ���:
			break;
		case w������::AVLTree::w״̬::�����δƽ��:
			ptr =_������ʧ��ڵ�_insert(m_val);
			break;
		case w������::AVLTree::w״̬::ɾ����δƽ��:
			if (!w�����ڵ��Ƿ�ƽ��(del_front))
				ptr = del_front;
			break;
		default:
			break;

		}
		return ptr;
	}

	bool AVLTree::w���Ƿ�ƽ��()
	{
		
		switch (state)
		{
		case w������::AVLTree::w״̬::ƽ���:
			return true;
		case w������::AVLTree::w״̬::�����δƽ��:
			//auto ptr = _������ʧ��ڵ�(m_val);
			if (_������ʧ��ڵ�_insert(m_val) == nullptr)
			{
				state = w״̬::ƽ���;
				return true;
			}
			return false;
		case w������::AVLTree::w״̬::ɾ����δƽ��:
			if (w�����ڵ��Ƿ�ƽ��(del_front))
			{
				state = w״̬::ƽ���;
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



	AVLTree* ����ƽ����()
	{
		//vector<int> ����������ظ���(int size);
		//vector<int> arr = ����������ظ���(10); // ���һ��sizeΪ11��vector

		vector<int> arr{ 5,40,43,51,55,65,70,83,96,100 };

		AVLTree* _head = new AVLTree(arr);
		qDebug() << "�������";
		_head->head->w�������();
		return _head;
		//delete head;
	}
}

void ����������()
{
	using namespace w������;

	AVLTree* av = ����ƽ����();
	av->insert(1);
	av->head->w�㼶����();
	qDebug() << "���� 50 ��" ;
	av->insert(50);
	av->head->w�㼶����();
	qDebug() << "++++++++++++++++";
}