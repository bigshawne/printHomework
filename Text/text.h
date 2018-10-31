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

	word() {};
	word(T key, int len) { this->key = key; this->len = len;}
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
	ifstream in(text);
	string line;
	while(getline(in, line, '\n'))
	{
		istringstream l(line);
		T w;
		while (getline(l, w, ' '))
		{
			t.push_back(new word<T>(w, w.length()));
		}
	}
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
	while(pos < t.size())
	{
		int end = s[pos];
		for(int x = pos; x <= end; ++x)
		{
			cout << t[x]->key << ' ';
			out << t[x]->key << ' ';
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
	r= vector<int>(t.size(), 0);
	s = vector<int>(t.size(), 0);
	for(int i = t.size() - 1; i >= 0; --i)
	{
		int q = INT_MAX;
		for(int j = i; j < t.size(); ++j)
		{
			if (p[i][j] < 0)
				break;
			if(j == t.size() - 1)
			{
				q = 0;
				s[i] = j;
			}
			else
			{
				if(q > p[i][j] + r[j + 1])
				{
					q = p[i][j] + r[j + 1];
					s[i] = j;
					if (q == 0)
						break;
				}
			}
		}
		r[i] = q;
	}
}

template <typename T>
void text<T>::price()
{
	for(unsigned int n = 0; n < t.size(); ++n)
	{
		p.push_back(vector<int>(t.size(), 0));
	}
	
	for(unsigned int i = 0; i < t.size(); ++i)
	{
		p[i][i] = line - t[i]->len;
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
				p[m][y] = p[m][y - 1] -1 - t[y]->len;
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
