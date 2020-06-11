#include "ItemWidget.h"

using namespace Wt;

ItemWidget::ItemWidget() : WContainerWidget(){}

void ItemWidget::init() 
{
  this->clear();
  auto tablePtr = cpp14::make_unique<WTable>();
  table_ = tablePtr.get();
  
  table_->setHeaderCount(1);
  table_->setWidth(Wt::WLength("100%"));

  table_->elementAt(0, 0)->addWidget(cpp14::make_unique<WText>("#"));
  table_->elementAt(0, 1)->addWidget(cpp14::make_unique<WText>("Item"));
  table_->elementAt(0, 2)->addWidget(cpp14::make_unique<WText>("Comment"));

  this->addWidget(std::move(tablePtr));
  table_->toggleStyleClass("table-bordered", true);
  table_->toggleStyleClass("table-hover", true);
  table_->toggleStyleClass("table-striped", true);
}

void ItemWidget::reload() 
{
  init();
  for (auto item : items_) {
    addToTable(item);
  }
}

void ItemWidget::addToTable(Item* item)
{
  table_->elementAt(item->seq(),0)->addWidget(cpp14::make_unique<WText>(WString("{1}").arg(item->seq())));
  table_->elementAt(item->seq(),1)->addWidget(cpp14::make_unique<WText>(item->entry()));
  table_->elementAt(item->seq(),2)->addWidget(cpp14::make_unique<WText>(WString("{1}").arg(item->comment())));
}


void ItemWidget::addItem(Item* item) 
{
  items_.push_back(item);
  reload();
}

void ItemWidget::deleteItem(Item* item)
{
  items_.pop_back();
  reload();
}