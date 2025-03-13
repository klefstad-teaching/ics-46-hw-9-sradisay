#include "ladder.h"
//
// error
//
void error(string word1, string word2, string msg) {
    cerr << msg << " " << word1 << " " << word2 << endl;
}

bool edit_distance_within(const string& s1, const string& s2, int d) {
    if (s1.size() != s2.size()) return false;
    int diff = 0;
    for (int i = 0; i < (int)s1.size(); i++) {
        if (s1[i] != s2[i] && ++diff > d) return false;
    }
    return diff <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> paths;
    set<string> visited;
    paths.push({begin_word});
    visited.insert(begin_word);
    while (!paths.empty()) {
        auto path = paths.front();
        paths.pop();
        if (path.back() == end_word) return path;
        for (auto &w : word_list) {
            if (!visited.count(w) && is_adjacent(path.back(), w)) {
                visited.insert(w);
                auto new_path = path;
                new_path.push_back(w);
                paths.push(new_path);
            }
        }
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    string w;
    while (file >> w) word_list.insert(w);
}

void print_word_ladder(const vector<string>& ladder) {
    for (int i = 0; i < (int)ladder.size(); i++) {
        cout << ladder[i];
        if (i < (int)ladder.size() - 1) cout << " ";
    }
    cout << endl;
}

void verify_word_ladder() {
    set<string> words;
    load_words(words, "words.txt");
    string start, goal;
    cin >> start >> goal;
    auto ladder = generate_word_ladder(start, goal, words);
    print_word_ladder(ladder);
}
