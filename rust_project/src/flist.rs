use std::fs::File;

struct Node {
    data: String,
    next: Option<Box<Node>>,
}

pub struct ForwardList {
    head: Option<Box<Node>>,
    size: usize,
}

impl ForwardList {
    pub fn new() -> Self {
        ForwardList { head: None, size: 0 }
    }

    pub fn push_front(&mut self, val: String) {
        let new_node = Box::new(Node { data: val, next: self.head.take() });
        self.head = Some(new_node);
        self.size += 1;
    }

    pub fn push_back(&mut self, val: String) {
        let mut current = &mut self.head;
        while let Some(node) = current {
            current = &mut node.next;
        }
        *current = Some(Box::new(Node { data: val, next: None }));
        self.size += 1;
    }

    pub fn insert_after(&mut self, target: &str, val: String) -> bool {
        let mut current = &mut self.head;
        while let Some(node) = current {
            if node.data == target {
                let new_node = Box::new(Node { data: val, next: node.next.take() });
                node.next = Some(new_node);
                self.size += 1;
                return true;
            }
            current = &mut node.next;
        }
        false
    }

    pub fn insert_before(&mut self, target: &str, val: String) -> bool {
        if let Some(head) = &self.head {
            if head.data == target {
                self.push_front(val);
                return true;
            }
        }
        
        let mut current = &mut self.head;
        while let Some(node) = current {
            if let Some(next_node) = &node.next {
                if next_node.data == target {
                    let new_node = Box::new(Node { data: val, next: node.next.take() });
                    node.next = Some(new_node);
                    self.size += 1;
                    return true;
                }
            }
            current = &mut node.next;
        }
        false
    }

    pub fn pop_front(&mut self) -> Option<String> {
        self.head.take().map(|node| {
            self.head = node.next;
            self.size -= 1;
            node.data
        })
    }

    pub fn pop_back(&mut self) -> Option<String> {
        if self.head.is_none() { return None; }
        
        if self.head.as_ref().unwrap().next.is_none() {
            self.size -= 1;
            return self.head.take().map(|node| node.data);
        }

        let mut current = &mut self.head;
        while let Some(node) = current {
            if node.next.as_ref().unwrap().next.is_none() {
                self.size -= 1;
                return node.next.take().map(|n| n.data);
            }
            current = &mut node.next;
        }
        None
    }

    pub fn remove_after(&mut self, target: &str) -> bool {
        let mut current = &mut self.head;
        while let Some(node) = current {
            if node.data == target {
                if node.next.is_some() {
                    node.next = node.next.take().unwrap().next;
                    self.size -= 1;
                    return true;
                }
                return false;
            }
            current = &mut node.next;
        }
        false
    }

    // Исправлено: убрали оператор ?, теперь стандартная проверка
    pub fn remove_before(&mut self, target: &str) -> bool {
        if self.head.is_none() || self.head.as_ref().unwrap().next.is_none() {
            return false;
        }
        
        if self.head.as_ref().unwrap().next.as_ref().unwrap().data == target {
            self.head = self.head.take().unwrap().next;
            self.size -= 1;
            return true;
        }

        let mut current = &mut self.head;
        while let Some(node) = current {
            if let Some(next) = &node.next {
                if let Some(nextnext) = &next.next {
                    if nextnext.data == target {
                        node.next = node.next.take().unwrap().next;
                        self.size -= 1;
                        return true;
                    }
                }
            }
            current = &mut node.next;
        }
        false
    }

    pub fn remove_by_value(&mut self, target: &str) -> bool {
        if let Some(head) = &self.head {
            if head.data == target {
                self.pop_front();
                return true;
            }
        }
        
        let mut current = &mut self.head;
        while let Some(node) = current {
            if let Some(next) = &node.next {
                if next.data == target {
                    node.next = node.next.take().unwrap().next;
                    self.size -= 1;
                    return true;
                }
            }
            current = &mut node.next;
        }
        false
    }

    pub fn find(&self, target: &str) -> bool {
        let mut current = &self.head;
        while let Some(node) = current {
            if node.data == target { return true; }
            current = &node.next;
        }
        false
    }

    pub fn print(&self) {
        let mut current = &self.head;
        print!("List: ");
        while let Some(node) = current {
            print!("{} -> ", node.data);
            current = &node.next;
        }
        println!("nullptr");
    }

    pub fn save(&self, filename: &str) {
        let mut vec_data = Vec::new();
        let mut current = &self.head;
        while let Some(node) = current {
            vec_data.push(node.data.clone());
            current = &node.next;
        }
        let mut f = File::create(filename).unwrap();
        bincode::serialize_into(&mut f, &vec_data).unwrap();
    }

    pub fn load(&mut self, filename: &str) {
        if let Ok(mut f) = File::open(filename) {
            if let Ok(vec_data) = bincode::deserialize_from::<_, Vec<String>>(&mut f) {
                self.head = None; self.size = 0;
                for item in vec_data { self.push_back(item); }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_flist_full_coverage() {
        let mut list = ForwardList::new();
        
        // 1. Операции на пустом списке (проверка веток с nullptr/None)
        assert!(list.pop_front().is_none());
        assert!(list.pop_back().is_none());
        assert!(!list.remove_after("Ghost"));
        assert!(!list.remove_before("Ghost"));
        assert!(!list.remove_by_value("Ghost"));
        assert!(!list.insert_after("Ghost", "X".to_string()));
        assert!(!list.insert_before("Ghost", "X".to_string()));

        // 2. Заполняем список: A -> B -> C
        list.push_back("B".to_string()); 
        list.push_front("A".to_string()); 
        list.push_back("C".to_string()); 
        assert_eq!(list.size, 3);
        
        // 3. Вставки
        assert!(list.insert_after("B", "D".to_string())); // A -> B -> D -> C
        assert!(list.insert_before("B", "X".to_string())); // A -> X -> B -> D -> C
        
        // 4. Удаления до/после (включая крайние случаи)
        list.remove_after("B"); // Удаляет D. Остается: A -> X -> B -> C
        list.remove_before("C"); // Удаляет B. Остается: A -> X -> C
        list.remove_after("C"); // Нечего удалять (C в конце)
        list.remove_before("A"); // Нечего удалять (A в начале)
        assert_eq!(list.size, 3);

        // 5. Удаление по значению (голова, хвост, середина)
        list.remove_by_value("X"); // Удаляет середину. Остается: A -> C
        list.remove_by_value("A"); // Удаляет голову. Остается: C
        list.remove_by_value("C"); // Удаляет хвост. Список пуст.
        assert_eq!(list.size, 0);

        // 6. Извлечение из списка (pop)
        list.push_back("1".to_string());
        list.push_back("2".to_string());
        assert_eq!(list.pop_front().unwrap(), "1");
        assert_eq!(list.pop_back().unwrap(), "2");
        assert_eq!(list.size, 0);

        // 7. Поиск
        list.push_back("Data".to_string());
        assert!(list.find("Data"));
        assert!(!list.find("Missing"));

        // 8. Печать
        list.print();

        // 9. Сериализация и десериализация (включая несуществующий файл)
        list.save("test_flist.bin");
        let mut list2 = ForwardList::new();
        list2.load("test_flist.bin");
        assert_eq!(list2.size, 1);
        
        let mut list3 = ForwardList::new();
        list3.load("ghost_flist.bin");
        assert_eq!(list3.size, 0);
    }
}