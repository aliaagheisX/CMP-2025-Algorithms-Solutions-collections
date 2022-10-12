#include <bits/stdc++.h>
using namespace std;

int dx[8] = {0, 1, 0, -1};
int dy[8] = {1, 0, -1, 0};
int n;
vector<vector<int>> grid;
vector<vector<bool>> vis;
deque<int> fpath, path;
int fcnt = INT_MAX;

void rec(int i, int j,int cnt) {
    if(n == 0) return;
    
    path.push_back(grid[i][j]);
    vis[i][j] = 1;
    cnt+=grid[i][j];


    if(i == n -1 && j == n-1) {
        if(cnt < fcnt)
            fcnt = cnt,
            fpath = path;
    }
    else {
        for(int k = 0;k < 4;k++) {
            int ni = i + dx[k];
            int nj = j + dy[k];

            if(ni < n && nj < n && ni >= 0 && nj >= 0 && !vis[ni][nj]) 
                rec(ni, nj, cnt);
            
        }
    }
    
    path.pop_back();
    vis[i][j] = 0;

}


int main()
{
    
    int t= 1;
    cin >> t;
    while(t--) {
        cin >> n;

        fcnt = INT_MAX;
        grid = vector<vector<int>>(n, vector<int>(n));
        vis = vector<vector<bool>>(n, vector<bool>(n));

        for(auto &i : grid) 
            for(auto &j: i) cin >> j;
        
        rec(0, 0, 0);

        while(!fpath.empty()) 
            cout << fpath.front()<<' ', 
            fpath.pop_front();
    }

    
    return 0;
}