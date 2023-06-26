
//      程序名：minheap.cpp
//      程序功能：最小堆的实现
//      作者：毛婧一
//      日期：2021.12.20
//          

#pragma once
#ifndef _MYHEAP_H_
#define _MYHEAP_H_
#pragma once
#include<iostream>
using namespace std;
const int defaultSize = 200;


///////////////////////////////
////    MyHeap类的定义     /////
///////////////////////////////

template<class T>
class MyHeap
{
	T* heap;//heap数组
	int currentSize;//当前元素数量
	int maxHeapSize;//最大元素数量
public:
	MyHeap(int sz = defaultSize);//缺省构造函数	
	MyHeap(T arr[], int n);//由数组生成最小堆
	~MyHeap() { delete[]heap; }//析构函数
	bool Insert(T& x);//最小堆插入
	bool Remove(T& x);//最小堆删除
	bool IsEmpty()const//判断堆是否为空
	{
		return currentSize == 0;
	}
	bool IsFull()const//判断堆是否已满
	{
		return currentSize == maxHeapSize;
	}
	void MakeEmpty()//清空堆
	{
		currentSize = 0;
	}
private:
	void siftDown(int start, int m);//最小堆向下调整算法
	void siftUp(int start);//最小堆向上调整算法
};



//////////////////////////////////////////////////////////////////////////////
//  构造函数
//  函数功能：创建堆数组并初始化
//函数参数：
//       sz   表示数组大小
//参数返回值：
//       无
template<class T>
MyHeap<T>::MyHeap(int sz)//缺省构造函数	
{
	maxHeapSize = (defaultSize < sz) ? sz : defaultSize;
	heap = new T[maxHeapSize];//创建堆数组
	currentSize = 0;
}



//////////////////////////////////////////////////////////////////////////////
//  构造函数
//  函数功能：由数组生成最小堆
//函数参数：
//       n        表示数组大小
//       T arr[]  表示字符次数数组
//参数返回值：
//       root 根结点 
template <class T>
MyHeap<T>::MyHeap(T arr[], int n)
{
	maxHeapSize = (defaultSize < n) ? n : defaultSize;
	heap = new T[maxHeapSize];
	for (int i = 0; i < n; i++)
	{
		heap[i] = arr[i];
	}
	currentSize = n;
	int currentPos = (currentSize - 2) / 2;
	while (currentPos >= 0)
	{
		siftDown(currentPos, currentSize - 1);//从currentPos调整到currentSize
		currentPos--;
	}
}



//////////////////////////////////////////////////////////////////////////////
//  插入函数
//  函数功能：最小堆插入
//函数参数：
//       x 表示插入的元素
//参数返回值：
//       true  表示插入成功
//       false 表示插入失败
template <class T>
bool MyHeap<T>::Insert(T& x)
{
	
	if (currentSize == maxHeapSize)//若堆已满
	{
		cout << "堆已满！" << endl;
		return false;
	}
	heap[currentSize] = x;
	siftUp(currentSize);   //向上调整
	currentSize++;		   //当前元素数加1
	return true;
}



//////////////////////////////////////////////////////////////////////////////
//  删除函数
//  函数功能：最小堆删除
//函数参数：
//       x 表示删除的元素
//参数返回值：
//       true  表示插入成功
//       false 表示插入失败
template <class T>
bool MyHeap<T>::Remove(T& x)//
{
	
	if (!currentSize)//若堆为空
	{
		cout << "堆为空" << endl;
		return false;
	}
	x = heap[0];					 // 返回最小元素
	heap[0] = heap[currentSize - 1]; //最后元素填补到根结点
	currentSize--;                   //当前元素数减1
	siftDown(0, currentSize - 1); //自上向下调整为堆
	return true;
}



//////////////////////////////////////////////////////////////////////////////
//  向下调整函数
//  函数功能：向下调整元素
//函数参数：
//       start 表示起点位置
//       m     表示终点位置
//参数返回值：
//       无
template<class T>
void MyHeap<T>::siftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;
	T temp = heap[i];
	while (j <= m)
	{
		
		if (j<m && heap[j]>heap[j + 1])
			j++;
		if (temp <= heap[j])break;
		else
		{
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;//往下走
		}
	}
	heap[i] = temp;
}



//////////////////////////////////////////////////////////////////////////////
//  向上调整函数
//  函数功能：向上调整元素
//函数参数：
//       strat 表示起始点
//参数返回值：
//       无
template<class T>
void MyHeap<T>::siftUp(int start)
{
	//从start开始向上调整到0
	int j = start, i = (j - 1) / 2;//i是j的双亲
	T temp = heap[j];
	while (j > 0)
	{
		if (heap[i] <= temp)break;
		else
		{
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;//往上走
		}
	}
	heap[j] = temp;
}
#endif

