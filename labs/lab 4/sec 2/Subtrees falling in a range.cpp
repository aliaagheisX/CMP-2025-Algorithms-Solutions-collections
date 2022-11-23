#include <bits/stdc++.h>
using namespace std;
int di[] = {0, 0, 1, -1};
int dj[] = {1, -1, 0, 0};
struct node
{
    int value;
    node *left, *right;
};
node *createNode(int value)
{
    node *x = new node;
    x->value = value;
    x->left = nullptr;
    x->right = nullptr;
    return x;
}
class Solution
{
    int v1, v2;
    void valid(node *root, bool &res)
    {
        if (!root)
            return;
        else if (root->value > v2 || root->value < v1)
            res = 0;
        else
        {
            valid(root->left, res);
            valid(root->right, res);
        }
    }

public:
    Solution()
    {
        int e;
        int rootVal;
        cin >> v1 >> v2;
        cin >> rootVal;
        cin >> e;
        unordered_map<int, node *> nodes;
        node *root = createNode(rootVal);
        nodes[rootVal] = root;

        for (int i = 0; i < e; i++)
        {
            char dir;
            int parent;
            int child;
            cin >> dir >> parent >> child;
            node *c = createNode(child);
            nodes[child] = c;
            if (dir == 'L')
                nodes[parent]->left = c;
            else
                nodes[parent]->right = c;
        }
        int res = 0;
        for (auto i : nodes)
        {
            bool x = 1;
            valid(i.second, x);
            if (x)
                res++;
        }
        cout << res;
    }
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solution *x = new Solution();
    delete x;
    return 0;
}