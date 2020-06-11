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
  static int RandomGuess = 0;
  const int PicNumber = 9;
  static int ItemSeq = 1;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1, 8);
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
  images_ = addWidget(cpp14::make_unique<ImagesWidget>(PicNumber));

  letters_ = addWidget(cpp14::make_unique<LettersWidget>());
  letters_->letterPushed().connect(this, &PomodoroWidget::registerGuess);

  addWidget(cpp14::make_unique<WBreak>());

  feelingLuckyButton_ = addWidget(cpp14::make_unique<WPushButton>(tr("pomodoro.feelingLucky")));
  feelingLuckyButton_->clicked().connect(this, &PomodoroWidget::draw);
}

void PomodoroWidget::draw()
{
  WString title(tr("pomodoro.enjoyBreak"));
  title_->setText(title.arg(name_));
  RandomGuess = distrib(gen);
  images_->showImage(RandomGuess);
  statusText_->setText("");
}

void PomodoroWidget::registerGuess(char c)
{
  auto item = new Item(ItemSeq, widen("Michael"), widen("Comment! Comment!"));
  itemWidget_->addItem(item);
  ItemSeq++;
}
