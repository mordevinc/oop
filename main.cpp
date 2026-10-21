#include <iostream>
#include <string>
#include <limits> // Нужно для очистки потока ввода при ошибках

#include "array.h"
#include "flist.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "hash_table.h"
#include "avl_tree.h"

using namespace std;

// Вспомогательная функция для очистки экрана (опционально, для красоты)
void clearScreen() {
    // Просто печатаем много пустых строк, чтобы сымитировать очистку
    for (int i = 0; i < 30; ++i) cout << "\n";
}

int main() {
    // Создаем объекты всех структур один раз при запуске программы.
    // Они будут жить в памяти, пока мы не выйдем из main().
    Array arr(100);
    ForwardList flist;
    DoublyList dlist;
    Stack stack;
    Queue queue;
    HashTable ht(10);
    AVLTree tree;

    int choice = -1;
    int subChoice = -1;
    string inputStr;
    int inputInt;

    while (true) {
        clearScreen();
        cout << "=== Лабораторная работа №3. ООП и структуры данных ===" << endl;
        cout << "1. Работа с Массивом (Array)" << endl;
        cout << "2. Работа с Односвязным списком (ForwardList)" << endl;
        cout << "3. Работа с Двусвязным списком (DoublyList)" << endl;
        cout << "4. Работа со Стеком (Stack)" << endl;
        cout << "5. Работа с Очередью (Queue)" << endl;
        cout << "6. Работа с Хеш-таблицей (HashTable)" << endl;
        cout << "7. Работа с АВЛ-деревом (AVLTree)" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите структуру: ";
        cin >> choice;

        if (choice == 0) break; // Выход из программы

        // Обработка выбора конкретной структуры
        switch (choice) {
            case 1: // --- ARRAY ---
                cout << "\n--- Array ---" << endl;
                cout << "1. Добавить элемент (push_back)" << endl;
                cout << "2. Вывести все элементы (print)" << endl;
                cout << "3. Сохранить в файл (save)" << endl;
                cout << "4. Загрузить из файла (load)" << endl;
                cout << "Выбор: ";
                cin >> subChoice;

                if (subChoice == 1) {
                    cout << "Введите строку: "; cin >> inputStr;
                    arr.push_back(inputStr);
                    cout << "Добавлено!" << endl;
                } else if (subChoice == 2) {
                    arr.print();
                } else if (subChoice == 3) {
                    arr.save("array.bin");
                    cout << "Сохранено в array.bin" << endl;
                } else if (subChoice == 4) {
                    arr.load("array.bin");
                    cout << "Загружено из array.bin" << endl;
                }
                break;

            case 2: // --- FORWARD LIST ---
                cout << "\n--- ForwardList ---" << endl;
                cout << "1. Добавить в конец (push_back)" << endl;
                cout << "2. Добавить в начало (push_front)" << endl;
                cout << "3. Найти элемент (find)" << endl;
                cout << "4. Вывести список (print)" << endl;
                cout << "5. Сохранить в файл" << endl;
                cout << "6. Загрузить из файла" << endl;
                cout << "Выбор: ";
                cin >> subChoice;

                if (subChoice == 1) {
                    cout << "Введите строку: "; cin >> inputStr;
                    flist.push_back(inputStr);
                } else if (subChoice == 2) {
                    cout << "Введите строку: "; cin >> inputStr;
                    flist.push_front(inputStr);
                } else if (subChoice == 3) {
                    cout << "Что ищем? "; cin >> inputStr;
                    cout << "Результат: " << (flist.find(inputStr) ? "Найдено" : "Не найдено") << endl;
                } else if (subChoice == 4) {
                    flist.print();
                } else if (subChoice == 5) {
                    flist.save("flist.bin");
                    cout << "Сохранено!" << endl;
                } else if (subChoice == 6) {
                    flist.load("flist.bin");
                    cout << "Загружено!" << endl;
                }
                break;

            case 3: // --- DOUBLY LIST ---
                cout << "\n--- DoublyList ---" << endl;
                cout << "1. Добавить в конец" << endl;
                cout << "2. Добавить в начало" << endl;
                cout << "3. Вывести список" << endl;
                cout << "4. Сохранить в файл" << endl;
                cout << "5. Загрузить из файла" << endl;
                cout << "Выбор: ";
                cin >> subChoice;

                if (subChoice == 1) {
                    cout << "Введите строку: "; cin >> inputStr;
                    dlist.push_back(inputStr);
                } else if (subChoice == 2) {
                    cout << "Введите строку: "; cin >> inputStr;
                    dlist.push_front(inputStr);
                } else if (subChoice == 3) {
                    dlist.print();
                } else if (subChoice == 4) {
                    dlist.save("dlist.bin");
                } else if (subChoice == 5) {
                    dlist.load("dlist.bin");
                }
                break;

            case 4: // --- STACK ---
                cout << "\n--- Stack ---" << endl;
                cout << "1. Положить в стек (push)" << endl;
                cout << "2. Забрать из стека (pop)" << endl;
                cout << "3. Вывести стек" << endl;
                cout << "4. Сохранить в файл" << endl;
                cout << "5. Загрузить из файла" << endl;
                cout << "Выбор: ";
                cin >> subChoice;

                if (subChoice == 1) {
                    cout << "Введите строку: "; cin >> inputStr;
                    stack.push(inputStr);
                } else if (subChoice == 2) {
                    cout << "Извлечено: " << stack.pop() << endl;
                } else if (subChoice == 3) {
                    stack.print();
                } else if (subChoice == 4) {
                    stack.save("stack.bin");
                } else if (subChoice == 5) {
                    stack.load("stack.bin");
                }
                break;

            case 5: // --- QUEUE ---
                cout << "\n--- Queue ---" << endl;
                cout << "1. Добавить в очередь (push)" << endl;
                cout << "2. Забрать из очереди (pop)" << endl;
                cout << "3. Вывести очередь" << endl;
                cout << "4. Сохранить в файл" << endl;
                cout << "5. Загрузить из файла" << endl;
                cout << "Выбор: ";
                cin >> subChoice;

                if (subChoice == 1) {
                    cout << "Введите строку: "; cin >> inputStr;
                    queue.push(inputStr);
                } else if (subChoice == 2) {
                    cout << "Извлечено: " << queue.pop() << endl;
                } else if (subChoice == 3) {
                    queue.print();
                } else if (subChoice == 4) {
                    queue.save("queue.bin");
                } else if (subChoice == 5) {
                    queue.load("queue.bin");
                }
                break;

            case 6: // --- HASH TABLE ---
                cout << "\n--- HashTable ---" << endl;
                cout << "1. Добавить пару ключ-значение" << endl;
                cout << "2. Вывести таблицу" << endl;
                cout << "3. Сохранить в файл" << endl;
                cout << "4. Загрузить из файла" << endl;
                cout << "Выбор: ";
                cin >> subChoice;

                if (subChoice == 1) {
                    string key, val;
                    cout << "Введите ключ: "; cin >> key;
                    cout << "Введите значение: "; cin >> val;
                    ht.insert(key, val);
                } else if (subChoice == 2) {
                    ht.print();
                } else if (subChoice == 3) {
                    ht.save("ht.bin");
                } else if (subChoice == 4) {
                    ht.load("ht.bin");
                }
                break;

            case 7: // --- AVL TREE ---
                cout << "\n--- AVL Tree ---" << endl;
                cout << "1. Добавить число в дерево" << endl;
                cout << "2. Проверить наличие числа" << endl;
                cout << "3. Вывести дерево" << endl;
                cout << "4. Сохранить в файл" << endl;
                cout << "5. Загрузить из файла" << endl;
                cout << "Выбор: ";
                cin >> subChoice;

                if (subChoice == 1) {
                    cout << "Введите число: "; cin >> inputInt;
                    tree.insert(inputInt);
                } else if (subChoice == 2) {
                    cout << "Введите число для поиска: "; cin >> inputInt;
                    cout << "Результат: " << (tree.contains(inputInt) ? "Есть" : "Нет") << endl;
                } else if (subChoice == 3) {
                    tree.print();
                } else if (subChoice == 4) {
                    tree.save("tree.bin");
                } else if (subChoice == 5) {
                    tree.load("tree.bin");
                }
                break;

            default:
                cout << "Неверный выбор!" << endl;
        }

        // Пауза, чтобы пользователь успел прочитать результат
        cout << "\nНажмите Enter для продолжения...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер
        cin.get(); // Ждем нажатия Enter
    }

    cout << "Выход из программы." << endl;
    return 0;
}