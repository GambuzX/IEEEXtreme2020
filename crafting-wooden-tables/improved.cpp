#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
    ll C, N, P, W;
    cin >> C >> N >> P >> W;
    
    ll filled_slots = W / P; // N-1 slots
    ll remaining = W % P; // last slot

    ll empty_slots = N - filled_slots - 1;
    
    // build tables
    ll table_count = 0;
    while(remaining + filled_slots*P >= C) {
        ll to_remove = C;
        while(to_remove > 0) {
            ll remove_val = min(remaining, to_remove);
            remaining -= remove_val;
            to_remove -= remove_val;
            
            if (remaining == 0) {
                remaining = P;
                filled_slots--;
                empty_slots++;
            }
        }
        
        if (empty_slots == 0) break; // no space for more tables
        
        table_count++;
        empty_slots--;
    }
    
    cout << table_count << endl;
    return 0;
}