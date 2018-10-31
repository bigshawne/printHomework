#pragma once
#include <string>
#include <vector>
#include <fstream>
#include<iostream>
#include <sstream>
#include <algorithm>
using namespace std;
template <typename T>
class word
{
public:
	T key;
	int len;
	int pos;

	word() {};
	word(T key, int len, int pos) { this->key = key; this->len = len; this->pos = pos; }
};

template <typename T>
class text
{
public:
	text(){};
	text(string text);
	~text();
	void print(int len);
private:
	void price();
	void traversal();
	vector<word<T>*> t;
	int line = 0;
	vector<vector<int>>p;
	vector<int> r;
	vector<int> s;
};

template <typename T>
text<T>::text(string text):r(t.size(), 0), s(t.size(), 0)
{
	int pos = 0;
	ifstream in(text);
	string line;
	while(getline(in, line, '\n'))
	{
		istringstream l(line);
		T w;
		while (getline(l, w, ' '))
		{
			w.push_back(' ');
			t.push_back(new word<T>(w, w.length(), pos));
			pos += w.length();
		}
	}
	
	t[t.size() - 1]->key.pop_back();
	--t[t.size() - 1]->len;
}

template <typename T>
text<T>::~text()
{
	auto itr = t.begin();
	while(itr != t.end())
	{
		delete *itr;
		++itr;
	}
}

template <typename T>
void text<T>::print(int len)
{
	line = len;
	price();
	traversal();
	unsigned int pos = 0;
	ofstream out("result.txt");
	while(pos < t.size() - 1)
	{
		int end = s[pos];
		for(int x = pos; x <= end; ++x)
		{
			cout << t[x]->key;
			out << t[x]->key;
		}
		cout << endl;
		out << endl;
		pos = end + 1;
	}
	out.close();
}

template <typename T>
void text<T>::traversal()
{
	vector<int> result(t.size(), 0);
	vector<int> seg(t.size(), 0);
	int e = t.size() - 1;
	for(int i =e; i > -1; --i)
	{
		int q = INT_MAX;
		int j = t.size() - 1;
		for(int k = i; k <= j; ++k)
		{
			if (p[i][k] >= 0) 
			{
				if(q > min(q, p[i][k] + result[k]))
				{
					q = min(q, p[i][k] + result[k]);
					seg[i] = k;
				}
			}
			else
				break;
		}
		result[i] = q;
	}
	r = result;
	s = seg;
}

template <typename T>
void text<T>::price()
{
	for(unsigned int n = 0; n < t.size(); ++n)
	{
		p.push_back(vector<int>(t.size(), 0));
	}
	
	for(unsigned int l = 0; l < t.size(); ++l)
	{
		p[l][l] = line - t[l]->len;
	}
	p[t.size() - 1][t.size() - 1] = 0;
	for(unsigned int m = 0; m < t.size() - 1; ++m)
	{
		for(unsigned int y = m + 1; y < t.size(); ++y)
		{
			if(y == t.size() - 1)
			{
				p[m][y] = 0;
			}
			else 
			{
				p[m][y] = p[m][y - 1] - 1 - t[y]->len;
			}
		}
	}
	for (unsigned int m = 0; m < t.size() - 1; ++m)
	{
		for(unsigned int x = 0; x < t.size() -1; ++x)
		{
			p[m][x] = (int)pow(p[m][x], 3);
		}
	}
}
