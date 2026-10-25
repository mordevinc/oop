#include "flist.h"
#include <fstream>

// Конструктор. Список пуст: голова и хвост смотрят в никуда (nullptr).
ForwardList::ForwardList() : head(nullptr), tail(nullptr), sz(0) {}

// Деструктор. Идем от головы к хвосту и удаляем каждый узел.
ForwardList::~ForwardList() {
    Node* curr = head;
    while (curr != nullptr) {
        Node* temp = curr; // Запоминаем текущий узел
        curr = curr->next; // Переходим к следующему
        delete temp;       // Удаляем запомненный (освобождаем память)
    }
}

// Конструктор копирования (по правилу трех)
ForwardList::ForwardList(const ForwardList& other) : head(nullptr), tail(nullptr), sz(0) {
    Node* curr = other.head;
    while (curr != nullptr) {
        push_back(curr->data); // Поэлементно копируем данные в новый список
        curr = curr->next;
    }
}

// Оператор присваивания (по правилу трех)
ForwardList& ForwardList::operator=(const ForwardList& other) {
    if (this != &other) { // Защита от самоприсваивания
        // Очищаем текущий список
        while (head != nullptr) {
            Node* t = head; 
            head = head->next; 
            delete t;
        }
        tail = nullptr; 
        sz = 0;
        
        // Копируем данные из другого списка
        Node* curr = other.head;
        while (curr != nullptr) {
            push_back(curr->data);
            curr = curr->next;
        }
    }
    return *this;
}

// Вспомогательный метод поиска узла по значению.
ForwardList::Node* ForwardList::getNode(const std::string& target) const {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data == target) return curr; // Нашли совпадение
        curr = curr->next; // Идем дальше
    }
    return nullptr; // Не нашли
}

// Добавление элемента в начало списка.
void ForwardList::push_front(const std::string& value) {
    Node* newNode = new Node(value);
    newNode->next = head; // Новый узел ссылается на старую голову
    head = newNode;       // Новый узел становится головой
    
    if (tail == nullptr) { // Если список был пуст, то это и хвост тоже
        tail = newNode;
    }
    sz++;
}

// Добавление элемента в конец списка.
void ForwardList::push_back(const std::string& value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) { // Если список был пуст
        head = newNode;
        tail = newNode;
    } else { // Если элементы уже есть
        tail->next = newNode; // Старый хвост теперь ссылается на новый узел
        tail = newNode;       // Новый узел официально становится хвостом
    }
    sz++;
}

// Вставка после узла с заданным значением.
void ForwardList::insert_after(const std::string& target, const std::string& value) {
    Node* targetNode = getNode(target);
    if (targetNode == nullptr) return; // Не нашли такой элемент
    
    Node* newNode = new Node(value);
    newNode->next = targetNode->next; // Новый узел ссылается на следующего за целью
    targetNode->next = newNode;       // Цель ссылается на новый узел
    
    if (targetNode == tail) tail = newNode; // Если вставили после хвоста, обновляем хвост
    sz++;
}

// Вставка перед узлом с заданным значением.
void ForwardList::insert_before(const std::string& target, const std::string& value) {
    if (head == nullptr) return;
    if (head->data == target) { // Если цель - голова, просто используем push_front
        push_front(value);
        return;
    }
    
    Node* curr = head;
    // Ищем узел, который стоит перед целью
    while (curr->next != nullptr && curr->next->data != target) {
        curr = curr->next;
    }
    
    if (curr->next != nullptr) { // Нашли элемент перед целью
        Node* newNode = new Node(value);
        newNode->next = curr->next;
        curr->next = newNode;
        sz++;
    }
}

// Удаление первого элемента (головы).
void ForwardList::pop_front() {
    if (head == nullptr) return; // Защита от пустого списка
    Node* temp = head;
    head = head->next;
    if (head == nullptr) tail = nullptr; // Если удалили последний элемент
    delete temp;
    sz--;
}

// Удаление последнего элемента (хвоста).
void ForwardList::pop_back() {
    if (head == nullptr) return;
    if (head == tail) { // Если в списке 1 элемент
        delete head;
        head = nullptr;
        tail = nullptr;
        sz = 0;
        return;
    }
    Node* curr = head;
    // Ищем предпоследний элемент
    while (curr->next != tail) {
        curr = curr->next;
    }
    delete tail;
    curr->next = nullptr;
    tail = curr;
    sz--;
}

// Удаление элемента, стоящего после заданного.
void ForwardList::remove_after(const std::string& target) {
    Node* targetNode = getNode(target);
    if (targetNode == nullptr || targetNode->next == nullptr) return; // Некуда удалять
    
    Node* temp = targetNode->next;
    targetNode->next = temp->next;
    if (temp == tail) tail = targetNode; // Если удалили хвост
    delete temp;
    sz--;
}

// Удаление элемента, стоящего перед заданным.
void ForwardList::remove_before(const std::string& target) {
    if (head == nullptr || head->next == nullptr) return;
    
    // Если цель - второй элемент, значит удаляем голову
    if (head->next->data == target) {
        pop_front();
        return;
    }
    
    Node* curr = head;
    // Ищем элемент перед элементом перед целью
    while (curr->next != nullptr && curr->next->next != nullptr && curr->next->next->data != target) {
        curr = curr->next;
    }
    
    if (curr->next != nullptr && curr->next->next != nullptr) {
        Node* temp = curr->next;
        curr->next = temp->next;
        delete temp;
        sz--;
    }
}

// Удаление первого найденного элемента с заданным значением.
void ForwardList::remove_by_value(const std::string& value) {
    if (head == nullptr) return;
    if (head->data == value) { // Если значение в голове
        pop_front();
        return;
    }
    Node* curr = head;
    // Ищем узел перед нужным значением
    while (curr->next != nullptr && curr->next->data != value) {
        curr = curr->next;
    }
    if (curr->next != nullptr) {
        Node* temp = curr->next;
        curr->next = temp->next;
        if (temp == tail) tail = curr;
        delete temp;
        sz--;
    }
}

// Поиск элемента по значению.
bool ForwardList::find(const std::string& value) const {
    return getNode(value) != nullptr;
}

// Возврат размера.
size_t ForwardList::size() const { 
    return sz; 
}

// Печать списка.
void ForwardList::print() const {
    Node* curr = head;
    std::cout << "List: ";
    while (curr != nullptr) {
        std::cout << curr->data << " -> ";
        curr = curr->next;
    }
    std::cout << "nullptr\n";
}

// Сохранение в файл.
void ForwardList::save(const std::string& filename) const {
    std::ofstream f(filename, std::ios::binary);
    f.write(reinterpret_cast<const char*>(&sz), sizeof(sz)); // Пишем размер списка
    
    Node* curr = head;
    while (curr != nullptr) {
        size_t len = curr->data.size();
        f.write(reinterpret_cast<const char*>(&len), sizeof(len)); // Пишем длину строки
        f.write(curr->data.c_str(), len);                          // Пишем саму строку
        curr = curr->next;
    }
}

// Загрузка из файла.
void ForwardList::load(const std::string& filename) {
    std::ifstream f(filename, std::ios::binary);
    if (!f) return;
    
    while (head != nullptr) { Node* t = head; head = head->next; delete t; }
    tail = nullptr; sz = 0;
    
    size_t file_sz = 0;
    if (!f.read(reinterpret_cast<char*>(&file_sz), sizeof(file_sz))) return;
    if (file_sz > 1000000) return;
    
    for (size_t i = 0; i < file_sz; ++i) {
        size_t len = 0;
        if (!f.read(reinterpret_cast<char*>(&len), sizeof(len))) break;
        if (len > 1000000) break;
        
        std::string temp(len, '\0');
        if (!f.read(&temp[0], len)) break;
        push_back(temp);
    }
}

// Вспомогательный метод для Хеш-таблицы: поиск значения по ключу.
// Ищет узел, данные которого начинаются на "key:", и возвращает часть после двоеточия.
std::string ForwardList::getValueByKey(const std::string& key) const {
    std::string searchStr = key + ":";
    Node* curr = head;
    while (curr != nullptr) {
        // rfind(..., 0) возвращает 0, если строка начинается с searchStr
        if (curr->data.rfind(searchStr, 0) == 0) { 
            return curr->data.substr(searchStr.length()); // Отрезаем "key:" и возвращаем значение
        }
        curr = curr->next;
    }
    return ""; // Не нашли
}

// Вспомогательный метод для Хеш-таблицы: удаление по ключу.
bool ForwardList::removeByKey(const std::string& key) {
    std::string searchStr = key + ":";
    if (head == nullptr) return false;
    
    // Если нужный ключ в голове
    if (head->data.rfind(searchStr, 0) == 0) {
        Node* temp = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete temp;
        sz--;
        return true;
    }
    
    // Ищем в остальном списке
    Node* curr = head;
    while (curr->next != nullptr) {
        if (curr->next->data.rfind(searchStr, 0) == 0) {
            Node* temp = curr->next;
            curr->next = temp->next;
            if (temp == tail) tail = curr;
            delete temp;
            sz--;
            return true;
        }
        curr = curr->next;
    }
    return false;
}