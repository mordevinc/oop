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

// Рекурсивная вставка элемента.
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

// Вспомогательный метод: найти узел с минимальным ключом (самый левый)
AVLTree::Node* AVLTree::findMin(Node* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// Рекурсивное удаление элемента
AVLTree::Node* AVLTree::removeRec(Node* node, int key) {
    if (!node) return nullptr;

    if (key < node->key) {
        node->left = removeRec(node->left, key);
    } else if (key > node->key) {
        node->right = removeRec(node->right, key);
    } else {
        // Нашли элемент, который нужно удалить
        if (!node->left || !node->right) {
            // Случай 1: нет детей или только один ребенок
            Node* temp = node->left ? node->left : node->right;
            if (!temp) {
                // Нет детей (лист) - просто удаляем
                delete node;
                return nullptr;
            } else {
                // Один ребенок - заменяем текущий узел ребенком
                Node* old_node = node;
                node = temp;
                delete old_node;
            }
        } else {
            // Случай 2: два ребенка
            // Находим минимальный узел в правом поддереве
            const Node* temp = findMin(node->right);
            // Заменяем ключ текущего узла на минимальный
            node->key = temp->key;
            // Удаляем минимальный узел из правого поддерева
            node->right = removeRec(node->right, temp->key);
        }
    }
    
    if (!node) return nullptr;
    
    // Балансируем узел после удаления
    return balance(node);
}

// Публичный метод удаления
void AVLTree::remove(int key) {
    if (contains(key)) {
        root = removeRec(root, key);
        sz--;
    }
}

// Поиск элемента (без изменений)
bool AVLTree::contains(int key) const {
    Node* curr = root;
    while (curr != nullptr) {
        if (key == curr->key) return true;
        curr = (key < curr->key) ? curr->left : curr->right;
    }
    return false;
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

// Вывод дерева (inorder).
void AVLTree::print() const {
    std::cout << "Tree (inorder): ";
    printInOrder(root);
    std::cout << "\n";
}

// Прямой обход (корень, лево, право)
void AVLTree::printPreOrder(Node* node) const {
    if (!node) return;
    std::cout << node->key << " ";  // Корень
    printPreOrder(node->left);      // Левое поддерево
    printPreOrder(node->right);     // Правое поддерево
}

// Вывод дерева (preorder).
void AVLTree::printPreorder() const {
    std::cout << "Tree (preorder): ";
    printPreOrder(root);
    std::cout << "\n";
}

// Обратный обход (лево, право, корень)
void AVLTree::printPostOrder(Node* node) const {
    if (!node) return;
    printPostOrder(node->left);     // Левое поддерево
    printPostOrder(node->right);    // Правое поддерево
    std::cout << node->key << " ";  // Корень
}

// Вывод дерева (postorder).
void AVLTree::printPostorder() const {
    std::cout << "Tree (postorder): ";
    printPostOrder(root);
    std::cout << "\n";
}

// Вспомогательный метод для сохранения (Preorder)
void AVLTree::saveNode(std::ofstream& f, Node* node) const {
    if (!node) {
        int null_marker = -1;
        f.write(reinterpret_cast<const char*>(&null_marker), sizeof(null_marker));
        return;
    }
    f.write(reinterpret_cast<const char*>(&node->key), sizeof(node->key));
    saveNode(f, node->left);
    saveNode(f, node->right);
}

void AVLTree::save(const std::string& filename) const {
    std::ofstream f(filename, std::ios::binary);
    if (!f) return;
    f.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
    saveNode(f, root);
}

// Вспомогательный метод для загрузки
AVLTree::Node* AVLTree::loadNode(std::ifstream& f) {
    int key = 0;
    if (!f.read(reinterpret_cast<char*>(&key), sizeof(key))) return nullptr;
    if (key == -1) return nullptr; // Маркер пустого узла
    
    Node* node = new Node(key);
    node->left = loadNode(f);
    node->right = loadNode(f);
    updateHeight(node);
    return node;
}

void AVLTree::load(const std::string& filename) {
    std::ifstream f(filename, std::ios::binary);
    if (!f) return;
    destroyTree(root);
    root = nullptr;
    
    if (!f.read(reinterpret_cast<char*>(&sz), sizeof(sz))) return;
    if (sz > 1000000) return; // Защита
    
    root = loadNode(f);
}