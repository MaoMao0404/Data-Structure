
//      程序名：student.h
//      程序功能：学生信息类
//      作者：毛婧一
//      日期：2021.11.18
//          

#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"BTree.h"
using namespace std;

///////////////////////////////
////student类的定义////////////
///////////////////////////////

//学生信息类
class student
{public:
	string number;//学号
	string name;//姓名
	string birthday;//出生日期
	int age;//年龄
	string sex;//性别
	string phone;//电话
	string address;//地址

	student() {};//构造函数
	student(student& s);//构造函数
	student(string nu);
	student(string nu,string na,string b,int a,string s,string ph,string ad);//构造函数
	
    //获取信息
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
