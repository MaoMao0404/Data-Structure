
//      ��������BTree.h
//      �����ܣ��������������������ҡ�ɾ���ȹ��ܵ�ʵ��
//      ���ߣ�ë�һ
//      ���ڣ�2021.11.18
//          

#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<queue>
#include"student.h"
using namespace std;

///////////////////////////////
////BinTreeNode�ṹ��Ķ���/////
///////////////////////////////

//���ṹ��
template<class T>
struct BinTreeNode
{
	T data;//������
	BinTreeNode<T>* leftchild, * rightchild;
	BinTreeNode(){leftchild = 0;rightchild = 0;}
	BinTreeNode<T>(T t , BinTreeNode<T>* l = 0, BinTreeNode<T>* r = 0) :data(t), leftchild(l), rightchild(r) {};
};


///////////////////////////////
////BinaryTree��Ķ���//////////
///////////////////////////////

//��������
template<class T>
class BinaryTree
{public:
	BinTreeNode<T>* root;//��ָ��
	BinaryTree() :root(0) {};//���캯��
	~BinaryTree() { destroy(root); }//��������
	BinTreeNode<T>* getroot()const { return root; }//ȡ��
	bool isempty() { return root == 0; }//�ж������Ƿ�Ϊ��
	
	void preorder(BinTreeNode<T>* subtree);//ǰ��������ȫ����Ϣ
	void inorder(BinTreeNode<T>* subtree);//����������ȫ����Ϣ
	void postorder(BinTreeNode<T>* subtree);//����������ȫ����Ϣ
	
 
	void destroy(BinTreeNode<T>*& subtree);//ɾ��
    //ɾ��Ԫ��
	void removenumber(BinTreeNode<T>* r, BinTreeNode<T>* pr, string number);//��ѧ��
	void removename(BinTreeNode<T>* r, BinTreeNode<T>* pr, string name);//������
	void removephone(BinTreeNode<T>* r, BinTreeNode<T>* pr, string phone);//���绰����


	bool insert(BinTreeNode<T>*& subtree, BinTreeNode<T>* p);//������Ԫ��
	//����
	void findnumber(BinTreeNode<T>* subtree, string number);//��ѧ��
	void findname(BinTreeNode<T>* subtree, string name);//������
	void findphone(BinTreeNode<T>* subtree, string phone);//���绰����

	void outmin(BinTreeNode<T>*subtree,BinTreeNode<T>* min);//���������С����Ϣ
	bool readfromfile();//���ļ�����
	
	bool writetofile(BinTreeNode<T>* subtree);//���ļ�д��



///////////////////////////////////
////��������BinaryTree���ʵ��/////
//////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
//  ������㺯��
//  �������ܣ��½�������
//����������
//       subtree ��ʾ�½����
//��������ֵ��
//       subtree �½���� 
	BinTreeNode<T>* creatNode(BinTreeNode<T>*& subtree)//�������
	{
		
		subtree= new BinTreeNode<T>();
		cout << "������ѧ����ѧ�š��������������ڡ����䡢�Ա𡢵绰����ַ" << endl;
		cin >> subtree->data.number >> subtree->data.name >> subtree->data.birthday
			>> subtree->data.age >> subtree->data.sex >> subtree->data.phone >> subtree->data.address;
		subtree->leftchild = 0;
		subtree->rightchild = 0;
		return subtree;
	}



//////////////////////////////////////////////////////////////////////////////
//  ���ҽ�㺯��
//  �������ܣ����Һ�̽��
//����������
//       subtree ��ʾ�����
//��������ֵ��
//       subtree ���ҵ��ĺ�̽��

	BinTreeNode<T>* findmin(BinTreeNode<T>* subtree)//���Һ�̽��
	{
		if (!subtree)
			return 0;
		else {
			if (!subtree->leftchild)
				return subtree;
			else {
				return findmin(subtree->leftchild);
			}
		}
	}



//////////////////////////////////////////////////////////////////////////////
//  ��������������
//  �������ܣ����ļ���ȡ��ν���������
//����������
//       subtree ��ʾ�����
//��������ֵ��
//       subtree �����
	
	BinTreeNode<T>* readfromfiletree(BinTreeNode<T>* subtree)
	{
		string number, name, b, age, sex, phone, add;
		fstream file("student.txt", ios::in);
		if (!file)
		{
			cout << "�ļ���ʧ��" << endl;
			
		}
		file >> number >> name >> b >> age >> sex >> phone >> add;

		queue<BinTreeNode<T>*>stu;
		subtree = new BinTreeNode<T>();
		file >> subtree->data.number >> subtree->data.name >> subtree->data.birthday
			>> subtree->data.age >> subtree->data.sex >> subtree->data.phone >> subtree->data.address;
		subtree->leftchild = 0;
		subtree->rightchild = 0;
		stu.push(subtree);//��������
		while (!stu.empty())
		{
			BinTreeNode<T>* temp = stu.front();//����Ԫ�س���
			stu.pop();
			BinTreeNode<T>* p;

			p = new BinTreeNode<T>();
			file >> p->data.number >> p->data.name >> p->data.birthday
				>> p->data.age >> p->data.sex >> p->data.phone >> p->data.address;
			p->leftchild = 0;
			p->rightchild = 0;//������
			if (p->data.number == "#")break;
			temp->leftchild = p;
			stu.push(p);

			p = new BinTreeNode<T>();
			file >> p->data.number >> p->data.name >> p->data.birthday
				>> p->data.age >> p->data.sex >> p->data.phone >> p->data.address;
			p->leftchild = 0;
			p->rightchild = 0;//������
			if (p->data.number == "#")break;
			temp->rightchild = p;
			stu.push(p);
		}
		return subtree;
	}

	
};



//////////////////////////////////////////////////////////////////////////////
//  �ļ�д�뺯��
//  �������ܣ���ѧ����Ϣд���ļ�
//����������
//       subtree ��ʾ�����
//��������ֵ��
//       true  ��ʾд��ɹ�
//       false ��ʾд��ʧ��
template<class T>
bool BinaryTree<T>::writetofile(BinTreeNode<T>* subtree)
{
	fstream file("student.txt", ios::out);
	if (!file)
	{
		cout << "�ļ���ʧ��" << endl;
		return false;
		
	}
	file << "ѧ��" << "     ����" << "        ��������" << "           ����" << "     �Ա�" << "        �绰����" << "        ��ַ" << endl;
	queue<BinTreeNode<T>*>q;
	BinTreeNode<T>* t = subtree;
	if (t != 0)
		q.push(t);
	while (!q.empty())
	{
		t = q.front();
		q.pop();
		file<< t->data.getnumber() << "          " << t->data.getname()
			<< "        " << t->data.getbirthday() << "         " << t->data.getage() << "        " << t->data.getsex()
			<< "          " << t->data.getphone() << "          " << t->data.getaddress() << endl;
		if (t->leftchild != 0)
			q.push(t->leftchild);
		if (t->rightchild != 0)
			q.push(t->rightchild);
	}
	file << "#" << " #" << " #" << " #" << " #" << " #" << " #" << endl;
	return true;
}



//////////////////////////////////////////////////////////////////////////////
//  ���Һ���
//  �������ܣ�����������Сѧ��
//����������
//       subtree ��ʾ�����
//       min     ��ʾ������Сѧ�����
//��������ֵ��
//       ��
template<class T>
void BinaryTree<T>::outmin(BinTreeNode<T>* subtree,BinTreeNode<T>*min)
{
	if (subtree != 0)
	{
		if (subtree->data.age<min->data.age)  
			min = subtree;
		outmin(subtree->leftchild, min);
		outmin(subtree->rightchild, min);
	}
}



//////////////////////////////////////////////////////////////////////////////
//  ���뺯��
//  �������ܣ����½�ѧ�������������
//����������
//       subtree ��ʾ�����
//       p       ��ʾ����Ľ��
//��������ֵ��
//       subtree �����
template<class T>
bool BinaryTree<T>::insert(BinTreeNode<T>*& subtree,BinTreeNode<T>*p)
{
		if (root == 0)
		{
			creatNode(p);
			root = p;
		}
		else
		{
			queue<BinTreeNode<T>*>stu;
			stu.push(root);
			BinTreeNode<T>* temp;
			while (!stu.empty())
			{
				temp = stu.front();
				stu.pop();
				if (temp->leftchild != 0)
					stu.push(temp->leftchild);
				else//˵�����ڴ˽�������������
				{
					creatNode(p);
					temp->leftchild = p;
					break;
				}
				if (temp->rightchild != 0)
					stu.push(temp->rightchild);
				else//˵�����ڴ˽�������������
				{
					creatNode(p);
					temp->rightchild = p;
					break;
				}
			}
		}
		return subtree;
}



//////////////////////////////////////////////////////////////////////////////
//  �ļ���ȡ����
//  �������ܣ����ļ��е�ѧ����Ϣ����
//����������
//       ��
//��������ֵ��
//       ��


template<class T>
bool BinaryTree<T>::readfromfile()
{
	fstream file("student.txt", ios::in);
	if (!file)
	{
		cout << "�ļ���ʧ��" << endl;
		return false;
	}
	char c[1000];
	while (!file.eof())
	{
		file.getline(c, sizeof(c));
		cout << c << endl;
	}
}



//////////////////////////////////////////////////////////////////////////////
//  ɾ������
//  �������ܣ��ֱ�ѧ�š��������绰����ɾ��ѧ����Ϣ
//����������
//      r       ��ʾ�������
//      pr      ��ʾǰ�����
//      number  ��ʾ���ҵ�ѧ��
//      phone   ��ʾ���ҵĵ绰��
//      name    ��ʾ���ҵ�����
//��������ֵ��
//       ��

//ɾ��
template<class T>
void BinaryTree<T>::removenumber(BinTreeNode<T>* r,BinTreeNode<T>*pr, string number)//��ѧ��
{
	if (r != 0)
	{
		removenumber(r->leftchild,r, number);
		if (r->data.getnumber() == number)
		{
			if (r->leftchild && r->rightchild)
			{
				BinTreeNode<T>* s = findmin(r->leftchild);
				r->data = s->data;
				removenumber(r->rightchild, r, s->data.number);
			}
			else
			{
				if (pr == 0)
				{
					if (r->leftchild != 0)
						r = r->leftchild;
					else
						r = r->rightchild;
				}
				else
				{
					if (r == pr->leftchild)
					{
						if (r->leftchild != 0)
							pr->leftchild = r->leftchild;
						else
							pr->leftchild = r->rightchild;
					}
					else
					{
						if (r->leftchild != 0)
							pr->rightchild = r->leftchild;
						else
							pr->rightchild = r->rightchild;
					}
				}
			}
		}
		removenumber(r->rightchild,r, number);
	}
}

template<class T>
void BinaryTree<T>::removephone(BinTreeNode<T>* r, BinTreeNode<T>* pr, string phone)//���绰��
{
	if (r != 0)
	{
		removephone(r->leftchild, r, phone);
		if (r->data.getphone() == phone)
		{
			if (r->leftchild && r->rightchild)
			{
				BinTreeNode<T>* s = findmin(r->leftchild);
				r->data = s->data;
				removephone(r->rightchild, r, s->data.phone);
			}
			else
			{
				if (pr == 0)
				{
					if (r->leftchild != 0)
						r = r->leftchild;
					else
						r = r->rightchild;
				}
				else
				{
					if (r == pr->leftchild)
					{
						if (r->leftchild != 0)
							pr->leftchild = r->leftchild;
						else
							pr->leftchild = r->rightchild;
					}
					else
					{
						if (r->leftchild != 0)
							pr->rightchild = r->leftchild;
						else
							pr->rightchild = r->rightchild;
					}
				}
			}
		}
		removenumber(r->rightchild, r, phone);
	}
}


template<class T>
void BinaryTree<T>::removename(BinTreeNode<T>* r, BinTreeNode<T>* pr,string name)//������
{
	if (r != 0)
	{
		removename(r->leftchild, r, name);
		if (r->data.getname() == name)
		{
			if (r->leftchild && r->rightchild)
			{
				BinTreeNode<T>* s = findmin(r->leftchild);
				r->data = s->data;
				removename(r->rightchild, r, s->data.name);
			}
			else
			{
				if (pr == 0)
				{
					if (r->leftchild != 0)
						r = r->leftchild;
					else
						r = r->rightchild;
				}
				else
				{
					if (r == pr->leftchild)
					{
						if (r->leftchild != 0)
							pr->leftchild = r->leftchild;
						else
							pr->leftchild = r->rightchild;
					}
					else
					{
						if (r->leftchild != 0)
							pr->rightchild = r->leftchild;
						else
							pr->rightchild = r->rightchild;
					}
				}
			}
		}
		removenumber(r->rightchild, r, name);
	}
}



//////////////////////////////////////////////////////////////////////////////
//  ���Һ���
//  �������ܣ��ֱ�ѧ�š��������绰�������ѧ����Ϣ
//����������
//      r       ��ʾ�������
//      pr      ��ʾǰ�����
//      number  ��ʾ���ҵ�ѧ��
//      phone   ��ʾ���ҵĵ绰��
//      name    ��ʾ���ҵ�����
//��������ֵ��
//       ��

//����
template<class T>
void BinaryTree<T>::findnumber(BinTreeNode<T>* subtree, string number)//��ѧ��
{
	if (subtree != 0)
	{
		findnumber(subtree->leftchild, number);
		if (subtree->data.getnumber() == number)
		{
			cout << "���ҵ���ѧ����Ϣ��" << endl;
			cout << "ѧ�ţ�" << subtree->data.getnumber() << "������" << subtree->data.getname()
				<< "�������ڣ�" << subtree->data.getbirthday() << "���䣺" << subtree->data.getage() << "�Ա�" << subtree->data.getsex()
				<< "�绰��" << subtree->data.getphone() << "��ַ��" << subtree->data.getaddress() << endl;
		}
		
		findnumber(subtree->rightchild, number);
	}
}

template<class T>
void BinaryTree<T>::findname(BinTreeNode<T>* subtree, string name)//������
{
	if (subtree != 0)
	{
		findnumber(subtree->leftchild, name);
		if (subtree->data.getname() == name)
		{
			cout << "���ҵ���ѧ����Ϣ��" << endl;
			cout << "ѧ�ţ�" << subtree->data.getnumber() << "������" << subtree->data.getname()
				<< "�������ڣ�" << subtree->data.getbirthday() << "���䣺" << subtree->data.getage() << "�Ա�" << subtree->data.getsex()
				<< "�绰��" << subtree->data.getphone() << "��ַ��" << subtree->data.getaddress() << endl;
		}
		
		findnumber(subtree->rightchild, name);
	}

}

template<class T>
void BinaryTree<T>::findphone(BinTreeNode<T>* subtree, string phone)//���绰����
{
	if (subtree != 0)
	{
		findnumber(subtree->leftchild, phone);
		if (subtree->data.getphone() == phone)
		{
			cout << "���ҵ���ѧ����Ϣ��" << endl;
			cout << "ѧ�ţ�" << subtree->data.getnumber() << "������" << subtree->data.getname()
				<< "�������ڣ�" << subtree->data.getbirthday() << "���䣺" << subtree->data.getage() << "�Ա�" << subtree->data.getsex()
				<< "�绰��" << subtree->data.getphone() << "��ַ��" << subtree->data.getaddress() << endl;
		}
		
		findnumber(subtree->rightchild, phone);
	}
}




//////////////////////////////////////////////////////////////////////////////
//  ɾ������
//  �������ܣ�ɾ���ͷ�������
//����������
//       subtree ��ʾ�����
//��������ֵ��
//       ��
template<class T>
void BinaryTree<T>::destroy(BinTreeNode<T>*& subtree)//ɾ��
{
	if (subtree != 0)
	{
		destroy(subtree->leftchild);
		destroy(subtree->rightchild);
		delete subtree;
	}
}



//////////////////////////////////////////////////////////////////////////////
//  ��������
//  �������ܣ��ֱ�ǰ�� ���� ������������
//����������
//       subtree ��ʾ�����
//��������ֵ��
//       ��

template<class T>
void BinaryTree<T>::preorder(BinTreeNode<T>*subtree)//ǰ��������
{
	if (subtree != 0)
	{
		cout << "ѧ�ţ�" << subtree->data.getnumber() << "������" << subtree->data.getname()
			<< "�������ڣ�" << subtree->data.getbirthday() << "���䣺" << subtree->data.getage() << "�Ա�" << subtree->data.getsex()
			<< "�绰��" << subtree->data.getphone() << "��ַ��" << subtree->data.getaddress() << endl;
		preorder(subtree->leftchild);
		preorder(subtree->rightchild);
	}
}

template<class T>
void BinaryTree<T>::inorder(BinTreeNode<T>* subtree)//����������
{
	if (subtree != 0)
	{
		inorder(subtree->leftchild);
		cout << "ѧ�ţ�" << subtree->data.getnumber() << "������" << subtree->data.getname()
			<< "�������ڣ�" << subtree->data.getbirthday() << "���䣺" << subtree->data.getage() << "�Ա�" << subtree->data.getsex()
			<< "�绰��" << subtree->data.getphone() << "��ַ��" << subtree->data.getaddress() << endl;
		inorder(subtree->rightchild);
	}
}

template<class T>
void BinaryTree<T>::postorder(BinTreeNode<T>* subtree)//����������
{
	if (subtree != 0)
	{
		postorder(subtree->leftchild);
		postorder(subtree->rightchild);
		cout << "ѧ�ţ�" << subtree->data.getnumber() << "������" << subtree->data.getname()
			<< "�������ڣ�" << subtree->data.getbirthday() << "���䣺" << subtree->data.getage() << "�Ա�" << subtree->data.getsex()
			<< "�绰��" << subtree->data.getphone() << "��ַ��" << subtree->data.getaddress() << endl;
	}
}