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
