#include "template.cpp"

template<
    typename t_state = int,
    typename t_states = set<t_state>,
    typename t_symbol = int,
    typename t_symbols = set<t_symbol>,
    typename t_transision = map<pair<t_state,t_symbol>, t_state>
>
struct DFA {
    t_states states;
    t_symbols symbols;
    t_transision transision;
    t_state start_state;
    t_states accept_states;

    DFA(
            const t_states& states,
            const t_symbols& symbols,
            const t_transision& transision,
            const t_state& start_state,
            const t_states& accept_states
       ) : states(states),
           symbols(symbols),
           transision(transision),
           start_state(start_state),
           accept_states(accept_states) {}

    template<typename t_input = vector<t_symbol>>
    bool run(const t_input& input) {
        t_state state = start_state;
        for (const t_symbol& symbol : input) {
            state = transision.at({ state, symbol });
        }
        return accept_states.find(state) != accept_states.end();
    }
};


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
