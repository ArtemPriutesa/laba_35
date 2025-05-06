#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class WordString {
    string word;
public:
    WordString(const string& w) : word(w) {}
    string getWord() const { return word; }
};

int count_vowels(const string& str) {
    int count = 0;
    string vowels = "aeiouAEIOU"; // English vowels
    for (char ch : str) {
        if (vowels.find(ch) != string::npos) {
            count++;
        }
    }
    return count;
}

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

    for (const auto& pair : word_count) {
        output_file << pair.first << " -> " << pair.second << endl;
    }
}

void task_c(ifstream& file, const string& search_word) {
    string line;
    cout << "Sentences containing the word \"" << search_word << "\":" << endl;
    while (getline(file, line)) {
        if (line.find(search_word) != string::npos) {
            cout << line << endl;
        }
    }
}

void task_d(ifstream& file, const string& search_word) {
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    WordString wordObj(search_word);
    size_t first_pos = text.find(wordObj.getWord());
    size_t last_pos = text.rfind(wordObj.getWord());

    if (first_pos == string::npos || last_pos == string::npos || first_pos == last_pos) {
        cout << "Error: The word does not exist or appears only once." << endl;
        return;
    }

    text.erase(first_pos + wordObj.getWord().length(), last_pos - first_pos - wordObj.getWord().length());

    ofstream output_file("z3.txt");
    output_file << "Searched word: " << wordObj.getWord() << endl;
    output_file << "Result: " << text << endl;
    output_file.close();
    cout << "Result saved to z3.txt" << endl;
}

void task_e() {
    ifstream file1("s1.txt"), file2("s2.txt");
    ofstream output_file("z4.txt");

    vector<string> words;
    string word;

    while (file1 >> word) {
        words.push_back(word);
    }
    while (file2 >> word) {
        words.push_back(word);
    }

    sort(words.begin(), words.end());

    for (const string& w : words) {
        output_file << w << endl;
    }

    file1.close();
    file2.close();
    output_file.close();
    cout << "Result saved to z4.txt" << endl;
}

int main() {
    int choice;
    cout << "Select a task (1-5): ";
    cin >> choice;

    ifstream file("z1.txt");
    ofstream output_file("z2.txt");
    vector<string> words;

    if (!file) {
        cout << "File not open" << endl;
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
            cout << "Enter a word to search: ";
            cin >> search_word;
            task_c(file, search_word);
            break;
        }
        case 4: {
            file.clear();
            file.seekg(0);
            string search_word;
            cout << "Enter a word to search: ";
            cin >> search_word;
            task_d(file, search_word);
            break;
        }
        case 5:
            task_e();
            break;
        default:
            cout << "Invalid choice!" << endl;
    }

    file.close();
    output_file.close();
    return 0;
}