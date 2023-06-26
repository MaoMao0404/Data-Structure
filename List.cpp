
//      程序名：List.cpp
//      程序功能：List类的实现
//      作者：毛婧一
//      日期：2021.10.18
//          


#include<iostream>
#include<string>
#include<fstream>
#include"List.h"
#include"student.h"
using namespace std;


    ///////////////////////////////////
	//// 接下来是List类的实现 /////
	//////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//  析构函数
//  函数功能：释放链表
//函数参数：
//      无
//参数返回值：
//       无
template<class T>
List<T>::~List()//析构函数
{
	makeEmpty();
}



//////////////////////////////////////////////////////////////////////////////
//  置为空表函数
//  函数功能：将链表置为空表
//函数参数：
//       无
//参数返回值：
//       无

template<class T>
void List<T>::makeEmpty()
{
	LinkNode<T>* q;
	while (first->link != 0)
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
}



//////////////////////////////////////////////////////////////////////////////
//  计数函数
//  函数功能：计算表长
//函数参数：
//       无
//参数返回值：
//       count 表长

template<class T>
int List<T>::Length()const
{
	LinkNode<T>* p = first->link;
	int count = 0;
	while (first != 0 && p->link != 0)
	{
		p = p->link;
		count++;
	}
	return count;
}



//////////////////////////////////////////////////////////////////////////////
//  添加函数
//  函数功能：添加新的学生信息
//函数参数：
//       无
//参数返回值：
//       无
template<class T>
void List<T>::add()
{
	LinkNode<T>* add = new LinkNode<T>();
	cout << "请输入添加学生的学号 姓名 出生日期 性别 健康状况" << endl;
	cin >> add->data.number >> add->data.name >> add->data.birthday >> add->data.sex >> add->data.healthy;
	add->link = 0;
	tail->link = add;
	tail = add;
}



//////////////////////////////////////////////////////////////////////////////
//  插入函数
//  函数功能：按位置插入新的学生信息
//函数参数：
//       head  表示头结点
//       i     表示位置号
//参数返回值：
//       true  表示插入成功
//       false 表示插入失败
template<class T>
bool List<T>::Insert(LinkNode<T>* head, int i)
{
	LinkNode<T>* current = Locate(head,i);
	if (current == 0)return false;
	LinkNode<T>* add = new LinkNode<T>();
	cout << "请输入添加学生的学号 姓名 出生日期 性别 健康状况" << endl;
	cin >> add->data.number >> add->data.name >> add->data.birthday >> add->data.sex >> add->data.healthy;
	if (add == 0) { cerr << "存储分配错误！" << endl;exit(1); }
	add->link = current->link;
	current->link = add;
	return true;
}



//////////////////////////////////////////////////////////////////////////////
//  查找函数
//  函数功能：按学号查找学生信息
//函数参数：
//      head  表示头结点
//      num   表示学号
//参数返回值：
//       无
template<class T>
void List<T>::search(LinkNode<T>* head, int num)
{
	LinkNode<T>* p = head->link;
	while (p->data.number != num && p->link != 0)
	{
		p = p->link;
	}
	if (p->data.number == num)
	{
		cout << "查找到的学生信息为：" << endl;
		cout << "学号：" << p->data.number << "  " << "姓名：" << p->data.name << "  " << "出生日期" << p->data.birthday << "  "
			<< "性别：" << p->data.sex << "  " << "健康状况：" << p->data.healthy << endl;
	}
	else
		cout << "查无此人" << endl;
}



//////////////////////////////////////////////////////////////////////////////
//  删除函数
//  函数功能：按学号删除学生信息
//函数参数：
//      head  表示头结点
//      num   表示学号
//参数返回值：
//       无
template<class T>
void List<T>::Remove(LinkNode<T>* head, int num)
{
	LinkNode<T>* pr = head;
	LinkNode<T>* p = head->link;
	while (p->data.number != num && p->link != 0)
	{
		pr = pr->link;
		p = p->link;
	}
	if (p->data.number == num)
	{
		cout << "需要删除学生信息为：" << endl;
		cout << "学号：" << p->data.number << "  " << "姓名：" << p->data.name << "  " << "出生日期" << p->data.birthday << "  "
			<< "性别：" << p->data.sex << "  " << "健康状况：" << p->data.healthy << endl;
	}
	else
	{
		cout << "查无此人" << endl;
	}
	LinkNode<T>* del = pr->link;
	pr->link = del->link;
	delete del;
	cout << "信息已被删除" << endl;

}



//////////////////////////////////////////////////////////////////////////////
//  修改函数
//  函数功能：按学号修改身体状况
//函数参数：
//      head  表示头结点
//      num   表示位置号
//参数返回值：
//       无
template<class T>
void List<T>::change(LinkNode<T>* head, int num)
{
	string hea;
	LinkNode<T>* p = head->link;
	while (p->data.number != num && p->link != 0)
	{
		p = p->link;
	}
	if (p->data.number == num)
	{
		cout << "查找到的学生信息为：" << endl;
		cout << "学号：" << p->data.number << "  " << "姓名：" << p->data.name << "  " << "出生日期" << p->data.birthday << "  "
			<< "性别：" << p->data.sex << "  " << "健康状况：" << p->data.healthy << endl;
		cout << "请输入修改后的身体状况" << endl;
		cin >> hea;
		p->data.healthy = hea;
		cout << "修改成功！" << endl;
		cout << "修改后的学生信息为：" << endl;
		cout << "学号：" << p->data.number << "  " << "姓名：" << p->data.name << "  " << "出生日期" << p->data.birthday << "  "
			<< "性别：" << p->data.sex << "  " << "健康状况：" << p->data.healthy << endl;
	}
	else
		cout << "查无此人" << endl;
}



//////////////////////////////////////////////////////////////////////////////
//  遍历函数
//  函数功能：遍历并输出所有学生信息
//函数参数：
//      head  表示头结点
//参数返回值：
//       无
template<class T>
void List<T>::output(LinkNode<T>* head)//输出全部学生信息
{
	LinkNode<T>* current = head->link;
	while (current != 0)
	{
		cout << "学号：" << current->data.number << "  " << "姓名：" << current->data.name << "  "
			<< "出生日期：" << current->data.birthday << "  " << "性别：" << current->data.sex << "  "
			<< "身体状况：" << current->data.healthy << endl;
		current = current->link;
	}
}



//////////////////////////////////////////////////////////////////////////////
//  排序函数
//  函数功能：按学号排序并显示结果
//函数参数：
//      head  表示头结点
//参数返回值：
//       无
template<class T>
void List<T>::sort(LinkNode<T>*head)
{
	LinkNode<T>* p = 0;
	LinkNode<T>* q = 0;
	//选择排序
	for (p = head;p != 0;p = p->link)
		for (q = p->link; q != 0; q = q->link)
			if (q->data.number < p->data.number)//交换数据
			{

				string temp1;
				int temp2;
				temp1 = q->data.name;//交换姓名
				q->data.name =p->data.name;
				p->data.name = temp1;
				temp2 = q->data.number;//交换学号
				q->data.number = p->data.number;
				p->data.number= temp2;
				temp1 = q->data.sex;//交换性别
				q->data.sex = p->data.sex;
				p->data.sex = temp1;
				temp1 = q->data.birthday;//交换出生日期
				q->data.birthday = p->data.birthday;
				p->data.birthday = temp1;
				temp1 = q->data.healthy;//交换健康状况
				q->data.healthy = p->data.healthy;
				p->data.healthy = temp1;
			}
	cout << "已经按照学号大小排序成功！！" << endl << endl;
	output(head);
	
}



//////////////////////////////////////////////////////////////////////////////
//  文件写入函数
//  函数功能：按层次遍历的顺序将信息写入文件
//函数参数：
//       head  表示头结点
//参数返回值：
//       true   表示成功
//       false  表示失败
template<class T>
bool List<T>::Write_to_file(LinkNode<T>*head)//将信息写入文件
{
	ofstream file("student.txt", ios::out);
	if (!file)
	{
		cout << "文件打开失败" << endl;
		return false;
	}
	file << "学号" << "     " << "姓名" << "      " << "出生日期" << "      " << "性别" << "       " << "健康状况" << endl;
	LinkNode<T>* current = head->link;
	while (current != 0)
	{
		file << current->data.number << "     " <<  current->data.name << "        "
			<<  current->data.birthday << "     " <<  current->data.sex << "        "<<current->data.healthy << endl;
		current = current->link;
	}
	file << "0 " << "# " << "# " << "# " << "# " << endl;
	cout << "信息已经写入student文件中" << endl;
	return true;
}



//////////////////////////////////////////////////////////////////////////////
//  文件读取函数
//  函数功能：从文件读取信息
//函数参数：
//       无
//参数返回值：
//       true   表示成功
//       false  表示失败

template<class T>
bool List<T>::Read_from_file()//从文件读取信息
{
	ifstream file("student.txt", ios::in);

	if (!file)
	{
		cout << "文件打开失败" << endl;
		return false;
	}

	char c[100];
	while (!file.eof())
	{
		file.getline(c, sizeof(c));
		cout << c << endl;
	}

	return true;
}