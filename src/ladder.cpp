#include "ladder.h"

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
//
// error
//
void error(string word1, string word2, string msg) {
    cerr << msg << " " << word1 << " " << word2 << endl;
}

static int get_length_diff(const string& a, const string& b)
{
    return abs((int)a.size() - (int)b.size());
}


static bool edit_distance_at_most_one(const string& a, const string& b) {
    int length_diff = get_length_diff(a, b);
    if (length_diff > 1) return false;

    int diff = length_diff;
    int shorter_size = a.size();
    if (b.size() < shorter_size)
        shorter_size = b.size();

    for (int i = 0; i < shorter_size; ++i)
        if (a[i] != b[i])
            ++diff;
    
    
    return diff <= 1;
}

bool edit_distance_within(const string& s1, const string& s2, int d) {
    return edit_distance_at_most_one(s1, s2);
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {};
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
    while (file >> w) {word_list.insert(w);}
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
