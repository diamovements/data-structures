#include <iostream>
#include <vector>
#include <unordered_map>
#include<algorithm>
#include<string>
#include <fstream>
#include <valarray>

using namespace std;
struct Node
{
	char ch;
	int freq;
	Node* l, * r;
};

int findMed(vector<Node*> node) {
	double sum = 0;
	for (auto i : node) {
		sum += i->freq;
	}
	if (node.size() > 2) {
		double temp = 0;
		int j = 0;
		for (auto& i : node) {
			j++;
			temp += i->freq;
			if (temp >= sum / 2) return j;
		}
	}
	else if (node.size() == 2)return -1;
	else if (node.size() == 1)return -2;
	else if (node.size() == 0)return 0;
	return -3;
}
void div_two(vector<Node*> dict, Node* root) {
	int l = findMed(dict);
	int r = dict.size() - l;
	vector<Node*> left;
	vector<Node*> right;
	if (l == 1) {
		root->l = dict[0];
		for (int i = l; i < dict.size(); ++i) {
			right.push_back(dict[i]);
		}
		Node* t2 = new Node();
		root->r = t2;
		div_two(right, t2);
	}
	else if (l == -2) root->l = dict[0];
	else if (l == 0) return;
	else if (l == -1) {
		root->l = dict[0];
		root->r = dict[1];
	}
	else {
		for (int i = 0; i < l; ++i) {
			left.push_back(dict[i]);
		}
		Node* t = new Node();
		root->l = t;
		div_two(left, t);
		for (int i = l; i < dict.size(); ++i) {
			right.push_back(dict[i]);
		}
		Node* t2 = new Node();
		root->r = t2;
		div_two(right, t2);
	}
}
void decode(Node* root, int& index, string str)
{
	if (root == nullptr) {
		return;
	}
	if (!root->l && !root->r)
	{
		cout << root->ch;
		return;
	}
	index++;
	if (str[index] == '0')
		decode(root->l, index, str);
	else
		decode(root->r, index, str);
}

void encode(Node* root, string str,
	unordered_map<char, string>& ShannonCode)
{
	if (root == nullptr)
		return;
	if (!root->l && !root->r) {
		ShannonCode[root->ch] = str;
	}
	encode(root->l, str + "0", ShannonCode);
	encode(root->r, str + "1", ShannonCode);
}
void ShennonFano(string a) {
	vector<pair<char, int>> dict;
	for (int i = 0; i < a.length(); i++) {
		char temp = a[i];
		int f = 0;
		for (pair<char, int>& j : dict) {
			if (j.first == temp) {
				j.second += 1;
				f++;
				break;
			}
		}
		if (f == 0) {
			dict.push_back(make_pair(temp, 1));
		}
	}
	sort(dict.begin(), dict.end(), [](const auto& x, const auto& y) { return x.second > y.second; });
	cout << "Dictionary: " << endl;
	for (pair<char, int>& j : dict) {
		cout << j.first << " " << j.second << " " << endl;
	}
	cout << endl;
	vector<Node*> nodes;
	for (int i = 0; i < dict.size(); ++i) {
		Node* temp = new Node();
		temp->ch = dict[i].first;
		temp->freq = dict[i].second;
		nodes.push_back(temp);
	}
	Node* root = new Node();
	div_two(nodes, root);
	unordered_map<char, string> fanoCode;
	root->l;
	encode(root, "", fanoCode);
	double average_len = 0;
	int fano_koef = 0;
	cout << "Fano codes:" << '\n';
	for (auto pair : fanoCode) {
		cout << pair.first << " " << pair.second << endl;;
		for (int i = 0; i < dict.size(); ++i) {
			if (dict[i].first == pair.first) {
				average_len += pair.second.length() * (dict[i].second);
				fano_koef += pair.second.length() * dict[i].second;
				break;
			}
		}
	}
	cout << endl;
	double dispers = 0;
	for (auto pair : fanoCode) {
		for (int i = 0; i < dict.size(); ++i) {
			if (dict[i].first == pair.first) {
				dispers +=(dict[i].second) * pow((pair.second.length() / average_len), 2);
				break;
			}
		}
	}
	string str = "";
	for (char ch : a) {
		str += fanoCode[ch];
	}
	cout << "Encoded string:" << endl << str << endl;
	int index = -1;
	cout << "Decoded string: " << endl;
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
	cout << endl << "ASCII bit: " << 8 * a.length() << endl;
	cout << "Fano bit: " << fano_koef << endl;
	cout << "Coefficient of zipping: " << (double)(8 * a.length()) / (double)fano_koef << endl;
	cout << "Average lenght: " << (double)average_len / (double)a.length() << endl;
	cout << "Dispersion: " << dispers;
}

int main() {
	system("chcp 65001");
	string line;
	string s = "";
	ifstream in("TextFile2.txt");
	if (in.is_open())
	{
		while (getline(in, line))
		{
			s = s + line;
		}
	}
	in.close();

	ShennonFano(s);

}

