use std::fs::File;

pub struct Stack {
    data: Vec<String>,
}

impl Stack {
    pub fn new() -> Self { Stack { data: Vec::new() } }

    pub fn push(&mut self, val: String) { self.data.push(val); }

    pub fn pop(&mut self) -> String {
        self.data.pop().unwrap_or_else(|| "Пусто".to_string())
    }

    pub fn print(&self) {
        print!("Stack: ");
        for item in self.data.iter().rev() { print!("{} ", item); }
        println!();
    }

    pub fn save(&self, filename: &str) {
        let mut f = File::create(filename).unwrap();
        bincode::serialize_into(&mut f, &self.data).unwrap();
    }

    pub fn load(&mut self, filename: &str) {
        if let Ok(mut f) = File::open(filename) {
            if let Ok(data) = bincode::deserialize_from::<_, Vec<String>>(&mut f) {
                self.data = data;
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_stack() {
        let mut s = Stack::new();
        s.push("A".to_string());
        s.push("B".to_string());
        assert_eq!(s.pop(), "B");
    }
}