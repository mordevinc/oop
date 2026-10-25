use std::fs::File;

pub struct HashTable {
    buckets: Vec<Vec<(String, String)>>,
    capacity: usize,
}

impl HashTable {
    pub fn new(cap: usize) -> Self { HashTable { buckets: vec![Vec::new(); cap], capacity: cap } }

    fn hash(&self, key: &str) -> usize {
        let mut sum = 0;
        for b in key.bytes() { sum += b as usize; }
        sum % self.capacity
    }

    pub fn insert(&mut self, key: String, value: String) {
        let idx = self.hash(&key);
        for pair in &mut self.buckets[idx] {
            if pair.0 == key { pair.1 = value; return; }
        }
        self.buckets[idx].push((key, value));
    }

    pub fn get(&self, key: &str) -> Option<&String> {
        let idx = self.hash(key);
        for (k, v) in &self.buckets[idx] { if k == key { return Some(v); } }
        None
    }

    pub fn remove(&mut self, key: &str) -> bool {
        let idx = self.hash(key);
        if let Some(pos) = self.buckets[idx].iter().position(|(k, _)| k == key) {
            self.buckets[idx].remove(pos);
            return true;
        }
        false
    }

    pub fn print(&self) {
        for (i, bucket) in self.buckets.iter().enumerate() {
            if !bucket.is_empty() { println!("Bucket {}: {:?}", i, bucket); }
        }
    }

    pub fn save(&self, filename: &str) {
        let file = File::create(filename).unwrap();
        serde_json::to_writer(file, &self.buckets).unwrap();
    }

    pub fn load(&mut self, filename: &str) {
        if let Ok(file) = File::open(filename) {
            if let Ok(buckets) = serde_json::from_reader(file) { self.buckets = buckets; }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_hash_table_full_coverage() {
        let mut ht = HashTable::new(5);
        
        ht.insert("A".to_string(), "1".to_string());
        ht.insert("A".to_string(), "2".to_string()); // Обновление
        assert_eq!(ht.get("A").unwrap(), "2");
        assert!(ht.get("B").is_none());

        ht.print();
        
        assert!(ht.remove("A"));
        assert!(!ht.remove("A")); // Удаление несуществующего

        ht.insert("K".to_string(), "V".to_string());
        ht.save("test_ht.json");
        
        let mut ht2 = HashTable::new(5);
        ht2.load("test_ht.json");
        assert_eq!(ht2.get("K").unwrap(), "V");
        
        let mut ht3 = HashTable::new(5);
        ht3.load("ghost.json");
    }
}