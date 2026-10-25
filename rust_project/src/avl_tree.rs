use std::fs::File;

struct Node {
    key: i32,
    height: i32,
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
}

pub struct AVLTree {
    root: Option<Box<Node>>,
}

impl AVLTree {
    pub fn new() -> Self { AVLTree { root: None } }

    fn height(node: &Option<Box<Node>>) -> i32 {
        node.as_ref().map_or(0, |n| n.height)
    }

    fn update_height(node: &mut Node) {
        node.height = 1 + std::cmp::max(Self::height(&node.left), Self::height(&node.right));
    }

    fn balance_factor(node: &Node) -> i32 {
        Self::height(&node.left) - Self::height(&node.right)
    }

    fn rotate_right(mut y: Box<Node>) -> Box<Node> {
        let mut x = y.left.take().unwrap();
        y.left = x.right.take();
        Self::update_height(&mut y);
        Self::update_height(&mut x);
        x.right = Some(y);
        x
    }

    fn rotate_left(mut x: Box<Node>) -> Box<Node> {
        let mut y = x.right.take().unwrap();
        x.right = y.left.take();
        Self::update_height(&mut x);
        Self::update_height(&mut y);
        y.left = Some(x);
        y
    }

    fn balance(mut node: Box<Node>) -> Box<Node> {
        Self::update_height(&mut node);
        let bf = Self::balance_factor(&node);

        if bf > 1 {
            if Self::balance_factor(node.left.as_ref().unwrap()) < 0 {
                let left = node.left.take().unwrap();
                node.left = Some(Self::rotate_left(left));
            }
            return Self::rotate_right(node);
        }
        if bf < -1 {
            if Self::balance_factor(node.right.as_ref().unwrap()) > 0 {
                let right = node.right.take().unwrap();
                node.right = Some(Self::rotate_right(right));
            }
            return Self::rotate_left(node);
        }
        node
    }

    fn insert_rec(node: Option<Box<Node>>, key: i32) -> Option<Box<Node>> {
        let mut node = match node {
            Some(n) => n,
            None => return Some(Box::new(Node { key, height: 1, left: None, right: None })),
        };

        if key < node.key {
            node.left = Self::insert_rec(node.left.take(), key);
        } else if key > node.key {
            node.right = Self::insert_rec(node.right.take(), key);
        } else {
            return Some(node);
        }

        Some(Self::balance(node))
    }

    pub fn insert(&mut self, key: i32) {
        self.root = Self::insert_rec(self.root.take(), key);
    }

    fn min_node(node: &Option<Box<Node>>) -> Option<i32> {
        if let Some(n) = node {
            if n.left.is_none() {
                return Some(n.key);
            }
            return Self::min_node(&n.left);
        }
        None
    }

    fn remove_rec(node: Option<Box<Node>>, key: i32) -> Option<Box<Node>> {
        let mut current = node?;

        if key < current.key {
            current.left = Self::remove_rec(current.left.take(), key);
        } else if key > current.key {
            current.right = Self::remove_rec(current.right.take(), key);
        } else {
            if current.left.is_none() {
                return current.right;
            } else if current.right.is_none() {
                return current.left;
            }
            let min_val = Self::min_node(&current.right).unwrap();
            current.key = min_val;
            current.right = Self::remove_rec(current.right.take(), min_val);
        }

        Self::update_height(&mut current);
        Some(Self::balance(current))
    }

    pub fn remove(&mut self, key: i32) {
        self.root = Self::remove_rec(self.root.take(), key);
    }

    pub fn contains(&self, key: i32) -> bool {
        let mut current = &self.root;
        while let Some(node) = current {
            if key == node.key { return true; }
            current = if key < node.key { &node.left } else { &node.right };
        }
        false
    }

    fn print_rec(node: &Option<Box<Node>>) {
        if let Some(n) = node {
            Self::print_rec(&n.left);
            print!("{} ", n.key);
            Self::print_rec(&n.right);
        }
    }

    pub fn print(&self) {
        print!("Tree: ");
        Self::print_rec(&self.root);
        println!();
    }

    fn preorder_rec(node: &Option<Box<Node>>) {
        if let Some(n) = node {
            print!("{} ", n.key);
            Self::preorder_rec(&n.left);
            Self::preorder_rec(&n.right);
        }
    }

    pub fn print_preorder(&self) {
        print!("Tree (preorder): ");
        Self::preorder_rec(&self.root);
        println!();
    }

    fn postorder_rec(node: &Option<Box<Node>>) {
        if let Some(n) = node {
            Self::postorder_rec(&n.left);
            Self::postorder_rec(&n.right);
            print!("{} ", n.key);
        }
    }

    pub fn print_postorder(&self) {
        print!("Tree (postorder): ");
        Self::postorder_rec(&self.root);
        println!();
    }

    // Вспомогательный метод для сохранения (Preorder обход)
    fn serialize_rec(node: &Option<Box<Node>>, buffer: &mut Vec<i32>) {
        match node {
            Some(n) => {
                buffer.push(n.key);
                Self::serialize_rec(&n.left, buffer);
                Self::serialize_rec(&n.right, buffer);
            }
            None => {
                // Маркер пустого узла
                buffer.push(-999999);
            }
        }
    }

    // Вспомогательный метод для загрузки
    fn deserialize_rec(iter: &mut std::slice::Iter<i32>) -> Option<Box<Node>> {
        if let Some(&key) = iter.next() {
            if key == -999999 {
                return None;
            }
            let mut node = Box::new(Node {
                key,
                height: 1,
                left: None,
                right: None,
            });
            node.left = Self::deserialize_rec(iter);
            node.right = Self::deserialize_rec(iter);
            Self::update_height(&mut node);
            return Some(node);
        }
        None
    }

    // НАСТОЯЩЕЕ сохранение в файл
    pub fn save(&self, filename: &str) {
        let mut f = File::create(filename).expect("Ошибка создания файла");
        let mut buffer = Vec::new();
        Self::serialize_rec(&self.root, &mut buffer);
        bincode::serialize_into(&mut f, &buffer).expect("Ошибка записи в файл");
    }

    // НАСТОЯЩАЯ загрузка из файла
    pub fn load(&mut self, filename: &str) {
        if let Ok(mut f) = File::open(filename) {
            if let Ok(buffer) = bincode::deserialize_from::<_, Vec<i32>>(&mut f) {
                let mut iter = buffer.iter();
                self.root = Self::deserialize_rec(&mut iter);
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_avl_full_coverage() {
        let mut tree = AVLTree::new();
        
        tree.insert(30); tree.insert(20); tree.insert(10); 
        tree.insert(40); tree.insert(50); 
        tree.insert(25); 
        
        assert!(tree.contains(20));
        assert!(!tree.contains(99));
        
        tree.print();
        tree.print_preorder();
        tree.print_postorder();

        tree.remove(20);
        tree.remove(40);
        tree.remove(30); 
        tree.remove(999);
        
        // Проверяем реальную сериализацию
        tree.save("test_tree.bin");
        let mut tree2 = AVLTree::new();
        tree2.load("test_tree.bin");
        
        // Проверяем, что дерево восстановилось
        assert!(tree2.contains(10));
        assert!(tree2.contains(50));
        
        let mut tree3 = AVLTree::new();
        tree3.load("ghost.bin"); // Несуществующий файл
    }
}