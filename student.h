
//      ��������student.h
//      �����ܣ�ѧ����Ϣ��
//      ���ߣ�ë�һ
//      ���ڣ�2021.10.18
//          

#pragma once
#include<iostream>
using namespace std;
#include<fstream>
#include<string>
//ѧ����Ϣ
class student
{public:
	int number;//ѧ��
	string name;//����
	string birthday;//��������
	string sex;//�Ա�
	string healthy;//����״��
	
	student() {};
	student(student& s)
	{
		number = s.number;
		name = s.name;
		birthday = s.birthday;
		sex = s.sex;
		healthy = s.healthy;
	}
	
	
};

