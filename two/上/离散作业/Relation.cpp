#include "stdio.h"
#include <fstream>
#include <string.h>
#include <iostream>

using namespace std;

class Relation
{
protected:
	int dimension;
	int *Matrix;
public:
	//====================================================================================================
	Relation(int d = 1);										//构造一个维数为d（如不指定，默认为d=1）的空关系
	Relation(int d, const int *M);									//由关系矩阵的维数和一个关系矩阵的值的数组构造关系
	Relation(const Relation &r);									//拷贝构造函数
	Relation &operator =(const Relation &r);							//赋值运算符重载
	~Relation();											//析构函数
	//====================================================================================================
	int GetDimension() const;									//返回关系矩阵的维数
	int GetatPosition(int row, int column) const;							//得到关系矩阵的第row行第column列的值，如果越界则返回-1
	int operator() (int row, int column) const;							//可以使用R(i,j)来得到关系矩阵的第row行第column列的值，
													//如果越界则返回-1
    	bool GetMatrix(int *result) const;								//得到关系矩阵的值
    	//====================================================================================================
    	void Output() const;										//在屏幕显示该关系的关系矩阵
    	friend ostream &operator <<(ostream &os, const Relation &t);					//以流的方式输出，类似于Output和OutputtoFile
	//====================================================================================================
	bool IsReflexive() const;									//判断该关系的性质
	bool IsIrreflexive() const;									//判断该关系的性质
	bool IsSymmetric() const;									//判断该关系的性质
	bool IsAsymmetric() const;									//判断该关系的性质
	bool IsAntisymmetric() const;									//判断该关系的性质
	bool IsTransitive() const;									//判断该关系的性质
	//====================================================================================================
	Relation ReflexiveClosure() const;								//返回自反闭包的关系矩阵
	Relation SymmetricClosure() const;								//返回对称闭包的关系矩阵
	Relation TransitiveClosure() const;								//返回传递闭包的关系矩阵
	//====================================================================================================
	bool IsEquivalence() const;									//判断该关系是否是一个等价关系
	//====================================================================================================
	bool EquiClasses(int *result) const;								//result是一个大小为dimension的数组，如果当前关系
													//是等价关系，则result中存放的是当前关系的各个元素
													//所在等价类的编号，返回true；否则result数组中任一
													//项的值都是-1，并返回false。
	/*
	你还可以自己定义
	void Relation::Union(Relation r);
	void Relation::Complement();
	void Relation::Intersection(Relation r);
	void Relation::Inverse();
	void Relation::Compostion(Relation r);
    	等等
	*/
};
//---------------------------------------------------------------------------------------------------

Relation::Relation(int d)
{
	//构造一个维数为d的空关系
	dimension = d;
	Matrix = new int[dimension * dimension];
	memset(Matrix, 0, sizeof(int) * dimension * dimension);
}

Relation::Relation(int d, const int *M)
{
	//由关系矩阵的维数和一个关系矩阵的值的数组构造关系
	dimension = d;
	Matrix = new int[dimension * dimension];
	memcpy(Matrix, M, sizeof(int) * dimension * dimension);
}

Relation::~Relation()
{
	//析构函数
	delete []Matrix;
}

Relation::Relation(const Relation &r)
{
	dimension = r.dimension;
	Matrix = new int[dimension * dimension];
	memcpy(Matrix, r.Matrix, sizeof(int)*dimension * dimension);
}

Relation &Relation::operator =(const Relation &r)
{
	dimension = r.dimension;
	Matrix = new int[dimension * dimension];
	memcpy(Matrix, r.Matrix, sizeof(int)*dimension * dimension);
	return *this;
}

int Relation::GetDimension() const
{
	//得到关系矩阵的维数
	return dimension;
}

int Relation::GetatPosition(int row, int column) const
{
	//得到关系矩阵的第row行第column列的值，如果越界则返回-1
	if (row >= 0 && row < dimension && column >= 0 && column < dimension)
		return Matrix[row * dimension + column];
    	else
		return -1;
}

int Relation::operator()(int row, int column) const
{
	//可以使用R(i,j)来得到关系矩阵的第row行第column列的值，如果越界则返回-1
	if (row >= 0 && row < dimension && column >= 0 && column < dimension)
		return Matrix[row * dimension + column];
	else
		return -1;
}

bool Relation::GetMatrix(int *result) const
{
	//得到关系矩阵的值
	if (result != NULL)
	{
		memcpy(result, Matrix, sizeof(int)*dimension * dimension);
		return true;
	}
	return false;
}

void Relation::Output() const
{
    //在屏幕显示该关系的关系矩阵
    int row, column;
    cout<<dimension<<endl;
	for (row = 0; row < dimension; row++)
    {
        for (column = 0; column < dimension; column++)
        {
            cout << (*this)(row, column);
        }
        cout << "\n";
    }
}

ostream &operator <<(ostream &os, const Relation &r)
{
	int row, column;
	os<<r.GetDimension()<<endl;
	for (row = 0; row < r.GetDimension(); row++)
	{
		for (column = 0; column < r.GetDimension(); column++)
		{
			os << r(row, column);
		}
		os << endl;
	}
	return os;
}

bool Relation::IsReflexive() const
{
	//ToDo：判断该关系的性质
	return true;
}

bool Relation::IsIrreflexive() const
{
	//ToDo：判断该关系的性质
	return true;
}

bool Relation::IsSymmetric() const
{
	//ToDo：判断该关系的性质
	return true;
}

bool Relation::IsAsymmetric() const
{
	//ToDo：判断该关系的性质
	return true;
}

bool Relation::IsAntisymmetric() const
{
	//ToDo：判断该关系的性质
	return true;
}

bool Relation::IsTransitive() const
{
	//ToDo：判断该关系的性质
	return true;
}

bool Relation::IsEquivalence() const
{
	//ToDo：判断该关系是否是一个等价关系
	return true;
}

Relation Relation::ReflexiveClosure() const
{
	int *m = new int[dimension * dimension];
	GetMatrix(m);

	/*
	ToDo: 修改*m，得到自反闭包的关系矩阵，由之构造对象r并返回
	*/

	Relation r(dimension, m);
	delete []m;
	return r;
}

Relation Relation::SymmetricClosure() const
{
	int *m = new int[dimension * dimension];
	GetMatrix(m);

	/*
	ToDo: 修改*m，得到对称闭包的关系矩阵，由之构造对象r并返回
	*/

	Relation r(dimension, m);
	delete []m;
	return r;
}

Relation Relation::TransitiveClosure() const
{
	int *m = new int[dimension * dimension];
	GetMatrix(m);

	/*
	ToDo: 修改*m，得到传递闭包的关系矩阵，由之构造对象r并返回
	*/

	Relation r(dimension, m);
	delete []m;
	return r;
}

bool Relation::EquiClasses(int *result) const
{
	/*
	ToDo: result是一个大小为dimension的数组，如果当前关系是等价关系，则result中存放的是当前关系的各个元素
	所在等价类的编号（编号从0开始，且按照各个元素的值从小到大考虑其所在的等价类编号），并返回true；否则
	result数组中任一项的值都是-1，并返回false。
	*/
	memset(result, 255, sizeof(int) * dimension);
	return false;
}

//---------------------------------------------------------------------------------------------------

int main()
{	
	int row, col, d;
	Relation r;
	Relation rr;

	cin>>d;
	int *M = new int[d * d];

	for (row = 0; row < d; row++)
		for (col = 0; col < d; col++)
			cin>>M[row * d + col];

	r = Relation(d, M);
	delete []M;

	cout<<"Is it reflexive: "<<(r.IsReflexive()?"YES":"NO")<<endl;
	cout<<"Is it irreflexive: "<<(r.IsIrreflexive()?"YES":"NO")<<endl;		
	cout<<"Is it symmetric: "<<(r.IsSymmetric()?"YES":"NO")<<endl;
	cout<<"Is it asymmetric: "<<(r.IsAsymmetric()?"YES":"NO")<<endl;
	cout<<"Is it antisymmetric: "<<(r.IsAntisymmetric()?"YES":"NO")<<endl;
	cout<<"Is it transitive: "<<(r.IsTransitive()?"YES":"NO")<<endl;

	cout<<endl;
	rr=r.ReflexiveClosure();
	cout<<"Its reflexive closure is:"<<endl;
	rr.Output();
	rr=r.SymmetricClosure();
	cout<<"Its symmetric closure is:"<<endl;
	rr.Output();
	rr=r.TransitiveClosure();
	cout<<"Its transitive closure is:"<<endl;
	rr.Output();
	
	cout<<endl;
	cout<<"Is it an equivalent relation: "<<(r.IsEquivalence()?"YES":"NO")<<endl;
	
	if (r.IsEquivalence())
	{
		int i;	
		int *EClass = new int[r.GetDimension()];
		r.EquiClasses(EClass);
		cout<<"The equivalent classes are:"<<endl;
		for (i=0; i < r.GetDimension(); i++)
		{
			cout<<i;
			if (i != r.GetDimension()-1)
				cout<<' ';
		}
		cout<<endl;
		for (i=0; i < r.GetDimension(); i++)
		{
			cout<<EClass[i];
			if (i != r.GetDimension()-1)
				cout<<' ';
		}
		cout<<endl;
		delete[] EClass;
	}

	return 0;
}