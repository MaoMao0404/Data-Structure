
//      程序名：student.h
//      程序功能：学生信息类
//      作者：毛婧一
//      日期：2021.10.18
//          

#pragma once
#include<iostream>
using namespace std;
#include<fstream>
#include<string>
//学生信息
class student
{public:
	int number;//学号
	string name;//姓名
	string birthday;//出生日期
	string sex;//性别
	string healthy;//身体状况
	
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

