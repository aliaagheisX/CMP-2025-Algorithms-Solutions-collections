#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <set>
using namespace std;
using ll = long long;

/*
 
 
 
 
 

				
						ÕáæÇ Úáì ÑÓæá Çááå






*/

struct Node {
	int data;
	Node* left;
	Node* right;
	Node* parent;
	Node* neighbour;
	Node* predecessor;
	Node* successor;
	Node(int d = 0) {
		data = d;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	Node(Node* l, Node* r, Node* p, int d) {
		left = l; right = r; parent = p; data = d; neighbour = NULL; predecessor = NULL; successor = NULL;
	}
	Node(Node* l, Node* r, Node* p, Node* n, int d) {
		left = l; right = r; parent = p; data = d; neighbour = n; predecessor = NULL; successor = NULL;
	}
	void set(Node* l, Node* r, Node* p, int d) {
		left = l; right = r; parent = p; data = d; neighbour = NULL; predecessor = NULL; successor = NULL;
	}
};

//***************************QUESTION 3*****************************//

int lca_a(Node* ptr1, Node* ptr2) {
	Node* temp1 = ptr1;
	while (temp1) {
		Node* temp2 = ptr2;
		while (temp2) {
			if (temp1 == temp2) return temp1->data;
			temp2 = temp2->parent;
		}
		temp1 = temp1->parent;
	}
	return -1;
}

int lca_b(Node* ptr1, Node* ptr2) {
	unordered_map<Node*, int> mp;
	Node* temp1 = ptr1;
	Node* temp2 = ptr2;
	while (temp1) {
		mp[temp1]++;
		temp1 = temp1->parent;
	}
	while (temp2) {
		if (mp[temp2]) return temp2->data;
		temp2 = temp2->parent;
	}
	return -1;
}

int lca_c(Node* ptr1, Node* ptr2) {
	Node* temp1 = ptr1;
	Node* temp2 = ptr2;
	ll count1 = 0, count2 = 0;
	Node* temp11 = temp1;
	Node* temp22 = temp2;
	while (temp11) {
		count1++;
		temp11 = temp11->parent;
	}
	while (temp22) {
		count2++;
		temp22 = temp22->parent;
	}
	if (count1 > count2) {
		ll diff = count1 - count2;
		while (diff--) {
			temp1 = temp1->parent;
		}
	}
	if (count1 < count2) {
		ll diff = count2 - count1;
		while (diff--) {
			temp2 = temp2->parent;
		}
	}
	while (temp1 && temp2) {
		if (temp1 == temp2) return temp1->data;
		temp1 = temp1->parent;
		temp2 = temp2->parent;
	}
	return -1;
}

//***************************QUESTION 4*****************************//

int num_bst(int n) {
	if (n == 0 || n == 1) return 1;
	ll sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += num_bst(i - 1) * num_bst(n - i);
	}
	return sum;
}

//***************************QUESTION 5*****************************//

int previous = INT32_MIN;

bool check_bst(Node* sub_root) {
	if (!sub_root) return true;
	bool f1 = check_bst(sub_root->left);
	if (sub_root->data < previous) return false;
	previous = sub_root->data;
	bool f2 = check_bst(sub_root->right);
	return f1 && f2;
}

//***************************QUESTION 6*****************************//

void inclusive(Node* sub_root, int v1, int v2, vector<Node*>& nums) {
	if (!sub_root) return;
	inclusive(sub_root->left, v1, v2, nums);
	if (sub_root->data >= v1 && sub_root->data <= v2) nums.push_back(sub_root);
	inclusive(sub_root->right, v1, v2, nums);
}

//***************************QUESTION 7*****************************//

void in_order_iterative(Node* sub_root) {
	if (!sub_root) return;
	stack<Node*> st;
	Node* current = sub_root;
	while (!st.empty() || current) {
		while (current) {
			st.push(current);
			current = current->left;
		}
		current = st.top();
		st.pop();
		cout << current->data << "\t";
		current = current->right;
	}
	cout << endl;
}

//***************************QUESTION 8*****************************//

void reverse_tree(Node* sub_root) {
	if (!sub_root) return;
	reverse_tree(sub_root->left);
	reverse_tree(sub_root->right);
	swap(sub_root->left, sub_root->right);
}

//***************************QUESTION 9*****************************//

void sum_heights(Node* sub_root, ll& sum, int height) {
	if (!sub_root) return;
	(height % 2) ? sum -= sub_root->data : sum += sub_root->data;
	sum_heights(sub_root->left, sum, height + 1);
	sum_heights(sub_root->right, sum, height + 1);
}

//***************************QUESTION 10*****************************//


/*
		quick explanation

		the below algorithm calculates the number of nodes in each level by going through all nodes
		and detecting each one's level, then increments its level's count by 1. At the end the level
		with the largest count is the desired level. 
	
		The queue has a pair of two parameters : the current node and its level

		The map's first parameter is the level number while the second parameter is this level's count
*/
bool map_max_by_second(const pair<int, int>& x, const pair<int, int>& y) {
	return x.second < y.second;
}

int max_level(Node* sub_root) {
	unordered_map<int, int> mp;
	queue<pair<Node*, int>> q;
	int level = 1; // assuming the root starts at level 1
	q.push({ sub_root, level });
	while (!q.empty()) {
		pair<Node*, int> f = q.front();
		q.pop();
		mp[f.second]++;		// increment the count of the level of the current node by 1
		if (f.first->left) q.push({ f.first->left,f.second + 1 });
		if (f.first->right) q.push({ f.first->right,f.second + 1 });
	}
	return max_element(mp.begin(), mp.end(), map_max_by_second)->first;
}

//***************************QUESTION 11*****************************//

/*
		quick explanation

		the queue holds three parameters: the current node, the current node's
		level, and the path from the root uptill this current node. Whenever we
		detect that the path till our current node is on a higher level than the
		maximum's level(longer path uptill now till the maximum), we declare the
		current path as the new maximum. 

		note: using a string to store the path consumes much less memory than
		using a vector for every single node
*/

void longest_path(Node* sub_root) {
	queue<pair<Node*, pair<int, string>>> q;
	pair<int, string> maximum = { 0,"" };
	q.push({ sub_root,{1,to_string(sub_root->data)} });
	while (!q.empty()) {
		pair<Node*, pair<int, string>> f = q.front();
		q.pop();
		if (f.second.first > maximum.first) {
			maximum = { f.second.first,f.second.second };
		}
		if (f.first->left) {
			q.push({ f.first->left,{f.second.first + 1,f.second.second + " " + to_string(f.first->left->data)} });
		}
		if (f.first->right) {
			q.push({ f.first->right,{f.second.first + 1,f.second.second + " " + to_string(f.first->right->data)} });
		}
	}
	cout << maximum.first << endl << maximum.second << endl;
}

//***************************QUESTION 12*****************************//

/*

		quick explanation

		We store all left and right nodes at first to get rid of them, and store
		them in a set to avoid printing them again when printing leaf nodes.
		Then we store the non repeated leaves and print everything

*/

void perimeter(Node* sub_root) {
	set<Node*> se;
	string result = "";
	Node* temp1 = sub_root;
	Node* temp2 = sub_root;
	while (temp1) {
		if (se.find(temp1) == se.end()) {
			result += " " + to_string(temp1->data);
			se.insert(temp1);
		}
		temp1 = temp1->left;
	}
	while (temp2) {
		if (se.find(temp2) == se.end()) {
			result += " " + to_string(temp2->data);
			se.find(temp2);
		}
		temp2 = temp2->right;
	}
	queue<Node*> q;
	q.push(sub_root);
	while (!q.empty()) {
		Node* tempo = q.front();
		q.pop();
		if (!tempo->left && !tempo->right && se.find(tempo) == se.end()) {
			result += " " + to_string(tempo->data);
		}
		if (tempo->left) q.push(tempo->left);
		if (tempo->right) q.push(tempo->right);
	}
	cout << result << endl;
}

//***************************QUESTION 13*****************************//

/*

		quick explanation

		the queue holds three parameters: the current node, the current node
		with respect to the parent (its left or its right), and the current
		node's parent. The second parameter is to know which to set to null
		for the parent now, its left or its right. The rest is the usual 
		recursive post order traversal, just iteratively

*/

void delete_iterative(Node*& sub_root) {
	stack<pair<Node*, pair<char, Node*>>> s;
	s.push({ sub_root,{'R',NULL} });
	while (!s.empty()) {
		pair<Node*, pair<char, Node*>> f = s.top();
		if (!f.first->left && !f.first->right) {
			if (f.first == sub_root) {
				delete sub_root;
				sub_root = NULL;
				s.pop();
				break;
			}
			delete f.first;
			f.first = NULL;
			if (f.second.first == 'L') {
				f.second.second->left = NULL;
			}
			if (f.second.first == 'R') {
				f.second.second->right = NULL;
			}
			s.pop();
		}
		else {
			if (f.first->left) {
				s.push({ f.first->left,{'L',f.first} });
			}
			if (f.first->right) {
				s.push({ f.first->right,{'R',f.first} });
			}
		}
	}
}

//***************************QUESTION 14*****************************//

/*

		quick explanation

		The best way to approach this problem is to store all nodes in the same 
		level together in a vector and make each node's neighbour the one after
		it in the vector

		The queue holds the current node and its level, so that it pushes this
		node in this level's vector

*/

int height_tree(Node* sub_root) {
	if (!sub_root) return 0;
	int hl = 1 + height_tree(sub_root->left);
	int hr = 1 + height_tree(sub_root->right);
	return max(hl, hr);
}

void right_neighbour(Node*& sub_root) {
	if (!sub_root) return;
	ll si = height_tree(sub_root) + 1;
	vector<vector<Node*>> v(si);
	queue<pair<Node*, int>> q;
	q.push({ sub_root,1 });
	while (!q.empty()) {
		pair<Node*, int> temp = q.front();
		q.pop();
		v[temp.second].push_back(temp.first);
		if (temp.first->left) q.push({ temp.first->left,temp.second + 1 });
		if (temp.first->right) q.push({ temp.first->right,temp.second + 1 });
	}
	for (ll i = 1; i < si; i++) {
		ll si2 = v[i].size();
		for (ll j = 1; j < si2; j++) {
			v[i][j - 1]->neighbour = v[i][j];
		}
	}
}

void print_neighbours(Node* sub_root) {
	if (!sub_root) return;
	queue<Node*> q;
	q.push(sub_root);
	while (!q.empty()) {
		Node* temp = q.front();
		q.pop();
		if (temp->neighbour) cout << temp->neighbour->data << "\t";
		if (temp->left) q.push(temp->left);
		if (temp->right) q.push(temp->right);
	}
}

//***************************QUESTION 15*****************************//

string in_order_alt(Node* sub_root, string s) {
	if (!sub_root) return s;
	stack<Node*> st;
	Node* current = sub_root;
	while (!st.empty() || current) {
		while (current) {
			st.push(current);
			current = current->left;
		}
		current = st.top();
		st.pop();
		s += " " + to_string(current->data);
		current = current->right;
	}
	//cout << endl;
	return s;
}

bool same_in_order(Node* sub_root_1, Node* sub_root_2) {
	string s1 = in_order_alt(sub_root_1, "");
	string s2 = in_order_alt(sub_root_2, "");
	return s1 == s2;
}

//***************************QUESTION 16*****************************//

/*

		quick explanation

		we store all the tree nodes in their in_order form in a vector, then set
		each node's	right and left to null to break apart the original tree,
		then set the right pointer of each node to the node just after it in
		the vector

*/

void in_order_alt3(Node* sub_root, vector<Node*>& s) {
	if (!sub_root) return;
	stack<Node*> st;
	Node* current = sub_root;
	while (!st.empty() || current) {
		while (current) {
			st.push(current);
			current = current->left;
		}
		current = st.top();
		st.pop();
		s.push_back(current);
		current = current->right;
	}
}

void rightskew(Node*& sub_root) {
	if (!sub_root) return;
	vector<Node*> v;
	in_order_alt3(sub_root, v);
	sub_root = v[0];
	ll si = v.size();
	for (ll i = 1; i < si; i++) {
		v[i - 1]->right = v[i];
		v[i - 1]->left = NULL;
	}
	v[si - 1]->right = v[si - 1]->left = NULL;
}

void print_only_right(Node* sub_root) {
	if (!sub_root) return;
	cout << sub_root->data << "\t";
	print_only_right(sub_root->right);
}

//***************************QUESTION 17*****************************//

int closest_value(Node* sub_root, float value) {
	int closest = INT32_MAX;
	queue<Node*> q;
	q.push(sub_root);
	while (!q.empty()) {
		Node* f = q.front();
		q.pop();
		if (abs(f->data - value) < abs(closest - value)) closest = f->data;
		if (f->left) q.push(f->left);
		if (f->right) q.push(f->right);
	}
	return closest;
}

//***************************QUESTION 18*****************************//

/*

		quick explanation

		we store all nodes in their in_order form in a vector, then each node's
		next is the node just after it in the vector and each node's prev is the
		node just before it

*/

void make_predecessor_successor(Node*& sub_root) {
	if (!sub_root || (!sub_root->left && !sub_root->right)) return;
	vector<Node*> v;
	in_order_alt3(sub_root, v);
	ll si = v.size();
	v[0]->successor = v[1];
	for (ll i = 1; i < si - 1; i++) {
		v[i]->predecessor = v[i - 1];
		v[i]->successor = v[i + 1];
	}
	v[si - 1]->predecessor = v[si - 2];
}

void print_pre_suc(Node* sub_root) {
	if (!sub_root || (!sub_root->left && !sub_root->right)) return;
	queue<Node*> q;
	q.push(sub_root);
	while (!q.empty()) {
		Node* temp = q.front();
		q.pop();
		if (temp->predecessor) cout << temp->predecessor->data;
		cout << "\t";
		if (temp->successor) cout << temp->successor->data;
		cout << endl;
		if (temp->left) q.push(temp->left);
		if (temp->right) q.push(temp->right);
	}
}

//***************************QUESTION 19*****************************//

/*

		idea doesn't differ much from problem 11's idea

*/

void in_order_alt2(Node* sub_root, vector<int>& s) {
	if (!sub_root) return;
	stack<Node*> st;
	Node* current = sub_root;
	while (!st.empty() || current) {
		while (current) {
			st.push(current);
			current = current->left;
		}
		current = st.top();
		st.pop();
		s.push_back(current->data);
		current = current->right;
	}
}

void longest_consecutive(Node* sub_root) {
	vector<int> v;
	in_order_alt2(sub_root, v);
	ll si = v.size();
	string s = to_string(v[0]) + " ";
	pair<int, string> maximum = { 1,s };
	ll cnt = 1;
	for (ll i = 0; i < si - 1; i++) {
		if (v[i] + 1 == v[i + 1]) {
			cnt++;
			s += to_string(v[i + 1]) + " ";
			if (cnt > maximum.first) {
				maximum = { cnt,s };
			}
		}
		else {
			cnt = 1;
			s = to_string(v[i + 1]) + " ";
		}
	}
	if (cnt > maximum.first) {
		maximum = { cnt,s };
	}
	cout << maximum.second << endl;
}

//***************************QUESTION 20*****************************//

/*

		quick explanation

		we traverse in the in_order traversal throughout the three. If we find 
		two nodes not in place, we simply swap them(temp1 && temp2). If we find
		only one node not in place, that means that this node and its direct
		successor are the ones not in place, so when we find the first node not
		in place, we always store the one right after it just in case we don't
		find another one. In this case we swap temp1 && temp3(also called current
		in the recursive function).

*/

void check_bst_2(Node* sub_root, Node*& temp1, Node*& temp2, Node*& current, Node*& previous) {
	if (!sub_root) return;
	check_bst_2(sub_root->left, temp1, temp2, current, previous);
	if (sub_root->data < previous->data) {
		if (!temp1) {
			temp1 = previous;
			current = sub_root;
		}
		else temp2 = sub_root;
	}
	previous = sub_root;
	check_bst_2(sub_root->right, temp1, temp2, current, previous);
}

void fix_swap(Node* sub_root) {
	if (!sub_root) return;
	Node* temp1 = NULL;
	Node* temp2 = NULL;
	Node* temp3 = NULL;
	Node* previous = new Node(INT32_MIN);
	Node* dummy = previous;
	check_bst_2(sub_root, temp1, temp2, temp3, previous);
	delete dummy;
	if (!temp2) swap(temp1->data, temp3->data); //true if only one node found not in place
	else swap(temp1->data, temp2->data); //the common case of finding two nodes
}

//***************************QUESTION 21*****************************//

/*

		quick explanation

		we form the tree using the pre order vector and after it check for the 
		number of children of each node, then store it along with its case(either
		true or false) only of it's not a leaf node.

*/

Node* insert(Node* sub_root, Node* newnode) {
	if (!sub_root) return newnode;
	if (sub_root->data > newnode->data) sub_root->left = insert(sub_root->left, newnode);
	if (sub_root->data < newnode->data) sub_root->right = insert(sub_root->right, newnode);
	return sub_root;
}

void has_two_children(vector<Node*>& v, vector<pair<Node*, bool>>& booleans) {
	ll si = v.size();
	if (!si) return;
	Node* root = v[0];
	for (ll i = 0; i < si; i++) {
		root = insert(root, v[i]);
	}
	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node* front = q.front();
		q.pop();
		if (!front->left && front->right || front->left && !front->right) {
			booleans.push_back({ front,0 });
		}
		if (front->left && front->right) {
			booleans.push_back({ front,1 });
		}
		if (front->left) q.push(front->left);
		if (front->right) q.push(front->right);
	}
}

void print_non_leaf_vector(vector<pair<Node*, bool>>& booleans) {
	for (auto &i : booleans) {
		cout << "Node number " << i.first->data << " -> " << i.second << endl;
	}
}

//***************************QUESTION 22*****************************//

/*

		quick explanation

		we store all tree nodes in a vector, then declare the passed new node
		as a root and insert all nodes in the vector one by one with respect
		to this new root (of course except for the node itself, we aren't
		inserting it again).

*/

void new_root(Node* sub_root, Node* newroot) {
	if (!sub_root || !newroot) return;
	vector<Node*> v;
	in_order_alt3(sub_root, v);
	ll si = v.size();
	newroot->left = NULL;
	newroot->right = NULL;
	for (ll i = 0; i < si; i++) {
		if (v[i] != newroot) {
			v[i]->left = NULL;
			v[i]->right = NULL;
			newroot = insert(newroot, v[i]);
		}
	}
}

//***************************QUESTION 23*****************************//

/*

		the queue's second parameter indicates if we have already passed by
		node b in the current path or not. If we reach node c and we didn't see
		b on the way then that's a false, but if we do see it we return a true.
		Also, not seeing c in any way in any path counts as a false.

*/

bool path_presence(Node* a, Node* b, Node* c) {
	if (!a || !b || !c) return 0;
	//assuming c cannot be an ancestor of a
	queue<pair<Node*, bool>> q;
	q.push({ a,0 });
	while (!q.empty()) {
		pair<Node*, bool> front = q.front();
		q.pop();
		bool flag = true;
		if (!front.second) flag = false;
		if (front.first == b) flag = true;
		if (front.first == c) {
			if (front.second) return true;
			return false;
		}
		if (front.first->left) q.push({ front.first->left,flag });
		if (front.first->right) q.push({ front.first->right,flag });
	}
	return false;
}

//***************************QUESTION 24*****************************//

/*

		quick explanation

		this solution assumes that if for example we have a node A, and a node B,
		and to reach B from A we take its left child then right child, then A and
		B are on the same column

		a map stores for each column number a vector storing the nodes from top
		to bottom. We assume the root's column is any big number because we don't
		know how deep we go to the left, so to stay on the safe side we take for
		example 5000 as the root's column to avoid reaching a negative column 
		number deep on the left

		using the map would automatically sort according to the column number,
		which is what's needed in the question.

		going left means decreasing column number by one
		going right means increasing column number by one

*/

void node_columns(Node* sub_root) {
	map<int, vector<Node*>> mp;
	queue<pair<Node*, int>> q;
	q.push({ sub_root,5000 });
	while (!q.empty()) {
		pair<Node*, int> front = q.front();
		q.pop();
		mp[front.second].push_back(front.first);
		if (front.first->left) q.push({ front.first->left,front.second - 1 });
		if (front.first->right) q.push({ front.first->right,front.second + 1 });
	}
	for (auto& i : mp) {
		for (auto& j : i.second) {
			cout << j->data << "\t";
		}
	}
	cout << endl;
}

int main() {


	/*
							5
						  /   \						
						3		7
					   / \       \
					  2   4       11
					 /           /  \
					1			10	 13
							   /      \
							  9	       16
							          /
							        15
	*/

	Node* p5 = new Node(5);
	Node* p4 = new Node(4);
	Node* p2 = new Node(2);
	Node* p3 = new Node(3);
	Node* p1 = new Node(1);
	Node* p7 = new Node(7);
	Node* p11 = new Node(11);
	Node* p10 = new Node(10);
	Node* p9 = new Node(9);
	Node* p13 = new Node(13);
	Node* p16 = new Node(16);
	Node* p15 = new Node(15);


	p5->set(p3, p7, NULL, 5);
	p3->set(p2, p4, p5, 3);
	p2->set(p1, NULL, p3, 2);
	p1->set(NULL, NULL, p2, 1);
	p4->set(NULL, NULL, p3, 4);
	p7->set(NULL, p11, p5, 7);
	p11->set(p10, p13, p7, 11);
	p10->set(p9, NULL, p11, 10);
	p9->set(NULL, NULL, p10, 9);
	p13->set(NULL, p16, p11, 13);
	p16->set(p15, NULL, p13, 16);
	p15->set(NULL, NULL, p16, 15);

	//***************************QUESTION 3*****************************//
	//cout << lca_a(p10, p15) << endl;
	//cout << lca_b(p10, p15) << endl;
	//cout << lca_c(p10, p15) << endl;
	
	//***************************QUESTION 4*****************************//
	//cout << num_bst(2) << endl;
	
	//***************************QUESTION 5*****************************//
	//cout << check_bst(p5) << endl;

	//***************************QUESTION 6*****************************//
	/*vector<Node*> nums;
	inclusive(p5, 2, 10, nums);
	for (auto i : nums) cout << i->data << "\t";*/

	//***************************QUESTION 7*****************************//
	//in_order_iterative(p5);

	//***************************QUESTION 8*****************************//
	/*reverse_tree(p5);
	in_order_iterative(p5);*/

	//***************************QUESTION 9*****************************//
	/*ll sum = 0;
	sum_heights(p5, sum, 0);
	cout << sum << endl;*/

	//***************************QUESTION 10*****************************//
	//cout << max_level(p5) << endl;

	//***************************QUESTION 11*****************************//
	//longest_path(p5);

	//***************************QUESTION 12*****************************//
	//perimeter(p5);

	//***************************QUESTION 13*****************************//
	/*in_order_iterative(p5);
	delete_iterative(p5);
	in_order_iterative(p5);*/

	//***************************QUESTION 14*****************************//
	/*print_neighbours(p5);
	right_neighbour(p5);
	print_neighbours(p5);*/

	//***************************QUESTION 15*****************************//
	//cout << same_in_order(p5, p5) << endl;

	//***************************QUESTION 16*****************************//
	/*in_order_iterative(p5);
	rightskew(p5);
	print_only_right(p5);*/

	//***************************QUESTION 17*****************************//
	//cout << closest_value(p5, 14);

	//***************************QUESTION 18*****************************//
	/*print_pre_suc(p5);
	make_predecessor_successor(p5);
	print_pre_suc(p5);*/

	//***************************QUESTION 19*****************************//
	//longest_consecutive(p5);

	//***************************QUESTION 20*****************************//
	/*in_order_iterative(p5);
	fix_swap(p5);
	in_order_iterative(p5);*/

	//***************************QUESTION 21*****************************//
	//comment out the set functions of the nodes above in the main for this next problem
	/*
					5
				  /   \
				3      11
				 \    /  \
				  4  10   16
				    /
				   7
	*/
	/*vector<Node*> v;
	vector<pair<Node*, bool>> booleans;
	v.push_back(p5);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p11);
	v.push_back(p10);
	v.push_back(p7);
	v.push_back(p16);
	has_two_children(v, booleans);
	print_non_leaf_vector(booleans);*/

	//***************************QUESTION 22*****************************//
	/*in_order_iterative(p5);
	new_root(p5, p11);
	in_order_iterative(p11);*/

	//***************************QUESTION 23*****************************//
	//cout << path_presence(p5, p13, p15) << endl;
	
	//***************************QUESTION 24*****************************//
	//node_columns(p5);
	return 0;
}