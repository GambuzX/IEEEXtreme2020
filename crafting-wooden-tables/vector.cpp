#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
    ll C, N, P, W;
    cin >> C >> N >> P >> W;
    
    // fill the slots from left to right
    vector<ll> slots(N, 0);
    ll slot_i = 0;
    while(W > 0) {
        ll deposit = min(P, W);
        slots[slot_i++] = deposit;
        W -= deposit;
    }
    slot_i--;
    
    // build tables
    ll table_count = 0;
    ll table_i = N-1;
    while(slot_i >= 0 && table_i >= 0) {
        ll to_remove = C;
        while(to_remove > 0 && slot_i >= 0) {
            ll remove_val = min(slots[slot_i], to_remove);
            slots[slot_i] -= remove_val;
            to_remove -= remove_val;
            
            if (slots[slot_i] == 0) slot_i--;
        }
        
        if (to_remove != 0) break; // could not find materials
        if (slots[table_i] != 0) break; // no space for more tables
        
        table_count++;
        table_i--;
    }
    
    cout << table_count << endl;
    return 0;
}