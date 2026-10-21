use std::fs::File;

// Узел списка
struct Node {
    data: String,
    next: Option<Box<Node>>,
}

// Односвязный список
pub struct ForwardList {
    head: Option<Box<Node>>,
    size: usize,
}

impl ForwardList {
    pub fn new() -> Self {
        ForwardList { head: None, size: 0 }
    }

    // Добавление в начало
    pub fn push_front(&mut self, val: String) {
        let new_node = Box::new(Node {
            data: val,
            next: self.head.take(),
        });
        self.head = Some(new_node);
        self.size += 1;
    }

    // Добавление в конец
    pub fn push_back(&mut self, val: String) {
        let mut current = &mut self.head;
        while let Some(node) = current {
            current = &mut node.next;
        }
        *current = Some(Box::new(Node { data: val, next: None }));
        self.size += 1;
    }

    // Поиск элемента
    pub fn find(&self, val: &str) -> bool {
        let mut current = &self.head;
        while let Some(node) = current {
            if node.data == val { return true; }
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

    // Сохранение (упрощенное через вектор)
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
                self.head = None;
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
    fn test_flist() {
        let mut list = ForwardList::new();
        list.push_back("B".to_string());
        list.push_front("A".to_string());
        assert_eq!(list.size, 2);
        assert!(list.find("A"));
        assert!(!list.find("C"));
    }
}