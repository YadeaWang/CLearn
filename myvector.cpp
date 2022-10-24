#include <iostream>
#include <cstring>
#include <memory>

class MyVector {

    public:
        MyVector() : ptr(nullptr), size(0), capacity(0) {

        } 

        MyVector(int n, int x=0) : ptr(nullptr), size(n), capacity(n) {
            this->ptr = (int *)malloc(n * sizeof(int));
            for (int i = 0; i < n; i++) {
                ptr[i] = x;
            }
        } 

        MyVector(MyVector &vec_src)
        {
            this->size = vec_src.size;
            this->capacity = vec_src.capacity;
            this->ptr = (int *)malloc(this->capacity * sizeof(int));


            memcpy(this->ptr, vec_src.ptr, size * sizeof(int));

        }

        MyVector(const MyVector&& vec_src) {
            this->size = vec_src.size;
            this->capacity = vec_src.capacity;
            this->ptr = (int *)malloc(this->capacity * sizeof(int));

            memcpy(this->ptr, vec_src.ptr, size * sizeof(int));
        }

        
        MyVector& operator=(const MyVector& v){
            this->size = v.size;
            this->capacity = v.capacity;
            free(this->ptr);
            this->ptr=new int[this->size];
            for (int i=0; i < this->get_size(); i++) {
                this->ptr[i]=v.ptr[i];
            }
            return *this;
        };

        MyVector& operator=(MyVector&& v){
            this->size = v.size;
            this->capacity = v.capacity;
            delete[] ptr;
            this->ptr=new int[this->size];
            for (int i=0; i < this->get_size(); i++) {
                this->ptr[i]=v.ptr[i];
            }
            return *this;
        };

       

        ~MyVector() {
            size = 0;
            capacity = 0;
            if(ptr)
            delete[] ptr;
        }


        int &operator[] (int idx) {
            if (idx < 0 || idx >= this->size) {
                return ptr[0];
            }
            return ptr[idx];
        }

        int get_size() const {
            return this->size;
        }

        MyVector &operator+= (int x) {
            if (size == capacity)
            {
                int new_capacity = (capacity == 0 ? 8 : 2 * capacity);
                int *new_ptr = new int[new_capacity];
                for (int i = 0; i < size; i++)
                {
                    new_ptr[i] = ptr[i];
                }
                delete []ptr;

                ptr = new_ptr;
                capacity = new_capacity;
            }

            ptr[size++] = x;

            return *this;
        }
    private:
        int *ptr;
        int size;
        int capacity;
};

MyVector operator+ (const MyVector &va, const MyVector &vb) {
    MyVector result(va.get_size() + vb.get_size());
    int idx = 0;
    for (int i = 0; i < va.get_size(); i++)
    {
       result[idx++] = va[i];
    }

    for (int i = 0; i < vb.get_size(); i++)
    {
       result[idx++] = vb[i];
    }

    return result;
    
}