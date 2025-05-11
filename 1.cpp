#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// Клас для представлення слова
class WordString {
    string word;
public:
    WordString(const string& w) : word(w) {} // Конструктор для ініціалізації слова
    string getWord() const { return word; }  // Метод для отримання слова
};

// Функція для підрахунку кількості голосних у рядку
int count_vowels(const string& str) {
    int count = 0;
    string vowels = "aeiouAEIOU"; 
    for (char ch : str) {
        if (vowels.find(ch) != string::npos) { // Перевірка, чи є символ голосним
            count++;
        }
    }
    return count;
}

// Завдання A: Обробка слів із файлу та запис їх у інший файл
void task_a(ifstream& file, ofstream& output_file, vector<string>& words) {
    string word;
    while (file >> word) {
        int vowels_word = count_vowels(word); 
        output_file << word << " "; 
        if (vowels_word > 2) { 
            output_file << word << " ";
        }
        words.push_back(word);
    }
}

// Завдання B: Підрахунок кількості входжень кожного слова та запис результатів у файл
void task_b(const vector<string>& words, ofstream& output_file) {
    vector<pair<string, int>> word_count;

    for (const string& word : words) {
        bool found = false;
        for (auto& pair : word_count) { 
            if (pair.first == word) {
                pair.second++; 
                found = true;
                break;
            }
        }
        if (!found) { 
            word_count.push_back({word, 1});
        }
    }

    for (const auto& pair : word_count) { // Записуємо кількість входжень у файл
        output_file << pair.first << " -> " << pair.second << endl;
    }
}

// Завдання C: Знайти та вивести речення, що містять задане слово
void task_c(ifstream& file, const string& search_word) {
    string line;
    cout << "line\"" << search_word << "\":" << endl;
    while (getline(file, line)) { // Зчитування рядків із файлу
        if (line.find(search_word) != string::npos) { // Перевірка, чи містить рядок слово
            cout << line << endl; // Виведення рядка
        }
    }
}

// Завдання D: Видалити символи між першим і останнім входженням слова
void task_d(ifstream& file, const string& search_word) {
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>()); // Зчитуємо весь файл у рядок
    WordString wordObj(search_word);
    int first_pos = text.find(wordObj.getWord()); // Знаходимо перше входження слова
    int last_pos = text.rfind(wordObj.getWord()); // Знаходимо останнє входження слова

    if (first_pos == string::npos || last_pos == string::npos || first_pos == last_pos) {
        cout << "eror slowo 1 raz" << endl;
        return;
    }

    // Видаляємо символи між першим і останнім входженням слова
    text.erase(first_pos + wordObj.getWord().length(), last_pos - first_pos - wordObj.getWord().length());

    ofstream output_file("z3.txt"); // Записуємо результат у файл
    output_file << "serch slowo: " << wordObj.getWord() << endl;
    output_file << "result: " << text << endl;
    output_file.close();
    cout << "z3.txt" << endl;
}

// Завдання E: Об'єднати та відсортувати слова з двох файлів
void task_e() {
    ifstream file1("s1.txt"), file2("s2.txt");
    ofstream output_file("z4.txt");

    vector<string> words;
    string word;

    while (file1 >> word) { // Зчитування слів із першого файлу
        words.push_back(word);
    }
    while (file2 >> word) { // Зчитування слів із другого файлу
        words.push_back(word);
    }

    sort(words.begin(), words.end()); // Сортування слів за алфавітом

    for (const string& w : words) { // Запис відсортованих слів у файл
        output_file << w << endl;
    }

    file1.close();
    file2.close();
    output_file.close();
    cout << "z4.txt" << endl;
}

int main() {
    int choice;
    cout << "(1-5): ";
    cin >> choice;

    ifstream file("z1.txt");
    ofstream output_file("z2.txt");
    vector<string> words;

    if (!file) { // Перевірка, чи відкрився файл
        cout << "!file is open" << endl;
        return 0;
    }

    switch (choice) {
        case 1:
            task_a(file, output_file, words);
            break;
        case 2:
            task_b(words, output_file);
            break;
        case 3: {
            file.clear();
            file.seekg(0); 
            string search_word;
            cout << "serch: ";
            cin >> search_word;
            task_c(file, search_word); 
            break;
        }
        case 4: {
            file.clear();
            file.seekg(0); 
            string search_word;
            cout << "serch word: ";
            cin >> search_word;
            task_d(file, search_word); 
            break;
        }
        case 5:
            task_e();
            break;
        default:
            cout << "neprav!" << endl;
    }

    file.close();
    output_file.close();
    return 0;
}