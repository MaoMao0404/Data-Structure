
//      ��������List.h
//      �����ܣ����ṹ�塢�����������
//      ���ߣ�ë�һ
//      ���ڣ�2021.10.18
//          

#pragma once
#include<iostream>
#include<fstream>
#include"student.h"
#include<string>
using namespace std;


///////////////////////////////
//// LinkNode�ṹ��Ķ��� /////
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
////  List��Ķ���   /////
///////////////////////////////
template<class T>
class List
{
public:
	LinkNode<T>* first, * tail;
	List() :first(0), tail(0) {};//���캯��
	~List();//��������
	void makeEmpty();//��Ϊ�ձ�
	int Length()const;//�����
    void add();//����µ�ѧ����Ϣ
	bool Insert(LinkNode<T>*head,int i);//��λ�ò����µ�ѧ����Ϣ
	void search(LinkNode<T>* head, int num);//��ѧ�Ų���ѧ����Ϣ
	void Remove(LinkNode<T>* head, int num);//��ѧ��ɾ��ѧ����Ϣ
	void change(LinkNode<T>* head, int num);//��ѧ���޸�ѧ������״��
	void output(LinkNode<T>*head);//���ȫ��ѧ����Ϣ
	void sort(LinkNode<T>*head);//��ѧ��������ʾ���
	bool Read_from_file(); //��ȡ�ļ���Ϣ
	bool Write_to_file(LinkNode<T>*head); //��Ϣд���ļ�


	///////////////////////////////////
    //// ��������List���ʵ�� /////
    //////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//  �½�������
//  �������ܣ��½�ѧ��������
//����������
//       head ��ʾͷ���
//       n    ��ʾ����������
//��������ֵ��
//       head ͷ��� 

	LinkNode<T>* creatList(LinkNode<T>*head,int n)//�½�ѧ������
	{    //�ն�����
		/*LinkNode<T>* p;
		head = tail = new LinkNode<T>();
		head->link = 0;
		for (int i = 0;i < n;i++)
		{
			p = new LinkNode<T>();
			cout << "�밴˳������ѧ�� ���� �������� �Ա� ����״��" << endl;
			cin >> p->data.number >> p->data.name >> p->data.birthday >> p->data.sex >> p->data.healthy;
			p->link = 0;
			tail->link = p;
			tail = p;
		}
		cout << "�½��������" << endl;
		return head;
		*/

		//�ļ�д�뽨��
		string num;string name;string bir;string sex;string hea;
		fstream file("student.txt", ios::in);
		if (!file)
		{
			cout << "�ļ���ʧ��" << endl;
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
		cout << "�½��������" << endl;
		output(head);//���ȫ��ѧ����Ϣ
		return head;
	}



	//////////////////////////////////////////////////////////////////////////////
	//  ��λ����
	//  �������ܣ�������i��Ԫ�ص�λ��
	//����������
	//      head  ��ʾͷ���
	//      i     ��ʾλ�ú�
	//��������ֵ��
	//       head ͷ��� 	

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


