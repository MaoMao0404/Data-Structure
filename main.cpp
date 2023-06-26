
//      程序名：main.cpp
//      程序功能：main函数的功能是实现与用户的交互，显示主菜单，然后根据用户的选择调用相关的函数实现相应的系统功能
//      作者：毛婧一
//      日期：2021.11.18
//          

#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#include"BTree.h"
#include"student.h"

/////////////////////////
/////// 主函数  /////////
//参数返回值：0
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
		cout << "欢迎进入学生通讯录管理系统" << endl;
		cout << "1.新建学生通讯录" << endl;
		cout << "2.向学生通讯录插入学生信息" << endl;
		cout << "3.按学号查询学生信息" << endl;
		cout << "4.按姓名查询学生信息" << endl;
		cout << "5.按电话号码查询学生信息" << endl;
		cout << "6.删除学生信息" << endl;
		cout << "7.输出年龄最小的学生信息" << endl;
		cout << "8.输出全部学生信息" << endl;
		cout << "9.从文件中读取通讯录信息" << endl;
		cout << "10.向文件写入学生通讯录信息" << endl;
		cout << "11.退出" << endl;
		cout << endl;
		cout << "输入选择的项目:" << endl;
		cin >> c;


		/////////////////////////////////////
		////  接下来是新建学生通讯录
		/////////////////////////////////////
		if (c == 1)
		{
			if (flag)
			{
				cout << "已经完成新建表，请选择其它选项" << endl;
				goto in;
			}
			flag = true;
			B.root = B.readfromfiletree(subtree);
			cout << "学生通讯录已新建完成!" << endl;
			B.preorder(B.root);
			goto in;
		}


		/////////////////////////////////////
		////  接下来是向通讯录中插入学生信息
		/////////////////////////////////////
		if (c == 2)
		{
			B.insert(B.root, p);
			goto in;
		}


		/////////////////////////////////////
		////  接下来是按学号查找信息
		/////////////////////////////////////
		if (c == 3)
		{
			cout << "请输入要查找学生的学号:" << endl;
			cin >> number;
			B.findnumber(B.root, number);
			goto in;
		}


		/////////////////////////////////////
		////  接下来是按姓名查找信息
		/////////////////////////////////////
		if (c == 4)
		{
			cout << "请输入要查找学生的姓名" << endl;
			cin >> name;
			B.findname(B.root, name);
			goto in;
		}


		/////////////////////////////////////
		////  接下来是按电话号码查找信息
		/////////////////////////////////////
		if (c == 5)
		{
			cout << "请输入要查找学生的电话号码" << endl;
			cin >> phone;
			B.findnumber(B.root, phone);
			goto in;
		}



		/////////////////////////////////////
		////  接下来是删除学生信息
		/////////////////////////////////////
		if (c == 6)
		{
			cout << "请选择删除学生信息的查找方式" << endl;
			cout << "1.按学号查找删除 2.按姓名查找删除 3.按电话号码查找删除" << endl;
			cin >> c1;

			if (c1 == 1)
			{
				BinTreeNode<student>* pr = new BinTreeNode<student>;
				cout << "请输入要删除学生的学号" << endl;
				cin >> number;
				B.removenumber(B.root,pr, number);
				goto in;

			}
			
			if (c1 == 2)
			{
				BinTreeNode<student>* pr = new BinTreeNode<student>;
				cout << "请输入要删除学生的姓名" << endl;
				cin >> name;
				B.removename(B.root,pr, name);
				goto in;

			}
			
			if (c1 == 3)
			{
				BinTreeNode<student>* pr = new BinTreeNode<student>;
				cout << "请输入要删除学生的电话号码" << endl;
				cin >> phone;
				B.removephone(B.root,pr, number);
				goto in;

			}
			
		}



		/////////////////////////////////////
		////  接下来是查找年龄最小的学生
		/////////////////////////////////////
		if (c == 7)
		{
			minnode = B.root;
			B.outmin(B.root, minnode);
			cout << "学号：" << minnode->data.getnumber() << "姓名：" << minnode->data.getname()
				<< "出生日期：" << minnode->data.getbirthday() << "年龄：" << minnode->data.getage() << "性别：" << minnode->data.getsex()
				<< "电话：" << minnode->data.getphone() << "地址：" << minnode->data.getaddress() << endl;
			goto in;
		}


		/////////////////////////////////////
		////  接下来是遍历并输出所有学生的信息
		/////////////////////////////////////
		if (c == 8)
		{
			cout << "请选择输出学生信息的遍历方式" << endl;
			cout << "1.前序遍历 2.中序遍历 3.后序遍历" << endl;
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
		////  接下来是从文件中读取信息
		/////////////////////////////////////
		if (c == 9)
		{
			B.readfromfile();
		}


		/////////////////////////////////////
		////  接下来是保存学生信息到文件
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