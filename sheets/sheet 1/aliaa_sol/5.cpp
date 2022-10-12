#include <bits/stdc++.h>
using namespace std;

// i assum the graph G 
// = is undirected graph
// = (n) nodes and (e) edges


int n, e; // n = number of nodes
          // e = number of edges

vector<vector<int>> gp;
vector<int> colors;


void rec(int i) {
    if(i == n) return;

    set<int> a; // store connected edges colors in order
    for(auto j : gp[i]) {
        a.insert(colors[j]);
    }

    //all possible colors (1 <= c <= n)
    //find the minimum color i can assign the node[i]
    for(int c = 1;c <= n;c++) {
        if(a.find(c) == a.end()) {
            colors[i] = c;
            break;
        }
    }

    rec(i+1);
}


int main()
{
    
    
    int t = 1;cin >> t;
    while(t--) {
        cin >> n >> e;
        gp = vector<vector<int>> (n);
        colors = vector<int> (n, 0);
        for(int i = 0;i < e;i++) {
            int x,y;
            cin >> x >> y;
            gp[x].push_back(y);
            gp[y].push_back(x);
        }

        rec(0);

        auto it = max_element(colors.begin(), colors.end());
        cout << (*it);
    }
    
    return 0;
}