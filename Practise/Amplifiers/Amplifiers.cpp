#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	unsigned long long N;
	std::cin >> N;

	if (N % 2 == 0)
	{
		std::cout << "No\n";
		return 0;
	}	
	N >>= 1;

	std::vector<unsigned long long> result;
	while (N != 0)
	{
		result.push_back((N & 1) + 1);
		N >>= 1;
	}

	std::cout << result.size() << '\n';
	std::reverse(result.begin(), result.end());

	for (auto i : result)
	{
		std::cout << i << " ";
	}
	std::cout << '\n';


	return 0;
}