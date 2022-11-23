#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int value;
    Node *left, *right;
};
class BST
{
    // private methods and attributes

    Node *root;

    void destroyTree(Node *root)
    {
        if (root)
        {
            destroyTree(root->left);
            destroyTree(root->right);
            root->left = nullptr;
            root->right = nullptr;
            delete root;
        }
    }

    Node *createNode(int x)
    {
        Node *node = new Node();
        node->value = x;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }

    Node *insert(Node *&root, int x)
    {
        if (root == nullptr)
        {
            Node *node = createNode(x);
            root = node;
        }
        else if (root->value >= x)
        {
            root->left = insert(root->left, x);
        }
        else if (root->value < x)
        {
            root->right = insert(root->right, x);
        }
        return root;
    }

    Node *remove(Node *&root, int x)
    {
        if (root == nullptr)
            return nullptr; // corner case empty tree
        else if (root->value < x)
            root->right = remove(root->right, x);
        else if (root->value > x)
            root->left = remove(root->left, x);
        else
        {
            // NO CHILD
            if (root->left == nullptr && root->right == nullptr) // leaf
            {
                delete root;
                root = nullptr;
            }
            // ONE CHILD
            else if (root->left == nullptr)
            {
                Node *temp = root;
                root = root->right;
                delete temp;
            }
            else if (root->right == nullptr)
            {
                Node *temp = root;
                root = root->left;
                delete temp;
            }
            // TWO CHILDREN
            else
            {
                Node *temp = root->left;
                while (temp->right != nullptr)
                    temp = temp->right;
                root->value = temp->value;
                remove(root->left, temp->value);
            }
        }
        return root; // to reset the parent's pointer
    }
    Node *search(Node *root, int x)
    {
        if (root == nullptr)
            return nullptr;
        else if (root->value == x)
            return root;
        else
        {
            Node *res;
            switch (root->value >= x)
            {
            case 1:
                res = search(root->left, x);
                break;
            case 0:
                res = search(root->right, x);
                break;
            };
            return res;
        }
    }
    void deleteLeaves(Node *&ptr)
    {
        if (!ptr)
            return;
        if (!ptr->left && !ptr->right)
        {
            delete ptr;
            ptr = nullptr;
            return;
        }
        Node *left = ptr->left;
        Node *right = ptr->right;
        deleteLeaves(left);
        deleteLeaves(right);
        ptr->left = left;
        ptr->right = right;
    }
    void printPaths(Node *ptr, vector<int> list = {})
    {
        if (!ptr)
            return;
        list.push_back(ptr->value);
        if (!ptr->left && !ptr->right)
        {
            for (int i = 0; i < list.size(); i++)
            {
                cout << list[i] << " ";
            }
            cout << endl;
            return;
        }
        printPaths(ptr->left, list);
        printPaths(ptr->right, list);
    }
    int height(Node *ptr)
    {
        if (!ptr)
            return 0;
        return 1 + max(height(ptr->left), height(ptr->right));
    }
    bool isBalanced(Node *ptr)
    {
        if (!ptr)
            return true;
        return !(abs(height(ptr->left) - height(ptr->right)) > 1);
    }

public:
    BST()
    {
        this->root = nullptr;
    }
    ~BST()
    {
        destroyTree(root);
    }
    void insert(int x)
    {
        insert(this->root, x);
    }
    void remove(int x)
    {
        remove(this->root, x);
    }
    Node *getRoot()
    {
        return root;
    }
    Node *search(int x)
    {
        return search(this->root, x);
    }
    int reLessThan(Node *ptr, int data)
    {
        if (!ptr)
            return 0;
        if (ptr->value < data)
        {
            return 1 + reLessThan(ptr->left, data) + reLessThan(ptr->right, data);
        }
        else
            return reLessThan(ptr->left, data) + reLessThan(ptr->right, data);
    }
    int countNodes(Node *ptr)
    {
        if (!ptr)
            return 0;
        else
            return 1 + countNodes(ptr->left) + countNodes(ptr->right);
    }
    int sumOfTree(Node *ptr)
    {
        if (!ptr)
            return 0;
        else
            return ptr->value + sumOfTree(ptr->left) + sumOfTree(ptr->right);
    }
    int noOfLeaves(Node *ptr)
    {
        if (!ptr)
            return 0;
        if (!ptr->left && !ptr->right)
            return 1;
        else
            return noOfLeaves(ptr->left) + noOfLeaves(ptr->right);
    }

    int noOfLeavesOfEvenValues(Node *ptr)
    {
        if (!ptr)
            return 0;
        if (!ptr->left && !ptr->right)
        {
            if (ptr->value % 2 == 0)
                return 1;
            else
                return 0;
        }
        else
            return noOfLeavesOfEvenValues(ptr->left) + noOfLeavesOfEvenValues(ptr->right);
    }
    // int max()
    // {
    //   if (!this->root)
    //   {
    //     return -1;
    //   }
    //   Node *tra = this->root;
    //   while (tra->right != nullptr)
    //   {
    //     tra = tra->right;
    //   }
    //   return tra->value;
    // }
    void printLessThan(Node *ptr, int data)
    {
        if (!ptr)
        {
            return;
        }
        else if (ptr->value < data)
        {
            cout << ptr->value << ' ';
        }
        printLessThan(ptr->left, data);
        printLessThan(ptr->right, data);
    }
    bool allNodesEqualTo(int x)
    {
        int sum = 0;
        queue<Node *> q;
        q.push(this->root);
        while (!q.empty())
        {
            Node *x = q.front();
            q.pop();
            if (x->left)
                q.push(x->left);
            if (x->right)
                q.push(x->right);
            sum += x->value;
        }
        return sum == x;
    }
    void reverse(Node *ptr)
    {
        if (ptr)
        {
            Node *left = ptr->left;
            Node *right = ptr->right;
            ptr->left = right;
            ptr->right = left;
            reverse(ptr->left);
            reverse(ptr->right);
        }
    }
    static bool isMirror(Node *aT, Node *bT)
    {
        if (!aT && !bT)
            return true;
        if (!aT || !bT || aT->value != bT->value)
            return false;
        return isMirror(aT->left, bT->right) && isMirror(aT->right, bT->left);
    }
    void BFS()
    {
        if (!root)
            return;
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *x = q.front();
            q.pop();
            if (x->left)
                q.push(x->left);
            if (x->right)
                q.push(x->right);
            cout << x->value << " ";
        }
    }
    void deleteLeaves()
    {
        deleteLeaves(root);
    }
    void printPaths()
    {
        printPaths(this->root);
    }
    int height()
    {
        return height(root);
    }
    bool isBalanced()
    {
        return isBalanced(root);
    }
};
int main()
{
    BST *a = new BST;
    int n;
    cin >> n;
    vector<int> num(n);
    for (auto &i : num)
        cin >> i;
    if (is_sorted(num.begin(), num.end()) || is_sorted(num.rbegin(), num.rend()))
    {
        for (int i : num)
            cout << i << " ";
    }
    else
    {
        for (int x : num)
            a->insert(x);
        a->BFS();
    }
    delete a;

    return 0;
}