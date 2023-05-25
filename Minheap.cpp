#include <vector>
#include <stdexcept>
template <typename T> class MinHeap {

private:
    //members
    std::vector<T> arr;
    int size;
    
    //methods
    void minHeapify(int i);
    int parent(int i);
    int left(int i);
    int right(int i);
    bool isLeaf(int i);

public:
    //constructors
    MinHeap();
    MinHeap(std::vector<T>& inputArr);
    
    //methods
    void add(T elem);
    int getSize();
    T peek();
    T extractMin();
};

template <typename T> MinHeap<T>::MinHeap() {
    arr = std::vector<T>();
    size = 0;
}

template <typename T> MinHeap<T>::MinHeap(std::vector<T>& inputArr) {
    arr = inputArr;
    size = inputArr.size();
    for (int i = size/2; i >= 0; i--) {
        minHeapify(i);
    }
}

template <typename T> void MinHeap<T>::minHeapify(int i) {
    if (isLeaf(i)) {
        return; //we good
    }
    //assume left and right children are valid minheaps
    int l = left(i);
    int r = right(i);

    if (r < size) {
        if (arr[l] < arr[i] || arr[r] < arr[i]) {
            int swapInd = l;
            if (arr[r] < arr[l]) {
                swapInd = r;
            }
            T temp = arr[i];
            arr[i] = arr[swapInd];
            arr[swapInd] = temp;
            minHeapify(swapInd);
        }
    } else {
        if (arr[l] < arr[i]) {
            T temp = arr[i];
            arr[i] = arr[l];
            arr[l] = temp;
            minHeapify(l);
        }
    }
}

template <typename T> int MinHeap<T>::parent(int i) {
    return (i-1) / 2;
}

template <typename T> int MinHeap<T>::left(int i) {
    return 2*i + 1;
}

template <typename T> int MinHeap<T>::right(int i) {
    return 2*i + 2;
}

template <typename T> bool MinHeap<T>::isLeaf(int i) {
    return (2*i + 1) >= size;
}

template <typename T> void MinHeap<T>::add(T elem) {
    int ind = size;
    arr.push_back(elem);
    size++;
    while (ind > 0) {
        ind = parent(ind);
        minHeapify(ind);
    }
}

template <typename T> int MinHeap<T>::getSize() {
    return size;
}

template <typename T> T MinHeap<T>::peek() {
    //throw error if size == 0...
    if (arr.empty()) {
        throw std::out_of_range("Vector is empty.");
    } else {
        return *(arr.begin());
    }
}

template <typename T> T MinHeap<T>::extractMin() {
    if (arr.empty()) {
        throw std::out_of_range("Vector is empty.");
    } else {
        T root = *(arr.begin());
        arr[0] = arr[size-1];
        size--;
        arr.pop_back();
        minHeapify(0);
        return root;
    }
}
