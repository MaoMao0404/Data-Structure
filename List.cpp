
//      ��������List.cpp
//      �����ܣ�List���ʵ��
//      ���ߣ�ë�һ
//      ���ڣ�2021.10.18
//          


#include<iostream>
#include<string>
#include<fstream>
#include"List.h"
#include"student.h"
using namespace std;


    ///////////////////////////////////
	//// ��������List���ʵ�� /////
	//////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//  ��������
//  �������ܣ��ͷ�����
//����������
//      ��
//��������ֵ��
//       ��
template<class T>
List<T>::~List()//��������
{
	makeEmpty();
}



//////////////////////////////////////////////////////////////////////////////
//  ��Ϊ�ձ���
//  �������ܣ���������Ϊ�ձ�
//����������
//       ��
//��������ֵ��
//       ��

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
//  ��������
//  �������ܣ������
//����������
//       ��
//��������ֵ��
//       count ��

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
//  ��Ӻ���
//  �������ܣ�����µ�ѧ����Ϣ
//����������
//       ��
//��������ֵ��
//       ��
template<class T>
void List<T>::add()
{
	LinkNode<T>* add = new LinkNode<T>();
	cout << "���������ѧ����ѧ�� ���� �������� �Ա� ����״��" << endl;
	cin >> add->data.number >> add->data.name >> add->data.birthday >> add->data.sex >> add->data.healthy;
	add->link = 0;
	tail->link = add;
	tail = add;
}



//////////////////////////////////////////////////////////////////////////////
//  ���뺯��
//  �������ܣ���λ�ò����µ�ѧ����Ϣ
//����������
//       head  ��ʾͷ���
//       i     ��ʾλ�ú�
//��������ֵ��
//       true  ��ʾ����ɹ�
//       false ��ʾ����ʧ��
template<class T>
bool List<T>::Insert(LinkNode<T>* head, int i)
{
	LinkNode<T>* current = Locate(head,i);
	if (current == 0)return false;
	LinkNode<T>* add = new LinkNode<T>();
	cout << "���������ѧ����ѧ�� ���� �������� �Ա� ����״��" << endl;
	cin >> add->data.number >> add->data.name >> add->data.birthday >> add->data.sex >> add->data.healthy;
	if (add == 0) { cerr << "�洢�������" << endl;exit(1); }
	add->link = current->link;
	current->link = add;
	return true;
}



//////////////////////////////////////////////////////////////////////////////
//  ���Һ���
//  �������ܣ���ѧ�Ų���ѧ����Ϣ
//����������
//      head  ��ʾͷ���
//      num   ��ʾѧ��
//��������ֵ��
//       ��
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
		cout << "���ҵ���ѧ����ϢΪ��" << endl;
		cout << "ѧ�ţ�" << p->data.number << "  " << "������" << p->data.name << "  " << "��������" << p->data.birthday << "  "
			<< "�Ա�" << p->data.sex << "  " << "����״����" << p->data.healthy << endl;
	}
	else
		cout << "���޴���" << endl;
}



//////////////////////////////////////////////////////////////////////////////
//  ɾ������
//  �������ܣ���ѧ��ɾ��ѧ����Ϣ
//����������
//      head  ��ʾͷ���
//      num   ��ʾѧ��
//��������ֵ��
//       ��
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
		cout << "��Ҫɾ��ѧ����ϢΪ��" << endl;
		cout << "ѧ�ţ�" << p->data.number << "  " << "������" << p->data.name << "  " << "��������" << p->data.birthday << "  "
			<< "�Ա�" << p->data.sex << "  " << "����״����" << p->data.healthy << endl;
	}
	else
	{
		cout << "���޴���" << endl;
	}
	LinkNode<T>* del = pr->link;
	pr->link = del->link;
	delete del;
	cout << "��Ϣ�ѱ�ɾ��" << endl;

}



//////////////////////////////////////////////////////////////////////////////
//  �޸ĺ���
//  �������ܣ���ѧ���޸�����״��
//����������
//      head  ��ʾͷ���
//      num   ��ʾλ�ú�
//��������ֵ��
//       ��
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
		cout << "���ҵ���ѧ����ϢΪ��" << endl;
		cout << "ѧ�ţ�" << p->data.number << "  " << "������" << p->data.name << "  " << "��������" << p->data.birthday << "  "
			<< "�Ա�" << p->data.sex << "  " << "����״����" << p->data.healthy << endl;
		cout << "�������޸ĺ������״��" << endl;
		cin >> hea;
		p->data.healthy = hea;
		cout << "�޸ĳɹ���" << endl;
		cout << "�޸ĺ��ѧ����ϢΪ��" << endl;
		cout << "ѧ�ţ�" << p->data.number << "  " << "������" << p->data.name << "  " << "��������" << p->data.birthday << "  "
			<< "�Ա�" << p->data.sex << "  " << "����״����" << p->data.healthy << endl;
	}
	else
		cout << "���޴���" << endl;
}



//////////////////////////////////////////////////////////////////////////////
//  ��������
//  �������ܣ��������������ѧ����Ϣ
//����������
//      head  ��ʾͷ���
//��������ֵ��
//       ��
template<class T>
void List<T>::output(LinkNode<T>* head)//���ȫ��ѧ����Ϣ
{
	LinkNode<T>* current = head->link;
	while (current != 0)
	{
		cout << "ѧ�ţ�" << current->data.number << "  " << "������" << current->data.name << "  "
			<< "�������ڣ�" << current->data.birthday << "  " << "�Ա�" << current->data.sex << "  "
			<< "����״����" << current->data.healthy << endl;
		current = current->link;
	}
}



//////////////////////////////////////////////////////////////////////////////
//  ������
//  �������ܣ���ѧ��������ʾ���
//����������
//      head  ��ʾͷ���
//��������ֵ��
//       ��
template<class T>
void List<T>::sort(LinkNode<T>*head)
{
	LinkNode<T>* p = 0;
	LinkNode<T>* q = 0;
	//ѡ������
	for (p = head;p != 0;p = p->link)
		for (q = p->link; q != 0; q = q->link)
			if (q->data.number < p->data.number)//��������
			{

				string temp1;
				int temp2;
				temp1 = q->data.name;//��������
				q->data.name =p->data.name;
				p->data.name = temp1;
				temp2 = q->data.number;//����ѧ��
				q->data.number = p->data.number;
				p->data.number= temp2;
				temp1 = q->data.sex;//�����Ա�
				q->data.sex = p->data.sex;
				p->data.sex = temp1;
				temp1 = q->data.birthday;//������������
				q->data.birthday = p->data.birthday;
				p->data.birthday = temp1;
				temp1 = q->data.healthy;//��������״��
				q->data.healthy = p->data.healthy;
				p->data.healthy = temp1;
			}
	cout << "�Ѿ�����ѧ�Ŵ�С����ɹ�����" << endl << endl;
	output(head);
	
}



//////////////////////////////////////////////////////////////////////////////
//  �ļ�д�뺯��
//  �������ܣ�����α�����˳����Ϣд���ļ�
//����������
//       head  ��ʾͷ���
//��������ֵ��
//       true   ��ʾ�ɹ�
//       false  ��ʾʧ��
template<class T>
bool List<T>::Write_to_file(LinkNode<T>*head)//����Ϣд���ļ�
{
	ofstream file("student.txt", ios::out);
	if (!file)
	{
		cout << "�ļ���ʧ��" << endl;
		return false;
	}
	file << "ѧ��" << "     " << "����" << "      " << "��������" << "      " << "�Ա�" << "       " << "����״��" << endl;
	LinkNode<T>* current = head->link;
	while (current != 0)
	{
		file << current->data.number << "     " <<  current->data.name << "        "
			<<  current->data.birthday << "     " <<  current->data.sex << "        "<<current->data.healthy << endl;
		current = current->link;
	}
	file << "0 " << "# " << "# " << "# " << "# " << endl;
	cout << "��Ϣ�Ѿ�д��student�ļ���" << endl;
	return true;
}



//////////////////////////////////////////////////////////////////////////////
//  �ļ���ȡ����
//  �������ܣ����ļ���ȡ��Ϣ
//����������
//       ��
//��������ֵ��
//       true   ��ʾ�ɹ�
//       false  ��ʾʧ��

template<class T>
bool List<T>::Read_from_file()//���ļ���ȡ��Ϣ
{
	ifstream file("student.txt", ios::in);

	if (!file)
	{
		cout << "�ļ���ʧ��" << endl;
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