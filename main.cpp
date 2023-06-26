
//      ��������main.cpp
//      �����ܣ�main�����Ĺ�����ʵ�����û��Ľ�������ʾ���˵���Ȼ������û���ѡ�������صĺ���ʵ����Ӧ��ϵͳ����
//      ���ߣ�ë�һ
//      ���ڣ�2021.11.18
//          

#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#include"BTree.h"
#include"student.h"

/////////////////////////
/////// ������  /////////
//��������ֵ��0
int main()
{
	BinTreeNode<student> n;
	BinaryTree<student> B;
	BinTreeNode<student>* subtree=0;
	BinTreeNode<student>* p=0;
	BinTreeNode<student>* minnode = new BinTreeNode<student>;
	bool flag = false;
	bool flag1 = false;
	int c = 0;
	int c1 = 0;
	string number, name, phone;
	
	while (1)
	{
		in:
		cout << "��ӭ����ѧ��ͨѶ¼����ϵͳ" << endl;
		cout << "1.�½�ѧ��ͨѶ¼" << endl;
		cout << "2.��ѧ��ͨѶ¼����ѧ����Ϣ" << endl;
		cout << "3.��ѧ�Ų�ѯѧ����Ϣ" << endl;
		cout << "4.��������ѯѧ����Ϣ" << endl;
		cout << "5.���绰�����ѯѧ����Ϣ" << endl;
		cout << "6.ɾ��ѧ����Ϣ" << endl;
		cout << "7.���������С��ѧ����Ϣ" << endl;
		cout << "8.���ȫ��ѧ����Ϣ" << endl;
		cout << "9.���ļ��ж�ȡͨѶ¼��Ϣ" << endl;
		cout << "10.���ļ�д��ѧ��ͨѶ¼��Ϣ" << endl;
		cout << "11.�˳�" << endl;
		cout << endl;
		cout << "����ѡ�����Ŀ:" << endl;
		cin >> c;


		/////////////////////////////////////
		////  ���������½�ѧ��ͨѶ¼
		/////////////////////////////////////
		if (c == 1)
		{
			if (flag)
			{
				cout << "�Ѿ�����½�����ѡ������ѡ��" << endl;
				goto in;
			}
			flag = true;
			B.root = B.readfromfiletree(subtree);
			cout << "ѧ��ͨѶ¼���½����!" << endl;
			B.preorder(B.root);
			goto in;
		}


		/////////////////////////////////////
		////  ����������ͨѶ¼�в���ѧ����Ϣ
		/////////////////////////////////////
		if (c == 2)
		{
			B.insert(B.root, p);
			goto in;
		}


		/////////////////////////////////////
		////  �������ǰ�ѧ�Ų�����Ϣ
		/////////////////////////////////////
		if (c == 3)
		{
			cout << "������Ҫ����ѧ����ѧ��:" << endl;
			cin >> number;
			B.findnumber(B.root, number);
			goto in;
		}


		/////////////////////////////////////
		////  �������ǰ�����������Ϣ
		/////////////////////////////////////
		if (c == 4)
		{
			cout << "������Ҫ����ѧ��������" << endl;
			cin >> name;
			B.findname(B.root, name);
			goto in;
		}


		/////////////////////////////////////
		////  �������ǰ��绰���������Ϣ
		/////////////////////////////////////
		if (c == 5)
		{
			cout << "������Ҫ����ѧ���ĵ绰����" << endl;
			cin >> phone;
			B.findnumber(B.root, phone);
			goto in;
		}



		/////////////////////////////////////
		////  ��������ɾ��ѧ����Ϣ
		/////////////////////////////////////
		if (c == 6)
		{
			cout << "��ѡ��ɾ��ѧ����Ϣ�Ĳ��ҷ�ʽ" << endl;
			cout << "1.��ѧ�Ų���ɾ�� 2.����������ɾ�� 3.���绰�������ɾ��" << endl;
			cin >> c1;

			if (c1 == 1)
			{
				BinTreeNode<student>* pr = new BinTreeNode<student>;
				cout << "������Ҫɾ��ѧ����ѧ��" << endl;
				cin >> number;
				B.removenumber(B.root,pr, number);
				goto in;

			}
			
			if (c1 == 2)
			{
				BinTreeNode<student>* pr = new BinTreeNode<student>;
				cout << "������Ҫɾ��ѧ��������" << endl;
				cin >> name;
				B.removename(B.root,pr, name);
				goto in;

			}
			
			if (c1 == 3)
			{
				BinTreeNode<student>* pr = new BinTreeNode<student>;
				cout << "������Ҫɾ��ѧ���ĵ绰����" << endl;
				cin >> phone;
				B.removephone(B.root,pr, number);
				goto in;

			}
			
		}



		/////////////////////////////////////
		////  �������ǲ���������С��ѧ��
		/////////////////////////////////////
		if (c == 7)
		{
			minnode = B.root;
			B.outmin(B.root, minnode);
			cout << "ѧ�ţ�" << minnode->data.getnumber() << "������" << minnode->data.getname()
				<< "�������ڣ�" << minnode->data.getbirthday() << "���䣺" << minnode->data.getage() << "�Ա�" << minnode->data.getsex()
				<< "�绰��" << minnode->data.getphone() << "��ַ��" << minnode->data.getaddress() << endl;
			goto in;
		}


		/////////////////////////////////////
		////  �������Ǳ������������ѧ������Ϣ
		/////////////////////////////////////
		if (c == 8)
		{
			cout << "��ѡ�����ѧ����Ϣ�ı�����ʽ" << endl;
			cout << "1.ǰ����� 2.������� 3.�������" << endl;
			cin >> c1;
			if (c1 == 1)
			{
				B.preorder(B.root);
				goto in;
			}
			
			if (c1 == 2)
			{
				B.inorder(B.root);
				goto in;
			}
			
			if (c1 == 3)
			{
				B.postorder(B.root);
				goto in;
			}
			
		}


		/////////////////////////////////////
		////  �������Ǵ��ļ��ж�ȡ��Ϣ
		/////////////////////////////////////
		if (c == 9)
		{
			B.readfromfile();
		}


		/////////////////////////////////////
		////  �������Ǳ���ѧ����Ϣ���ļ�
		/////////////////////////////////////
		if (c == 10)
		{
			
			B.writetofile(B.root);
		}
		if (c == 11)
			break;
	}
	
	return 0;
}