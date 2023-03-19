#include "PmergeMe.hpp"
#include "IndexableList.hpp"

#include <deque>
#include <vector>
#include <time.h>

std::string numToString(int num)
{
    std::ostringstream oss;
    oss << num;
    return oss.str();
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: ./PmergeMe [Integer Sequence]" << std::endl;
        return (1);
    }

    std::deque<int> data;
    size_t i = 1;
    while (argv[i])
    {
        std::istringstream iss(argv[i]);
        std::string buffer;

        while (std::getline(iss, buffer, ' '))
        {
            int value = std::atoi(buffer.c_str());
            if (value < 0 || numToString(value) != buffer)
            {
                std::cout << "Error" << std::endl;
                return (1);
            }
            data.push_back(value);
        }
        ++i;
    }

    std::cout << "Before: ";
    for (std::deque<int>::iterator it = data.begin(); it != data.end(); ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    clock_t start = clock();
    PmergeMe<IndexableList<int> > stdList;
    stdList.insertData(data);
    stdList.sort();
    clock_t end = clock();
    double elapsedTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
    
    std::cout << "After: ";
    stdList.print();

    std::cout << "Time to process a range of " << data.size() << " elements with std::list   : " << elapsedTime << " us => " << elapsedTime / 1000000.0  << "s" << std::endl;

    start = clock();
    PmergeMe<std::vector<int> > stdVector;
    stdVector.insertData(data);
    stdVector.sort();
    end = clock();
    elapsedTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;

    std::cout << "Time to process a range of " << data.size() << " elements with std::vector : " << elapsedTime << " us => " << elapsedTime / 1000000.0 << "s" << std::endl;

    start = clock();
    PmergeMe<std::deque<int> > stdDeque;
    stdDeque.insertData(data);
    stdDeque.sort();
    end = clock();
    elapsedTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;

    std::cout << "Time to process a range of " << data.size() << " elements with std::deque  : " << elapsedTime << " us => " << elapsedTime / 1000000.0 << "s" << std::endl;

    return 0;
}