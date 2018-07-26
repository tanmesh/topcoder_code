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
#include <queue>

using namespace std;

int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};

class CollectingRiders {
    public:
    int minimalMoves(vector<string> board) {
        int n = board.size();
        int m = board[0].size();
        int d[10][10];
        int moves = -1;
        for(int sx=0; sx<n; ++sx) {
            for(int sy=0; sy<m; ++sy) {
                queue<int> q;
                fill(d[0], d[10], 10000);
                d[sx][sy] = 0;
                q.push(sx); q.push(sy);
                while(!q.empty()){
                    int x = q.front(); q.pop();
                    int y = q.front(); q.pop();
                    int mm = d[x][y] + 1;
                    for(int i=0; i<8; ++i) {
                        int x1 = x + dx[i], y1 = y + dy[i];
                        if(x1 >= 0 && x1 < n && y1 >= 0 && y1 < m && d[x1][y1] == 10000) {
                            q.push(x1); q.push(y1);
                            d[x1][y1] = mm;
                        }
                    }
                }
                int s = 0;
                for(int x=0; x<n; ++x) {
                    for(int y=0; y<m; ++y) {
                        if(board[x][y] != '.') {
                            if(d[x][y] == 10000) {
                                s = -10000000;
                            }
                            else{
                                int k =board[x][y]- '0';
                                s += d[x][y] == 0 ? 0 : (d[x][y]+k-1)/k;
                            }
                        }
                    }
                }
                if(s >= 0 && (moves < 0 || s < moves)) {
                    moves = s;
                }
            }
        }
        return moves;
    }
};

// CUT begin
ifstream data("/Users/tanmesh/dev/topcoder_code/SRM 382/CollectingRiders.sample");

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
    CollectingRiders *instance = new CollectingRiders();
    int __result = instance->minimalMoves(board);
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
        int T = time(NULL) - 1532581948;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "CollectingRiders (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
