use std::fs::File;

pub struct HashTable {
    buckets: Vec<Vec<(String, String)>>,
    capacity: usize,
}

impl HashTable {
    pub fn new(cap: usize) -> Self {
        HashTable { buckets: vec![Vec::new(); cap], capacity: cap }
    }

    // Простая хеш-функция
    fn hash(&self, key: &str) -> usize {
        let mut sum = 0;
        for b in key.bytes() { sum += b as usize; }
        sum % self.capacity
    }

    pub fn insert(&mut self, key: String, value: String) {
        let idx = self.hash(&key);
        // Проверяем, есть ли ключ, обновляем, иначе добавляем
        for pair in &mut self.buckets[idx] {
            if pair.0 == key {
                pair.1 = value;
                return;
            }
        }
        self.buckets[idx].push((key, value));
    }

    pub fn print(&self) {
        for (i, bucket) in self.buckets.iter().enumerate() {
            if !bucket.is_empty() {
                println!("Bucket {}: {:?}", i, bucket);
            }
        }
    }

    // Сериализация через JSON (текстовый формат)
    pub fn save(&self, filename: &str) {
        let file = File::create(filename).unwrap();
        serde_json::to_writer(file, &self.buckets).unwrap();
    }

    pub fn load(&mut self, filename: &str) {
        if let Ok(file) = File::open(filename) {
            if let Ok(buckets) = serde_json::from_reader(file) {
                self.buckets = buckets;
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_hash_table() {
        let mut ht = HashTable::new(5);
        ht.insert("A".to_string(), "1".to_string());
        ht.insert("A".to_string(), "2".to_string()); // Обновление
        let idx = ht.hash("A");
        assert_eq!(ht.buckets[idx][0].1, "2");
    }
}