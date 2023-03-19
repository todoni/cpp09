#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <deque>

template <typename Container>
class PmergeMe
{
public:
    void sort()
    {
        mergeInsertionSort(0, container.size() - 1);
    }

    void print()
    {
        for (typename Container::iterator it = container.begin(); it != container.end(); ++it)
        {
            std::cout << *it << ' ';
        }
        std::cout << std::endl;
    }

    void insertData(const std::deque<int>& data)
    {
        container.assign(data.begin(), data.end());
    }

    PmergeMe() {}
    ~PmergeMe() {}
private: 
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    void mergeInsertionSort(long start, long end)
    {
        if (start >= end)
        {
            return;
        }

        if (end - start + 1 <= 10)
        {
            insertionSort(start, end);
            return;
        }

        long mid = start + (end - start) / 2;

        mergeInsertionSort(start, mid);
        mergeInsertionSort(mid + 1, end);
        merge(start, mid, end);
    }

    void merge(long start, long mid, long end)
    {
        Container sorted(end - start + 1);

        long i, j, k;

        i = start;
        j = mid + 1;
        k = 0;

        while (i <= mid && j <= end)
        {
            if (container[i] <= container[j])
            {
                sorted[k] = container[i];
                ++i;
            }
            else
            {
                sorted[k] = container[j];
                ++j;
            }
            ++k;
        }

        while (i <= mid)
        {
            sorted[k] = container[i];
            ++k;
            ++i;
        }

        while (j <= end)
        {
            sorted[k] = container[j];
            ++k;
            ++j;
        }

        for (long i = start, k = 0; i <= end; i++, k++)
        {
            container[i] = sorted[k];
        }
    }

    void insertionSort(long start, long end)
    {
        for (long i = start + 1; i <= end; i++)
        {
            int key = container[i];
            long j = i - 1;

            while (j >= start && container[j] > key)
            {
                container[j + 1] = container[j];
                --j;
            }

            container[j + 1] = key;
        }
    }
private:
    Container container;
};

#endif