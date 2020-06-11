#include "Item.h"

Item::Item(int seq, std::wstring comment, std::wstring entry) 
{
    seq_ = seq;
    comment_ = comment;
    entry_ = entry;
}