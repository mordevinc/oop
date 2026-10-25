use std::collections::VecDeque;
use std::fs::File;

pub struct Queue {
    data: VecDeque<String>,
}

impl Queue {
    pub fn new() -> Self { Queue { data: VecDeque::new() } }

    pub fn push(&mut self, val: String) { self.data.push_back(val); }

    pub fn pop(&mut self) -> String {
        self.data.pop_front().unwrap_or_else(|| "Пусто".to_string())
    }

    pub fn print(&self) {
        print!("Queue: ");
        for item in &self.data { print!("{} ", item); }
        println!();
    }

    pub fn save(&self, filename: &str) {
        let mut f = File::create(filename).unwrap();
        bincode::serialize_into(&mut f, &self.data).unwrap();
    }

    pub fn load(&mut self, filename: &str) {
        if let Ok(mut f) = File::open(filename) {
            if let Ok(data) = bincode::deserialize_from::<_, VecDeque<String>>(&mut f) {
                self.data = data;
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_push_pop() {
        let mut q = Queue::new();
        q.push("A".to_string());
        q.push("B".to_string());
        assert_eq!(q.pop(), "A");
        assert_eq!(q.pop(), "B");
        // Проверяем pop из пустой очереди
        assert_eq!(q.pop(), "Пусто");
    }

    #[test]
    fn test_print() {
        let mut q = Queue::new();
        q.push("X".to_string());
        q.print();
    }

    #[test]
    fn test_serialization() {
        let mut q = Queue::new();
        q.push("Data".to_string());
        q.save("test_queue.bin");
        
        let mut q2 = Queue::new();
        q2.load("test_queue.bin");
        assert_eq!(q2.data.len(), 1);
    }
}