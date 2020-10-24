#include <iostream>
#include <vector>

using namespace std;

struct day {
  long l, r, v;
  day(long l, long r, long v) {
      this->l = l;
      this->r = r;
      this->v = v;
  }
};

long max_soldiers(vector<long> &hideouts, const vector<day>& days) {
    long evacuated = 0;
    
    vector<long> rescue_opportunities(hideouts.size(), 0);
    for(const day& d: days) {
        for(long i = d.l; i <= d.r; i++) {
            rescue_opportunities[i]++;
        }
    }
    
    for(const day& d : days) {
        // collect all soldiers
        long candidates = 0;
        for (long i = d.l; i <= d.r; i++) {
            candidates += hideouts[i];
            hideouts[i] = 0; // reset temporarily, will be reorganized later
            rescue_opportunities[i]--;
        }
        
        // evacuate 
        long to_evacuate = min(candidates, d.v);
        evacuated += to_evacuate;
        candidates -= to_evacuate;
        
        // reorganize remaining soldiers
        long best_hideout = d.l;
        for (long i = d.l+1; i <= d.r; i++) {
            if (rescue_opportunities[i] > rescue_opportunities[best_hideout])
                best_hideout = i;
        }
        hideouts[best_hideout] = candidates;
    }
    
    return evacuated;
}

int main() {
    long N, D, Li, Ri, Vi;
    cin >> N;
    vector<long> hideouts(N);  // soldiers per hideout
    for (long i = 0; i < N; i++) {
        cin >> hideouts[i];
    }
    
    cin >> D;
    vector<day> days;
    for (long i = 0; i < D; i++) {
        cin >> Li >> Ri >> Vi;
        days.push_back(day(Li-1, Ri-1, Vi));
    }
    
    cout << max_soldiers(hideouts, days) << endl;
    return 0;
}