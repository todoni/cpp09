#ifndef INDEXABLELIST_HPP
# define INDEXABLELIST_HPP

# include <list>

template <typename T>
class IndexableList : public std::list<T>
{
public:
    IndexableList() : std::list<T>() {}
    IndexableList(typename std::list<T>::size_type n) : std::list<T>(n) {}
    ~IndexableList() {}
    IndexableList(const IndexableList &other) : std::list<T>(other) {}
    IndexableList &operator=(const IndexableList &other)
    {
        if (this != &other)
        {
            std::list<T>::operator=(other);
        }
        return (*this);
    }
    T &operator[](typename std::list<T>::size_type index)
    {
        typename std::list<T>::iterator it = this->begin();
        std::advance(it, index);
        return *it;
    }
};

#endif