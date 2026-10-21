#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <string>

// Класс АВЛ-дерева (сбалансированное дерево поиска).
class AVLTree {
private:
    // Узел дерева.
    struct Node {
        int key;      // Ключ узла
        int height;   // Высота поддерева
        Node* left;   // Левый ребенок
        Node* right;  // Правый ребенок
        explicit Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root; // Корень дерева
    size_t sz;  // Количество узлов

    // Вспомогательные методы для балансировки (скрыты от пользователя).
    int getHeight(Node* node) const;
    int getBalance(Node* node) const;
    void updateHeight(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);
    
    // Рекурсивная вставка.
    Node* insert(Node* node, int key);
    
    // Очистка и печать.
    void destroyTree(Node* node);
    void printInOrder(Node* node) const;

public:
    // Конструктор и деструктор.
    AVLTree();
    ~AVLTree();

    // Публичный метод для вставки.
    void insert(int key);
    
    bool contains(int key) const; 

    // Получение размера.
    size_t size() const;
    
    // Вывод дерева (симметричный обход).
    void print() const;

    // Упрощенная сериализация.
    void save(const std::string& filename) const;
    void load(const std::string& filename);
        // Вспомогательные методы для сериализации дерева
    void saveNode(std::ofstream& f, Node* node) const;
    Node* loadNode(std::ifstream& f);
};

#endif