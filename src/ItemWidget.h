#ifndef ITEM_WIDGET_H_
#define ITEM_WIDGET_H_

#include "Item.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WTableCell.h>
#include <Wt/WLineEdit.h>
#include <Wt/WText.h>
#include <Wt/WCheckBox.h>


#include <memory>

using namespace Wt;

class ItemWidget : public WContainerWidget
{
public:
  ItemWidget();

  void addToTable(Item* item);

  void addItem(Item* item);

  void deleteItem(Item* item);

  void reload();
  
  void init();

private:
  WTable                        *table_;
  std::vector<Item*>             items_;
};

#endif //ITEM_WIDGET_H_
