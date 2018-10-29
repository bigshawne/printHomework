#pragma once
#include <string>
#include <vector>
#include <fstream>
#include<iostream>
using namespace std;
template <typename T>
class word
{
public:
	T key;
	int len;

	word() {};
	word(T key, int len) { this->key = key; this->len = len; }
};

template <typename T>
class text
{
public:
	text() :t(10000), r(10000), s(10000) {};
	text(string text);
	~text();
	void print(int p, int len);
private:
	int price(int i, int j, int len, int n);

	vector<word<T>*> t;
	int total_len = 0;
	int remain;
	int penalty;
	vector<int> r;
	vector<int> s;
};

template <typename T>
text<T>::text(string text)
{
	ifstream in(text);
	T w;
	while(getline(in, w, ' '))
	{
		t.push_back(new word<T>(w, w.length()));
		total_len += w.length();
		total_len++;
	}
	total_len--;
	remain = total_len;
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
void text<T>::print(int p, int len)
{
	int sum = 0;
	for(unsigned int i = p; i < t.size(); ++i)
	{
		word<T>* next = t[i];
		sum += next->len;
		++sum;
		remain -= sum;
		if(sum > len)
		{
			for (unsigned int j = p; j < i; j++)
				cout << t[j]->key <<" ";
			cout << endl;
			break;
		}
	}
}

template <typename T>
int text<T>::price(int i, int j, int len, int n)
{
	if (remain < n)
		return 0;
	int p = n - j + i - len;
	penalty += p;
	return pow(penalty, 3);
}
