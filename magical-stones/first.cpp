#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct Stone {
    long state;
};

class Solution {
private:
    long N;
    vector<long> spell;
public:
    Solution(long N) {
        this->N = N;
        this->spell = vector<long>(N, -1);
    }
    
    string state_hash(const unordered_set<long>& stones) {
        string s = "";
        for(long l : stones) s += to_string(l) + "-";
        return s;
    }
    
    // TODO use dp
    long min_spells(long K) {
        unordered_set<long> stones;
        for(int i = 1; i <= this->N; i++) stones.insert(i); // initial state;
        
        unordered_set<string> seen_states;
        seen_states.insert(state_hash(stones));
        
        int n_spells = 0;
        while(stones.size() > (size_t) K) {
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
        }
        return stones.size() == (size_t) K ? n_spells : -1;
    }
    
    vector<long> &spellRef() { return spell; }
};

int main() {
    long N, Q, K;
    cin >> N;
    Solution sol(N);
    vector<long> &spell = sol.spellRef();
    for (long i = 0; i < N; i++) {
        cin >> spell[i];
    }
    
    cin >> Q;
    for(long i = 0; i < Q; i++) {
        cin >> K;
        cout << sol.min_spells(K) << endl;
    }
    
    return 0;
}