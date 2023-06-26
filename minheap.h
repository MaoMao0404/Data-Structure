
//      ��������minheap.cpp
//      �����ܣ���С�ѵ�ʵ��
//      ���ߣ�ë�һ
//      ���ڣ�2021.12.20
//          

#pragma once
#ifndef _MYHEAP_H_
#define _MYHEAP_H_
#pragma once
#include<iostream>
using namespace std;
const int defaultSize = 200;


///////////////////////////////
////    MyHeap��Ķ���     /////
///////////////////////////////

template<class T>
class MyHeap
{
	T* heap;//heap����
	int currentSize;//��ǰԪ������
	int maxHeapSize;//���Ԫ������
public:
	MyHeap(int sz = defaultSize);//ȱʡ���캯��	
	MyHeap(T arr[], int n);//������������С��
	~MyHeap() { delete[]heap; }//��������
	bool Insert(T& x);//��С�Ѳ���
	bool Remove(T& x);//��С��ɾ��
	bool IsEmpty()const//�ж϶��Ƿ�Ϊ��
	{
		return currentSize == 0;
	}
	bool IsFull()const//�ж϶��Ƿ�����
	{
		return currentSize == maxHeapSize;
	}
	void MakeEmpty()//��ն�
	{
		currentSize = 0;
	}
private:
	void siftDown(int start, int m);//��С�����µ����㷨
	void siftUp(int start);//��С�����ϵ����㷨
};



//////////////////////////////////////////////////////////////////////////////
//  ���캯��
//  �������ܣ����������鲢��ʼ��
//����������
//       sz   ��ʾ�����С
//��������ֵ��
//       ��
template<class T>
MyHeap<T>::MyHeap(int sz)//ȱʡ���캯��	
{
	maxHeapSize = (defaultSize < sz) ? sz : defaultSize;
	heap = new T[maxHeapSize];//����������
	currentSize = 0;
}



//////////////////////////////////////////////////////////////////////////////
//  ���캯��
//  �������ܣ�������������С��
//����������
//       n        ��ʾ�����С
//       T arr[]  ��ʾ�ַ���������
//��������ֵ��
//       root ����� 
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
		siftDown(currentPos, currentSize - 1);//��currentPos������currentSize
		currentPos--;
	}
}



//////////////////////////////////////////////////////////////////////////////
//  ���뺯��
//  �������ܣ���С�Ѳ���
//����������
//       x ��ʾ�����Ԫ��
//��������ֵ��
//       true  ��ʾ����ɹ�
//       false ��ʾ����ʧ��
template <class T>
bool MyHeap<T>::Insert(T& x)
{
	
	if (currentSize == maxHeapSize)//��������
	{
		cout << "��������" << endl;
		return false;
	}
	heap[currentSize] = x;
	siftUp(currentSize);   //���ϵ���
	currentSize++;		   //��ǰԪ������1
	return true;
}



//////////////////////////////////////////////////////////////////////////////
//  ɾ������
//  �������ܣ���С��ɾ��
//����������
//       x ��ʾɾ����Ԫ��
//��������ֵ��
//       true  ��ʾ����ɹ�
//       false ��ʾ����ʧ��
template <class T>
bool MyHeap<T>::Remove(T& x)//
{
	
	if (!currentSize)//����Ϊ��
	{
		cout << "��Ϊ��" << endl;
		return false;
	}
	x = heap[0];					 // ������СԪ��
	heap[0] = heap[currentSize - 1]; //���Ԫ����������
	currentSize--;                   //��ǰԪ������1
	siftDown(0, currentSize - 1); //�������µ���Ϊ��
	return true;
}



//////////////////////////////////////////////////////////////////////////////
//  ���µ�������
//  �������ܣ����µ���Ԫ��
//����������
//       start ��ʾ���λ��
//       m     ��ʾ�յ�λ��
//��������ֵ��
//       ��
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
			j = 2 * j + 1;//������
		}
	}
	heap[i] = temp;
}



//////////////////////////////////////////////////////////////////////////////
//  ���ϵ�������
//  �������ܣ����ϵ���Ԫ��
//����������
//       strat ��ʾ��ʼ��
//��������ֵ��
//       ��
template<class T>
void MyHeap<T>::siftUp(int start)
{
	//��start��ʼ���ϵ�����0
	int j = start, i = (j - 1) / 2;//i��j��˫��
	T temp = heap[j];
	while (j > 0)
	{
		if (heap[i] <= temp)break;
		else
		{
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;//������
		}
	}
	heap[j] = temp;
}
#endif

