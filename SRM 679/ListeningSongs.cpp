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

class ListeningSongs {
    public:
        // int minimum(vector<int> a){
        //     int min=a[0];
        //     for(int i=1;i<a.size();++i){
        //         if(a[i] < min ) min =a[i];
        //     }
        //     return min;
        // }
        // int minimum_id(vector<int> a){
        //     int min=a[0],id;
        //     for(int i=1;i<a.size();++i){
        //         if(a[i] < min ) {
        //             min =a[i];
        //             id=i;
        //         }
        //     }
        //     return id;
        // }
    int listen(vector<int> durations1, vector<int> durations2, int min, int T) {

        min*=60;

        if(durations1.size()<T || durations2.size()<T) return -1;

        sort(durations1.begin(),durations1.end());
        sort(durations2.begin(),durations2.end());

        vector<int> a,b;
        for(int i=0;i<T;++i){
            a.push_back(durations1[i]);
            b.push_back(durations2[i]);
            min-=(durations1[i]+durations2[i]);
        }

        if(min < 0 ) return -1;

        int ans = 2*T;

        vector<int> durations;
        for(int i=T;i<durations1.size();++i){
            durations.push_back(durations1[i]);
        }
        for(int i=T;i<durations2.size();++i){
            durations.push_back(durations2[i]);
        }

        sort(durations.begin(),durations.end());
        for(int i=0;i<durations.size();++i){
            min-=durations[i];
            if(min >= 0) ++ans;
        }

        return ans;
    }
};

// CUT begin
ifstream data("ListeningSongs.sample");

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

bool do_test(vector<int> durations1, vector<int> durations2, int minutes, int T, int __expected) {
    time_t startClock = clock();
    ListeningSongs *instance = new ListeningSongs();
    int __result = instance->listen(durations1, durations2, minutes, T);
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
        vector<int> durations1;
        from_stream(durations1);
        vector<int> durations2;
        from_stream(durations2);
        int minutes;
        from_stream(minutes);
        int T;
        from_stream(T);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(durations1, durations2, minutes, T, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1486224161;
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
        cout << "ListeningSongs (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
