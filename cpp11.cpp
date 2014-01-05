#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <numeric>

using namespace std;

int main(int argc, char *argv[])
{
	int arr[] = { 2, -5, 9, 7, -2, 5, 3, 1, 0, -3, 7 };
	vector<int> num(arr, arr + sizeof(arr) / sizeof(arr[0]));
	vector<int> p_num;
	copy_if(num.begin(), num.end(), back_inserter(p_num), bind2nd(greater<int>(), 0));
	int average = accumulate(p_num.begin(), p_num.end(), 0) / p_num.size();
	cout << "averge: " << average << endl;
	return 0;
}