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
    
    string state_hash(const vector<long>& stones, long n_stones) {
        string s = "";
        for(int i = 0; i < n_stones; i++) s += to_string(stones[i]) + "-";
        return s;
    }
    
    void min_spells_dp(long min_size) {
        min_spells = vector<long>(N+1, -1);
        min_spells[N] = 0;

        long n_stones = N;
        vector<long> stones(N, 0);
        for(int i = 1; i <= this->N; i++) stones[i-1] = i; // initial state;
        
        unordered_set<string> seen_states;
        seen_states.insert(state_hash(stones, n_stones));
        
        int n_spells = 0;
        while(n_stones >= (size_t) min_size) {
            unordered_set<long> seen_stones;
            long insert_offset = 0;

            long prev_size = n_stones;
            for(long i = 0; i < prev_size; i++) {
                long next_stone = this->spell[stones[i]-1];
                if (seen_stones.find(next_stone) != seen_stones.end()) { //purify stones
                    n_stones--;
                    insert_offset++;
                }
                else {
                    seen_stones.insert(next_stone);
                    stones[i-insert_offset] = next_stone;
                }
            }
            
            if (insert_offset == 0) { // number of stones did not change
                string s_hash = state_hash(stones, n_stones);
                if(seen_states.find(s_hash) != seen_states.end()) break;
                seen_states.insert(s_hash);
            }          
            n_spells++;
            if(min_spells[n_stones] == -1)
                min_spells[n_stones] = n_spells;
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