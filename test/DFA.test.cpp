#include "../lib/DFA.cpp"

void test_dfa1() {
    printf("3 の倍数を受理するDFA のテスト\n");
    DFA<> dfa(
            set<int>{0,1,2},
            set<int>{0,1},
            map<pair<int,int>,int>{
                {{0,0},0},
                {{0,1},1},
                {{1,0},2},
                {{1,1},0},
                {{2,0},1},
                {{2,1},2}},
            0,
            set<int>{0});

    assert(dfa.run(vector<int>{1,0,0}) == false); // 100(2) = 4
    assert(dfa.run(vector<int>{1,0,1}) == false); // 101(2) = 5
    assert(dfa.run(vector<int>{1,1,0}) == true);  // 110(2) = 6
}

void test_dfa2() {
    printf("01* を受理するDFA のテスト\n");
    DFA<> dfa(
            set<int>{0,1,2},
            set<int>{0,1},
            map<pair<int,int>,int>{
                {{0,0},1},
                {{0,1},2},
                {{1,0},2},
                {{1,1},1},
                {{2,0},2},
                {{2,1},2}},
            0,
            set<int>{1});

    assert(dfa.run(vector<int>{0,1,1}) == true);
    assert(dfa.run(vector<int>{0}) == true);
    assert(dfa.run(vector<int>{}) == false);
    assert(dfa.run(vector<int>{1,0}) == false);
}


int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    test_dfa1();
    test_dfa2();

    return 0;
}
