#include "template.cpp"

template<typename T>
struct TapeIterator;

template<typename T>
struct Tape {
    vector<T> data;
    const T blank;

    Tape(const initializer_list<T>& data, const T& blank) :
        data(data), blank(blank) {}

    TapeIterator<T> begin() {
        return TapeIterator<T>(*this, 0);
    }
    TapeIterator<T> end() {
        return TapeIterator<T>(*this, data.size());
    }
};

template<typename T>
struct TapeIterator {
    Tape<T>& tape;
    int idx;
    TapeIterator(Tape<T>& tape, int idx) :
        tape(tape), idx(idx) {}

    const T& operator*() const {
        if (idx == tape.data.size()) {
            tape.data.push_back(tape.blank);
        }
        return tape.data[idx];
    }
    T& operator*() {
        if (idx == tape.data.size()) {
            tape.data.push_back(tape.blank);
        }
        return tape.data[idx];
    }

    TapeIterator& operator++() {
        if (++idx > tape.data.size()) {
            tape.data.push_back(tape.blank);
        }
        return *this;
    }
    TapeIterator& operator--() {
        if (--idx < 0) {
            tape.data.insert(tape.data.begin(), tape.blank);
            ++idx;
        }
        return *this;
    }
};

template<
    typename t_state = int,
    typename t_symbol = int,
    typename t_states = set<t_state>,
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

    template<typename t_input>
    bool run(t_input&& input) {
        auto iterator = input.begin();
        t_state state = start_state;

        while (transision.count({state, *iterator})) {
            t_state nxt_state;
            t_symbol nxt_symbol;
            bool direction;

            std::tie(nxt_state, nxt_symbol, direction) =
                transision.at({state, *iterator});

            state = nxt_state;
            *iterator = nxt_symbol;

            direction ? ++iterator : --iterator;
        }
        return accept_states.find(state) != accept_states.end();
    }
};
