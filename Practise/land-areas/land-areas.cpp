#include <iostream>
#include <vector>

int F(std::vector<int>& current, std::vector<int>& best, int num)
{
	int minValue = 100001;

	if (num == 0)
	{
		return 0;
	}

	if (num == 1)
	{
		return 1;
	}

	if (current[num] != 0)
	{
		return current[num];
	}

	for (int i = (int)(sqrt(num)); i > 0; --i)
	{
		int iToSquare = i * i;
		int value = F(current, best, num - iToSquare) + 1;

		if (value < minValue)
		{
			best[num] = iToSquare;
			minValue = value;
		}
	}

	current[num] = minValue;
	return minValue;
}

int main()
{
	int num; 

	std::cin >> num;

	if (num <= 0 || num > 100000)
	{
		std::cout << "Invalid number. Number is in range [1;100000]\n";
		return 1;
	}

	std::vector<int> current(num + 1, 0);
	std::vector<int> best(num + 1, 0);

	best[1] = 1;
	std::cout << F(current, best, num) << std::endl;

	do
	{
		std::cout << best[num] << ' ';
		num -= best[num];

	} while (num > 0);
	std::cout << '\n';

	return 0;
}


