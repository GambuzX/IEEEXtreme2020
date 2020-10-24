#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <climits>

using namespace std;

class Solution {
public:
    long N;
    vector<long> spell;
    vector<long> min_spells;

    Solution(long N) {
        this->N = N;
        this->spell = vector<long>(N, -1);
    }
    
    string state_hash(const unordered_set<long>& stones) {
        string s = "";
        for(long l : stones) s += to_string(l) + "-";
        return s;
    }
    
    void min_spells_dp(long min_size) {
        min_spells = vector<long>(N+1, -1);

        unordered_set<long> stones;
        for(int i = 1; i <= this->N; i++) stones.insert(i); // initial state;
        
        unordered_set<string> seen_states;
        seen_states.insert(state_hash(stones));
        
        int n_spells = 0;
        min_spells[stones.size()] = n_spells;
        while(stones.size() >= (size_t) min_size) {
            unordered_set<long> newStones;
            for(long s : stones) {
                newStones.insert(this->spell[s-1]); // state is 1-indexed
            }
            
            if (newStones.size() == stones.size()) {
                string s_hash = state_hash(newStones);
                if(seen_states.find(s_hash) != seen_states.end()) break;
                seen_states.insert(s_hash);
            }
            stones = newStones;            
            n_spells++;
            if(min_spells[stones.size()] == -1)
                min_spells[stones.size()] = n_spells;
        }
    }

};

int main() {
    long N, Q;
    cin >> N;
    Solution sol(N);
    for (long i = 0; i < N; i++) {
        cin >> sol.spell[i];
    }
    
    cin >> Q;
    vector<long> queries(Q, -1);
    long min_query = LONG_MAX;
    for(long i = 0; i < Q; i++) {
        cin >> queries[i];
        min_query = min(min_query, queries[i]);
    }

    sol.min_spells_dp(min_query);
    for(long q : queries) 
        cout << (q > N ? -1 : sol.min_spells[q]) << endl;
    
    return 0;
}