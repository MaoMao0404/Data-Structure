
//      ��������student.h
//      �����ܣ�ѧ����Ϣ��
//      ���ߣ�ë�һ
//      ���ڣ�2021.11.18
//          

#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"BTree.h"
using namespace std;

///////////////////////////////
////student��Ķ���////////////
///////////////////////////////

//ѧ����Ϣ��
class student
{public:
	string number;//ѧ��
	string name;//����
	string birthday;//��������
	int age;//����
	string sex;//�Ա�
	string phone;//�绰
	string address;//��ַ

	student() {};//���캯��
	student(student& s);//���캯��
	student(string nu);
	student(string nu,string na,string b,int a,string s,string ph,string ad);//���캯��
	
    //��ȡ��Ϣ
	string getnumber();
	string getname();
	string getbirthday();
	int getage();
	string getsex();
	string getphone();
	string getaddress();
	
};
student::student(student& s)
{
	s.number = number;
	s.name = name;
	s.birthday = birthday;
	s.age = age;
	s.sex = sex;
	s.phone = phone;
	s.address = address;
}
student::student(string nu)
{
	number = nu;
}
student::student(string nu,string na, string b, int a, string s, string ph, string ad)
{
	number = nu;
	name = na;
	birthday = b;
	age = a;
	sex = s;
	phone = ph;
	address = ad;
}
string student:: getnumber()
{
	return number;
}
string student::getname()
{
	return name;
}
string student::getbirthday()
{
	return birthday;
}
int student::getage()
{
	return age;
}
string student::getphone()
{
	return phone;
}
string student::getsex()
{
	return sex;
}
string student::getaddress()
{
	return address;
}
