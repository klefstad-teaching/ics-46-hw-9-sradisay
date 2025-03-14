#include "ladder.h"
#include <unordered_map>

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
//
// error
//
void error(string word1, string word2, string msg) {
    cerr << msg << " " << word1 << " " << word2 << endl;
}

bool edit_distance_within(const string& s1, const string& s2, int d) {
    int s1_size = s1.size(), s2_size = s2.size();
    if (abs(s1_size - s2_size) > d) return false;
    
    vector<int> prev(s2_size + 1), curr(s2_size + 1);
    
    for (int j = 0; j <= s2_size; j++) {
        prev[j] = j;
    }
    
    for (int i = 1; i <= s1_size; i++) {
        curr[0] = i;  
        int rowMin = curr[0];
        
        for (int j = 1; j <= s2_size; j++) {
            if (s1[i - 1] == s2[j - 1])
                curr[j] = prev[j - 1];
            else
                curr[j] = 1 + min({ prev[j],      
                                    curr[j - 1], 
                                    prev[j - 1] });
            
            rowMin = min(rowMin, curr[j]);
        }
        
        if (rowMin > d)
            return false;
        
        prev.swap(curr);
    }
    
    return prev[s2_size] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list)
{
    if (word_list.find(end_word) == word_list.end())
        return vector<string>(); 

    queue<vector<string>> ladder_queue;
    
    ladder_queue.push({begin_word});
    
    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladder_queue.empty())
    {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        
        string last_word = ladder.back();
        
        for (const string &word : word_list)
        {
            if (is_adjacent(last_word, word))
            {
                if (visited.find(word) == visited.end())
                {
                    visited.insert(word);
                    
                    vector<string> new_ladder(ladder);
                    new_ladder.push_back(word);
                    
                    if (word == end_word)
                    {
                        return new_ladder;
                    }
                    
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return vector<string>();
}
void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    string w;
    while (file >> w) word_list.insert(w);
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }

    cout << "Word ladder found: ";
    for (int i = 0; i < (int)ladder.size(); i++) 
        cout << ladder[i] << " ";
    cout << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "../src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
