#include "pch.h"
#include <algorithm>
#include "../ConsoleApplication_Heap/Heap.h"

// author: Денисова Екатерина
// тестирование класса кучи

/*Heap<int> createHeap1() {

    // создаётся куча
    Heap<int> h(10);
    h.Insert(10);
    h.Insert(15);
    h.Insert(40);
    h.Insert(50);
    h.Insert(30);
    h.Insert(100);


    //        10
    //      /   \
    //     15    50
    //    / \    /
    //   30 40  100



    return h;
}*/

TEST(TestHeap, TestConstructor) {

    Heap<int>heap0(15);
    EXPECT_EQ(15, heap0.GetMaxSize());
    EXPECT_EQ(0, heap0.GetSize());

    // проверть для размерности 0 и 1

    Heap<int> heap1(10);
    heap1.Insert(10);
    heap1.Insert(15);
    heap1.Insert(40);
    heap1.Insert(50);
    heap1.Insert(30);
    heap1.Insert(100);
    //Heap<int>heap2 = createHeap1();
    EXPECT_EQ(10, heap1.GetMaxSize());
    EXPECT_EQ(6, heap1.GetSize());

    int* arr = new int[6] {10, 15, 40, 50, 30, 100};
    Heap<int> heap2(arr, 6, 10);
    EXPECT_EQ(10, heap2.GetMaxSize());
    EXPECT_EQ(6, heap2.GetSize());

    vector<int> v = heap2.GetArray();
    vector<int> v1 = { 10, 15, 40,50,30,100 };

    // make_heap создаёт кучу на основе вектора (меняется сам вектор)

    make_heap(v1.begin(), v1.end(), std::greater<>{});
    EXPECT_EQ(v1, v);
}

TEST(TestHeap, TestInsert) {

    Heap<int> heap1(10);
    heap1.Insert(2);

    EXPECT_EQ(10, heap1.GetMaxSize());
    EXPECT_EQ(1, heap1.GetSize());
    vector<int>v1 = heap1.GetArray();
    vector<int> v = { 2 };
    EXPECT_EQ(v1, v);

    heap1.Insert(1);
    v1 = heap1.GetArray();
    v = { 1,2 };
    EXPECT_EQ(10, heap1.GetMaxSize());
    EXPECT_EQ(2, heap1.GetSize());
    EXPECT_EQ(v1, v);

    heap1.Insert(3);
    v1 = heap1.GetArray();
    v.push_back(3);
    EXPECT_EQ(10, heap1.GetMaxSize());
    EXPECT_EQ(3, heap1.GetSize());
    EXPECT_EQ(v1, v);
}

TEST(TestHeap, TestSearch) {

    int* arr = new int[6] {10, 15, 40, 50, 30, 100};
    Heap<int> heap2(arr, 6, 10);

    int s = heap2.Search(10);
    EXPECT_EQ(s, 0);

    s = heap2.Search(50);
    EXPECT_EQ(s, 3);

    s = heap2.Search(30);
    EXPECT_EQ(s, 4);

    s = heap2.Search(100);
    EXPECT_EQ(s, 5);
}

TEST(TestHeap, TestDelete) {

    int* arr = new int[6] {10, 15, 40, 50, 30, 100};
    Heap<int> heap2(arr, 6, 10);

    heap2.Delete(); // удаляем 10

    EXPECT_EQ(10, heap2.GetMaxSize());
    EXPECT_EQ(5, heap2.GetSize());

    vector<int> v = heap2.GetArray();
    EXPECT_TRUE(is_heap(v.begin(), v.end(), std::greater<>{}));
    vector<int> v1 = { 15,30,40,50,100 };
    make_heap(v1.begin(), v1.end(), std::greater<>{});
    EXPECT_EQ(v1, v);

    heap2.Delete(); // удаляем 15

    EXPECT_EQ(10, heap2.GetMaxSize());
    EXPECT_EQ(4, heap2.GetSize());

    v = heap2.GetArray();

    // коммент про is_heap и make_heap
    EXPECT_TRUE(is_heap(v.begin(), v.end(), std::greater<>{}));
    v1 = { 30,50,40,100 };
    make_heap(v1.begin(), v1.end(), std::greater<>{});
    EXPECT_EQ(v1, v);

    heap2.Delete(); // удаляем 30
    EXPECT_EQ(10, heap2.GetMaxSize());
    EXPECT_EQ(3, heap2.GetSize());

    v = heap2.GetArray();
    EXPECT_TRUE(is_heap(v.begin(), v.end(), std::greater<>{}));
    v1 = { 50, 40,100 };
    make_heap(v1.begin(), v1.end(), std::greater<>{});
    EXPECT_EQ(v1, v);

}

TEST(TestHeap, TestHeapSort) {
    int* arr = new int[6] {10, 15, 40, 50, 30, 100};
    HeapSort(arr, 6);

    int* arr1 = new int[6] {10, 15, 30, 40, 50, 100};

    for (int i = 0; i < 6; i++) {
        EXPECT_EQ(arr[i], arr1[i]);
    }

    delete[] arr;
    delete[] arr1;

    arr = new int[10] {55, 48, -54, 36, -24, 38, 12, 5, 2, -1};
    arr1 = new int[10] {-54, -24, -1, 2, 5, 12, 36, 38, 48, 55};
    HeapSort(arr, 10);

    for (int i = 0; i < 6; i++) {
        EXPECT_EQ(arr[i], arr1[i]);
    }

    delete[] arr;
    delete[] arr1;

    arr = new int[8] {34, 9, -44, 35, -72, -79, 8, 56 };
    arr1 = new int[8] {-79, -72, -44, 8, 9, 34, 35, 56};
    HeapSort(arr, 8);

    for (int i = 0; i < 6; i++) {
        EXPECT_EQ(arr[i], arr1[i]);
    }

    delete[] arr;
    delete[] arr1;

}