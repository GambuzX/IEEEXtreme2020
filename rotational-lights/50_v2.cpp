#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

typedef unsigned long long ull;

void shift_by_n(vector<bool> &lights, ull n) {
    std::rotate(lights.begin(), lights.begin()+lights.size()-n, lights.end());
}

int main() {
    ull N, T, I;
    cin >> N >> T;
    
    ull min_lit_i = ULLONG_MAX;
    vector<bool> lights(T, false);
    for(ull i = 0; i < N; i++) {
        cin >> I;
        min_lit_i = min(min_lit_i, I);
        lights[I] = true;
    }
    
    ull permutation = 0;
    vector<bool> curr = lights;
    do {
        ull rotation_amount = 1;
        ull find_light_i = min_lit_i == 0 ? T-1 : min_lit_i-1;
        while(!curr[find_light_i]) {
            rotation_amount++;
            find_light_i = find_light_i == 0 ? T-1 : find_light_i-1;
        }
        
        shift_by_n(curr, rotation_amount);
        permutation += rotation_amount;
    } while(!std::equal(lights.begin(), lights.end(), curr.begin()));
    
    cout << permutation-1 << endl;  // do not count initial permutation
    return 0;
}