#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;

int rec(int curr, int prev) {
    if(curr == n) return 0;

    int ch1 = rec(curr+1, prev);
    int ch2 = 0;

    if(a[prev] <= a[curr]){
        ch2 = 1 + rec(curr+1, curr);
    }

    return max(ch1, ch2);
    
}
int main()
{


    cin >> n;
    a = vector<int> (n);
    for(auto &i : a) cin >> i;

    cout << rec(0,0) <<'\n';
    

    
    return 0;
}