#include <vector>
#include <iostream>

using namespace std;

int main()
{
	int N;
	std::cin >> N;

	vector<int> inversion(N);
	for (int i = 0; i < N; ++i)
	{
		cin >> inversion[i];
	}

	cout << "\n";

	vector<int> temp(N);
	for (int j = 1; j <= N; ++j)
	{
		temp[j - 1] = j;
	}

	vector<int> result;
	for (int k = N - 1; k >= 0; --k)
	{
		int index = inversion[k];

		result.push_back(temp[temp.size() - index - 1]);
		temp.erase(temp.end() - index - 1);
	}

	copy(result.rbegin(), result.rend(), ostream_iterator<int>(cout, " "));
	cout << '\n';

	return 0;
}