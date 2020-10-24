#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class CompareCoins
{
public:
  bool operator() (const pair<int, int>& lhs, const pair<int, int>&rhs) const
  {
  	return lhs.first * lhs.second < rhs.first * rhs.second;
  }
};

typedef priority_queue<pair<int, int>, vector<pair<int, int>>, CompareCoins> myPQ;

unordered_map<string, myPQ> auctionHouseCoins;


bool hasString(string name){
    return auctionHouseCoins.find(name) != auctionHouseCoins.end();
}

typedef enum {ZULIAN, SANFURY, GURUBASHI, NONE} setType;

setType hasAnySet(){
    if(hasString("Zulian") && hasString("Razzashi") && hasString("Hakkari"))
        return ZULIAN;
    if(hasString("Sanfury") && hasString("Skullsplitter") && hasString("Bloodscalp"))
        return SANFURY;
    if(hasString("Gurubashi") && hasString("Vilebranch") && hasString("Witherbark"))
        return GURUBASHI;
    return NONE;
}

class NumCards {
public:
    int zulian = 0;
    int razzashi = 0;
    int hakkari = 0;
    int sanfury = 0;
    int skullsplitter = 0;
    int bloodscalp = 0;
    int gurubashi = 0;
    int vilebranch = 0;
    int witherbark = 0;
};

pair<int, int> getPair(string name){
    auto it = auctionHouseCoins.find(name);
    pair<int, int> p = (*it).second.top();
    (*it).second.pop();
    if((*it).second.empty()){
        auctionHouseCoins.erase(it);
    }

    return p;
}

void getPrice(int n){
    int price = 0;
    NumCards nc = NumCards();

    while(n > 0){
        setType type;

        if((type = hasAnySet()) == NONE){
            cout << "impossible" << endl;
            return;
        }

        if(type == ZULIAN){
            pair<int, int> p1 = getPair("Zulian"), p2 = getPair("Razzashi"), p3 = getPair("Hakkari");
            price += p1.second + p2.second + p3.second;
            int min_val = min({p1.first, p2.first, p3.first});
            n -= min_val;
            nc.zulian = p1.first-min_val;
            nc.razzashi = p2.first-min_val;
            nc.hakkari = p3.first-min_val;
        }else if(type == SANFURY){
            pair<int, int> p1 = getPair("Sanfury"), p2 = getPair("Skullsplitter"), p3 = getPair("Bloodscalp");
            price += p1.second + p2.second + p3.second;
            int min_val = min({p1.first, p2.first, p3.first});
            n -= min_val;
            nc.sanfury = p1.first-min_val;
            nc.skullsplitter = p2.first-min_val;
            nc.bloodscalp = p3.first-min_val;
        }else if(type == GURUBASHI){
            pair<int, int> p1 = getPair("Gurubashi"), p2 = getPair("Vilebranch"), p3 = getPair("Witherbark");
            price += p1.second + p2.second + p3.second;
            int min_val = min({p1.first, p2.first, p3.first});
            n -= min_val;
            nc.gurubashi = p1.first-min_val;
            nc.vilebranch = p2.first-min_val;
            nc.witherbark = p3.first-min_val;
        }
    }
    cout << price << endl;
}

int main() {
    int n, m;
    cin >> n >> m;

    string name;
    int k, p;

    for(int i = 0; i < m; i++){
        cin >> name >> k >> p;
        auto it = auctionHouseCoins.find(name);

        if(it == auctionHouseCoins.end()){
            auto iter = auctionHouseCoins.insert(make_pair(name, myPQ()));
            (*iter.first).second.push(make_pair(k, p));
        }else{
            (*it).second.push(make_pair(k, p));
        }
    }

    getPrice(n);

    return 0;
}