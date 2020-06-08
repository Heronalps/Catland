#ifndef WORD_WIDGET_H_
#define WORD_WIDGET_H_

#include <Wt/WContainerWidget.h>

using namespace Wt;

class ItemWidget : public WContainerWidget
{
public:
  ItemWidget();

  std::wstring item() const { return item_; } 
  int count() const { return count_; } 

  void init(const std::wstring &word);
  bool guess(wchar_t c);

  bool won();

private:
  std::vector<WText *>           wordLetters_;
  std::wstring                   item_;
  int                            count_;

  unsigned                       displayedLetters_;
};

#endif //WORD_WIDGET_H_
