#pragma once

#include <stdlib.h>
#include <stdexcept>


typedef size_t usize;


/**
 * @brief Fastest log2 by calculating the number of leading zeros in the binary
 * representation of `n`
 * 
 * Complexity: `O(1)`
 */
int log2i(int n) {
    return ((sizeof(int) * 8) - 1) - __builtin_clz(n);
}

/**
 * @brief Fastest log2 by calculating the number of leading zeros in the binary
 * representation of `n`
 * 
 * Complexity: `O(1)`
 */
usize log2us(usize n) {
    return ((sizeof(usize) * 4) - 1) - __builtin_clz(n);
}

/**
 * @brief A dynamic vector that does not perform any copies of its elements.
 */
template <typename T>
struct NoCopyVec {
    T** data;

    usize len;  // Count of elements
    usize size;  // Pointer array capacity
    usize capacity;  // Total capacity

    /**
     * @brief Constructs a new NoCopyVec object.
     */
    NoCopyVec() : len(0), size(1), capacity(1) {
        data = new T*[size];
        data[0] = new T[1];
    }

    /**
     * @brief Constructs a new NoCopyVec object with a specified base size.
     * 
     * @param base_size The base size of the vector.
     */
    NoCopyVec(usize base_size) : len(0), size(base_size), capacity(1) {
        data = new T*[size];
        data[0] = new T[1];
    }

    /**
     * @brief Destroys the NoCopyVec object.
     * 
     * Complexity: `O(log2(n))`
     */
    ~NoCopyVec() {
        usize arr_count = log2us(capacity + 1);

        for (usize i = 0; i < arr_count; i++) {
            delete[] data[i];
        }

        delete[] data;
    }

    /**
     * @brief Grows the vector to fit more elements.
     * 
     * Complexity: `Ω(1), O(log2(n))`
     */
    inline void grow() {
        usize arr_count = log2us(capacity + 1);

        if (arr_count == size) {
            size *= 2;

            T** new_data = new T*[size];

            for (usize i = 0; i < arr_count; i++) {
                new_data[i] = data[i];
            }

            delete[] data;
            data = new_data;
        }

        data[arr_count] = new T[capacity + 1];

        capacity += capacity + 1;
    }

    /**
     * @brief Pushes an element onto the vector.
     * 
     * Complexity: `Ω(1), O(log2(n))`
     */
    inline void push(const T val) {
        if (len == capacity) {
            grow();
        }

        len += 1;

        usize arr_index = log2us(len);  // Get the array index
        usize offset = len - (1 << arr_index);  // Get the offset

        data[arr_index][offset] = val;  // Set the value
    }
    
    /**
     * @brief Returns the element at the specified index.
     * 
     * Complexity: `O(1)`
     */
    T at(usize index) {
        if (index < 0 || index > capacity) {
            throw std::out_of_range("Index out of range");
        }

        index += 1;
        usize arr_index = log2us(index);  // Get the array index
        usize offset = index - (1 << arr_index);  // Get the offset

        return data[arr_index][offset];
    }
};


template <typename T>
struct NoCopyVecPre {
    T** data;

    usize len;  // Count of elements
    usize capacity;  // Total capacity

    /**
     * @brief Constructs a new NoCopyVecPre object with a specified finale size.
     * 
     * @param alloc The finale size of the vector.
     */
    NoCopyVecPre(usize alloc) : len(0), capacity(1) {
        data = new T*[alloc];
        data[0] = new T[1];
    }

    /**
     * @brief Destroys the NoCopyVecPre object.
     * 
     * Complexity: `O(log2(n))`
     */
    ~NoCopyVecPre() {
        usize arr_count = log2us(capacity + 1);

        for (usize i = 0; i < arr_count; i++) {
            delete[] data[i];
        }

        delete[] data;
    }

    /**
     * @brief Grows the vector to fit more elements.
     * 
     * Complexity: `O(1)`
     */
    inline void grow() {
        usize arr_count = log2us(capacity + 1);

        data[arr_count] = new T[capacity + 1];

        capacity += capacity + 1;
    }

    /**
     * @brief Pushes an element onto the vector.
     * 
     * Complexity: `O(1)`
     */
    inline void push(const T val) {
        if (len == capacity) {
            grow();
        }

        len += 1;

        usize arr_index = log2us(len);  // Get the array index
        usize offset = len - (1 << arr_index);  // Get the offset

        data[arr_index][offset] = val;  // Set the value
    }
    
    /**
     * @brief Returns the element at the specified index.
     * 
     * Complexity: `O(1)`
     */
    T at(usize index) {
        if (index < 0 || index > capacity) {
            throw std::out_of_range("Index out of range");
        }

        index += 1;
        usize arr_index = log2us(index);  // Get the array index
        usize offset = index - (1 << arr_index);  // Get the offset

        return data[arr_index][offset];
    }
};
