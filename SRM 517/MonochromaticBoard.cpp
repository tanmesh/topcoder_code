#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

class MonochromaticBoard {
    public:
    int theMin(vector<string> board) {
        int R=board.size(),C=board[0].size();
        int ansR=0,ansC=0,cnt=0,ans=0;
        int no_of_black=0;
        for(int i=0;i<R;++i){
            for(int j=0;j<C;++j){   
                // ++no_of_black; 
                if('B'!=board[i][j]){
                    cnt=0;
                    break;
                }
                else{
                    ++cnt;
                }
            }
            if(cnt==C){
                ++ansR;
                cnt=0;
            }
        }
        for(int i=0;i<C;++i){
            for(int j=0;j<R;++j){    
                if('B'!=board[j][i]){
                    cnt=0;
                    break;
                }
                else{
                    ++cnt;
                }
            }
            if(cnt==R){
                ++ansC;
                cnt=0;
            }
        }
        for(int i=0;i<R;++i){
            for(int j=0;j<C;++j){    
                if('B'==board[i][j]){
                    ++no_of_black;
                }
            }
            
        }
        if(ansC*R==ansR*C && ansR*C==R*C && ansC*R==R*C){
            ans = ansR<ansC ? ansR : ansC ;
        }
        else{
            ans=ansC+ansR;
        }
        
        return ans;
    }
};

// CUT begin
ifstream data("MonochromaticBoard.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(vector<string> board, int __expected) {
    time_t startClock = clock();
    MonochromaticBoard *instance = new MonochromaticBoard();
    int __result = instance->theMin(board);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        vector<string> board;
        from_stream(board);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1477369563;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "MonochromaticBoard (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
