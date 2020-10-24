#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T, M, N, K, I;;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> M >> N >> K;
        
        vector<long> switches;
        for (int j = 0; j < M; j++) {
            cin >> I;
            switches.push_back(I);
        }
        sort(switches.begin(), switches.end());
        
        long total = 0;
        int j = 0;
        for(; j < K; j++) total += N - switches[j];
        for(; j < M; j++) total += switches[j];
        cout << total << endl;
    }
    return 0;
}