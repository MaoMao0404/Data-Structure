
//      程序名：huffmantree.cpp
//      程序功能：哈夫曼树建立及编码解码等
//      作者：毛婧一
//      日期：2021.12.20
//          

#pragma once
#include<iostream>
#include<fstream>
using namespace std;
#include "minheap.h"

///////////////////////////////
////huffmannode结构体的定义/////
///////////////////////////////
struct huffmannode
{
	char key;//字母
	float times;//结点数据 频度
	string code;//对应编码
	huffmannode* leftchild, * rightchild;
	huffmannode* parent;
	huffmannode() :leftchild(0), rightchild(0), parent(0)
	{
		key = '\0';
		times = 0;
		code = "";
	}
	
	bool operator<=(huffmannode& R) { return times <= R.times; }//重载<=运算符
	bool operator>(huffmannode& R) { return times > R.times; }//重载>运算符
};



///////////////////////////////
////HuffmanTree类的定义/////////
///////////////////////////////
class HuffmanTree
{protected:

	huffmannode* root;
	void mergetree(huffmannode* bt1, huffmannode* bt2, huffmannode*& parent);//将两棵树合成一棵树
public:
	int num;//输入字符的个数
	string* codes;//字符串数组，用于存储每个字符的编码
	char* keys;//字符数组，存储出现的字符
	float* times;//存储每个字符出现的次数
	HuffmanTree()//构造函数
	{
		codes = 0;
		times = 0;
		root = 0;
		num = 0;
		keys = 0;
	}
	~HuffmanTree() //析构函数
	{
		deletetree(root);
		delete[]times;
		delete[]codes;
		delete[]keys;
	} 
	huffmannode* getroot() { return root; }
	void deletetree(huffmannode* root);//删除树
	void count(string file);//统计字符及其出现的频度
	void Initialization(char keys[],float w[], int n); //初始化哈夫曼树
	void Encoding(huffmannode* root, string s);//哈夫曼编码
	void setCodeArray(huffmannode* root);//编写codes[]字符串数组的内容
	void savehuffmantree();//哈夫曼树存入文件hfmTree,存储的是每个字符以及字符出现的次数
	void FileTran(string file);  //对文件ToBeTran中的正文进行编码，然后将结果存入CodeFile中
	void decoding();   //哈夫曼译码为英文文章
	void Print(); //将文件CodeFile以紧凑格式显示在终端上，每行50个代码。同时将此字符形式的编码文件写入文件CodePrin中。
	void TreePrinting(huffmannode* t, int level);//将已在内存中的哈夫曼树以直观的方式(树或凹入表形式)显示在终端上，同时将此字符形式的哈夫曼树写入文件TreePrint中
	
};


///////////////////////////////////
////接下来是HuffmanTree类的实现/////
//////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//  删除树函数
//  函数功能：将整棵树删除
//函数参数：
//       root 表示根结点
//参数返回值：
//       root 根结点 

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
//  统计字符和频度函数
//  函数功能：统计文件中的字符和字符频度
//函数参数：
//       file 表示文件名
//参数返回值：
//       无

void HuffmanTree::count(string file)//统计字符和字符频度
{
	int counts[128];
	memset(counts, 0, sizeof(counts));
	ifstream in(file, ios::in);
	if (!in)
	{
		cout << "文件打开失败！";
		return ;
	}
	char c;
	while (in.peek() != EOF)
	{
		c = in.get(); //读入一个字符
		counts[c - '\0']++;
	}
	int num = 0;//统计出现的字符个数
	for (int i = 31; i < 128; i++)//输出字符及其对应的频度
	{
		if (counts[i] != 0)
		{
			c = i - 0;
			cout << c<< " " << counts[i] << " " << endl;
			num++;
		}
	}
	cout << "字符个数为" << num << endl;
	in.close();
}



//////////////////////////////////////////////////////////////////////////////
//  初始化函数
//  函数功能：建立哈夫曼树
//函数参数：
//       char keys[]  表示字符数组
//       float w[]    表示字符频度数组
//       int n        表示字符个数
//参数返回值：
//       无

void HuffmanTree::Initialization(char keys[],float w[], int n)//初始化哈夫曼树
{
	MyHeap<huffmannode> hp;
	huffmannode*parent=0,* first, * second, * work,temp;
	for (int i = 0; i < n; i++)//逐个插入最小堆
	{
		work = new huffmannode();
		work->leftchild = 0;
		work->rightchild = 0;
		work->parent = work;
		work->key = keys[i];
		work->times = w[i];
		hp.Insert(*work);
	}
	//执行n-1次操作，以建立哈夫曼树
	for (int i = 1; i <= n - 1; i++)
	{
		hp.Remove(temp);
		first = temp.parent;
		hp.Remove(temp);
		second = temp.parent;
		mergetree(first, second, parent);//合并
		hp.Insert(*parent);//新节点插入堆中
	}
	root = parent;
}




//////////////////////////////////////////////////////////////////////////////
//  合并函数
//  函数功能：将两棵树合并成一棵
//函数参数：
//       huffmannode* bt1      表示第一个合并树根结点
//       huffmannode* bt2      表示第二个合并树根结点
//       huffmannode*& parent  表示新树的根结点
//参数返回值：
//       无
void HuffmanTree::mergetree(huffmannode* bt1, huffmannode* bt2, huffmannode*& parent)//将两棵树合成一棵
{
	
	parent = new huffmannode;
	parent->leftchild = bt1;
	parent->rightchild = bt2;
	parent->parent = parent;
	parent->times = bt1->times + bt2->times;
	parent->key = '\0';//不是叶子结点的值设置成'\0'
	bt1->parent = bt2->parent = parent;


	
}



//////////////////////////////////////////////////////////////////////////////
//  编码函数
//  函数功能：为每个结点编码
//函数参数：
//       huffmannode* root    表示哈夫曼树根结点
//       string s             表示当前结点的编码
//参数返回值：
//       无

void HuffmanTree::Encoding(huffmannode* root, string s)//哈夫曼编码，向左走记录‘0’，向右走记录‘1’
{
	if (root == 0)
		return;
	s = s + '0';//先访问左子树,s需要加上'0'
	if (root->leftchild != 0)
	{
		root->leftchild->code = s;
	}
	Encoding(root->leftchild, s);//遍历左子树

	s[s.size() - 1] = '1';//向右走之前，最后一个编码换成1
	if (root->rightchild != 0)
	{
		root->rightchild->code = s;
	}
	Encoding(root->rightchild, s);//遍历右子树

}



//////////////////////////////////////////////////////////////////////////////
//  编写字符串函数
//  函数功能：将叶子结点对应的编码存入对应字符串数组
//函数参数：
//       huffmannode* root     表示哈夫曼树根结点
//参数返回值：
//       无

void HuffmanTree::setCodeArray(huffmannode* root)//编写字符串数组的内容
{
	if (root == 0)return;
	if (root->leftchild == 0 && root->rightchild == 0)
	{
		for (int i = 0; i < num; i++)//找到对应的编号
			if (keys[i] == root->key)codes[i] = root->code;
	}
	setCodeArray(root->leftchild);
	setCodeArray(root->rightchild);

}



//////////////////////////////////////////////////////////////////////////////
//  编写字符串函数
//  函数功能：将叶子结点对应的编码存入对应字符串数组
//函数参数：
//       huffmannode* root     表示哈夫曼树根结点
//参数返回值：
//       无
void HuffmanTree::savehuffmantree()//哈夫曼树存入文件hfmTree.txt,存储的是每个字符以及字符出现的次数
{
	ofstream file("hfmTree.txt", ios::out);
	if (!file)
	{
		cout << "文件打开失败！" << endl;
		return;
	}
	file << "字符" << "    " << "频度" << "         "<<"编码"<<endl;
	for (int i = 0; i < num; i++)//写入各字符和频度
	{
		file << keys[i] << "          " << times[i] <<"         "<<codes[i]<< endl;
		
	}
	file.close();
	cout << "哈夫曼树已存入hfmTree文件中" << endl;
}



//////////////////////////////////////////////////////////////////////////////
//  编码英文文章函数
//  函数功能：对文件中的正文进行编码，然后将结果存入CodeFile文件中
//函数参数：
//       string file   表示需要编码的文件名
//参数返回值：
//       无
void HuffmanTree::FileTran(string file)  
{
	ofstream out("CodeFile.txt", ios::out);
	ifstream in(file, ios::in);
	if (!in || !out)
	{
		cout << "打开文件失败！" << endl;
		return;
	}
	char c='0';//从文件读出来的字符
	while (c!='#')
	{
		c = in.get();
		for (int u = 0;u <num;u++)//找到c字符对应codes数组的哪个下标
		{
			if (keys[u] == c)//找到
			{
				for (int i = 0; i < codes[u].length(); i++)//将c的编码写到CodeFile中
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
	cout << "编码结果已存入CodeFile文件中" << endl;
}



//////////////////////////////////////////////////////////////////////////////
//  译码函数
//  函数功能：哈夫曼译码为英文文章 将文件CodeFile中的代码进行译码，结果存入文件TextFile中
//函数参数：
//       无
//参数返回值：
//       无

void HuffmanTree::decoding()
{
	ofstream out("TextFile.txt", ios::out);
	ifstream in("CodeFile.txt", ios::in);
	if (!in || !out)
	{
		cout << "打开文件失败！" << endl;
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
			current = root;//复位，从树根开始往下走
		}
	}
	out.close();
	in.close();
	cout << "译码已存入TextFile文件中" << endl;

}



//////////////////////////////////////////////////////////////////////////////
//  打印编码函数
//  函数功能：将文件CodeFile以紧凑格式显示在终端上，每行50个代码。同时将此字符形式的编码文件写入文件CodePrin中
//函数参数：
//       无
//参数返回值：
//       无

void HuffmanTree::Print() 
{
	ofstream out("CodePrin.txt", ios::out);
	ifstream file("CodeFile.txt", ios::in);
	if (!file||!out)
	{
		cout << "文件打开失败" << endl;
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
	cout << "终端内容已存入CodePrin文件中" << endl;
}



//////////////////////////////////////////////////////////////////////////////
//  打印哈夫曼树函数
//  函数功能：将已在内存中的哈夫曼树以直观的方式(树或凹入表形式)显示在终端上，同时将此字符形式的哈夫曼树写入文件TreePrint中
//函数参数：
//       huffmannode* root     表示哈夫曼树根结点
//       int level             表示树的层数
//参数返回值：
//       无
void HuffmanTree::TreePrinting(huffmannode*t,int level)
                                                       
{
	ofstream file("TreePrint.txt", ios::out|ios::app);
	if (!file)
	{
		cout << "文件打开失败" << endl;
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
