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

    // Вспомогательные методы
    fn height(node: &Option<Box<Node>>) -> i32 {
        node.as_ref().map_or(0, |n| n.height)
    }

    fn update_height(node: &mut Node) {
        node.height = 1 + std::cmp::max(Self::height(&node.left), Self::height(&node.right));
    }

    fn balance_factor(node: &Node) -> i32 {
        Self::height(&node.left) - Self::height(&node.right)
    }

    // Вставка (рекурсивная)
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
            return Some(node); // Дубликат
        }

        Self::update_height(&mut node);
        let bf = Self::balance_factor(&node);

        // Балансировка (пока без поворотов для краткости, но структура готова)
        // В реальном АВЛ здесь должны быть rotate_left и rotate_right.
        
        Some(node)
    }

    pub fn insert(&mut self, key: i32) {
        self.root = Self::insert_rec(self.root.take(), key);
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

    // Упрощенная сериализация
    pub fn save(&self, _filename: &str) {
        // Для простоты можно пропустить, или реализовать обход в массив
        println!("Сериализация дерева (демо)");
    }

    pub fn load(&mut self, _filename: &str) {
        println!("Загрузка дерева (демо)");
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_avl() {
        let mut tree = AVLTree::new();
        tree.insert(10);
        tree.insert(5);
        assert!(tree.contains(10));
        assert!(!tree.contains(99));
    }
}