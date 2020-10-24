#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

typedef unsigned long long ull;

string hash_lights(const vector<bool> &lights) {
    string s = "";
    for(bool b : lights) s += (b ? "1" : "0");
    return s;
}

void shift_by_one(vector<bool> &lights) {
    bool last = lights[lights.size()-1];
    for(ull i = lights.size()-1; i > 0; i--)
        lights[i] = lights[i-1];
    lights[0] = last;
}

int main() {
    ull N, T, I;
    cin >> N >> T;
    
    vector<bool> lights(T, false);
    for(ull i = 0; i < N; i++) {
        cin >> I;
        lights[I] = true;
    }
    
    ull total = 0;
    unordered_set<string> seen;
    for(ull mult = 0; mult < T; mult++) {
        string lhash = hash_lights(lights);
        if (seen.find(lhash) != seen.end()) break;
        total++;
        seen.insert(lhash);
        shift_by_one(lights);
    }
    
    cout << total-1 << endl;  // do not count initial permutation
    return 0;
}