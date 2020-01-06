#include "template.cpp"

template<
    typename t_state = int,
    typename t_states = set<t_state>,
    typename t_symbol = int,
    typename t_symbols = set<t_symbol>,
    typename t_transision = map<pair<t_state,t_symbol>,
                                tuple<t_state,t_symbol,bool>>
>
struct TM {
    t_states states;
    t_symbols input_symbols;
    t_symbols symbols;
    t_transision transision;
    t_state start_state;
    t_symbol blank;
    t_states accept_states;

    TM(
            const t_states& states,
            const t_symbols& symbols,
            const t_transision& transision,
            const t_state& start_state,
            const t_symbol& blank,
            const t_states& accept_states
       ) : states(states),
           symbols(symbols),
           transision(transision),
           start_state(start_state),
           blank(blank),
           accept_states(accept_states) {}

    // TODO: blank をいい感じにしてくれる構造体
    template<typename t_input = vector<t_symbol>>
    bool run(t_input&& input) {
        auto iterator = input.begin()+1;
        t_state state = start_state;

        while (transision.count({state, *iterator})) {
            t_state nxt_state;
            t_symbol nxt_symbol;
            bool direction;

            std::tie(nxt_state, nxt_symbol, direction) =
                transision.at({state, *iterator});

            state = nxt_state;
            *iterator = nxt_symbol;

            direction ? iterator++ : iterator--;
        }
        return accept_states.find(state) != accept_states.end();
    }
};

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

    assert(tm.run(vector<int>{B,B}) == true);
    assert(tm.run(vector<int>{B,0,1,0,B}) == true);
    assert(tm.run(vector<int>{B,0,0,1,1,0,0,B}) == true);

    assert(tm.run(vector<int>{B,0,1,0,0,B}) == false);
    assert(tm.run(vector<int>{B,0,1,1,0,B}) == false);
    assert(tm.run(vector<int>{B,0,0,1,0,B}) == false);

    assert(tm.run(vector<int>{B,0,0,0,B}) == false);
    assert(tm.run(vector<int>{B,1,1,1,B}) == false);

    assert(tm.run(vector<int>{B,0,1,1,B}) == false);
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    test_tm1();

    return 0;
}
