use std::rc::Rc;
use std::cell::RefCell;
use std::fs::File;

struct Node {
    data: String,
    prev: Option<Rc<RefCell<Node>>>,
    next: Option<Rc<RefCell<Node>>>,
}

pub struct DoublyList {
    head: Option<Rc<RefCell<Node>>>,
    tail: Option<Rc<RefCell<Node>>>,
    size: usize,
}

impl DoublyList {
    pub fn new() -> Self {
        DoublyList { head: None, tail: None, size: 0 }
    }

    pub fn push_back(&mut self, val: String) {
        let new_node = Rc::new(RefCell::new(Node {
            data: val, prev: self.tail.clone(), next: None,
        }));
        if let Some(old_tail) = &self.tail {
            old_tail.borrow_mut().next = Some(new_node.clone());
        } else {
            self.head = Some(new_node.clone());
        }
        self.tail = Some(new_node);
        self.size += 1;
    }

    pub fn push_front(&mut self, val: String) {
        let new_node = Rc::new(RefCell::new(Node {
            data: val, prev: None, next: self.head.clone(),
        }));
        if let Some(old_head) = &self.head {
            old_head.borrow_mut().prev = Some(new_node.clone());
        } else {
            self.tail = Some(new_node.clone());
        }
        self.head = Some(new_node);
        self.size += 1;
    }

    pub fn print(&self) {
        let mut current = self.head.clone();
        print!("List: ");
        while let Some(node) = current {
            print!("{} <-> ", node.borrow().data);
            current = node.borrow().next.clone();
        }
        println!("nullptr");
    }

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

    pub fn load(&mut self, filename: &str) {
        if let Ok(mut f) = File::open(filename) {
            if let Ok(vec_data) = bincode::deserialize_from::<_, Vec<String>>(&mut f) {
                self.head = None; self.tail = None; self.size = 0;
                for item in vec_data { self.push_back(item); }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_dlist() {
        let mut list = DoublyList::new();
        list.push_back("A".to_string());
        list.push_front("Z".to_string());
        assert_eq!(list.size, 2);
    }
}