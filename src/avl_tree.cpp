#include "avl_tree.h"
#include <algorithm>
#include <fstream>

// Инициализация пустого дерева.
AVLTree::AVLTree() : root(nullptr), sz(0) {}

// Деструктор.
AVLTree::~AVLTree() {
    destroyTree(root);
}

// Рекурсивное удаление всех узлов (постфиксный обход).
void AVLTree::destroyTree(Node* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// Возвращает высоту узла. Если узел пустой, высота равна 0.
int AVLTree::getHeight(Node* node) const {
    return node ? node->height : 0;
}

// Вычисляет фактор баланса: разница высот левого и правого поддеревьев.
int AVLTree::getBalance(Node* node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Обновляет высоту узла (высота = 1 + максимум из высот детей).
void AVLTree::updateHeight(Node* node) {
    if (node) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}

// Малое правое вращение (применяется, когда перевес слева).
// ВАЖНО: за пределами класса тип Node нужно указывать как AVLTree::Node
AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    
    // Переставляем указатели
    x->right = y;
    y->left = T2;
    
    // Обновляем высоты
    updateHeight(y);
    updateHeight(x);
    return x; // Новый корень поддерева
}

// Малое левое вращение (применяется, когда перевес справа).
AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    
    // Переставляем указатели
    y->left = x;
    x->right = T2;
    
    // Обновляем высоты
    updateHeight(x);
    updateHeight(y);
    return y;
}

// Балансировка узла. Если разница высот больше 1, выполняем вращения.
AVLTree::Node* AVLTree::balance(Node* node) {
    updateHeight(node);
    int bf = getBalance(node);

    if (bf > 1) { // Левый перевес
        if (getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left); // Двойное вращение
        }
        return rotateRight(node);
    }
    if (bf < -1) { // Правый перевес
        if (getBalance(node->right) > 0) {
            node->right = rotateRight(node->right); // Двойное вращение
        }
        return rotateLeft(node);
    }
    return node;
}

// Рекурсивная вставка элемента (как в обычном BST).
AVLTree::Node* AVLTree::insert(Node* node, int key) {
    if (!node) return new Node(key); // Нашли место для нового узла

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node; // Дубликаты не добавляем
    }
    
    return balance(node); // Балансируем на обратном пути к корню
}

// Публичный метод вставки.
void AVLTree::insert(int key) {
    root = insert(root, key);
    sz++;
}


// Проверяет, есть ли ключ в дереве (обычный поиск по правилам BST)
bool AVLTree::contains(int key) const {
    Node* curr = root;
    while (curr != nullptr) {
        if (key == curr->key) return true; // Нашли
        // Если искомый ключ меньше, идем влево, иначе вправо
        curr = (key < curr->key) ? curr->left : curr->right;
    }
    return false; // Не нашли
}


size_t AVLTree::size() const { 
    return sz; 
}

// Симметричный обход (выводит элементы по возрастанию).
void AVLTree::printInOrder(Node* node) const {
    if (!node) return;
    printInOrder(node->left);       // Левое поддерево
    std::cout << node->key << " ";  // Корень
    printInOrder(node->right);      // Правое поддерево
}

// Вывод дерева.
void AVLTree::print() const {
    std::cout << "Tree (inorder): ";
    printInOrder(root);
    std::cout << "\n";
}

// Рекурсивный обход (Preorder) для сохранения дерева в файл
void AVLTree::saveNode(std::ofstream& f, Node* node) const {
    if (!node) {
        // Если узла нет, пишем -1 (маркер пустоты)
        int null_marker = -1;
        f.write(reinterpret_cast<const char*>(&null_marker), sizeof(null_marker));
        return;
    }
    
    // Пишем ключ текущего узла
    f.write(reinterpret_cast<const char*>(&node->key), sizeof(node->key));
    
    // Рекурсивно идем влево и вправо
    saveNode(f, node->left);
    saveNode(f, node->right);
}

// Сохранение дерева
void AVLTree::save(const std::string& filename) const {
    std::ofstream f(filename, std::ios::binary);
    if (!f) return;
    
    // Пишем общий размер
    f.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
    
    // Запускаем рекурсивное сохранение с корня
    saveNode(f, root);
}

// Рекурсивное восстановление дерева из файла
AVLTree::Node* AVLTree::loadNode(std::ifstream& f) {
    int key;
    // Читаем число
    if (!f.read(reinterpret_cast<char*>(&key), sizeof(key))) return nullptr;
    
    // Если прочитали -1, значит дальше пусто
    if (key == -1) return nullptr;
    
    // Создаем новый узел
    Node* node = new Node(key);
    
    // Рекурсивно восстанавливаем левое и правое поддерево
    node->left = loadNode(f);
    node->right = loadNode(f);
    
    // Обновляем высоту узла (балансировка не нужна, так как мы восстанавливаем уже готовое дерево)
    updateHeight(node);
    
    return node;
}

// Загрузка дерева
void AVLTree::load(const std::string& filename) {
    std::ifstream f(filename, std::ios::binary);
    if (!f) return;
    
    // Очищаем текущее дерево перед загрузкой
    destroyTree(root);
    root = nullptr;
    
    // Читаем размер
    f.read(reinterpret_cast<char*>(&sz), sizeof(sz));
    
    // Восстанавливаем дерево
    root = loadNode(f);
}