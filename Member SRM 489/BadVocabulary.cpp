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

class BadVocabulary {
    public:
    int count(string badPrefix, string badSuffix, string badSubstring, vector<string> vocabulary) {
        int ans=0;
        for(int i=0;i<vocabulary.size();++i){
            if(badPrefix == vocabulary[i].substr(0, badPrefix.length())) {
                ++ans;
                continue;
            }
            int len = vocabulary[i].length()-badSuffix.length();
            if (len >= 0) {
                if(badSuffix == vocabulary[i].substr(vocabulary[i].length()-badSuffix.length())) {
                    ++ans;
                    continue;
                }
            }
            
            if(vocabulary[i].length()==1){
                continue;
            }
            string str = vocabulary[i].substr(1, vocabulary[i].length()-2);
            std::size_t found = str.find(badSubstring);
            if (found!=std::string::npos){
                ans++;
            }
        }
        return ans;
    }
};

// CUT begin
ifstream data("BadVocabulary.sample");

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

bool do_test(string badPrefix, string badSuffix, string badSubstring, vector<string> vocabulary, int __expected) {
    time_t startClock = clock();
    BadVocabulary *instance = new BadVocabulary();
    int __result = instance->count(badPrefix, badSuffix, badSubstring, vocabulary);
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
        string badPrefix;
        from_stream(badPrefix);
        string badSuffix;
        from_stream(badSuffix);
        string badSubstring;
        from_stream(badSubstring);
        vector<string> vocabulary;
        from_stream(vocabulary);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(badPrefix, badSuffix, badSubstring, vocabulary, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1489139227;
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
        cout << "BadVocabulary (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
