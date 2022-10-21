#include <bits/stdc++.h>
using namespace std;
int di[] = {0, 0, 1, -1};
int dj[] = {1, -1, 0, 0};
int n, m;
vector<vector<bool>> mat(10, vector<bool>(10));
class solution
{
    bool flag = 0;
    void recAns(set<int> vis, int i = 0)
    {
        if (vis.find(i) == vis.end())
        {
            vis.insert(i);
            for (int j = 0; j < n; j++)
                if (mat[i][j] && vis.find(j) == vis.end())
                    recAns(vis, j);
        }
        if (vis.size() == n && (mat[i][0] == 1 || i == 0))
            flag = 1;
    }

public:
    solution()
    {
        cin >> n >> m;
        for (int i = 0; i < m; i++)
        {
            int x, y;
            cin >> x >> y;
            mat[x][y] = 1;
            mat[y][x] = 1;
        }
        set<int> vis;
        recAns(vis);
        if (flag)
            cout << 1;
        else
            cout << 0;
    }
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    solution *x = new solution();
    delete x;
    return 0;
}