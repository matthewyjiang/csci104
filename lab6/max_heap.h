#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class MaxHeap {
private:
    std::vector<T> data;
public:
    void push(const T& item);
    // Removes the largest element in the heap
    void pop();
    // Returns the largest element in the heap (but does not remove it)
    T const& top() const;
    std::size_t size() const;
};

template <typename T>
void MaxHeap<T>::push(const T& item) {
    data.push_back(item);
    std::size_t index = data.size() - 1;
    while (index != 0) {
        std::size_t parent_index = (index - 1) / 2;
        T& current = data[index];
        T& parent = data[parent_index];
        if (current <= parent) {
            break;
        }
        std::swap(current, parent);
        index = parent_index;
    }
}

template <typename T>
void MaxHeap<T>::pop() {
    if (data.empty()) {
        throw std::out_of_range("heap is empty");
    }
    std::swap(data[0], data[data.size()-1]);
    data.pop_back();
    std::size_t index = 0;
    std::size_t left_child;
    std::size_t right_child;

    while(true) {
        left_child = 2*index+1;
        right_child = 2*index+2;
        if(left_child >= data.size()){
            return;
        }
        if(right_child >= data.size()) {
            if(data[index] < data[left_child]) {
                std::swap(data[index], data[left_child]);
            }
            return;
        }
        if(data[left_child] > data[right_child]) {
            if(data[index] < data[left_child]) {
                std::swap(data[index], data[left_child]);
            } else {
                return;
            }
            index = left_child;
        } else {
            if(data[index] < data[right_child]) {
                std::swap(data[index], data[right_child]);
            } else {
                return;
            }
            index = right_child;
        }
    }
    
}

template <typename T>
T const& MaxHeap<T>::top() const {
    if (data.empty()) {
        throw std::out_of_range("heap is empty");
    }
    return data[0];
}

template <typename T>
std::size_t MaxHeap<T>::size() const {
    return data.size();
}
