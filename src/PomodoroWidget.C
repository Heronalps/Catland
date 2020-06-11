#include "PomodoroWidget.h"

#include <Wt/WBreak.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WAny.h>
#include <Wt/WStringUtil.h>

#include "Session.h"
#include "Dictionary.h"
#include "ItemWidget.h"
#include "ImagesWidget.h"
#include "LettersWidget.h"
#include "Item.h"

using namespace Wt;

namespace {
  const int MaxGuesses = 9;
  static int ItemSeq = 1;
}

PomodoroWidget::PomodoroWidget(const std::string &name)
  : WContainerWidget(),
    name_(name),
    badGuesses_(0)
{
  setContentAlignment(AlignmentFlag::Center);
  
  title_ = addWidget(cpp14::make_unique<WText>(tr("pomodoro.lottery")));

  itemWidget_ = addWidget(cpp14::make_unique<ItemWidget>());
  statusText_ = addWidget(cpp14::make_unique<WText>());
  images_ = addWidget(cpp14::make_unique<ImagesWidget>(MaxGuesses));

  letters_ = addWidget(cpp14::make_unique<LettersWidget>());
  letters_->letterPushed().connect(this, &PomodoroWidget::registerGuess);

  addWidget(cpp14::make_unique<WBreak>());

  newGameButton_ = addWidget(cpp14::make_unique<WPushButton>(tr("pomodoro.newGame")));
  newGameButton_->clicked().connect(this, &PomodoroWidget::newGame);
}

void PomodoroWidget::newGame()
{
  WString title(tr("pomodoro.feelingLuck"));
  title_->setText(title.arg(name_));

  // language_->hide();
  newGameButton_->hide();
  badGuesses_ = 0;
  images_->showImage(badGuesses_);
  statusText_->setText("");
}

void PomodoroWidget::registerGuess(char c)
{
  auto item = new Item(ItemSeq, 456, widen("Michael"));
  itemWidget_->addItem(item);
  ItemSeq++;
}
