#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
int count_vowels(const string& str) {
    int count = 0;
    string vowels = "аеєиіїоуяюАЕЄИІЇОУЯЮ";
    for (char ch : str) {
        if (vowels.find(ch) != string::npos) {
            count++;
        }
    }
    return count;
}


int main(){ 
    ifstream file("z1.txt");
    ofstream output_file("z2.txt");
    vector<string> words;
    string word;
    
   
    if(!file){
        cout<<"file no open"<<endl;
        return 0;
    }
    
    while (file >> word)
    {
        int vowels_word=count_vowels(word);
        output_file<<word<<" ";
        if(vowels_word>2){
            output_file<<word<<" ";
        }
    }
    while (file>>word)
    {
        words.push_back(word);
    }
    sort(words.begin(), words.end(), [](const string& a, const string& b) {
    return a.size() > b.size();
    });
    cout << "3 dowgi slova:" << endl;
    for (int i = 0; i < 3 && i < words.size(); ++i) {
        int count = 0;
        for (const string& w : words) {
            if (w == words[i]) {
                count++;
            }
        }
        cout << words[i] << " (" << count << " n)" << endl;
    }
	file.close();
    output_file.close();
    return 0;
}