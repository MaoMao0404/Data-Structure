
//      程序名：List.h
//      程序功能：结点结构体、链表类的声明
//      作者：毛婧一
//      日期：2021.10.18
//          

#pragma once
#include<iostream>
#include<fstream>
#include"student.h"
#include<string>
using namespace std;


///////////////////////////////
//// LinkNode结构体的定义 /////
///////////////////////////////
template<class T>
struct LinkNode
{
	T data;
	LinkNode<T>* link;
	LinkNode() { link = 0; }
	LinkNode<T>(T t, LinkNode<T>* l = 0) : data(t), link(l) {};
	
};


///////////////////////////////
////  List类的定义   /////
///////////////////////////////
template<class T>
class List
{
public:
	LinkNode<T>* first, * tail;
	List() :first(0), tail(0) {};//构造函数
	~List();//析构函数
	void makeEmpty();//置为空表
	int Length()const;//计算表长
    void add();//添加新的学生信息
	bool Insert(LinkNode<T>*head,int i);//按位置插入新的学生信息
	void search(LinkNode<T>* head, int num);//按学号查找学生信息
	void Remove(LinkNode<T>* head, int num);//按学号删除学生信息
	void change(LinkNode<T>* head, int num);//按学号修改学生身体状况
	void output(LinkNode<T>*head);//输出全部学生信息
	void sort(LinkNode<T>*head);//按学号排序并显示结果
	bool Read_from_file(); //读取文件信息
	bool Write_to_file(LinkNode<T>*head); //信息写入文件


	///////////////////////////////////
    //// 接下来是List类的实现 /////
    //////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//  新建链表函数
//  函数功能：新建学生健康表
//函数参数：
//       head 表示头结点
//       n    表示建立结点个数
//参数返回值：
//       head 头结点 

	LinkNode<T>* creatList(LinkNode<T>*head,int n)//新建学生链表
	{    //终端输入
		/*LinkNode<T>* p;
		head = tail = new LinkNode<T>();
		head->link = 0;
		for (int i = 0;i < n;i++)
		{
			p = new LinkNode<T>();
			cout << "请按顺序输入学号 姓名 出生日期 性别 健康状况" << endl;
			cin >> p->data.number >> p->data.name >> p->data.birthday >> p->data.sex >> p->data.healthy;
			p->link = 0;
			tail->link = p;
			tail = p;
		}
		cout << "新建链表完成" << endl;
		return head;
		*/

		//文件写入建链
		string num;string name;string bir;string sex;string hea;
		fstream file("student.txt", ios::in);
		if (!file)
		{
			cout << "文件打开失败" << endl;
			return 0;
		}
		file >> num >> name >> bir >> sex >> hea;
		LinkNode<T>* p;
		head = tail = new LinkNode<T>();
		head->link = 0;
		while (1)
		{
			p = new LinkNode<T>();
			file >> p->data.number >> p->data.name >> p->data.birthday >> p->data.sex >> p->data.healthy;
			if (p->data.name == "#")break;
			else
			{
				p->link = 0;
				tail->link = p;
				tail = p;
			}
			
		}
		file.close();
		cout << "新建链表完成" << endl;
		output(head);//输出全部学生信息
		return head;
	}



	//////////////////////////////////////////////////////////////////////////////
	//  定位函数
	//  函数功能：搜索第i个元素的位置
	//函数参数：
	//      head  表示头结点
	//      i     表示位置号
	//参数返回值：
	//       head 头结点 	

	LinkNode<T>* Locate(LinkNode<T>*head,int i)
	{
		if (i < 0)return 0;
		int k = 0;
		while (head != 0 && k < i)
		{
			head = head->link;
			k++;
		}
		return head;
	}
	
};


