#include <iostream>
#include<string>
#include <unordered_map>
#include<vector>
#include <fstream>
#include <valarray>

using namespace std;

unordered_map<char, int> symbol_frequency;
unordered_map<char, string> symbol_codes;


struct Node {
	vector<char> symbols;
	int counter;
	string code;
	Node* left;
	Node* right;

};

vector<Node*> nodes;
Node* root;

void fill_map(string s) {
	for (int i = 0; i < s.length(); i++) {
		if (!symbol_frequency.count(s[i]))
			symbol_frequency[s[i]] = 1;
		else symbol_frequency[s[i]]+= 1;

	}
	unordered_map<char, int>::iterator it = symbol_frequency.begin();
	for (int i = 0; it != symbol_frequency.end(); it++, i++) {
		Node* node = new Node;
		node->symbols.push_back(it->first);// add symbol
		node->counter = it->second; // add meeting
		cout << it->first << " " << it->second<<endl;
		node->code = "";
        //children
		node->left = nullptr;
		node->right = nullptr;
		nodes.push_back(node);
	}
}

void node_bubble_sorting() {
	for (int i = 0; i <nodes.size(); i++) {
        for (int j = 0; j < nodes.size() - i - 1; j++) {
            if (nodes[j + 1]->counter > nodes[j]->counter) {
                swap(nodes[j], nodes[j + 1]);
            }
        }
    }
}

void build_tree() {
    // add all nodes excluding root
	while (nodes.size() != 1) {
		vector<Node*> newNodes;
		bool flag = false;
		for (int i = nodes.size() - 2; i > -1; i -= 2) {
            //merging neighbour nodes
			Node* node = new Node;
			for (int j = 0; j < nodes[i]->symbols.size(); j++) {
				node->symbols.push_back(nodes[i]->symbols[j]);
			}
			for (int j = 0; j < nodes[i + 1]->symbols.size(); j++) {
				node->symbols.push_back(nodes[i+1]->symbols[j]);
			}
            // give values to nodes
            node->counter = nodes[i + 1]->counter + nodes[i]->counter;
            node->code = "";
            node->left = nodes[i];
            node->right = nodes[i + 1];
            newNodes.push_back(node);
            if (i == 1) {
                flag = true;
            }
        }
        if (flag) {
            newNodes.push_back(nodes[0]);
        }
        nodes = newNodes;
        node_bubble_sorting();
    }
    root = nodes[0]; //new root
}


void huffman_encode(Node* root) {
    if (root->left == nullptr) {
        symbol_codes[root->symbols[0]] = root->code;
        return;
    }
    root->left->code = root->code + '0';
    root->right->code = root->code + '1';
    huffman_encode(root->left);
    huffman_encode(root->right);
}
//decoding symbols
void decode(Node* root, int& index, string str) {
    if (root == nullptr) {
        return;
    }
    //trying to find value of node
    if (!root->left && !root->right) {
        cout << root->symbols[0];
        return;
    }
    index++;
    if (str[index] == '0')
        decode(root->left, index, str);
    else
        decode(root->right, index, str);
}



void encode(string str) {
    fill_map(str);
    node_bubble_sorting();
    build_tree();
    huffman_encode(root);

    string result = "";
    for (int i = 0; i < str.length(); i++) {
        result += symbol_codes[str[i]];
    }
    int size_of_code = 0;
    int size_of_decode = 0;
    double zip = 0;
    unordered_map<char, string> ::iterator it = symbol_codes.begin();
    unordered_map<char, int> ::iterator itr = symbol_frequency.begin();
    for (int i = 0; it != symbol_codes.end(); it++, i++, itr++) {
        cout << it->first << " : " << it->second << endl;
        size_of_code += it->second.length() * itr->second;
        size_of_decode += 8 * itr->second;
    }
    int index = -1;
    cout << "Encoded string: " << endl;
    cout << result << endl;
    cout << "Decoded string: " << endl;
    while (index < (int)result.size() - 2) {
        decode(root, index, result);
    }
    cout << endl;

    zip = (double)size_of_decode / size_of_code;
    cout << "Coded string: " << size_of_code << " bits" << endl;
    cout << "Encoded string: " << size_of_decode << " bits" << endl;
    cout << "Average length: " << (double)size_of_code / (double)str.length() << endl;
    cout << "Coefficient: " << zip << endl;

    double dispers = 0;
    for (auto pair : symbol_codes) {
        for (int i = 0;i < symbol_frequency.size();++i) {
            if (symbol_frequency[str[i]] == pair.first) {
                dispers +=((double)symbol_frequency[str[i]]/ (double)str.length()) * pow((pair.second.length() / ((double)size_of_code / (double)str.length())), 2);
                break;
            }
        }
    }
    cout << "Dispersion: " << (double)dispers << endl;
}

int main() {
    system("chcp 65001");
    string line;
    string str = "абдукаримова карина маратовна";
    encode(str);
    encode(str);
}

