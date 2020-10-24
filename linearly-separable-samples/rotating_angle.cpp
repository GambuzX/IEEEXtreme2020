#include <iostream>
#include <math.h>
#include <vector>

using namespace std;
#define PI 3.14159265

struct point {
  float x1, x2;
  int y;
  point(float x1, float x2, int y) {
      this->x1 = x1;
      this->x2 = x2;
      this->y = y;
  }
};

float tang(float deg) {
    return tan ( deg * PI / 180.0 );
}

int main() {
    int t, n;
    cin >> t;
    for(int i = 0; i < t; i++){
        cin >> n;
        float x1, x2;
        int y;
        vector<point> points;
        for(int j = 0; j < n; j++){
            cin >> x1 >> x2 >> y;
            points.push_back(point(x1,x2,y));
        }
        
        // assume that points with y=1 must be above line and y=-1 below
        bool separate = false;
        for (float angle = 0; angle < 360.0; angle += 0.1) {
            float slope = tang(angle);
            
            bool finished = true;
            for (point& p : points) {
                float yval = p.x1 * slope;
                if ((p.y == -1 && p.x2 > yval) || (p.y == 1 && p.x2 < yval)) {
                    finished = false;
                    break;
                }
            }
            if(finished) {
                separate = true;
                break;
            }
        }
        cout << (separate ? "YES" : "NO") << endl;
        
    }
    return 0;
}