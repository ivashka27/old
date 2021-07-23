#include<bits/stdc++.h>

#define int long long

using namespace std;
 
int32_t main() {
    int t = 1; //cin >> t;
    while (t--) {
        int n, two = 0, four = 0, eight = 0, six = 0; cin >> n;
        vector<int> mx, mp(n + n);
        for (int i = 0; i < n; i++) {
            int c; cin >> c;
            mp[c]++;
        }
        /*int n; cin >> n;
        map<int, int> a;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            a[x]++;
        }
        bool kv = false, pr = false;
            int kvv = (int)1e18;
            int k = 0, p = 0;
            
            for (auto e : a) {
                if (e.second >= 4) { kv = true;
                if (e.second < kvv) kvv = e.second, k = e.first;
                                   }
            }
            int tmp = 0;
            //for (auto e : a) {
              //  cout << e.first << ": " << e.second << "\n";
            //}
            //cout << "\n";
            //cout << k << " ?\n";
            for (auto e : a) {
                if (e.first == k) {
                    if (e.second - 4 >= 4) {
                        pr = true;
                        break;
                    }
                    if (e.second - 4 >= 2) tmp++;
                }
                else { 
                    if (e.second >= 4) {
                        pr = true;
                        break;
                    }
                    if (e.second >= 2) tmp++;
                }
            }
            //cout << tmp << " !\n";
            //cout << "\n";
            
            if (!pr && tmp >= 2) pr = true;
        */    
        /*int q; cin >> q;
        while (q--) {
            char op; cin >> op;
            int x; cin >> x;
            if (op == '-') {
                a[x]--;
            }
            else a[x]++;
            
        }
        */
        
        for (auto x : mp) {
            if (x >= 2) two++;
            if (x >= 4) four++;
            if (x >= 6) six++;
            if (x >= 8) eight++;
        }
        int q; cin >> q;
        while (q--) {
            char op; cin >> op;
            int x; cin >> x;
            if (mp[x] >= 2) two--;
            if (mp[x] >= 4) four--;
            if (mp[x] >= 6) six--;
            if (mp[x] >= 8) eight--;
            if (c == '-') mp[x]--;
            else mp[x]++;
            if (mp[x] >= 2) two++;
            if (mp[x] >= 4) four++;
            if (mp[x] >= 6) six++;
            if (mp[x] >= 8) eight++;
            if (eight || (four >= 2) || (four && two >= 3) || (six && two >= 2)) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}