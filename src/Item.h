#ifndef ITEM_H_
#define ITEM_H_

#include <string>

class Item 
{
public:
    Item(int seq, std::wstring comment, std::wstring entry);

    std::wstring entry() const { return entry_; } 
    std::wstring comment() const { return comment_; } 
    int seq() const { return seq_; }
private:
    int            seq_;
    std::wstring   comment_;
    std::wstring   entry_;
};


#endif //ITEM_H_