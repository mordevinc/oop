use std::fs::File;

pub struct Array {
    data: Vec<String>,
    capacity: usize,
}

impl Array {
    pub fn new(cap: usize) -> Self { Array { data: Vec::new(), capacity: cap } }

    pub fn push(&mut self, val: String) {
        if self.data.len() < self.capacity { self.data.push(val); }
    }

    pub fn insert_at(&mut self, index: usize, val: String) {
        if index <= self.data.len() && self.data.len() < self.capacity { self.data.insert(index, val); }
    }

    pub fn get(&self, index: usize) -> Option<&String> { self.data.get(index) }

    pub fn set(&mut self, index: usize, val: String) {
        if index < self.data.len() { self.data[index] = val; }
    }

    pub fn remove(&mut self, index: usize) -> Option<String> {
        if index < self.data.len() { Some(self.data.remove(index)) } else { None }
    }

    pub fn print(&self) {
        print!("[ ");
        for item in &self.data { print!("{} ", item); }
        println!("]");
    }

    pub fn save(&self, filename: &str) {
        let mut f = File::create(filename).expect("Ошибка");
        bincode::serialize_into(&mut f, &self.data).expect("Ошибка сериализации");
    }

    pub fn load(&mut self, filename: &str) {
        if let Ok(mut f) = File::open(filename) {
            if let Ok(loaded) = bincode::deserialize_from::<_, Vec<String>>(&mut f) {
                self.data = loaded;
                self.capacity = self.data.len().max(100);
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_array_full_coverage() {
        let mut arr = Array::new(2);
        arr.push("A".to_string());
        arr.push("B".to_string());
        arr.push("C".to_string()); // Переполнение (ветка else)
        
        // insert_at
        arr.remove(0);
        arr.insert_at(0, "Z".to_string());
        arr.insert_at(5, "X".to_string()); // Ошибка индекса
        
        // get, set, remove
        assert_eq!(arr.get(0).unwrap(), "Z");
        arr.set(0, "Q".to_string());
        assert_eq!(arr.get(0).unwrap(), "Q");
        assert!(arr.get(5).is_none());
        assert!(arr.remove(5).is_none());
        
        arr.print();
        arr.save("test_arr.bin");
        let mut arr2 = Array::new(2);
        arr2.load("test_arr.bin");
        assert_eq!(arr2.data[0], "Q");
        
        let mut arr3 = Array::new(2);
        arr3.load("ghost.bin"); // Несуществующий файл
    }
}