#include <bits/stdc++.h>
using namespace std;


/* 

if you have coins (a) of size (n)

can choose subset of (a) that their sum = (t)?

 */

int n; ll t;
vector<int> a(25);


bool rec(int i, ll curr) {
    if(i == n) return(curr == t);   

    if(curr >= t) return (curr == t);

    return rec(i+1, curr+a[i]) + rec(i+1, curr);
}

void solve() {
    cin  >> t >> n;
    fi(0,n) cin >> a[i];

    cout << rec(0, 0);

}
 
int main()
{
   solve();
    return 0;
}
 
/* 
*/