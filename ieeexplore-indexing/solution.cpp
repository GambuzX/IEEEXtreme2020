#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

unordered_set<string> stop_words;
unordered_map<string, size_t> index_terms;

vector<string> getWords(string line){
    vector<string> v;
    ostringstream oss;

    for(size_t i = 0; i < line.length(); i++){
        if(line[i] == ';'){
            v.push_back(oss.str());
            oss.str("");
        }else{
            oss << line[i];
        }
    }
    
    v.push_back(oss.str());
    return v;
}

string replace_characters(string s, vector<char> v){
    ostringstream oss;
    for(size_t i = 0; i < s.length(); ++i){
        if(s[i] == ' ' || s[i] == '\n'){
            oss << (char)(' ');
        }else{
            if(isalpha(s[i])){
                oss << (char)(tolower(s[i]));
            }else{
                bool found = false;
                for(size_t j = 0; j < v.size(); ++j){
                    if(s[i] == v[j]){
                        found = true;
                        break;
                    }
                }

                if(!found) oss << (char)(s[i]);
            }
        }
    }
    return oss.str();
}

int getTagPoints(string tag){
    if(tag == "title")
        return 5; 
    if(tag == "abstract")
        return 3;
    if(tag == "body")
        return 1;
    return -1;
}

int countWord(string tmp, int count){
    if(tmp.length() < 4) return 0;

    if(stop_words.find(tmp) == stop_words.end()){
        auto it = index_terms.find(tmp);
        if(it != index_terms.end()){
            (*it).second += count;
        }

        return 1;
    }
    return 0;
}

size_t countWords(string s, int count){
    int initPos = 0;

    if(count == -1){
        initPos = s.find('<');
        if(initPos == -1) return 0;
    }

    size_t numWords = 0;
    for(size_t i = initPos; i < s.length(); i++) {
        if(s[i] == ' ' || s[i] == '\n'){
            continue;
        } else if(s[i] == '<'){
            size_t pos = s.find('>', i+1);
            string tagName = s.substr(i+1, pos-i-1); 
            string closeTag = "</" + tagName + ">";
            size_t finalPos = s.find(closeTag, pos+1);
            int points = getTagPoints(tagName);
            numWords += countWords(s.substr(pos+1, finalPos-pos-1), points == -1 ? count : points);
            i = finalPos + closeTag.length() - 1;
        } else {
            int pos = s.find(' ', i); 
            if(count != -1){
                if(pos == -1){
                    numWords += countWord(s.substr(i), count);
                    break;
                }else{
                    string tmp = s.substr(i, pos-i);
                    numWords += countWord(tmp, count);
                }
            }else if(pos == -1) break;

            i = pos;
        }
    }
    
    return numWords;
} 

class Compare {
public:
    bool operator() (pair<string, size_t> p1, pair<string, size_t> p2)
    {
        if(p1.second == p2.second) return p1.first > p2.first;

        return p1.second < p2.second;
    }
};

double keywordDensity(double S, double L){
    return S/L * 100;
}

int main() {
    string line;
    getline(cin, line);
    vector<string> v = getWords(line);
    stop_words = unordered_set<string>(v.begin(), v.end());
    
    getline(cin, line);

    v = getWords(line);
    for(string s : v)
    {
        index_terms.insert(make_pair(s, 0));
    }
    
    ostringstream oss;
    
    while(!cin.eof()){
        getline(cin, line);
        oss << replace_characters(line, {',', '.', '?', '!'});
    }
    
    string xml = oss.str();
    
    size_t L = countWords(xml, -1);

    priority_queue<pair<string, size_t>, vector<pair<string, size_t>>, Compare> pq(index_terms.begin(), index_terms.end());

    if(!pq.empty()){
        cout << pq.top().first << ": " << keywordDensity(pq.top().second, L) << endl;
        pq.pop();

        if(!pq.empty()){
            cout << pq.top().first << ": " << keywordDensity(pq.top().second, L) << endl;
            pq.pop();

            if(!pq.empty()){
                size_t num = pq.top().second;
                cout << pq.top().first << ": " << keywordDensity(num, L) << endl;
                pq.pop();

                while(!pq.empty()){
                    if(pq.top().second != num){
                        break;
                    }            
                    cout << pq.top().first << ": " << keywordDensity(num, L) << endl;
                    pq.pop();
                }
            }
        }
    }

    return 0;
}