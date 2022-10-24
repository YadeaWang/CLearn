#include <iostream>
#include <stdexcept>

template <typename T, int startIndex>
class Array
{
private:
    T* elements;
    size_t size;
public:
    explicit Array(size_t arraySize);
    Array(const Array& array);
    ~Array();
    T& operator[](int index);
    const T& operator[](int index) const;
    Array& operator=(const Array& rhs);
    size_t getSize() const { return size; }
    void swap(Array& other) noexcept;
};

template <typename T, int startIndex>
Array<T, startIndex>::Array(size_t arraySize)
    :elements{new T[arraySize]}, size{arraySize}
{}

template <typename T, int startIndex>
Array<T, startIndex>::Array(const Array& array)
    : Array(array.size)
{
    for(size_t i {}; i < size; ++i)
    {
        elements[i] = array.elements[i];
    }
}

template <typename T, int startIndex>
Array<T, startIndex>::~Array()
{
    delete[] elements;
}

template <typename T, int startIndex>
const T& Array<T, startIndex>::operator[](int index) const
{
    if(index < startIndex)
        throw std::out_of_range {"Index too small:" + std::to_string(index)};

    if(index > startIndex + static_cast<int>(size) - 1)
        throw std::out_of_range {"Index too large:" + std::to_string(index)};

    return elements[index - startIndex];
}

template <typename T, int startIndex>
T& Array<T, startIndex>::operator[](int index)
{
    return const_cast<T&>(std::as_const(*this)[index]);
}

// assign operator - more simple
template <typename T, int startIndex>
Array<T, startIndex>& Array<T, startIndex>::operator=(const Array& copyArray)
{
    swap(copyArray);
    return *this;
}

// Array::swap
template <typename T, int startIndex>
void Array<T, startIndex>::swap(Array &other) noexcept
{
    std::swap(elements, other.elements);
    std::swap(size, other.size);
}

