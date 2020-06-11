#include "Item.h"

Item::Item(int seq, std::wstring entry, std::wstring comment) 
{
    seq_ = seq;
    entry_ = entry;
    comment_ = comment;
}