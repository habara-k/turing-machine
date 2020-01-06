#include "template.cpp"
#include "DFA.cpp"

template<
    typename t_state = int,
    typename t_symbol = int,
    typename t_states = set<t_state>,
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
        t_states cur_states{ start_state };

        // epsilon 遷移
        auto epsilon_transition = [&]() {
            while (true) {
                t_states next_states = cur_states;
                for (const t_state& state : cur_states) {
                    for (const t_state& nxt :
                            transision[make_pair(state, epsilon)]) {
                        next_states.insert(nxt);
                    }
                }
                if (next_states.size() == cur_states.size()) break;
                swap(next_states, cur_states);
            }
        };

        for (const t_symbol& symbol : input) {
            epsilon_transition();

            t_states next_states;
            for (const t_state& state : cur_states) {
                for (const t_state& nxt :
                        transision[make_pair(state, symbol)]) {
                    next_states.insert(nxt);
                }
            }
            swap(next_states, cur_states);
        }
        epsilon_transition();

        for (const t_state& state : cur_states) {
            if (accept_states.find(state) != accept_states.end()) {
                return true;
            }
        }
        return false;
    }

    template<typename dfa_t_state = int>
    auto convert() {
        map<t_state,dfa_t_state> state_idx;
        for (const t_state& state : states) state_idx[state] = -1;
        dfa_t_state size = 0;
        for (auto& p : state_idx) p.second = size++;

        set<dfa_t_state> dfa_states;
        for (dfa_t_state mask = 0; mask < 1<<size; ++mask) {
            dfa_states.insert(mask);
        }

        set<dfa_t_state> dfa_accept_states;
        for (dfa_t_state mask : dfa_states) {
            for (const t_state& state : states) {
                if ((mask & (1<<state_idx[state])) == 0) continue;
                if (accept_states.find(state) != accept_states.end()) {
                    dfa_accept_states.insert(mask);
                    break;
                }
            }
        }

        dfa_t_state dfa_start_state = 1<<state_idx[start_state];

        map<pair<dfa_t_state,t_symbol>,dfa_t_state> dfa_transisions;
        for (dfa_t_state mask : dfa_states) {
            for (const t_symbol& symbol : symbols) {

                t_states next_states;

                for (const t_state& state : states) {
                    if ((mask & (1<<state_idx[state])) == 0) continue;

                    for (const t_state& nxt :
                            transision[make_pair(state, epsilon)]) {
                        next_states.insert(nxt);
                    }
                    for (const t_state& nxt :
                            transision[make_pair(state, symbol)]) {
                        next_states.insert(nxt);
                    }
                }

                dfa_t_state next_mask = 0;
                for (const t_state& state : next_states) {
                    next_mask |= 1<<state_idx[state];
                }

                dfa_transisions[make_pair(mask,symbol)] = next_mask;
            }
        }

        return DFA<dfa_t_state,t_symbol>(
                dfa_states,
                symbols,
                dfa_transisions,
                dfa_start_state,
                dfa_accept_states
            );
    }
};
