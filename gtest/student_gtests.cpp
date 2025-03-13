#include <gtest/gtest.h>
#include <vector>
#include "dijkstras.h"
#include "ladder.h"

using namespace std;


TEST(Dijkstra, Test) {
    Graph G;
    G.numVertices = 4;
    G.resize(4);
    G[0].push_back(Edge(0, 1, 2));
    G[0].push_back(Edge(0, 2, 5));
    G[1].push_back(Edge(1, 2, 2));
    G[1].push_back(Edge(1, 3, 1));
    G[2].push_back(Edge(2, 3, 2));

    vector<int> prev(G.numVertices, -1);
    auto dist = dijkstra_shortest_path(G, 0, prev);
    auto path = extract_shortest_path(dist, prev, 3);

    cout << "Distances: ";
    for (auto d : dist) cout << d << " ";
    cout << endl;

    cout << "Shortest path from 0 to 3: ";
    for (auto v : path) cout << v << " ";
    cout << endl;

    print_path(path, dist[2]);
    
    EXPECT_EQ(dist[3], 3);
    EXPECT_EQ(path.size(), 3);
    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 1);
    EXPECT_EQ(path[2], 3);
}

TEST(Dijkstra, TestSmall) {
    Graph G;
    file_to_graph("../src/small.txt", G);
    vector<int> previous(G.numVertices, -1);
    auto dist = dijkstra_shortest_path(G, 0, previous);
    auto path = extract_shortest_path(dist, previous, 3);
    ASSERT_FALSE(path.empty());
    EXPECT_EQ(path.front(), 0);
    EXPECT_EQ(path.back(), 3);
}

TEST(Ladder, Test) {
    set<string> words = {"hit","hot","dot","dog","cog","lot","log"};
    auto ladder = generate_word_ladder("hit", "cog", words);
    vector<string> expected = {"hit","hot","dot","dog","cog"};
    EXPECT_EQ(ladder, expected);
}

TEST(Ladder, TestWords) {
    set<string> words;
    load_words(words, "../src/words.txt");
    auto ladder = generate_word_ladder("hit", "cog", words);
    ASSERT_FALSE(ladder.empty());
    EXPECT_EQ(ladder.front(), "hit");
    EXPECT_EQ(ladder.back(), "cog");
}

