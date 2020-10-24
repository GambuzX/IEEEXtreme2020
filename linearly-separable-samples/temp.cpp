#include <iostream>

using namespace std;

struct point {
  float x1, x2;
  int y;
  point(float x1, float x2, int y) {
      this->x1 = x1;
      this->x2 = x2;
      this->y = y;
  }
};

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
        
        for (float angle = 0; angle < 360; angle += 0.1) {
            
        }
        
    }
    return 0;
}