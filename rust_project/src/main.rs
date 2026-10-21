mod array;
mod flist;
mod dlist;
mod stack;
mod queue;
mod hash_table;
mod avl_tree;

use std::io::{self, Write};
use array::Array;
use flist::ForwardList;
use dlist::DoublyList;
use stack::Stack;
use queue::Queue;
use hash_table::HashTable;
use avl_tree::AVLTree;

// Функция для чтения строки из консоли
fn read_input() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.trim().to_string()
}

fn main() {
    // Инициализируем структуры
    let mut arr = Array::new(100);
    let mut flist = ForwardList::new();
    let mut dlist = DoublyList::new();
    let mut stack = Stack::new();
    let mut queue = Queue::new();
    let mut ht = HashTable::new(10);
    let mut tree = AVLTree::new();

    loop {
        println!("\n=== Лабораторная работа №3 (Rust) ===");
        println!("1. Массив");
        println!("2. Односвязный список");
        println!("3. Двусвязный список");
        println!("4. Стек");
        println!("5. Очередь");
        println!("6. Хеш-таблица");
        println!("7. АВЛ-дерево");
        println!("0. Выход");
        print!("Выбор: ");
        io::stdout().flush().unwrap();

        let choice = read_input();

        match choice.as_str() {
            "1" => {
                println!("1. Добавить (push)\n2. Вывести\n3. Сохранить\n4. Загрузить");
                let sub = read_input();
                if sub == "1" {
                    print!("Строка: "); io::stdout().flush().unwrap();
                    arr.push(read_input());
                } else if sub == "2" { arr.print(); }
                else if sub == "3" { arr.save("array.bin"); }
                else if sub == "4" { arr.load("array.bin"); }
            }
            "2" => {
                println!("1. В конец (push_back)\n2. В начало (push_front)\n3. Поиск\n4. Вывести\n5. Сохранить\n6. Загрузить");
                let sub = read_input();
                if sub == "1" { print!("Строка: "); io::stdout().flush().unwrap(); flist.push_back(read_input()); }
                else if sub == "2" { print!("Строка: "); io::stdout().flush().unwrap(); flist.push_front(read_input()); }
                else if sub == "3" { print!("Искать: "); io::stdout().flush().unwrap(); println!("Есть? {}", flist.find(&read_input())); }
                else if sub == "4" { flist.print(); }
                else if sub == "5" { flist.save("flist.bin"); }
                else if sub == "6" { flist.load("flist.bin"); }
            }
            "3" => {
                println!("1. В конец\n2. В начало\n3. Вывести\n4. Сохранить\n5. Загрузить");
                let sub = read_input();
                if sub == "1" { print!("Строка: "); io::stdout().flush().unwrap(); dlist.push_back(read_input()); }
                else if sub == "2" { print!("Строка: "); io::stdout().flush().unwrap(); dlist.push_front(read_input()); }
                else if sub == "3" { dlist.print(); }
                else if sub == "4" { dlist.save("dlist.bin"); }
                else if sub == "5" { dlist.load("dlist.bin"); }
            }
            "4" => {
                println!("1. Push\n2. Pop\n3. Вывести\n4. Сохранить\n5. Загрузить");
                let sub = read_input();
                if sub == "1" { print!("Строка: "); io::stdout().flush().unwrap(); stack.push(read_input()); }
                else if sub == "2" { println!("Извлечено: {}", stack.pop()); }
                else if sub == "3" { stack.print(); }
                else if sub == "4" { stack.save("stack.bin"); }
                else if sub == "5" { stack.load("stack.bin"); }
            }
            "5" => {
                println!("1. Push\n2. Pop\n3. Вывести\n4. Сохранить\n5. Загрузить");
                let sub = read_input();
                if sub == "1" { print!("Строка: "); io::stdout().flush().unwrap(); queue.push(read_input()); }
                else if sub == "2" { println!("Извлечено: {}", queue.pop()); }
                else if sub == "3" { queue.print(); }
                else if sub == "4" { queue.save("queue.bin"); }
                else if sub == "5" { queue.load("queue.bin"); }
            }
            "6" => {
                println!("1. Вставить (key, value)\n2. Вывести\n3. Сохранить\n4. Загрузить");
                let sub = read_input();
                if sub == "1" {
                    print!("Ключ: "); io::stdout().flush().unwrap(); let k = read_input();
                    print!("Значение: "); io::stdout().flush().unwrap(); let v = read_input();
                    ht.insert(k, v);
                }
                else if sub == "2" { ht.print(); }
                else if sub == "3" { ht.save("ht.json"); }
                else if sub == "4" { ht.load("ht.json"); }
            }
            "7" => {
                println!("1. Вставить (число)\n2. Поиск\n3. Вывести\n4. Сохранить\n5. Загрузить");
                let sub = read_input();
                if sub == "1" {
                    print!("Число: "); io::stdout().flush().unwrap();
                    if let Ok(num) = read_input().parse::<i32>() { tree.insert(num); }
                }
                else if sub == "2" {
                    print!("Искать: "); io::stdout().flush().unwrap();
                    if let Ok(num) = read_input().parse::<i32>() { println!("Есть? {}", tree.contains(num)); }
                }
                else if sub == "3" { tree.print(); }
                else if sub == "4" { tree.save("tree.bin"); }
                else if sub == "5" { tree.load("tree.bin"); }
            }
            "0" => break,
            _ => println!("Неверный ввод!"),
        }
    }
}