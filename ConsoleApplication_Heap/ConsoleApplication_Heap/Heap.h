#pragma once
// author: Денисова Екатерина
// класс Heap

#include<iostream>

template <typename T>
class Heap
{
private:
	// hlist указывает на массив, который может быть динамически создан
	// конструктором (inArray == 0) или передан как параметр (inArray == 1)
	T* hlist;
	//int inArray;

	// максимальный и текущий размеры пирамиды
	int maxheapsize;
	int heapsize; // определяет конец списка

	// утилиты восстановления пирамидальной структуры
	void FilterDown(int i);
	void FilterUp(int i);

public:
	// конструкторы и деструктор
	Heap(int maxsize) { // создать пустую пирамиду
		if (maxsize <= 0) {
			std::cout << "Неправильная размерность массива";
		}
		maxheapsize = maxsize;
		heapsize = 0;
		hlist = new T[maxheapsize];
	}

	Heap(const T* arr, int n, int maxsize) { // преобразовать arr в пирамиду 
		int j, currentpos;
		// n <= 0 является недопустимым размером массива
		if ((n <= 0) || (maxsize <= 0)) {
			std::cout << "Неправильная размерность массива";
		}

		// использовать n для установки размера пирамиды и максимального размера пирамиды.
		// копировать массив аrr в список пирамиды
		maxheapsize = maxsize;
		heapsize = n;
		hlist = new T[maxsize];

		for (int i = 0; i < n; i++) {
			hlist[i] = arr[i];
		}

		// присвоить переменной currentpos индекс последнего родителя.
		// вызывать FilterDown в цикле с индексами currentpos..0
		currentpos = (heapsize - 2) / 2;
		while (currentpos >= 0)
		{
			// выполнить условие пирамидальности для поддерева
			// с корнем hlist[currentpos]
			FilterDown(currentpos);
			currentpos--;
		}

	} 

	~Heap() { // деструктор
		delete[] hlist;
	} 


	// методы обработки списков
	//int ListSize() const;
	//int ListEmpty() const;
	//int ListFull() const;
	void Insert(const T& item);
	void Delete();
	void ClearList();
	void PrintHeap();
	// Метод для поиска элемента в куче
	int Search(const T& element);
	T GetMin();


};

template <class T>
T Heap<T>::GetMin() {
	return hlist[0];
}

// утилита для восстановления пирамиды, начиная с индекса i,
// подниматься вверх по дереву, переходя от предка к предку.
// менять элементы местами, если сын меньше родителя
template <class T>
void Heap<T>::FilterUp(int i)
{
	int currentpos, parentpos;
	T target;
	// currentpos — индекс текущей позиции на пути предков.
	// target — вставляемое значение, для которого выбирается
	// правильная позиция в пирамиде
	currentpos = i;
	parentpos = (i - 1) / 2;
	target = hlist[i];

	// подниматься к корню по пути родителей
	while (currentpos != 0)
	{
		// если родитель <= target, то все в порядке,
		if (hlist[parentpos] <= target)
			break;
		else
			// поменять местами родителя с сыном и обновить индексы
			// для проверки следующего родителя
		{
			// переместить данные из родительской позиции в текущую.
			// назначить родительскую позицию текущей.
			// проверить следующего родителя
			hlist[currentpos] = hlist[parentpos];
			currentpos = parentpos;
			parentpos = (currentpos - 1) / 2;
		}
	}
	// правильная позиция найдена, поместить туда target
	hlist[currentpos] = target;
}

// вставить в пирамиду новый элемент и восстановить ее структуру
template <typename T>
void Heap<T>::Insert(const T& item)
{
	// проверить, заполнена ли пирамида и выйти, если да
	if (heapsize == maxheapsize) {
		std::cout<< "Пирамида заполнена";
	}
	else {
		// записать элемент в конец пирамиды и увеличить heapsize.
		// вызвать FilterUp для восстановления пирамидального упорядочения
		hlist[heapsize] = item;
		FilterUp(heapsize);
		heapsize++;
	}
}

// утилита для восстановления пирамиды, начиная с индекса i,
// менять местами родителя и сына так, чтобы поддерево,
// начинающееся в узле i, было пирамидой
template <typename T>
void Heap<T>::FilterDown(int i) 
{
	int currentpos, childpos;
	T target;

	// начать с узла i и присвоить его значение переменной target
	currentpos = i;
	target = hlist[i];

	// вычислить индекс левого сына и начать движение вниз по пути,
	// проходящему через меньших сыновей до конца списка
	childpos = 2 * i + 1;

	while (childpos < heapsize) // пока не конец списка
	{
		// индекс правого сына равен childpos+1. присвоить переменной
		// childpos индекс наименьшего из двух сыновей
		if ((childpos + 1 < heapsize) && (hlist[childpos + 1] <= hlist[childpos]))
			childpos = childpos + 1;

		// если родитель меньше сына, пирамида в порядке, выход
		if (target <= hlist[childpos])
			break;
		else
		{
			// переместить значение меньшего сына в родительский узел.
			// теперь позиция меньшего сына не занята
			hlist[currentpos] = hlist[childpos];
			// обновить индексы и продолжить сканирование
			currentpos = childpos;
			childpos = 2 * currentpos + 1;
		}
	}

	// поместить target в только что ставшую незанятой позицию
	hlist[currentpos] = target;
}

// возвратить значение корневого элемента и обновить пирамиду.
// попытка удаления элемента из пустой пирамиды влечет за собой
// выдачу сообщения об ошибке и прекращение программы
template <typename T>
void Heap<T>::Delete()
{
	T tempitem;

	// проверить, пуста ли пирамида
	if (heapsize != 0) {

		// копировать корень в tempitem. заменить корень последним элементом
		// пирамиды и произвести декремент переменной heapsize
		tempitem = hlist[0];
		hlist[0] = hlist[heapsize - 1];
		heapsize--;
		// вызвать FilterDown для установки нового значения корня
		FilterDown(0);
		// возвратить исходное значение корня
		//return tempitem;
	}
}

//печать кучи 
template <typename T>
void Heap<T>::PrintHeap()
{
	for (int i = 0; i < heapsize; i++)
	{
		std::cout << hlist[i] << " ";
	}
	std::cout << std::endl;
}

// Метод для поиска элемента в куче
// Возвращает индекс элемента или -1, если элемент не найден
template <typename T>
int Heap<T>::Search(const T& element) {
	for (int i = 0; i < heapsize; i++) {
		if (hlist[i] == element)
			return i;
	}
	return -1;
}

// отсортировать массив А по убыванию
template <typename T>
void HeapSort(T* A, int n)
{
	// конструктор, преобразующий А в пирамиду
	Heap<T> heap1(A, n, n);
	T elt;
	// цикл заполнения элементов А[n-1] ... А[1]
	//for (int i = n - 1; i >= 0; i--)
	for (int i = 0; i < n; i++)
	{
		// исключить наименьший элемент из пирамиды и запомнить его в A[i]
		elt = heap1.GetMin();
		A[i] = elt;
		heap1.Delete();
	}
}