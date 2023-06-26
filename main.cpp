
//      ��������main.cpp
//      �����ܣ�main�����Ĺ�����ʵ�����û��Ľ�������ʾ���˵���Ȼ������û���ѡ�������صĺ���ʵ����Ӧ��ϵͳ����
//      ���ߣ�ë�һ
//      ���ڣ�2021.12.20
//          

#include "huffmantree.h"
#include <iostream>
#include<string>
using namespace std;


/////////////////////////
/////// ������  /////////
//��������ֵ��0

int main()
{
	int choice, i;
	bool once = false;
	HuffmanTree h;
	//��������
	float a[27] = { 186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,63,15,1,48,51,80,23,8,18,1,16,1 };
	char ch[27] = { ' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	bool flag = false;
	string file;

	while (1)
	{in:
		cout << "----------------��ӭ��������������/����ϵͳ��---------------" << endl;
		cout << endl;
		cout << endl;
		cout << "0------�ĵ��еĲ�������" << endl;
		cout << "1------��ʼ��" << endl;
		cout << "2------����" << endl;
		cout << "3------����" << endl;
		cout << "4------ӡ�����ļ�" << endl;
		cout << "5------ӡ��������" << endl;
		cout << "6------�˳�" << endl;
		cout << "������ѡ��" << endl;
		cin >> choice;
		
		
		/////////////////////////////////////
        ////  ���������ĵ��и����������ݵĲ���
        /////////////////////////////////////
		if (choice == 0)
		{
			//��������
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
		////  �������ǹ��������ĳ�ʼ��
		/////////////////////////////////////

		if (choice == 1)
		{
			if (flag == true)
			{
				cout << "�Ѿ����ڲ�������,��ѡ������ѡ��" << endl;
				goto in;
			}
			
			    cout << "���������ļ���" << endl;
			    cin >> file;
				h.count(file);
				cout << "����ͳ�Ƴ����ַ��ĸ���" << endl;
				cin >> h.num;
				h.keys = new char[h.num + 1];
				h.times = new float[h.num];
				h.codes = new string[h.num];
				cout << "�����ַ�����Ӧ��Ƶ��" << endl;
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
		////  ��������ΪӢ�����±���
		/////////////////////////////////////
		if (choice == 2)
		{
			h.FileTran(file);
			goto in;
		}


		/////////////////////////////////////
		////  ��������ΪӢ�����½���
		/////////////////////////////////////
		if (choice == 3)
		{
			h.decoding();
			goto in;
		}


		/////////////////////////////////////
		////  �������Ǵ�ӡ����
		/////////////////////////////////////
		if (choice == 4)
		{
			h.Print();
			goto in;
		}


		/////////////////////////////////////
		////  ��������ֱ�۴�ӡ��������
		/////////////////////////////////////
		if (choice == 5)
		{
			h.TreePrinting(h.getroot(), 0);
			cout << "�ն������Ѵ���TreePrint�ļ���" << endl;
			goto in;
		}
		if (choice == 6)break;
	}
		return 0;
}
