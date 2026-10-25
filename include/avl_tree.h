#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <string>
#include <fstream> // Нужно для std::ofstream и std::ifstream

// Класс АВЛ-дерева
class AVLTree {
private:
    // Узел дерева (скрыт от пользователя).
    struct Node {
        int key;      // Ключ узла
        int height;   // Высота поддерева
        Node* left;   // Левый ребенок
        Node* right;  // Правый ребенок
        explicit Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root; // Корень дерева
    size_t sz;  // Количество узлов

    // Вспомогательные методы для балансировки
    int getHeight(Node* node) const;
    int getBalance(Node* node) const;
    void updateHeight(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);
    
    // Рекурсивные методы для вставки и удаления
    Node* insert(Node* node, int key);
    Node* removeRec(Node* node, int key); // Вспомогательный для удаления
    Node* findMin(Node* node);            // Поиск минимума (для удаления)
    
    // Очистка и обходы
    void destroyTree(Node* node);
    void printInOrder(Node* node) const;
    void printPreOrder(Node* node) const;
    void printPostOrder(Node* node) const;

    // Вспомогательные методы для сериализации дерева
    void saveNode(std::ofstream& f, Node* node) const;
    Node* loadNode(std::ifstream& f);

public:
    // Конструктор и деструктор
    AVLTree();
    ~AVLTree();

    // Публичные методы
    void insert(int key);
    void remove(int key); // Удаление элемента
    bool contains(int key) const;
    size_t size() const;
    
    // Вывод дерева разными способами
    void print() const;          // Симметричный (по возрастанию)
    void printPreorder() const;  // Прямой (корень, лево, право)
    void printPostorder() const; // Обратный (лево, право, корень)

    // Сериализация
    void save(const std::string& filename) const;
    void load(const std::string& filename);
};

#endif