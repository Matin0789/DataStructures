#ifndef DICT_H
#define DICT_H

#include <iostream>
#include <functional>
#include <stddef.h>
#include <stdexcept>
#include <sstream>

struct Cell
{
    int key;
    long int value;
    short tag;
    Cell() : key(0), value(0), tag(-1) {}
    Cell(int _key, long int _value) : key(_key), value(_value), tag(-1) {}
};

class Dict
{
    friend std::ostream& operator<<(std::ostream& out, const Dict& dict);
private:
    Cell *data;
    size_t max_size;
    size_t size;
    void resize();
    std::hash<int> hash2;
    unsigned int hash1(int);
    unsigned int hash(int, int);
public:
    Dict();
    ~Dict();
    void insert(int, long int);
    long int find(int);
    void erase(int);
};

Dict::Dict(/* args */)
{
    max_size = 8;
    size = 0;
    data = new Cell[max_size];
}

Dict::~Dict()
{
    delete[] data;
}

void Dict::resize()
{
    size_t old_max_size = max_size;
    Cell *old_data = data;
    
    max_size *= 2;
    data = new Cell[max_size];
    size = 0;
    
    for(int i = 0; i < old_max_size; i++)
    {
        if(old_data[i].tag == 1)
        {
            insert(old_data[i].key, old_data[i].value);
        }
    }

    delete[] old_data;

}

unsigned int Dict::hash1(int value)
{
    unsigned int hash = (value * 2654435761) % (1 << 32);
    return hash;
}
  
unsigned int Dict::hash(int key, int i)
{
    unsigned int h2 = hash2(key);
    if (h2 == 0) h2 = 1;
    return (hash1(key) + h2 * i) % max_size;
}

void Dict::insert(int key, long int value)
{
    if(size >= max_size * 0.75)
    {
        resize();
    }

    Cell newData(key, value);
    int i = 0;
    while(true)
    {
        unsigned int _hash = hash(key, i);
        if(data[_hash].tag <= 0)
        {
            data[_hash] = newData;
            data[_hash].tag = 1;
            break;
        }
        else
        {
            i++;
        }
    }
    size++;
    
}

long int Dict::find(int key)
{
    size_t i = 0;
    while(true)
    {
        if(i >= max_size)
        {
            throw std::runtime_error("key_error");
        }
        unsigned int hash_num = hash(key, i);
        if(data[hash_num].tag < 0)
        {
            throw std::runtime_error("key_error");
        }
        else if(data[hash_num].tag == 0)
        {
            i++;
        }
        else
        {
            if(data[hash_num].key == key)
            {
                return data[hash_num].value;
                break;
            }
            else
            {
                i++;
            }
        }
    }
}

void Dict::erase(int key)
{
    size_t i = 0;
    while(true)
    {
        if(i > max_size)
        {
            throw std::runtime_error("key_error");
        }
        unsigned int hash_num = hash(key, i);
        if(data[hash_num].tag < 0)
        {
            throw std::runtime_error("key_error");
        }
        else if(data[hash_num].tag == 0)
        {
            i++;
        }
        else
        {
            if(data[hash_num].key == key)
            {
                data[hash_num].tag = 0;
                size--;
                break;
            }
            else
            {
                i++;
            }
        }
    }
}

std::ostream& operator<<(std::ostream& out, const Dict& dict)
{
    out << '{';
    for(int i = 0; i < dict.max_size; i++)
    {
        if(dict.data[i].tag > 0)
        {
            out << '(' << dict.data[i].key << ',' << dict.data[i].value << ')';
            
        }
        else
        {
            out << "()";
        }
        if(i < dict.max_size-1)
        {
            out << " , ";
        }
    }
    out << '}';
    return out;
}

#endif
