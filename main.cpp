
//      程序名：main.cpp
//      程序功能：main函数的功能是实现与用户的交互，显示主菜单，然后根据用户的选择调用相关的函数实现相应的系统功能
//      作者：毛婧一
//      日期：2021.12.20
//          

#include "huffmantree.h"
#include <iostream>
#include<string>
using namespace std;


/////////////////////////
/////// 主函数  /////////
//参数返回值：0

int main()
{
	int choice, i;
	bool once = false;
	HuffmanTree h;
	//测试数据
	float a[27] = { 186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,63,15,1,48,51,80,23,8,18,1,16,1 };
	char ch[27] = { ' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	bool flag = false;
	string file;

	while (1)
	{in:
		cout << "----------------欢迎来到哈夫曼编码/译码系统！---------------" << endl;
		cout << endl;
		cout << endl;
		cout << "0------文档中的测试数据" << endl;
		cout << "1------初始化" << endl;
		cout << "2------编码" << endl;
		cout << "3------译码" << endl;
		cout << "4------印编码文件" << endl;
		cout << "5------印哈夫曼树" << endl;
		cout << "6------退出" << endl;
		cout << "请输入选项" << endl;
		cin >> choice;
		
		
		/////////////////////////////////////
        ////  接下来是文档中给出测试数据的测试
        /////////////////////////////////////
		if (choice == 0)
		{
			//测试数据
			h.num = 27;
			h.keys = new char[h.num+1];
			h.times = new float[h.num];
			h.codes = new string[h.num];
			for (int i = 0;i < h.num;i++)
			{
				h.keys[i] = ch[i];
				h.times[i] = a[i];
			}
			h.Initialization(h.keys, h.times, h.num);
			h.Encoding(h.getroot(), " ");
			h.setCodeArray(h.getroot());
			h.savehuffmantree();
			file = "ToBeTran.txt";
			flag = true;
			goto in;
			
		}


		/////////////////////////////////////
		////  接下来是哈夫曼树的初始化
		/////////////////////////////////////

		if (choice == 1)
		{
			if (flag == true)
			{
				cout << "已经存在测试数据,请选择其它选项" << endl;
				goto in;
			}
			
			    cout << "输入编译的文件名" << endl;
			    cin >> file;
				h.count(file);
				cout << "输入统计出的字符的个数" << endl;
				cin >> h.num;
				h.keys = new char[h.num + 1];
				h.times = new float[h.num];
				h.codes = new string[h.num];
				cout << "输入字符及对应的频度" << endl;
				for (int i = 0;i < h.num;i++)
				{
					cin.get();
					h.keys[i] = cin.get();
					cin >> h.times[i];
				}

				h.Initialization(h.keys, h.times, h.num);
				h.Encoding(h.getroot(), " ");
				h.setCodeArray(h.getroot());
				h.savehuffmantree();
				goto in;
			
		}


		/////////////////////////////////////
		////  接下来是为英文文章编码
		/////////////////////////////////////
		if (choice == 2)
		{
			h.FileTran(file);
			goto in;
		}


		/////////////////////////////////////
		////  接下来是为英文文章解码
		/////////////////////////////////////
		if (choice == 3)
		{
			h.decoding();
			goto in;
		}


		/////////////////////////////////////
		////  接下来是打印编码
		/////////////////////////////////////
		if (choice == 4)
		{
			h.Print();
			goto in;
		}


		/////////////////////////////////////
		////  接下来是直观打印哈夫曼树
		/////////////////////////////////////
		if (choice == 5)
		{
			h.TreePrinting(h.getroot(), 0);
			cout << "终端内容已存入TreePrint文件中" << endl;
			goto in;
		}
		if (choice == 6)break;
	}
		return 0;
}
