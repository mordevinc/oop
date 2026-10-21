use std::fs::File;
use std::io::{Read, Write};

// Структура динамического массива строк
pub struct Array {
    data: Vec<String>,
    capacity: usize,
}

impl Array {
    // Конструктор: создает пустой массив с заданной вместимостью
    pub fn new(cap: usize) -> Self {
        Array { data: Vec::new(), capacity: cap }
    }

    // Добавляет элемент в конец
    pub fn push(&mut self, val: String) {
        if self.data.len() < self.capacity {
            self.data.push(val);
        } else {
            println!("Массив полон!");
        }
    }

    // Выводит элементы
    pub fn print(&self) {
        print!("[ ");
        for item in &self.data {
            print!("{} ", item);
        }
        println!("]");
    }

    // Сохраняет массив в бинарный файл
    pub fn save(&self, filename: &str) {
        let mut f = File::create(filename).expect("Ошибка создания файла");
        // Сохраняем размер
        bincode::serialize_into(&mut f, &self.data).expect("Ошибка сериализации");
    }

    // Загружает массив из бинарного файла
    pub fn load(&mut self, filename: &str) {
        if let Ok(mut f) = File::open(filename) {
            if let Ok(loaded_data) = bincode::deserialize_from::<_, Vec<String>>(&mut f) {
                self.data = loaded_data;
                self.capacity = self.data.len().max(100);
            }
        }
    }
}

// Юнит-тесты
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_push_and_limit() {
        let mut arr = Array::new(2);
        arr.push("A".to_string());
        arr.push("B".to_string());
        arr.push("C".to_string()); // Должно проигнорироваться
        assert_eq!(arr.data.len(), 2);
    }

    #[test]
    fn test_serialization() {
        let mut arr = Array::new(5);
        arr.push("Test".to_string());
        arr.save("test_arr.bin");
        
        let mut arr2 = Array::new(5);
        arr2.load("test_arr.bin");
        assert_eq!(arr2.data[0], "Test");
    }
}