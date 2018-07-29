#include <cstdio>
#include <cmath>
#include <ctime>
#include <iostream>
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <queue>

using namespace std;

class SortingGame {
public:
    int fewestMoves(vector<int> board, int k) {
        map< vector <int> , int > dist;
        dist[board] = 0;

        queue< vector<int> > Q;
        Q.push(board);

        int i, N = board.size();

        while (!Q.empty()) {
            vector<int> u = Q.front();
            Q.pop();
            int d = dist[u];

            for (i = 1; i < N; i++) {
                if (u[i - 1] > u[i]) {
                    break;
                }
            }
            if (i == N) return d;

            for (i = 0; i + k <= N; i++) {
                vector<int> w = u;
                reverse(w.begin() + i, w.begin() + i + k);
                if (dist.count(w) == 0) {
                    dist[w] = d + 1;
                    Q.push(w);
                }
            }
        }
        return -1;
    }
};

// CUT begin
ifstream data("/Users/tanmesh/dev/topcoder_code/SRM 397/SortingGame.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template<typename T>
void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template<typename T>
void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template<typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(vector<int> board, int k, int __expected) {
    time_t startClock = clock();
    SortingGame *instance = new SortingGame();
    int __result = instance->fewestMoves(board, k);
    double elapsed = (double) (clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    } else {
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
        vector<int> board;
        from_stream(board);
        int k;
        from_stream(k);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if (do_test(board, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1532860491;
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
        if (string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "SortingGame (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
