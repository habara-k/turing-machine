#include "../lib/NFA.cpp"

void test_nfa1() {
    printf("0 or 1 偶数個 を受理するNFA のテスト\n");
    NFA<> nfa(
            set<int>{0,1,2,3,4},
            set<int>{0,1},
            map<pair<int,int>,set<int>>{
                {{0,-1},{1,3}},
                {{1,0},{2}},
                {{1,1},{1}},
                {{2,0},{1}},
                {{2,1},{2}},
                {{3,0},{3}},
                {{3,1},{4}},
                {{4,0},{4}},
                {{4,1},{3}}},
            0,
            set<int>{1,3},
            -1);

    assert(nfa.run(vector<int>{0,1,1}) == true);
    assert(nfa.run(vector<int>{1,0,0}) == true);
    assert(nfa.run(vector<int>{1,0}) == false);
    assert(nfa.run(vector<int>{0,1,0,1}) == true);
    assert(nfa.run(vector<int>{}) == true);

    auto dfa = nfa.convert();

    assert(dfa.run(vector<int>{0,1,1}) == true);
    assert(dfa.run(vector<int>{1,0,0}) == true);
    assert(dfa.run(vector<int>{1,0}) == false);
    assert(dfa.run(vector<int>{0,1,0,1}) == true);
    assert(dfa.run(vector<int>{}) == true);
}

void test_nfa2() {
    printf("0* を受理するNFA のテスト\n");

    NFA<> nfa(
            set<int>{0},
            set<int>{0,1},
            map<pair<int,int>,set<int>> {
                {{0,0},{0}}
            },
            0,
            set<int>{0},
            -1);

    assert(nfa.run(vector<int>{0,0,0}) == true);
    assert(nfa.run(vector<int>{}) == true);

    assert(nfa.run(vector<int>{0,1}) == false);
    assert(nfa.run(vector<int>{1}) == false);

    auto dfa = nfa.convert();

    assert(dfa.run(vector<int>{0,0,0}) == true);
    assert(dfa.run(vector<int>{}) == true);

    assert(dfa.run(vector<int>{0,1}) == false);
    assert(dfa.run(vector<int>{1}) == false);
}


int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    test_nfa1();
    test_nfa2();

    return 0;
}
