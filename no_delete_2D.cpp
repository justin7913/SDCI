#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "iterator" //求交并补使用到的迭代器
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

vector<string> vectors_intersection(vector<string> v1, vector<string> v2)
{
	vector<string> v;
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v));
	return v;
}

void GetIntersection(const vector<string>& vectorA, const vector<string>& vectorB, vector<string>& vectorC, int start, int start2, int end, int end2)
{
	set <string> s;
	for (int i = start; i < end; i++)
	{
		s.insert(vectorA[i]);
	}
	for (int j = start2; j < end2; j++)
	{
		if (s.find(vectorB[j]) != s.end())
		{
			vectorC.push_back(vectorB[j]);
		}
	}
}

int k = 10;    //top-k 的 k
int score = 0;
int min_temp = 0;

int main()
{
	vector <string> d1;
	vector <string> d2;
	vector <string> d3;
	vector <string> candidate;
	vector <int> candidate_score;
	vector <string> temp2;
	vector <string> temp3;
	vector <string> temp1f;
	vector <string> temp2f;
	vector <string> intersection;
	vector <string> intersection2;
	vector <string> intersection3;
	vector <string> intersection4;


	ifstream fin_d1("500kd1.csv");
	string line;
	while (getline(fin_d1, line))
	{
		d1.push_back(line);
	}

	ifstream fin_d2("500kd2.csv");
	while (getline(fin_d2, line))
	{
		d2.push_back(line);
	}
	//讀完檔

	string temp;
	int num1 = 0;
	int num2 = 0;
	int num3 = 0;
	int totalsize = d1.size();
	int candidate_change = 1;
	int x = 0;
	int find2 = 0;
	int find3 = 0;
	int j = 0;
	int p = 0;

	while (candidate.size() == 0 || ((d1.size() - x) > candidate_score[min_temp]))
	{
		int min = 999999;
		if (candidate_change == 1)
		{
			for (int i = 0; i < candidate_score.size(); i++)
			{
				if (candidate_score[i] < min)
				{
					min = candidate_score[i];
					min_temp = i;
				}
			}
		}
		//找出candidate最小的

		if (candidate.size() == 0 || (d1.size() - x) > candidate_score[min_temp])
		{
			temp = d1[num1];
			find2 = 0;
			j = 0;
			while (find2 == 0)
			{
				if (d2[j] == temp)
				{
					num2 = j;
					find2 = 1;
				}
				j++;
			}

			if (num1 >= num2)
			{
				if (candidate.size() < k || d1.size() - num1 - 1 > candidate_score[min_temp])
				{

					GetIntersection(d1, d2, intersection, 0, 0, num1, num2);   //1 2
					score = d1.size() - 1 - (num1 + num2) + intersection.size();
					if (candidate.size() < k)
					{
						candidate.push_back(temp);
						candidate_score.push_back(score);
						candidate_change = 1;
					}
					else if (candidate.size() >= k && score > candidate_score[min_temp])
					{
						candidate.push_back(temp);
						candidate_score.push_back(score);
						candidate.erase(candidate.begin() + min_temp);
						candidate_score.erase(candidate_score.begin() + min_temp);
						candidate_change = 1;
					}
					else if (candidate.size() >= k && score <= candidate_score[min_temp])
					{
						candidate_change = 0;
					}
				}
			}

			else if (num2 > num1)
			{
				if (candidate.size() < k || d2.size() - num2 - 1 > candidate_score[min_temp])
				{

					GetIntersection(d1, d2, intersection, 0, 0, num1, num2);   //1 2
					score = d1.size() - 1 - (num1 + num2) + intersection.size();
					if (candidate.size() < k)
					{
						candidate.push_back(temp);
						candidate_score.push_back(score);
						candidate_change = 1;
					}
					else if (candidate.size() >= k && score > candidate_score[min_temp])
					{
						candidate.push_back(temp);
						candidate_score.push_back(score);
						candidate.erase(candidate.begin() + min_temp);
						candidate_score.erase(candidate_score.begin() + min_temp);
						candidate_change = 1;
					}
					else if (candidate.size() >= k && score <= candidate_score[min_temp])
					{
						candidate_change = 0;
					}
				}
			}
			intersection.clear();
			x++;
			num1++;
		}
	}
	system("pause");
	return 0;
}



