#ifndef ITEM_H_
#define ITEM_H_

#include <string>

class Item 
{
public:
    Item(int seq, int count, std::wstring entry);

    std::wstring entry() const { return entry_; } 
    int count() const { return count_; } 
    int seq() const { return seq_; }
private:
    int           seq_;
    int           count_;
    std::wstring   entry_;
};


#endif //ITEM_H_