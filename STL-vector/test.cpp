#include<iostream>

#include<assert.h>
#include<vector>
using namespace std;
#include"vector.h"



int main()
{
	vector<int> s;
	for (int i = 0; i < 4; i++)
	{
		s.push_back(i);
	}
	//while (it != s.cend())
	//{
	//	//*it = 10;
	//	++it;
	//}
	vector<int>::iterator its = s.begin();
	vector<int>::iterator end = s.end();
	while(its != end)
	{
		*its = 10;
		++its;
	}
	return 0;
}
