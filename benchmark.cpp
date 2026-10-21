#include <iostream>
#include <chrono>
#include <string>

#include "array.h"
#include "flist.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "hash_table.h"
#include "avl_tree.h"

using namespace std;
using namespace std::chrono;

// Константа: сколько элементов добавлять для замера
const int N = 10000;

int main() {
    cout << "Запуск бенчмарков (N = " << N << " элементов)..." << endl;
    cout << "----------------------------------------" << endl;

    // 1. Замер Array
    auto start = high_resolution_clock::now();
    Array arr(N);
    for (int i = 0; i < N; ++i) arr.push_back("test");
    auto end = high_resolution_clock::now();
    cout << "Array::push_back:      " << duration_cast<microseconds>(end - start).count() << " мкс" << endl;

    // 2. Замер ForwardList
    start = high_resolution_clock::now();
    ForwardList flist;
    for (int i = 0; i < N; ++i) flist.push_back("test");
    end = high_resolution_clock::now();
    cout << "ForwardList::push_back:" << duration_cast<microseconds>(end - start).count() << " мкс" << endl;

    // 3. Замер DoublyList
    start = high_resolution_clock::now();
    DoublyList dlist;
    for (int i = 0; i < N; ++i) dlist.push_back("test");
    end = high_resolution_clock::now();
    cout << "DoublyList::push_back: " << duration_cast<microseconds>(end - start).count() << " мкс" << endl;

    // 4. Замер Stack
    start = high_resolution_clock::now();
    Stack stack;
    for (int i = 0; i < N; ++i) stack.push("test");
    end = high_resolution_clock::now();
    cout << "Stack::push:           " << duration_cast<microseconds>(end - start).count() << " мкс" << endl;

    // 5. Замер Queue
    start = high_resolution_clock::now();
    Queue queue;
    for (int i = 0; i < N; ++i) queue.push("test");
    end = high_resolution_clock::now();
    cout << "Queue::push:           " << duration_cast<microseconds>(end - start).count() << " мкс" << endl;

    // 6. Замер HashTable
    start = high_resolution_clock::now();
    HashTable ht(N);
    for (int i = 0; i < N; ++i) ht.insert(to_string(i), "val");
    end = high_resolution_clock::now();
    cout << "HashTable::insert:     " << duration_cast<microseconds>(end - start).count() << " мкс" << endl;

    // 7. Замер AVLTree
    start = high_resolution_clock::now();
    AVLTree tree;
    for (int i = 0; i < N; ++i) tree.insert(i);
    end = high_resolution_clock::now();
    cout << "AVLTree::insert:       " << duration_cast<microseconds>(end - start).count() << " мкс" << endl;

    cout << "----------------------------------------" << endl;
    cout << "Бенчмарк завершен!" << endl;
    return 0;
}