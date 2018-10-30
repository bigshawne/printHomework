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
	void print(int len)
	{
		cout << print(0, len, INT_MAX);
	}
private:
	int price(int i, int j, int len, int n);
	int end(int i, int n);
	int print(int i, int len, int q);
	bool if_lastline(int i, int n);
	vector<word<T>*> t;
	int total_len = 0;
	int penalty = 0;
	vector<int> r;
	vector<int> s;
};

template <typename T>
text<T>::text(string text)
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
			total_len += w.length();
			total_len++;
			pos += w.length();
		}
	}
	
	t[t.size() - 1]->key.pop_back();
	t[t.size() - 1]->len--;
	total_len--;
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

/*
 *Greedy Algorithm
template <typename T>
void text<T>::print(int i, int len)
{
	int line = 0;
	for(unsigned int j = 0; j < t.size(); ++j)
	{
		if(line + t[j]->len > len)
		{
			cout << endl;
			cout << t[j]->key;
			line = 0;
			line += t[j]->len;
		}
		else
		{
			cout << t[j]->key;
			line += t[j]->len;
		}
	}
}
*/


//Recursive solution
template <typename T>
int text<T>::print(int i, int len, int q)
{
	int e = end(i, len);
	int line = 0;
	for(int k = i; i < e; i++)
	{
		line += t[k]->len;
		int p = price(i, k, line, len);
		cout << p << endl;
		q = min(q, p + print(k + 1, len, q));
	}
	return q;
}

template <typename T>
bool text<T>::if_lastline(int i, int n)
{
	int remain = total_len - t[i]->pos;
	return remain < n;
}

template <typename T>
int text<T>::price(int i, int j, int len, int n)
{
	if (if_lastline(i, n))
		return pow(penalty, 3);
	int p = n - j + i - len;
	penalty += p;
	return pow(penalty, 3);
}

template <typename T>
int text<T>::end(int i, int n)
{
	unsigned int end = i;
	int line = 0;
	while(end < t.size())
	{
		if(line + t[end]->len > n)
		{
			return end;
		}
		line += t[end]->len;
		++end;
	}
	return end;
}


