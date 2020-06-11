#ifndef ITEM_H_
#define ITEM_H_

#include <string>

class Item 
{
public:
    Item(int seq, std::wstring entry, std::wstring comment);
    
    int seq() const { return seq_; }
    std::wstring entry() const { return entry_; } 
    std::wstring comment() const { return comment_; } 
private:
    int            seq_;
    std::wstring   entry_;
    std::wstring   comment_;
};


#endif //ITEM_H_