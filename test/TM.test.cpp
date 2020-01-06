#include "../lib/TM.cpp"

void test_tm1() {
    printf("0^n 1^n 0^n を受理するTM のテスト\n");
    bool R = true, L = false;
    int a = 7, b = 8, c = 9;
    int B = -1;
    TM<> tm(
            set<int>{0,1,2,3,4,5},
            set<int>{0,1,a,b,c},
            map<pair<int,int>,
                tuple<int,int,bool>>{
                    {{0,0},{1,a,R}},
                    {{1,0},{1,0,R}},
                    {{1,b},{1,b,R}},
                    {{1,1},{2,b,R}},
                    {{2,1},{2,1,R}},
                    {{2,c},{2,c,R}},
                    {{2,0},{3,c,L}},
                    {{3,0},{3,0,L}},
                    {{3,1},{3,1,L}},
                    {{3,b},{3,b,L}},
                    {{3,c},{3,c,L}},
                    {{3,a},{0,a,R}},

                    {{0,a},{4,a,R}},
                    {{0,b},{4,b,R}},
                    {{0,c},{4,c,R}},
                    {{4,a},{4,a,R}},
                    {{4,b},{4,b,R}},
                    {{4,c},{4,c,R}},
                    {{4,B},{5,B,L}},

                    {{0,B},{5,B,L}}},
            0,
            B,
            set<int>{5});

    assert(tm.run(Tape<int>({},B)) == true);
    assert(tm.run(Tape<int>({0,1,0},B)) == true);
    assert(tm.run(Tape<int>({0,0,1,1,0,0},B)) == true);

    assert(tm.run(Tape<int>({0,1,0,0},B)) == false);
    assert(tm.run(Tape<int>({0,1,1,0},B)) == false);
    assert(tm.run(Tape<int>({0,0,1,0},B)) == false);

    assert(tm.run(Tape<int>({0,0,0},B)) == false);
    assert(tm.run(Tape<int>({1,1,1},B)) == false);

    assert(tm.run(Tape<int>({0,1,1},B)) == false);
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    test_tm1();

    return 0;
}
