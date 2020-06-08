#include "ItemWidget.h"

#include <Wt/WText.h>

using namespace Wt;

ItemWidget::ItemWidget() :
  WContainerWidget()
{
  addStyleClass("itemcontainer");
}

void ItemWidget::init(const std::wstring &word)
{
  item_ = word;
  displayedLetters_ = 0;

  clear();
  wordLetters_.clear();
  for(unsigned int i = 0; i < item_.size(); ++i) {
    WText *c = this->addWidget(cpp14::make_unique<WText>("-"));
    wordLetters_.push_back(c);
  }
}

bool ItemWidget::guess(wchar_t c)
{
  bool correct = false;

  for(unsigned int i = 0; i < item_.size(); ++i) {
    if(item_[i] == c) {
      displayedLetters_++;
      wordLetters_[i]->setText(std::wstring(1, c));
      correct = true;
    }
  }

  return correct;
}

bool ItemWidget::won()
{
  return displayedLetters_ == item_.size();
}
