//#include "stdio.h"
//#include <fstream>
//#include <string.h>
//#include <iostream>
//
//using namespace std;
//
//class Relation
//{
//protected:
//	int dimension;
//	int* Matrix;
//public:
//	//====================================================================================================
//	Relation(int d = 1);										//����һ��ά��Ϊd���粻ָ����Ĭ��Ϊd=1���Ŀչ�ϵ
//	Relation(int d, const int* M);									//�ɹ�ϵ�����ά����һ����ϵ�����ֵ�����鹹���ϵ
//	Relation(const Relation& r);									//�������캯��
//	Relation& operator =(const Relation& r);							//��ֵ���������
//	~Relation();											//��������
//	//====================================================================================================
//	int GetDimension() const;									//���ع�ϵ�����ά��
//	int GetatPosition(int row, int column) const;							//�õ���ϵ����ĵ�row�е�column�е�ֵ�����Խ���򷵻�-1
//	int operator() (int row, int column) const;							//����ʹ��R(i,j)���õ���ϵ����ĵ�row�е�column�е�ֵ��
//	//���Խ���򷵻�-1
//	bool GetMatrix(int* result) const;								//�õ���ϵ�����ֵ
//	//====================================================================================================
//	void Output() const;										//����Ļ��ʾ�ù�ϵ�Ĺ�ϵ����
//	friend ostream& operator <<(ostream& os, const Relation& t);					//�����ķ�ʽ�����������Output��OutputtoFile
//	//====================================================================================================
//	bool IsReflexive() const;									//�жϸù�ϵ������
//	bool IsIrreflexive() const;									//�жϸù�ϵ������
//	bool IsSymmetric() const;									//�жϸù�ϵ������
//	bool IsAsymmetric() const;									//�жϸù�ϵ������
//	bool IsAntisymmetric() const;									//�жϸù�ϵ������
//	bool IsTransitive() const;									//�жϸù�ϵ������
//	//====================================================================================================
//	Relation ReflexiveClosure() const;								//�����Է��հ��Ĺ�ϵ����
//	Relation SymmetricClosure() const;								//���ضԳƱհ��Ĺ�ϵ����
//	Relation TransitiveClosure() const;								//���ش��ݱհ��Ĺ�ϵ����
//	//====================================================================================================
//	bool IsEquivalence() const;									//�жϸù�ϵ�Ƿ���һ���ȼ۹�ϵ
//	//====================================================================================================
//	bool EquiClasses(int* result) const;								//result��һ����СΪdimension�����飬�����ǰ��ϵ
//	//�ǵȼ۹�ϵ����result�д�ŵ��ǵ�ǰ��ϵ�ĸ���Ԫ��
//	//���ڵȼ���ı�ţ�����true������result��������һ
//	//���ֵ����-1��������false��
///*
//�㻹�����Լ�����
//void Relation::Union(Relation r);
//void Relation::Complement();
//void Relation::Intersection(Relation r);
//void Relation::Inverse();
//void Relation::Compostion(Relation r);
//	�ȵ�
//*/
//};
////---------------------------------------------------------------------------------------------------
//
//Relation::Relation(int d)
//{
//	//����һ��ά��Ϊd�Ŀչ�ϵ
//	dimension = d;
//	Matrix = new int[dimension * dimension];
//	memset(Matrix, 0, sizeof(int) * dimension * dimension);
//}
//
//Relation::Relation(int d, const int* M)
//{
//	//�ɹ�ϵ�����ά����һ����ϵ�����ֵ�����鹹���ϵ
//	dimension = d;
//	Matrix = new int[dimension * dimension];
//	memcpy(Matrix, M, sizeof(int) * dimension * dimension);
//}
//
//Relation::~Relation()
//{
//	//��������
//	delete[]Matrix;
//}
//
//Relation::Relation(const Relation& r)
//{
//	dimension = r.dimension;
//	Matrix = new int[dimension * dimension];
//	memcpy(Matrix, r.Matrix, sizeof(int) * dimension * dimension);
//}
//
//Relation& Relation::operator =(const Relation& r)
//{
//	dimension = r.dimension;
//	Matrix = new int[dimension * dimension];
//	memcpy(Matrix, r.Matrix, sizeof(int) * dimension * dimension);
//	return *this;
//}
//
//int Relation::GetDimension() const
//{
//	//�õ���ϵ�����ά��
//	return dimension;
//}
//
//int Relation::GetatPosition(int row, int column) const
//{
//	//�õ���ϵ����ĵ�row�е�column�е�ֵ�����Խ���򷵻�-1
//	if (row >= 0 && row < dimension && column >= 0 && column < dimension)
//		return Matrix[row * dimension + column];
//	else
//		return -1;
//}
//
//int Relation::operator()(int row, int column) const
//{
//	//����ʹ��R(i,j)���õ���ϵ����ĵ�row�е�column�е�ֵ�����Խ���򷵻�-1
//	if (row >= 0 && row < dimension && column >= 0 && column < dimension)
//		return Matrix[row * dimension + column];
//	else
//		return -1;
//}
//
//bool Relation::GetMatrix(int* result) const
//{
//	//�õ���ϵ�����ֵ
//	if (result != NULL)
//	{
//		memcpy(result, Matrix, sizeof(int) * dimension * dimension);
//		return true;
//	}
//	return false;
//}
//
//void Relation::Output() const
//{
//	//����Ļ��ʾ�ù�ϵ�Ĺ�ϵ����
//	int row, column;
//	cout << dimension << endl;
//	for (row = 0; row < dimension; row++)
//	{
//		for (column = 0; column < dimension; column++)
//		{
//			cout << (*this)(row, column);
//		}
//		cout << "\n";
//	}
//}
//
//ostream& operator <<(ostream& os, const Relation& r)
//{
//	int row, column;
//	os << r.GetDimension() << endl;
//	for (row = 0; row < r.GetDimension(); row++)
//	{
//		for (column = 0; column < r.GetDimension(); column++)
//		{
//			os << r(row, column);
//		}
//		os << endl;
//	}
//	return os;
//}
//
//bool Relation::IsReflexive() const
//{
//	//ToDo���жϸù�ϵ������
//	for (int i = 0; i < dimension; i++) {
//		if (GetatPosition(i, i) != 1)
//			return false;
//
//	}
//	return true;
//}
//
//bool Relation::IsIrreflexive() const
//{
//	//ToDo���жϸù�ϵ������
//	for (int i = 0; i < dimension; i++) {
//		if (GetatPosition(i, i) != 0)
//			return false;
//
//	}
//	return true;
//}
//
//bool Relation::IsSymmetric() const
//{
//	int row;
//	int column;
//	for (row = 0; row < dimension; row++)
//	{
//		for (column = row + 1; column < dimension; column++)
//		{
//			if (GetatPosition(row, column) != GetatPosition(column, row)) {
//				return false;
//			}
//		}
//
//	}
//
//	//ToDo���жϸù�ϵ������
//	return true;
//}
//
//bool Relation::IsAsymmetric() const
//{
//	int row;
//	int column;
//	for (row = 0; row < dimension; row++)
//	{
//		if (GetatPosition(row, row) != 0)
//			return false;
//		for (column = row + 1; column < dimension; column++)
//		{
//			if (GetatPosition(row, column) == 1) {
//				if (GetatPosition(column, row) == 1)
//					return false;
//			}
//		}
//
//	}
//	//ToDo���жϸù�ϵ������
//	return true;
//}
//
//bool Relation::IsAntisymmetric() const
//{
//	int row;
//	int column;
//	for (row = 0; row < dimension; row++)
//	{
//		for (column = row + 1; column < dimension; column++)
//		{
//			if (GetatPosition(row, column) == 1) {
//				if (GetatPosition(column, row) == 1)
//					return false;
//			}
//		}
//
//	}
//	//ToDo���жϸù�ϵ������
//	return true;
//}
//
//bool Relation::IsTransitive() const
//{
//	int row;
//	int column;
//	for (row = 0; row < dimension; row++)
//	{
//		for (column = 0; column < dimension; column++)
//		{
//			if (GetatPosition(row, column) == 1) {
//				for (int i = 0; i < dimension; i++) {
//					if (GetatPosition(column, i) == 1) {
//
//						if (GetatPosition(row, i) == 0) {
//							return false;
//						}
//					}
//				}
//			}
//		}
//
//	}
//	//ToDo���жϸù�ϵ������
//	return true;
//}
//
//bool Relation::IsEquivalence() const
//{
//	int row;
//	int column;
//	for (row = 0; row < dimension; row++)
//	{
//		if (GetatPosition(row, row) == 0)
//			return false;
//		for (column = row + 1; column < dimension; column++)
//		{
//			if (GetatPosition(row, column) != GetatPosition(column, row)) {
//				return false;
//			}
//			if (GetatPosition(row, column) == 1) {
//				for (int i = 0; i < dimension; i++) {
//					if (GetatPosition(column, i) == 1) {
//
//						if (GetatPosition(row, i) == 0) {
//							return false;
//						}
//					}
//				}
//			}
//		}
//
//	}
//	//ToDo���жϸù�ϵ�Ƿ���һ���ȼ۹�ϵ
//	return true;
//}
//
//Relation Relation::ReflexiveClosure() const
//{
//	int* m = new int[dimension * dimension];
//	GetMatrix(m);
//	for (int i = 0; i < dimension; i++) {
//
//		m[i * dimension + i] = 1;
//	}
//	/*
//	ToDo: �޸�*m���õ��Է��հ��Ĺ�ϵ������֮�������r������
//	*/
//
//	Relation r(dimension, m);
//	delete[]m;
//	return r;
//}
//
//Relation Relation::SymmetricClosure() const
//{
//	int* m = new int[dimension * dimension];
//	GetMatrix(m);
//	int row;
//	int column;
//	for (row = 0; row < dimension; row++)
//	{
//		for (column = 0; column < dimension; column++)
//		{
//			if (m[row * dimension + column] == 1) {
//				m[column * dimension + row] = 1;
//			}
//		}
//
//	}
//	/*
//	ToDo: �޸�*m���õ��ԳƱհ��Ĺ�ϵ������֮�������r������
//	*/
//
//	Relation r(dimension, m);
//	delete[]m;
//	return r;
//}
//
//Relation Relation::TransitiveClosure() const
//{
//	int* m = new int[dimension * dimension];
//	GetMatrix(m);
//	int row;
//	int column;
//	for (int i = 0; i < dimension; i++)
//	{
//		for (row = 0; row < dimension; row++)
//		{
//			for (column = 0; column < dimension; column++)
//			{
//
//				if ( ( m[row * dimension + i] == 1 && m[i* dimension + column] == 1))
//				{
//					m[row * dimension + column] = 1;
//				}
//				else if ((m[row * dimension + column] == 1)) {
//					m[row * dimension + column] = 1;
//				}
//				else
//				{
//					m[row * dimension + column] = 0;
//				}
//			}
//		}
//	}
//	/*
//	ToDo: �޸�*m���õ����ݱհ��Ĺ�ϵ������֮�������r������
//	*/
//
//	Relation r(dimension, m);
//	delete[]m;
//	return r;
//}
//
//bool Relation::EquiClasses(int* result) const
//{
//	if (IsEquivalence()) {
//		/*
//		ToDo: result��һ����СΪdimension�����飬�����ǰ��ϵ�ǵȼ۹�ϵ����result�д�ŵ��ǵ�ǰ��ϵ�ĸ���Ԫ��
//		���ڵȼ���ı�ţ���Ŵ�0��ʼ���Ұ��ո���Ԫ�ص�ֵ��С�����������ڵĵȼ����ţ���������true������
//		result��������һ���ֵ����-1��������false��
//		*/
//		result[0] = 0;
//		int num = 0;
//		bool flag;
//		for (int i = 1; i < dimension; i++) {
//			for (int j = 0; j <= i; j++) {
//				flag = true;
//				for (int k = 0; k < dimension; k++) {
//					if (GetatPosition(k, i) != GetatPosition(k, j)) {
//						flag = false;
//						break;
//					}
//				}
//				if (flag) {
//					if (j != i) {
//						result[i] = result[j];
//					}
//					else {
//						result[i] = ++num;
//					}
//					break;
//				}
//			}
//		}
//		return true;
//	}
//
//	else {
//		memset(result, 255, sizeof(int) * dimension);
//		return false;
//
//	}
//
//}
//
////---------------------------------------------------------------------------------------------------
//
//int main()
//{
//	int row, col, d;
//	Relation r;
//	Relation rr;
//
//	cin >> d;
//	int* M = new int[d * d];
//
//	for (row = 0; row < d; row++)
//		for (col = 0; col < d; col++)
//			cin >> M[row * d + col];
//
//	r = Relation(d, M);
//	delete[]M;
//
//	cout << "Is it reflexive: " << (r.IsReflexive() ? "YES" : "NO") << endl;
//	cout << "Is it irreflexive: " << (r.IsIrreflexive() ? "YES" : "NO") << endl;
//	cout << "Is it symmetric: " << (r.IsSymmetric() ? "YES" : "NO") << endl;
//	cout << "Is it asymmetric: " << (r.IsAsymmetric() ? "YES" : "NO") << endl;
//	cout << "Is it antisymmetric: " << (r.IsAntisymmetric() ? "YES" : "NO") << endl;
//	cout << "Is it transitive: " << (r.IsTransitive() ? "YES" : "NO") << endl;
//
//	cout << endl;
//	rr = r.ReflexiveClosure();
//	cout << "Its reflexive closure is:" << endl;
//	rr.Output();
//	rr = r.SymmetricClosure();
//	cout << "Its symmetric closure is:" << endl;
//	rr.Output();
//	rr = r.TransitiveClosure();
//	cout << "Its transitive closure is:" << endl;
//	rr.Output();
//
//	cout << endl;
//	cout << "Is it an equivalent relation: " << (r.IsEquivalence() ? "YES" : "NO") << endl;
//
//	if (r.IsEquivalence())
//	{
//		int i;
//		int* EClass = new int[r.GetDimension()];
//		r.EquiClasses(EClass);
//		cout << "The equivalent classes are:" << endl;
//		for (i = 0; i < r.GetDimension(); i++)
//		{
//			cout << i;
//			if (i != r.GetDimension() - 1)
//				cout << ' ';
//		}
//		cout << endl;
//		for (i = 0; i < r.GetDimension(); i++)
//		{
//			cout << EClass[i];
//			if (i != r.GetDimension() - 1)
//				cout << ' ';
//		}
//		cout << endl;
//		delete[] EClass;
//	}
//
//	return 0;
//}