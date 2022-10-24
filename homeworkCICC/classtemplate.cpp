#include <stddef.h>
#include <stdexcept>
#include <utility>
#include <iostream>
#include <vector>

template <typename T>
class Array
{
private:
    T *elements; // array of type T
    size_t size; // no. of array elements

public:
    explicit Array(size_t arraySize);
    Array(const Array<T> &array);
    ~Array();
    T &operator[](size_t index);
    const T &operator[](size_t index) const;
    // Array& operator=(const Array& rhs);
    Array &operator=(Array copyArray);
    size_t getSize() const { return size; };
    void swap(Array &other) noexcept;
};

// constructor
template <typename T>
Array<T>::Array(size_t arraySize) : elements(new T[arraySize]), size(arraySize)
{
}

// copy constructor
template <typename T>
Array<T>::Array(const Array<T> &array) : Array{array.size}
{
    for (size_t i{}; i < size; ++i)
    {
        elements[i] = array.elements[i];
    }
}

// destructor
template <typename T>
Array<T>::~Array()
{
    delete[] elements;
}

// subscript operator
template <typename T>
T &Array<T>::operator[](size_t index)
{
    // return const_cast<T&>(static_cast<const Array<T>&>(*this)[index]);
    return const_cast<T &>(std::as_const(*this)[index]);
}

// subscript operator-const arrays
template <typename T>
const T &Array<T>::operator[](size_t index) const
{
    if (index >= size)
        throw std::out_of_range{"Index too large: " + std::to_string(index)};

    return elements[index];
}

// assign operator 这个版本不符合异常的安全性
// template <typename T>
// Array<T>& Array<T>::operator=(const Array& rhs)
// {
//     if(&rhs != this)    // 为什么检查左操作数和右操作数是必不可少的？
//     {
//         delete[] elements;

//         size = rhs.size;
//         elements = new T[size];
//         for(size_t i {}; i < size; ++i)
//         {
//             elements[i] = rhs.elements[i];
//         }
//     }
//     return *this;
// }

// assign operator - available
// template <typename T>
// Array<T>& Array<T>::operator=(const Array& rhs)
// {
//     if(&rhs != this)
//     {
//         Array<T> copy(rhs);
//         swap(copy);
//         // this = copy; // error!
//     }
//     return *this;
// }

// assign operator - more simple
template <typename T>
Array<T> &Array<T>::operator=(Array copyArray)
{
    swap(copyArray);
    return *this;
}

// Array::swap
template <typename T>
void Array<T>::swap(Array &other) noexcept
{
    std::swap(elements, other.elements);
    std::swap(size, other.size);
}

// global swap
template <typename T>
void swap(Array<T> &one, Array<T> &other) noexcept
{
    one.swap(other);
}

int main()
{
    Array<int> data{40};
    Array<int> data2{30};

    std::cout << data.getSize() << std::endl;
    std::cout << data2.getSize() << std::endl;

    data2 = data;
}