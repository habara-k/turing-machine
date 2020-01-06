#include "template.cpp"

template<
    typename t_state = int,
    typename t_symbol = int,
    typename t_states = set<t_state>,
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
