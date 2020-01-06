#include "template.cpp"

template<
    typename t_state = int,
    typename t_states = set<t_state>,
    typename t_symbol = int,
    typename t_symbols = set<t_symbol>,
    typename t_transision = map<pair<t_state,t_symbol>, t_states>
>
struct NFA {
    t_states states;
    t_symbols symbols;
    t_transision transision;
    t_state start_state;
    t_states accept_states;
    t_symbol epsilon;

    NFA(
            const t_states& states,
            const t_symbols& symbols,
            const t_transision& transision,
            const t_state& start_state,
            const t_states& accept_states,
            const t_symbol& epsilon
       ) : states(states),
           symbols(symbols),
           transision(transision),
           start_state(start_state),
           accept_states(accept_states),
           epsilon(epsilon) {}

    template<typename t_input = vector<t_symbol>>
    bool run(const t_input& input) {
        t_states states{ start_state };

        // epsilon 遷移
        auto epsilon_transition = [&]() {
            while (true) {
                t_states next_states{ states };
                for (const t_state& state : states) {
                    for (const t_state& nxt :
                            transision[make_pair(state, epsilon)]) {
                        next_states.insert(nxt);
                    }
                }
                if (next_states.size() == states.size()) break;
                swap(next_states, states);
            }
        };

        for (const t_symbol& symbol : input) {
            epsilon_transition();

            t_states next_states;
            for (const t_state& state : states) {
                for (const t_state& nxt :
                        transision[make_pair(state, symbol)]) {
                    next_states.insert(nxt);
                }
            }
            swap(next_states, states);
        }
        epsilon_transition();

        for (const t_state& state : states) {
            if (accept_states.find(state) != accept_states.end()) {
                return true;
            }
        }
        return false;
    }
};


void test_nfa2() {
    printf("0 or 1 偶数個 を受理するDFA のテスト\n");
    NFA<> dfa(
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

    assert(dfa.run(vector<int>{0,1,1}) == true);
    assert(dfa.run(vector<int>{1,0,0}) == true);
    assert(dfa.run(vector<int>{1,0}) == false);
    assert(dfa.run(vector<int>{0,1,0,1}) == true);
    assert(dfa.run(vector<int>{}) == true);
}


int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    test_nfa2();

    return 0;
}
