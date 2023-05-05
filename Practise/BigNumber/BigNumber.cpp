#include <iostream>
#include <fstream>
#include <vector>

void Solve()
{
    char max = '9';
    size_t temp = -1;
    std::string num, path;
    int order;
    std::fstream fin;
    int counter;

    std::cout << "Enter a filename: ";
    std::cin >> path;
    std::cout << std::endl;

    fin.open(path);
    fin >> order;
    fin >> num;
    fin.close();

    
    for (int i = 0; i < num.size();i++)
    {
        if (num[i] < max)
        {
            max = num[i];
        }
    }
    for (int i = 0; i < num.size() - 1;++i)
    {
        temp = i;
        if (num[i] < num[i + 1])
        {
            break;
           
        }
    }
    while ((temp > 0) && num[temp] == num[temp - 1])
    {
        --temp;
    }
    std::cout << temp + 1;
}

int main()
{  
    Solve();

    return 0;
}

