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
    void mergeInsertionSort(long left, long right)
    {
        if (left >= right)
        {
            return;
        }

        if (right - left + 1 <= 10)
        {
            insertionSort(left, right);
            return;
        }

        long mid = left + (right - left) / 2;

        mergeInsertionSort(left, mid);
        mergeInsertionSort(mid + 1, right);
        merge(left, mid, right);
    }

    void merge(long left, long mid, long right)
    {
        Container temp_container(right - left + 1);

        long i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right)
        {
            if (container[i] <= container[j])
            {
                temp_container[k++] = container[i++];
            }
            else
            {
                temp_container[k++] = container[j++];
            }
        }

        while (i <= mid)
        {
            temp_container[k++] = container[i++];
        }

        while (j <= right)
        {
            temp_container[k++] = container[j++];
        }

        for (long i = left, k = 0; i <= right; i++, k++)
        {
            container[i] = temp_container[k];
        }
    }

    void insertionSort(long left, long right)
    {
        for (long i = left + 1; i <= right; i++)
        {
            int key = container[i];
            long j = i - 1;

            while (j >= left && container[j] > key)
            {
                container[j + 1] = container[j];
                j--;
            }

            container[j + 1] = key;
        }
    }
private:
    Container container;
};

#endif