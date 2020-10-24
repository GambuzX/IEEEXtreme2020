#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

int main() {
    int t, n;
    cin >> t;
    for(int i = 0; i < t; i++){
        cin >> n;
        float x1, x2;
        int y;
        
        float minx0 = INT_MAX, maxx0 = INT_MIN, miny0 = INT_MAX, maxy0 = INT_MIN;
        float minx1 = INT_MAX, maxx1 = INT_MIN, miny1 = INT_MAX, maxy1 = INT_MIN;
        
        for(int j = 0; j < n; j++){
            cin >> x1 >> x2 >> y;
            if (y == -1) {
                minx0 = min(minx0, x1);
                maxx0 = max(maxx0, x1);
                miny0 = min(miny0, x2);
                maxy0 = max(maxy0, x2); 
            }
            else {
                minx1 = min(minx1, x1);
                maxx1 = max(maxx1, x1);
                miny1 = min(miny1, x2);
                maxy1 = max(maxy1, x2); 
            }
        }
        
        bool intersect_horiz = max(minx0, minx1) < min(maxx0, maxx1);
        bool intersect_vert = max(miny0, miny1) < min(maxy0, maxy1);
        
        cout << (intersect_horiz && intersect_vert ? "NO" : "YES") << endl;
    }
    return 0;
}