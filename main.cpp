
//      程序名：main.cpp
//      程序功能：main函数的功能是实现与用户的交互，显示主菜单，然后根据用户的选择调用相关的函数实现相应的系统功能
//      作者：毛婧一
//      日期：2021.10.18
//          

#include<iostream>
#include<string>
#include<fstream>
#include"List.h"
#include"List.cpp"
#include"student.h"
using namespace std;

/////////////////////////
/////// 主函数  /////////
//参数返回值：0

int main()
{
	int choice = 0;
	int num, i;
	int n = 0;
	bool flag = false;
	LinkNode<student> N;
	LinkNode<student>* head = 0;
	List<student> L;
	while (1)
	{
	input:
		cout << endl;
		cout << "欢迎进入学生健康管理系统" << endl;
		cout << "1.新建学生健康表" << endl;
		cout << "2.向学生健康表添加新的学生信息" << endl;
		cout << "3.向学生健康表插入新的学生信息（按位置号插入）" << endl;
		cout << "4.按学号删除指定学生信息" << endl;
		cout << "5.按学号修改学生身体状况信息" << endl;
		cout << "6.按学生的学号排序并显示结果" << endl;
		cout << "7.按学号查询学生信息" << endl;
		cout << "8.输出全部学生信息" << endl;
		cout << "9.从文件中读取所有学生健康表信息" << endl;
		cout << "10.向文件写入所有学生健康表信息" << endl;
		cout << "11.退出" << endl;
		cout << endl;


		cout << "请输入选择的选项" << endl;
		cin >> choice;



		/////////////////////////////////////
		////  接下来是新建学生健康表
		/////////////////////////////////////
		if (choice == 1)
		{
			if (flag)//判断是否第一次新建健康表
			{
				cout << "已经完成新建健康表，请选择其它操作" << endl;
				goto input;
			}
			flag = true;
			
			//终端输入
			/*cout << "输入创建学生表的学生数量" << endl;
			cin >> n;*/
			
			//文件写入建链
			L.first = L.creatList(head,n);
			goto input;
		}

		/////////////////////////////////////
		////  接下来是添加新的学生信息
		/////////////////////////////////////

		if (choice == 2)
		{
			L.add();
			cout << "添加成功！" << endl;
			goto input;
		}


		/////////////////////////////////////
		////  接下来是按位置号插入学生信息
		/////////////////////////////////////
		if (choice == 3)
		{
			cout << "请输入要插入的位置号" << endl;
			cin >> i;
			L.Insert(L.first, i);
			cout << "插入成功！" << endl;
			goto input;
		}

		/////////////////////////////////////
		////  接下来是按学号删除学生信息
		/////////////////////////////////////
		if (choice == 4)
		{
			cout << "请输入删除的学生学号" << endl;
			cin >> num;
			L.Remove(L.first, num);
			goto input;
		}


		/////////////////////////////////////
		////  接下来是按学号修改学生信息
		/////////////////////////////////////
		if (choice == 5)
		{
			cout << "请输入修改学生信息的学生学号" << endl;
			cin >> num;
			L.change(L.first, num);
			cout << "修改成功！" << endl;
			goto input;
		}

		/////////////////////////////////////
		////  接下来是按学号排序
		/////////////////////////////////////
		if (choice == 6)
		{
			L.sort(L.first);
			goto input;
		}

		/////////////////////////////////////
		////  接下来是按学号查询
		/////////////////////////////////////

		if (choice == 7)
		{
			cout << "请输入要查询学生信息的学号" << endl;
			cin >> num;
			L.search(L.first, num);
			goto input;

		}

		/////////////////////////////////////
		////  接下来是输出所有学生信息
		/////////////////////////////////////
		if (choice == 8)
		{
			L.output(L.first);
			goto input;
		}

		/////////////////////////////////////
		////  接下来是从文件读取学生信息
		/////////////////////////////////////
		if (choice == 9)
		{
			L.Read_from_file();
			goto input;
		}


		/////////////////////////////////////
		////  接下来是将学生信息写入文件
		/////////////////////////////////////
		if (choice == 10)
		{
			L.Write_to_file(L.first);
			goto input;
		}
		if (choice == 11)
			break;
	}
	return 0;
	
}