
//      ��������huffmantree.cpp
//      �����ܣ�����������������������
//      ���ߣ�ë�һ
//      ���ڣ�2021.12.20
//          

#pragma once
#include<iostream>
#include<fstream>
using namespace std;
#include "minheap.h"

///////////////////////////////
////huffmannode�ṹ��Ķ���/////
///////////////////////////////
struct huffmannode
{
	char key;//��ĸ
	float times;//������� Ƶ��
	string code;//��Ӧ����
	huffmannode* leftchild, * rightchild;
	huffmannode* parent;
	huffmannode() :leftchild(0), rightchild(0), parent(0)
	{
		key = '\0';
		times = 0;
		code = "";
	}
	
	bool operator<=(huffmannode& R) { return times <= R.times; }//����<=�����
	bool operator>(huffmannode& R) { return times > R.times; }//����>�����
};



///////////////////////////////
////HuffmanTree��Ķ���/////////
///////////////////////////////
class HuffmanTree
{protected:

	huffmannode* root;
	void mergetree(huffmannode* bt1, huffmannode* bt2, huffmannode*& parent);//���������ϳ�һ����
public:
	int num;//�����ַ��ĸ���
	string* codes;//�ַ������飬���ڴ洢ÿ���ַ��ı���
	char* keys;//�ַ����飬�洢���ֵ��ַ�
	float* times;//�洢ÿ���ַ����ֵĴ���
	HuffmanTree()//���캯��
	{
		codes = 0;
		times = 0;
		root = 0;
		num = 0;
		keys = 0;
	}
	~HuffmanTree() //��������
	{
		deletetree(root);
		delete[]times;
		delete[]codes;
		delete[]keys;
	} 
	huffmannode* getroot() { return root; }
	void deletetree(huffmannode* root);//ɾ����
	void count(string file);//ͳ���ַ�������ֵ�Ƶ��
	void Initialization(char keys[],float w[], int n); //��ʼ����������
	void Encoding(huffmannode* root, string s);//����������
	void setCodeArray(huffmannode* root);//��дcodes[]�ַ������������
	void savehuffmantree();//�������������ļ�hfmTree,�洢����ÿ���ַ��Լ��ַ����ֵĴ���
	void FileTran(string file);  //���ļ�ToBeTran�е����Ľ��б��룬Ȼ�󽫽������CodeFile��
	void decoding();   //����������ΪӢ������
	void Print(); //���ļ�CodeFile�Խ��ո�ʽ��ʾ���ն��ϣ�ÿ��50�����롣ͬʱ�����ַ���ʽ�ı����ļ�д���ļ�CodePrin�С�
	void TreePrinting(huffmannode* t, int level);//�������ڴ��еĹ���������ֱ�۵ķ�ʽ(���������ʽ)��ʾ���ն��ϣ�ͬʱ�����ַ���ʽ�Ĺ�������д���ļ�TreePrint��
	
};


///////////////////////////////////
////��������HuffmanTree���ʵ��/////
//////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//  ɾ��������
//  �������ܣ���������ɾ��
//����������
//       root ��ʾ�����
//��������ֵ��
//       root ����� 

void HuffmanTree::deletetree(huffmannode* root)
{
	if (root == 0)return;
	else
	{
		deletetree(root->leftchild);
		deletetree(root->rightchild);
		delete root;
	}
}



//////////////////////////////////////////////////////////////////////////////
//  ͳ���ַ���Ƶ�Ⱥ���
//  �������ܣ�ͳ���ļ��е��ַ����ַ�Ƶ��
//����������
//       file ��ʾ�ļ���
//��������ֵ��
//       ��

void HuffmanTree::count(string file)//ͳ���ַ����ַ�Ƶ��
{
	int counts[128];
	memset(counts, 0, sizeof(counts));
	ifstream in(file, ios::in);
	if (!in)
	{
		cout << "�ļ���ʧ�ܣ�";
		return ;
	}
	char c;
	while (in.peek() != EOF)
	{
		c = in.get(); //����һ���ַ�
		counts[c - '\0']++;
	}
	int num = 0;//ͳ�Ƴ��ֵ��ַ�����
	for (int i = 31; i < 128; i++)//����ַ������Ӧ��Ƶ��
	{
		if (counts[i] != 0)
		{
			c = i - 0;
			cout << c<< " " << counts[i] << " " << endl;
			num++;
		}
	}
	cout << "�ַ�����Ϊ" << num << endl;
	in.close();
}



//////////////////////////////////////////////////////////////////////////////
//  ��ʼ������
//  �������ܣ�������������
//����������
//       char keys[]  ��ʾ�ַ�����
//       float w[]    ��ʾ�ַ�Ƶ������
//       int n        ��ʾ�ַ�����
//��������ֵ��
//       ��

void HuffmanTree::Initialization(char keys[],float w[], int n)//��ʼ����������
{
	MyHeap<huffmannode> hp;
	huffmannode*parent=0,* first, * second, * work,temp;
	for (int i = 0; i < n; i++)//���������С��
	{
		work = new huffmannode();
		work->leftchild = 0;
		work->rightchild = 0;
		work->parent = work;
		work->key = keys[i];
		work->times = w[i];
		hp.Insert(*work);
	}
	//ִ��n-1�β������Խ�����������
	for (int i = 1; i <= n - 1; i++)
	{
		hp.Remove(temp);
		first = temp.parent;
		hp.Remove(temp);
		second = temp.parent;
		mergetree(first, second, parent);//�ϲ�
		hp.Insert(*parent);//�½ڵ�������
	}
	root = parent;
}




//////////////////////////////////////////////////////////////////////////////
//  �ϲ�����
//  �������ܣ����������ϲ���һ��
//����������
//       huffmannode* bt1      ��ʾ��һ���ϲ��������
//       huffmannode* bt2      ��ʾ�ڶ����ϲ��������
//       huffmannode*& parent  ��ʾ�����ĸ����
//��������ֵ��
//       ��
void HuffmanTree::mergetree(huffmannode* bt1, huffmannode* bt2, huffmannode*& parent)//���������ϳ�һ��
{
	
	parent = new huffmannode;
	parent->leftchild = bt1;
	parent->rightchild = bt2;
	parent->parent = parent;
	parent->times = bt1->times + bt2->times;
	parent->key = '\0';//����Ҷ�ӽ���ֵ���ó�'\0'
	bt1->parent = bt2->parent = parent;


	
}



//////////////////////////////////////////////////////////////////////////////
//  ���뺯��
//  �������ܣ�Ϊÿ��������
//����������
//       huffmannode* root    ��ʾ�������������
//       string s             ��ʾ��ǰ���ı���
//��������ֵ��
//       ��

void HuffmanTree::Encoding(huffmannode* root, string s)//���������룬�����߼�¼��0���������߼�¼��1��
{
	if (root == 0)
		return;
	s = s + '0';//�ȷ���������,s��Ҫ����'0'
	if (root->leftchild != 0)
	{
		root->leftchild->code = s;
	}
	Encoding(root->leftchild, s);//����������

	s[s.size() - 1] = '1';//������֮ǰ�����һ�����뻻��1
	if (root->rightchild != 0)
	{
		root->rightchild->code = s;
	}
	Encoding(root->rightchild, s);//����������

}



//////////////////////////////////////////////////////////////////////////////
//  ��д�ַ�������
//  �������ܣ���Ҷ�ӽ���Ӧ�ı�������Ӧ�ַ�������
//����������
//       huffmannode* root     ��ʾ�������������
//��������ֵ��
//       ��

void HuffmanTree::setCodeArray(huffmannode* root)//��д�ַ������������
{
	if (root == 0)return;
	if (root->leftchild == 0 && root->rightchild == 0)
	{
		for (int i = 0; i < num; i++)//�ҵ���Ӧ�ı��
			if (keys[i] == root->key)codes[i] = root->code;
	}
	setCodeArray(root->leftchild);
	setCodeArray(root->rightchild);

}



//////////////////////////////////////////////////////////////////////////////
//  ��д�ַ�������
//  �������ܣ���Ҷ�ӽ���Ӧ�ı�������Ӧ�ַ�������
//����������
//       huffmannode* root     ��ʾ�������������
//��������ֵ��
//       ��
void HuffmanTree::savehuffmantree()//�������������ļ�hfmTree.txt,�洢����ÿ���ַ��Լ��ַ����ֵĴ���
{
	ofstream file("hfmTree.txt", ios::out);
	if (!file)
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
		return;
	}
	file << "�ַ�" << "    " << "Ƶ��" << "         "<<"����"<<endl;
	for (int i = 0; i < num; i++)//д����ַ���Ƶ��
	{
		file << keys[i] << "          " << times[i] <<"         "<<codes[i]<< endl;
		
	}
	file.close();
	cout << "���������Ѵ���hfmTree�ļ���" << endl;
}



//////////////////////////////////////////////////////////////////////////////
//  ����Ӣ�����º���
//  �������ܣ����ļ��е����Ľ��б��룬Ȼ�󽫽������CodeFile�ļ���
//����������
//       string file   ��ʾ��Ҫ������ļ���
//��������ֵ��
//       ��
void HuffmanTree::FileTran(string file)  
{
	ofstream out("CodeFile.txt", ios::out);
	ifstream in(file, ios::in);
	if (!in || !out)
	{
		cout << "���ļ�ʧ�ܣ�" << endl;
		return;
	}
	char c='0';//���ļ����������ַ�
	while (c!='#')
	{
		c = in.get();
		for (int u = 0;u <num;u++)//�ҵ�c�ַ���Ӧcodes������ĸ��±�
		{
			if (keys[u] == c)//�ҵ�
			{
				for (int i = 0; i < codes[u].length(); i++)//��c�ı���д��CodeFile��
				{
					out<<codes[u][i];
					
				}
				break;
			}
		}
	}
	out << "#" << endl;
	in.close();
	out.close();
	cout << "�������Ѵ���CodeFile�ļ���" << endl;
}



//////////////////////////////////////////////////////////////////////////////
//  ���뺯��
//  �������ܣ�����������ΪӢ������ ���ļ�CodeFile�еĴ���������룬��������ļ�TextFile��
//����������
//       ��
//��������ֵ��
//       ��

void HuffmanTree::decoding()
{
	ofstream out("TextFile.txt", ios::out);
	ifstream in("CodeFile.txt", ios::in);
	if (!in || !out)
	{
		cout << "���ļ�ʧ�ܣ�" << endl;
		return;
	}
	char c='0';
	huffmannode* current = root;
	while (c != '#')
	{
		c = in.get();

		if (c == '0')
		{
			current = current->leftchild;
		}
		else if (c == '1')
		{
			current = current->rightchild;
		}
		if (current->leftchild == 0 && current->rightchild == 0)
		{
			c = current->key;
			out << c;
			current = root;//��λ����������ʼ������
		}
	}
	out.close();
	in.close();
	cout << "�����Ѵ���TextFile�ļ���" << endl;

}



//////////////////////////////////////////////////////////////////////////////
//  ��ӡ���뺯��
//  �������ܣ����ļ�CodeFile�Խ��ո�ʽ��ʾ���ն��ϣ�ÿ��50�����롣ͬʱ�����ַ���ʽ�ı����ļ�д���ļ�CodePrin��
//����������
//       ��
//��������ֵ��
//       ��

void HuffmanTree::Print() 
{
	ofstream out("CodePrin.txt", ios::out);
	ifstream file("CodeFile.txt", ios::in);
	if (!file||!out)
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}
	char c='0';
	int count = 0;
	while (c != '#')
	{
		file >> c;
		cout << c;
		out << c;
		count++;
		if (count % 50 == 0)
		{
			cout << endl;
			out << endl;
		}
	}
	out.close();
	file.close();
	cout << "�ն������Ѵ���CodePrin�ļ���" << endl;
}



//////////////////////////////////////////////////////////////////////////////
//  ��ӡ������������
//  �������ܣ��������ڴ��еĹ���������ֱ�۵ķ�ʽ(���������ʽ)��ʾ���ն��ϣ�ͬʱ�����ַ���ʽ�Ĺ�������д���ļ�TreePrint��
//����������
//       huffmannode* root     ��ʾ�������������
//       int level             ��ʾ���Ĳ���
//��������ֵ��
//       ��
void HuffmanTree::TreePrinting(huffmannode*t,int level)
                                                       
{
	ofstream file("TreePrint.txt", ios::out|ios::app);
	if (!file)
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}
	
	int i;
	if (t == 0)
	{
		return;
	}
	TreePrinting(t->rightchild, level + 1);
	for (i = 0;i < level;i++)
	{
		cout<<"     ";
		file << "     ";
	}
	if (t->key == ' ')
	{
		cout << "0" << endl;
		file << "0" << endl;
	}
	else if (t->key == '\0')
	{
		cout << "#" << endl;
		file << "#" << endl;
	}
	else
	{
		cout << t->key << endl;
		file << t->key << endl;
	}

	TreePrinting(t->leftchild, level + 1);
}
