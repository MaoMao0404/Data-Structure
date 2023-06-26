
//      程序名：BTree.h
//      程序功能：建立二叉树及其他查找、删除等功能的实现
//      作者：毛婧一
//      日期：2021.11.18
//          

#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<queue>
#include"student.h"
using namespace std;

///////////////////////////////
////BinTreeNode结构体的定义/////
///////////////////////////////

//结点结构类
template<class T>
struct BinTreeNode
{
	T data;//数据域
	BinTreeNode<T>* leftchild, * rightchild;
	BinTreeNode(){leftchild = 0;rightchild = 0;}
	BinTreeNode<T>(T t , BinTreeNode<T>* l = 0, BinTreeNode<T>* r = 0) :data(t), leftchild(l), rightchild(r) {};
};


///////////////////////////////
////BinaryTree类的定义//////////
///////////////////////////////

//二叉树类
template<class T>
class BinaryTree
{public:
	BinTreeNode<T>* root;//根指针
	BinaryTree() :root(0) {};//构造函数
	~BinaryTree() { destroy(root); }//析构函数
	BinTreeNode<T>* getroot()const { return root; }//取根
	bool isempty() { return root == 0; }//判二叉树是否为空
	
	void preorder(BinTreeNode<T>* subtree);//前序遍历输出全部信息
	void inorder(BinTreeNode<T>* subtree);//中序遍历输出全部信息
	void postorder(BinTreeNode<T>* subtree);//后序遍历输出全部信息
	
 
	void destroy(BinTreeNode<T>*& subtree);//删除
    //删除元素
	void removenumber(BinTreeNode<T>* r, BinTreeNode<T>* pr, string number);//按学号
	void removename(BinTreeNode<T>* r, BinTreeNode<T>* pr, string name);//按姓名
	void removephone(BinTreeNode<T>* r, BinTreeNode<T>* pr, string phone);//按电话号码


	bool insert(BinTreeNode<T>*& subtree, BinTreeNode<T>* p);//插入新元素
	//查找
	void findnumber(BinTreeNode<T>* subtree, string number);//按学号
	void findname(BinTreeNode<T>* subtree, string name);//按姓名
	void findphone(BinTreeNode<T>* subtree, string phone);//按电话号码

	void outmin(BinTreeNode<T>*subtree,BinTreeNode<T>* min);//输出年龄最小的信息
	bool readfromfile();//从文件读出
	
	bool writetofile(BinTreeNode<T>* subtree);//向文件写入



///////////////////////////////////
////接下来是BinaryTree类的实现/////
//////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
//  建立结点函数
//  函数功能：新建插入结点
//函数参数：
//       subtree 表示新建结点
//参数返回值：
//       subtree 新建结点 
	BinTreeNode<T>* creatNode(BinTreeNode<T>*& subtree)//建立结点
	{
		
		subtree= new BinTreeNode<T>();
		cout << "请输入学生的学号、姓名、出生日期、年龄、性别、电话、地址" << endl;
		cin >> subtree->data.number >> subtree->data.name >> subtree->data.birthday
			>> subtree->data.age >> subtree->data.sex >> subtree->data.phone >> subtree->data.address;
		subtree->leftchild = 0;
		subtree->rightchild = 0;
		return subtree;
	}



//////////////////////////////////////////////////////////////////////////////
//  查找结点函数
//  函数功能：查找后继结点
//函数参数：
//       subtree 表示根结点
//参数返回值：
//       subtree 查找到的后继结点

	BinTreeNode<T>* findmin(BinTreeNode<T>* subtree)//查找后继结点
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
//  建立二叉树函数
//  函数功能：从文件读取层次建立二叉树
//函数参数：
//       subtree 表示根结点
//参数返回值：
//       subtree 根结点
	
	BinTreeNode<T>* readfromfiletree(BinTreeNode<T>* subtree)
	{
		string number, name, b, age, sex, phone, add;
		fstream file("student.txt", ios::in);
		if (!file)
		{
			cout << "文件打开失败" << endl;
			
		}
		file >> number >> name >> b >> age >> sex >> phone >> add;

		queue<BinTreeNode<T>*>stu;
		subtree = new BinTreeNode<T>();
		file >> subtree->data.number >> subtree->data.name >> subtree->data.birthday
			>> subtree->data.age >> subtree->data.sex >> subtree->data.phone >> subtree->data.address;
		subtree->leftchild = 0;
		subtree->rightchild = 0;
		stu.push(subtree);//根结点入队
		while (!stu.empty())
		{
			BinTreeNode<T>* temp = stu.front();//队首元素出队
			stu.pop();
			BinTreeNode<T>* p;

			p = new BinTreeNode<T>();
			file >> p->data.number >> p->data.name >> p->data.birthday
				>> p->data.age >> p->data.sex >> p->data.phone >> p->data.address;
			p->leftchild = 0;
			p->rightchild = 0;//左子树
			if (p->data.number == "#")break;
			temp->leftchild = p;
			stu.push(p);

			p = new BinTreeNode<T>();
			file >> p->data.number >> p->data.name >> p->data.birthday
				>> p->data.age >> p->data.sex >> p->data.phone >> p->data.address;
			p->leftchild = 0;
			p->rightchild = 0;//右子树
			if (p->data.number == "#")break;
			temp->rightchild = p;
			stu.push(p);
		}
		return subtree;
	}

	
};



//////////////////////////////////////////////////////////////////////////////
//  文件写入函数
//  函数功能：将学生信息写入文件
//函数参数：
//       subtree 表示根结点
//参数返回值：
//       true  表示写入成功
//       false 表示写入失败
template<class T>
bool BinaryTree<T>::writetofile(BinTreeNode<T>* subtree)
{
	fstream file("student.txt", ios::out);
	if (!file)
	{
		cout << "文件打开失败" << endl;
		return false;
		
	}
	file << "学号" << "     姓名" << "        出生日期" << "           年龄" << "     性别" << "        电话号码" << "        地址" << endl;
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
//  查找函数
//  函数功能：查找年龄最小学生
//函数参数：
//       subtree 表示根结点
//       min     表示年龄最小学生结点
//参数返回值：
//       无
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
//  插入函数
//  函数功能：将新建学生结点插入二叉树
//函数参数：
//       subtree 表示根结点
//       p       表示插入的结点
//参数返回值：
//       subtree 根结点
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
				else//说明将在此结点的左子树插入
				{
					creatNode(p);
					temp->leftchild = p;
					break;
				}
				if (temp->rightchild != 0)
					stu.push(temp->rightchild);
				else//说明将在此结点的右子树插入
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
//  文件读取函数
//  函数功能：将文件中的学生信息读出
//函数参数：
//       无
//参数返回值：
//       无


template<class T>
bool BinaryTree<T>::readfromfile()
{
	fstream file("student.txt", ios::in);
	if (!file)
	{
		cout << "文件打开失败" << endl;
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
//  删除函数
//  函数功能：分别按学号、姓名、电话号码删除学生信息
//函数参数：
//      r       表示遍历结点
//      pr      表示前驱结点
//      number  表示查找的学号
//      phone   表示查找的电话号
//      name    表示查找的姓名
//参数返回值：
//       无

//删除
template<class T>
void BinaryTree<T>::removenumber(BinTreeNode<T>* r,BinTreeNode<T>*pr, string number)//按学号
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
void BinaryTree<T>::removephone(BinTreeNode<T>* r, BinTreeNode<T>* pr, string phone)//按电话号
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
void BinaryTree<T>::removename(BinTreeNode<T>* r, BinTreeNode<T>* pr,string name)//按姓名
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
//  查找函数
//  函数功能：分别按学号、姓名、电话号码查找学生信息
//函数参数：
//      r       表示遍历结点
//      pr      表示前驱结点
//      number  表示查找的学号
//      phone   表示查找的电话号
//      name    表示查找的姓名
//参数返回值：
//       无

//查找
template<class T>
void BinaryTree<T>::findnumber(BinTreeNode<T>* subtree, string number)//按学号
{
	if (subtree != 0)
	{
		findnumber(subtree->leftchild, number);
		if (subtree->data.getnumber() == number)
		{
			cout << "查找到的学生信息：" << endl;
			cout << "学号：" << subtree->data.getnumber() << "姓名：" << subtree->data.getname()
				<< "出生日期：" << subtree->data.getbirthday() << "年龄：" << subtree->data.getage() << "性别：" << subtree->data.getsex()
				<< "电话：" << subtree->data.getphone() << "地址：" << subtree->data.getaddress() << endl;
		}
		
		findnumber(subtree->rightchild, number);
	}
}

template<class T>
void BinaryTree<T>::findname(BinTreeNode<T>* subtree, string name)//按姓名
{
	if (subtree != 0)
	{
		findnumber(subtree->leftchild, name);
		if (subtree->data.getname() == name)
		{
			cout << "查找到的学生信息：" << endl;
			cout << "学号：" << subtree->data.getnumber() << "姓名：" << subtree->data.getname()
				<< "出生日期：" << subtree->data.getbirthday() << "年龄：" << subtree->data.getage() << "性别：" << subtree->data.getsex()
				<< "电话：" << subtree->data.getphone() << "地址：" << subtree->data.getaddress() << endl;
		}
		
		findnumber(subtree->rightchild, name);
	}

}

template<class T>
void BinaryTree<T>::findphone(BinTreeNode<T>* subtree, string phone)//按电话号码
{
	if (subtree != 0)
	{
		findnumber(subtree->leftchild, phone);
		if (subtree->data.getphone() == phone)
		{
			cout << "查找到的学生信息：" << endl;
			cout << "学号：" << subtree->data.getnumber() << "姓名：" << subtree->data.getname()
				<< "出生日期：" << subtree->data.getbirthday() << "年龄：" << subtree->data.getage() << "性别：" << subtree->data.getsex()
				<< "电话：" << subtree->data.getphone() << "地址：" << subtree->data.getaddress() << endl;
		}
		
		findnumber(subtree->rightchild, phone);
	}
}




//////////////////////////////////////////////////////////////////////////////
//  删除函数
//  函数功能：删除释放整棵树
//函数参数：
//       subtree 表示根结点
//参数返回值：
//       无
template<class T>
void BinaryTree<T>::destroy(BinTreeNode<T>*& subtree)//删除
{
	if (subtree != 0)
	{
		destroy(subtree->leftchild);
		destroy(subtree->rightchild);
		delete subtree;
	}
}



//////////////////////////////////////////////////////////////////////////////
//  遍历函数
//  函数功能：分别按前序 中序 后序遍历并输出
//函数参数：
//       subtree 表示根结点
//参数返回值：
//       无

template<class T>
void BinaryTree<T>::preorder(BinTreeNode<T>*subtree)//前序遍历输出
{
	if (subtree != 0)
	{
		cout << "学号：" << subtree->data.getnumber() << "姓名：" << subtree->data.getname()
			<< "出生日期：" << subtree->data.getbirthday() << "年龄：" << subtree->data.getage() << "性别：" << subtree->data.getsex()
			<< "电话：" << subtree->data.getphone() << "地址：" << subtree->data.getaddress() << endl;
		preorder(subtree->leftchild);
		preorder(subtree->rightchild);
	}
}

template<class T>
void BinaryTree<T>::inorder(BinTreeNode<T>* subtree)//中序遍历输出
{
	if (subtree != 0)
	{
		inorder(subtree->leftchild);
		cout << "学号：" << subtree->data.getnumber() << "姓名：" << subtree->data.getname()
			<< "出生日期：" << subtree->data.getbirthday() << "年龄：" << subtree->data.getage() << "性别：" << subtree->data.getsex()
			<< "电话：" << subtree->data.getphone() << "地址：" << subtree->data.getaddress() << endl;
		inorder(subtree->rightchild);
	}
}

template<class T>
void BinaryTree<T>::postorder(BinTreeNode<T>* subtree)//后序遍历输出
{
	if (subtree != 0)
	{
		postorder(subtree->leftchild);
		postorder(subtree->rightchild);
		cout << "学号：" << subtree->data.getnumber() << "姓名：" << subtree->data.getname()
			<< "出生日期：" << subtree->data.getbirthday() << "年龄：" << subtree->data.getage() << "性别：" << subtree->data.getsex()
			<< "电话：" << subtree->data.getphone() << "地址：" << subtree->data.getaddress() << endl;
	}
}