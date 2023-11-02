#pragma once
// author: �������� ���������
// ����� Heap

#include<iostream>

template <typename T>
class Heap
{
private:
	// hlist ��������� �� ������, ������� ����� ���� ����������� ������
	// ������������� (inArray == 0) ��� ������� ��� �������� (inArray == 1)
	T* hlist;
	//int inArray;

	// ������������ � ������� ������� ��������
	int maxheapsize;
	int heapsize; // ���������� ����� ������

	// ������� �������������� ������������� ���������
	void FilterDown(int i);
	void FilterUp(int i);

public:
	// ������������ � ����������
	Heap(int maxsize) { // ������� ������ ��������
		if (maxsize <= 0) {
			std::cout << "������������ ����������� �������";
		}
		maxheapsize = maxsize;
		heapsize = 0;
		hlist = new T[maxheapsize];
	}

	Heap(const T* arr, int n, int maxsize) { // ������������� arr � �������� 
		int j, currentpos;
		// n <= 0 �������� ������������ �������� �������
		if ((n <= 0) || (maxsize <= 0)) {
			std::cout << "������������ ����������� �������";
		}

		// ������������ n ��� ��������� ������� �������� � ������������� ������� ��������.
		// ���������� ������ �rr � ������ ��������
		maxheapsize = maxsize;
		heapsize = n;
		hlist = new T[maxsize];

		for (int i = 0; i < n; i++) {
			hlist[i] = arr[i];
		}

		// ��������� ���������� currentpos ������ ���������� ��������.
		// �������� FilterDown � ����� � ��������� currentpos..0
		currentpos = (heapsize - 2) / 2;
		while (currentpos >= 0)
		{
			// ��������� ������� ��������������� ��� ���������
			// � ������ hlist[currentpos]
			FilterDown(currentpos);
			currentpos--;
		}

	} 

	~Heap() { // ����������
		delete[] hlist;
	} 


	// ������ ��������� �������
	//int ListSize() const;
	//int ListEmpty() const;
	//int ListFull() const;
	void Insert(const T& item);
	void Delete();
	void ClearList();
	void PrintHeap();
	// ����� ��� ������ �������� � ����
	int Search(const T& element);
	T GetMin();


};

template <class T>
T Heap<T>::GetMin() {
	return hlist[0];
}

// ������� ��� �������������� ��������, ������� � ������� i,
// ����������� ����� �� ������, �������� �� ������ � ������.
// ������ �������� �������, ���� ��� ������ ��������
template <class T>
void Heap<T>::FilterUp(int i)
{
	int currentpos, parentpos;
	T target;
	// currentpos � ������ ������� ������� �� ���� �������.
	// target � ����������� ��������, ��� �������� ����������
	// ���������� ������� � ��������
	currentpos = i;
	parentpos = (i - 1) / 2;
	target = hlist[i];

	// ����������� � ����� �� ���� ���������
	while (currentpos != 0)
	{
		// ���� �������� <= target, �� ��� � �������,
		if (hlist[parentpos] <= target)
			break;
		else
			// �������� ������� �������� � ����� � �������� �������
			// ��� �������� ���������� ��������
		{
			// ����������� ������ �� ������������ ������� � �������.
			// ��������� ������������ ������� �������.
			// ��������� ���������� ��������
			hlist[currentpos] = hlist[parentpos];
			currentpos = parentpos;
			parentpos = (currentpos - 1) / 2;
		}
	}
	// ���������� ������� �������, ��������� ���� target
	hlist[currentpos] = target;
}

// �������� � �������� ����� ������� � ������������ �� ���������
template <typename T>
void Heap<T>::Insert(const T& item)
{
	// ���������, ��������� �� �������� � �����, ���� ��
	if (heapsize == maxheapsize) {
		std::cout<< "�������� ���������";
	}
	else {
		// �������� ������� � ����� �������� � ��������� heapsize.
		// ������� FilterUp ��� �������������� �������������� ������������
		hlist[heapsize] = item;
		FilterUp(heapsize);
		heapsize++;
	}
}

// ������� ��� �������������� ��������, ������� � ������� i,
// ������ ������� �������� � ���� ���, ����� ���������,
// ������������ � ���� i, ���� ���������
template <typename T>
void Heap<T>::FilterDown(int i) 
{
	int currentpos, childpos;
	T target;

	// ������ � ���� i � ��������� ��� �������� ���������� target
	currentpos = i;
	target = hlist[i];

	// ��������� ������ ������ ���� � ������ �������� ���� �� ����,
	// ����������� ����� ������� ������� �� ����� ������
	childpos = 2 * i + 1;

	while (childpos < heapsize) // ���� �� ����� ������
	{
		// ������ ������� ���� ����� childpos+1. ��������� ����������
		// childpos ������ ����������� �� ���� �������
		if ((childpos + 1 < heapsize) && (hlist[childpos + 1] <= hlist[childpos]))
			childpos = childpos + 1;

		// ���� �������� ������ ����, �������� � �������, �����
		if (target <= hlist[childpos])
			break;
		else
		{
			// ����������� �������� �������� ���� � ������������ ����.
			// ������ ������� �������� ���� �� ������
			hlist[currentpos] = hlist[childpos];
			// �������� ������� � ���������� ������������
			currentpos = childpos;
			childpos = 2 * currentpos + 1;
		}
	}

	// ��������� target � ������ ��� ������� ��������� �������
	hlist[currentpos] = target;
}

// ���������� �������� ��������� �������� � �������� ��������.
// ������� �������� �������� �� ������ �������� ������ �� �����
// ������ ��������� �� ������ � ����������� ���������
template <typename T>
void Heap<T>::Delete()
{
	T tempitem;

	// ���������, ����� �� ��������
	if (heapsize != 0) {

		// ���������� ������ � tempitem. �������� ������ ��������� ���������
		// �������� � ���������� ��������� ���������� heapsize
		tempitem = hlist[0];
		hlist[0] = hlist[heapsize - 1];
		heapsize--;
		// ������� FilterDown ��� ��������� ������ �������� �����
		FilterDown(0);
		// ���������� �������� �������� �����
		//return tempitem;
	}
}

//������ ���� 
template <typename T>
void Heap<T>::PrintHeap()
{
	for (int i = 0; i < heapsize; i++)
	{
		std::cout << hlist[i] << " ";
	}
	std::cout << std::endl;
}

// ����� ��� ������ �������� � ����
// ���������� ������ �������� ��� -1, ���� ������� �� ������
template <typename T>
int Heap<T>::Search(const T& element) {
	for (int i = 0; i < heapsize; i++) {
		if (hlist[i] == element)
			return i;
	}
	return -1;
}

// ������������� ������ � �� ��������
template <typename T>
void HeapSort(T* A, int n)
{
	// �����������, ������������� � � ��������
	Heap<T> heap1(A, n, n);
	T elt;
	// ���� ���������� ��������� �[n-1] ... �[1]
	//for (int i = n - 1; i >= 0; i--)
	for (int i = 0; i < n; i++)
	{
		// ��������� ���������� ������� �� �������� � ��������� ��� � A[i]
		elt = heap1.GetMin();
		A[i] = elt;
		heap1.Delete();
	}
}