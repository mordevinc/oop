use std::rc::Rc;
use std::cell::RefCell;
use std::fs::File;

// Узел двусвязного списка.
// prev и next хранятся как Rc<RefCell<...>> — это позволяет
// иметь несколько владельцев узла и менять его поля.
struct Node {
    data: String,
    prev: Option<Rc<RefCell<Node>>>,
    next: Option<Rc<RefCell<Node>>>,
}

// Сам двусвязный список: храним голову, хвост и размер.
pub struct DoublyList {
    head: Option<Rc<RefCell<Node>>>,
    tail: Option<Rc<RefCell<Node>>>,
    size: usize,
}

impl DoublyList {
    // Пустой список.
    pub fn new() -> Self {
        DoublyList { head: None, tail: None, size: 0 }
    }

    // Добавить элемент в начало.
    pub fn push_front(&mut self, val: String) {
        let new_node = Rc::new(RefCell::new(Node {
            data: val,
            prev: None,
            next: self.head.clone(),
        }));
        if let Some(old_head) = &self.head {
            // Старая голова теперь ссылается назад на новый узел.
            old_head.borrow_mut().prev = Some(new_node.clone());
        } else {
            // Список был пуст — новый узел становится и хвостом.
            self.tail = Some(new_node.clone());
        }
        self.head = Some(new_node);
        self.size += 1;
    }

    // Добавить элемент в конец.
    pub fn push_back(&mut self, val: String) {
        let new_node = Rc::new(RefCell::new(Node {
            data: val,
            prev: self.tail.clone(),
            next: None,
        }));
        if let Some(old_tail) = &self.tail {
            // Старый хвост теперь ссылается вперёд на новый узел.
            old_tail.borrow_mut().next = Some(new_node.clone());
        } else {
            // Список был пуст — новый узел становится и головой.
            self.head = Some(new_node.clone());
        }
        self.tail = Some(new_node);
        self.size += 1;
    }

    // Найти узел по значению (первый подходящий).
    fn get_node(&self, target: &str) -> Option<Rc<RefCell<Node>>> {
        let mut current = self.head.clone();
        while let Some(node) = current {
            if node.borrow().data == target {
                return Some(node);
            }
            current = node.borrow().next.clone();
        }
        None
    }

    // Вставить новый элемент после узла с заданным значением.
    pub fn insert_after(&mut self, target: &str, val: String) -> bool {
        if let Some(node) = self.get_node(target) {
            let next = node.borrow().next.clone();
            let new_node = Rc::new(RefCell::new(Node {
                data: val,
                prev: Some(node.clone()),
                next: next.clone(),
            }));

            // Если после node был узел — у него обновляем prev.
            // Иначе новый узел становится хвостом.
            if let Some(n) = &next {
                n.borrow_mut().prev = Some(new_node.clone());
            } else {
                self.tail = Some(new_node.clone());
            }

            node.borrow_mut().next = Some(new_node);
            self.size += 1;
            true
        } else {
            false
        }
    }

    // Вставить новый элемент перед узлом с заданным значением.
    pub fn insert_before(&mut self, target: &str, val: String) -> bool {
        if let Some(node) = self.get_node(target) {
            let prev = node.borrow().prev.clone();
            let new_node = Rc::new(RefCell::new(Node {
                data: val,
                prev: prev.clone(),
                next: Some(node.clone()),
            }));

            // Если перед node был узел — у него обновляем next.
            // Иначе новый узел становится головой.
            if let Some(p) = &prev {
                p.borrow_mut().next = Some(new_node.clone());
            } else {
                self.head = Some(new_node.clone());
            }

            node.borrow_mut().prev = Some(new_node);
            self.size += 1;
            true
        } else {
            false
        }
    }

    // Удалить первый элемент и вернуть его значение.
    pub fn pop_front(&mut self) -> Option<String> {
        self.head.take().map(|node| {
            let next = node.borrow().next.clone();
            if let Some(n) = &next {
                n.borrow_mut().prev = None;
            } else {
                // Список стал пустым.
                self.tail = None;
            }
            self.head = next;
            self.size -= 1;
            node.borrow().data.clone()
        })
    }

    // Удалить последний элемент и вернуть его значение.
    pub fn pop_back(&mut self) -> Option<String> {
        self.tail.take().map(|node| {
            let prev = node.borrow().prev.clone();
            if let Some(p) = &prev {
                p.borrow_mut().next = None;
            } else {
                // Список стал пустым.
                self.head = None;
            }
            self.tail = prev;
            self.size -= 1;
            node.borrow().data.clone()
        })
    }

    // Удалить узел, стоящий после target.
    pub fn remove_after(&mut self, target: &str) -> bool {
        if let Some(node) = self.get_node(target) {
            let next = node.borrow().next.clone();
            if next.is_none() {
                return false; // после target ничего нет
            }

            let nextnext = next.as_ref().unwrap().borrow().next.clone();
            node.borrow_mut().next = nextnext.clone();

            if let Some(nn) = &nextnext {
                nn.borrow_mut().prev = Some(node.clone());
            } else {
                // Удалили хвост — обновляем tail.
                self.tail = Some(node.clone());
            }

            self.size -= 1;
            true
        } else {
            false
        }
    }

    // Удалить узел, стоящий перед target.
    pub fn remove_before(&mut self, target: &str) -> bool {
        if let Some(node) = self.get_node(target) {
            let prev = node.borrow().prev.clone();
            if prev.is_none() {
                return false; // перед target ничего нет
            }

            let prevprev = prev.as_ref().unwrap().borrow().prev.clone();
            node.borrow_mut().prev = prevprev.clone();

            if let Some(pp) = &prevprev {
                pp.borrow_mut().next = Some(node.clone());
            } else {
                // Удалили голову — обновляем head.
                self.head = Some(node.clone());
            }

            self.size -= 1;
            true
        } else {
            false
        }
    }

    // Удалить узел по значению (первый подходящий).
    pub fn remove_by_value(&mut self, target: &str) -> bool {
        if let Some(node) = self.get_node(target) {
            let is_head = node.borrow().prev.is_none();
            let is_tail = node.borrow().next.is_none();

            if is_head && is_tail {
                // Единственный элемент.
                self.head = None;
                self.tail = None;
            } else if is_head {
                let next = node.borrow().next.clone();
                if let Some(n) = &next {
                    n.borrow_mut().prev = None;
                }
                self.head = next;
            } else if is_tail {
                let prev = node.borrow().prev.clone();
                if let Some(p) = &prev {
                    p.borrow_mut().next = None;
                }
                self.tail = prev;
            } else {
                let prev = node.borrow().prev.clone();
                let next = node.borrow().next.clone();
                if let Some(p) = &prev {
                    p.borrow_mut().next = next.clone();
                }
                if let Some(n) = &next {
                    n.borrow_mut().prev = prev.clone();
                }
            }
            self.size -= 1;
            true
        } else {
            false
        }
    }

    // Есть ли элемент с таким значением.
    pub fn find(&self, target: &str) -> bool {
        self.get_node(target).is_some()
    }

    // Печать списка от головы к хвосту.
    pub fn print(&self) {
        let mut current = self.head.clone();
        print!("List: ");
        while let Some(node) = current {
            print!("{} <-> ", node.borrow().data);
            current = node.borrow().next.clone();
        }
        println!("nullptr");
    }

    // Печать списка от хвоста к голове.
    pub fn print_reverse(&self) {
        let mut current = self.tail.clone();
        print!("Reverse: ");
        while let Some(node) = current {
            print!("{} <-> ", node.borrow().data);
            current = node.borrow().prev.clone();
        }
        println!("nullptr");
    }

    // Сохранить список в бинарный файл (bincode).
    pub fn save(&self, filename: &str) {
        let mut vec_data = Vec::new();
        let mut current = self.head.clone();
        while let Some(node) = current {
            vec_data.push(node.borrow().data.clone());
            current = node.borrow().next.clone();
        }
        let mut f = File::create(filename).unwrap();
        bincode::serialize_into(&mut f, &vec_data).unwrap();
    }

    // Загрузить список из бинарного файла.
    pub fn load(&mut self, filename: &str) {
        if let Ok(mut f) = File::open(filename) {
            if let Ok(vec_data) = bincode::deserialize_from::<_, Vec<String>>(&mut f) {
                self.head = None;
                self.tail = None;
                self.size = 0;
                for item in vec_data {
                    self.push_back(item);
                }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_dlist_full_coverage() {
        let mut list = DoublyList::new();

        // Пустой список: удаления до/после несуществующего узла — false.
        assert!(!list.remove_after("X"));
        assert!(!list.remove_before("X"));

        // Наполняем: Z <-> A <-> C
        list.push_back("A".to_string());
        list.push_back("C".to_string());
        list.push_front("Z".to_string());

        // Вставки:
        // insert_after("Z","A")  -> Z <-> A(new) <-> A(old) <-> C
        // insert_before("C","X") -> Z <-> A(new) <-> A(old) <-> X <-> C
        assert!(list.insert_after("Z", "A".to_string()));
        assert!(list.insert_before("C", "X".to_string()));
        // Вставки к несуществующему узлу.
        assert!(!list.insert_after("Ghost", "Y".to_string()));
        assert!(!list.insert_before("Ghost", "Y".to_string()));

        // Удаления:
        // remove_after("A")  — находит первый A (после Z), удаляет A(old).
        //                      стало: Z <-> A(new) <-> X <-> C
        // remove_before("C") — удаляет X.
        //                      стало: Z <-> A(new) <-> C
        // remove_by_value("Z") — удаляет Z (голову).
        //                      стало: A <-> C
        list.remove_after("A");
        list.remove_before("C");
        list.remove_by_value("Z");
        assert_eq!(list.size, 2);

        list.print();          // List: A <-> C <-> nullptr
        list.print_reverse();  // Reverse: C <-> A <-> nullptr

        // После всех удалений в списке ровно: A <-> C
        // Голова = A, хвост = C.
        // Исправлено: pop_front возвращает голову (A), pop_back — хвост (C).
        assert_eq!(list.pop_front().unwrap(), "A");
        assert_eq!(list.pop_back().unwrap(), "C");
        assert_eq!(list.size, 0);

        // Заполняем и сохраняем.
        list.push_back("Data".to_string());
        list.save("test_dlist.bin");

        let mut list2 = DoublyList::new();
        list2.load("test_dlist.bin");
        assert_eq!(list2.size, 1);
        assert!(list2.find("Data"));

        // Загрузка из несуществующего файла — ничего не происходит.
        let mut list3 = DoublyList::new();
        list3.load("ghost.bin");
        assert_eq!(list3.size, 0);
    }
}