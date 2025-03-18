#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <cstddef>
#include <string>

namespace mine
{
    class Trie
    {
    private:
        size_t counter;
        Trie* child[26];
    public:
        Trie();
        ~Trie();
        bool find(std::string);
        void insert(std::string);
        std::string remove(std::string);
    };

    Trie::Trie()
    {
        counter = 0;
        for(size_t i = 0; i < 26; i++)
            child[i] = nullptr;
    }

    Trie::~Trie()
    {
        for(size_t i = 0; i < 26; i++)
            delete child[i];
    }

    bool Trie::find(std::string phrase)
    {
        Trie* navigator = this;
        for(auto c : phrase)
        {
            size_t c_index = c - 'a';
            if (!navigator->child[c_index])
                return false;
            navigator = navigator->child[c_index];
        }

        return navigator->counter;
    }

    void Trie::insert(std::string phrase)
    {
        Trie* navigator = this;
        for(auto c : phrase)
        {
            size_t c_index = c - 'a';
            if (!navigator->child[c_index])
                navigator->child[c_index] = new Trie();
            navigator = navigator->child[c_index];
        }

        navigator->counter++;
    }

    std::string Trie::remove(std::string phrase)
    {
        Trie* navigator = this;
        for(auto c : phrase)
        {
            size_t c_index = c - 'a';
            if (!navigator->child[c_index])
                return NULL;
            navigator = navigator->child[c_index];
        }

        navigator->counter--;
        return phrase;
    }
}

#endif