#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include <stdexcept>
#include <vector>

class MaxHeap
{
private:
    std::vector<long int> data;
    void bubbleUp(size_t);
    void bubbleDown(size_t);
    void build_heap_with_bubble_up(std::vector<long int>&);
    void build_heap_with_bubble_down(std::vector<long int>&);
    size_t getParent(size_t);
    size_t getLeftChild(size_t);
    size_t getRightChild(size_t);
public:
    MaxHeap(std::vector<long int>&);
    MaxHeap();
    ~MaxHeap();
    void clear();
    size_t size();
    void insert(long int);
    long int deleteMax();
    long int getMax();
};

MaxHeap::MaxHeap(std::vector<long int>& inputData)
{
    build_heap_with_bubble_up(inputData);
    //build_heap_with_bubble_down(inputData);
}

MaxHeap::MaxHeap()
{

}

MaxHeap::~MaxHeap()
{

}

void MaxHeap::bubbleUp(size_t index)
{
    size_t parentIndex = getParent(index);
    while(index > 0 and data[parentIndex] < data[index])
    {
        std::swap(data[parentIndex], data[index]);
        index = parentIndex;
        parentIndex = getParent(index);
    }
}

void MaxHeap::bubbleDown(size_t index)
{
    
    while(index < size())
    {
        size_t leftChild = getLeftChild(index);
        size_t rightChild = getRightChild(index);
        size_t largestIndex = index; 

        if(leftChild < size() and data[leftChild] > data[largestIndex])
        {
            largestIndex = leftChild;
        }

        if(rightChild < size() and data[rightChild] > data[largestIndex])
        {
            largestIndex = rightChild;
        } 

        if(largestIndex != index)
        {
            std::swap(data[largestIndex], data[index]);
            index = largestIndex;
        }
        else
        {
            break;
        }
    }
}

void MaxHeap::build_heap_with_bubble_up(std::vector<long int>& array)
{
    data = array;
    for(int i = 0; i < data.size(); i++)
    {
        bubbleUp(i);
    }
}

void MaxHeap::build_heap_with_bubble_down(std::vector<long int>& array)
{
    data = array;
    for(int i = 0; i < data.size(); i++)
    {
        bubbleDown(i);
    }
}

size_t MaxHeap::getParent(size_t index)
{
    return (index-1)/2;
}

size_t MaxHeap::getLeftChild(size_t index)
{
    return 2*index + 1;
}

size_t MaxHeap::getRightChild(size_t index)
{
    return 2*index + 2;
}


void MaxHeap::clear()
{
    data.clear();
}

size_t MaxHeap::size()
{
    return data.size();
}

void MaxHeap::insert(long int value)
{
    this->data.push_back(value);
    bubbleUp(size() - 1);
}

long int MaxHeap::deleteMax()
{
    if (size() <= 0)
    {
        throw std::underflow_error("Heap is empty");
    }

    long int max = data[0];
    data[0] = data[size() - 1];
    data.pop_back();
    bubbleDown(0);
    return max;
}

long int MaxHeap::getMax()
{
    return data[0];
}

#endif