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



fn read_input() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.trim().to_string()
}

fn main() {
    let mut arr = Array::new(100);
    let mut flist = ForwardList::new();
    let mut dlist = DoublyList::new();
    let mut stack = Stack::new();
    let mut queue = Queue::new();
    let mut ht = HashTable::new(10);
    let mut tree = AVLTree::new();

    loop {
        println!("\n=== Лабораторная работа №3 (Rust) ===");
        println!("1. Массив\n2. Односвязный список\n3. Двусвязный список\n4. Стек\n5. Очередь\n6. Хеш-таблица\n7. АВЛ-дерево\n0. Выход");
        print!("Выбор: "); io::stdout().flush().unwrap();

        match read_input().as_str() {
            "1" => {
                println!("1. Push\n2. Insert_at\n3. Get\n4. Remove\n5. Print");
                let sub = read_input();
                if sub == "1" { print!("Строка: "); io::stdout().flush().unwrap(); arr.push(read_input()); }
                else if sub == "2" { print!("Индекс: "); io::stdout().flush().unwrap(); let i = read_input().parse().unwrap_or(0); print!("Строка: "); io::stdout().flush().unwrap(); arr.insert_at(i, read_input()); }
                else if sub == "3" { print!("Индекс: "); io::stdout().flush().unwrap(); let i = read_input().parse().unwrap_or(0); if let Some(s) = arr.get(i) { println!("{}", s); } else { println!("Нет"); } }
                else if sub == "4" { print!("Индекс: "); io::stdout().flush().unwrap(); let i = read_input().parse().unwrap_or(0); arr.remove(i); }
                else if sub == "5" { arr.print(); }
            }
            "2" => {
                println!("1. Push_back\n2. Insert_after\n3. Remove_by_value\n4. Print");
                let sub = read_input();
                if sub == "1" { print!("Строка: "); io::stdout().flush().unwrap(); flist.push_back(read_input()); }
                else if sub == "2" { print!("После чего: "); io::stdout().flush().unwrap(); let target = read_input(); print!("Строка: "); io::stdout().flush().unwrap(); flist.insert_after(&target, read_input()); }
                else if sub == "3" { print!("Строка: "); io::stdout().flush().unwrap(); flist.remove_by_value(&read_input()); }
                else if sub == "4" { flist.print(); }
            }
            "3" => {
                println!("1. Push_back\n2. Insert_before\n3. Remove_by_value\n4. Print_reverse");
                let sub = read_input();
                if sub == "1" { print!("Строка: "); io::stdout().flush().unwrap(); dlist.push_back(read_input()); }
                else if sub == "2" { print!("Перед чем: "); io::stdout().flush().unwrap(); let target = read_input(); print!("Строка: "); io::stdout().flush().unwrap(); dlist.insert_before(&target, read_input()); }
                else if sub == "3" { print!("Строка: "); io::stdout().flush().unwrap(); dlist.remove_by_value(&read_input()); }
                else if sub == "4" { dlist.print_reverse(); }
            }
            "4" => { print!("Строка: "); io::stdout().flush().unwrap(); stack.push(read_input()); }
            "5" => { print!("Строка: "); io::stdout().flush().unwrap(); queue.push(read_input()); }
            "6" => {
                println!("1. Insert\n2. Get\n3. Remove\n4. Print");
                let sub = read_input();
                if sub == "1" { print!("Ключ: "); io::stdout().flush().unwrap(); let k = read_input(); print!("Значение: "); io::stdout().flush().unwrap(); ht.insert(k, read_input()); }
                else if sub == "2" { print!("Ключ: "); io::stdout().flush().unwrap(); if let Some(v) = ht.get(&read_input()) { println!("{}", v); } else { println!("Нет"); } }
                else if sub == "3" { print!("Ключ: "); io::stdout().flush().unwrap(); ht.remove(&read_input()); }
                else if sub == "4" { ht.print(); }
            }
            "7" => {
                println!("1. Insert\n2. Remove\n3. Print_preorder\n4. Print_postorder");
                let sub = read_input();
                if sub == "1" { print!("Число: "); io::stdout().flush().unwrap(); tree.insert(read_input().parse().unwrap_or(0)); }
                else if sub == "2" { print!("Число: "); io::stdout().flush().unwrap(); tree.remove(read_input().parse().unwrap_or(0)); }
                else if sub == "3" { tree.print_preorder(); }
                else if sub == "4" { tree.print_postorder(); }
            }
            "0" => break,
            _ => println!("Неверный ввод!"),
        }
    }
}