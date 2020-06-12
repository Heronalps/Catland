#include "PomodoroWidget.h"

#include <Wt/WBreak.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WAny.h>
#include <Wt/WStringUtil.h>

#include "Session.h"
#include "ItemWidget.h"
#include "ImagesWidget.h"
#include "LettersWidget.h"
#include "Item.h"

using namespace Wt;

namespace {
  static int RandomGuess = 0;
  const int PicNumber = 25;
  static int ItemSeq = 1;

  static std::vector<std::string> itemMap({"Aerobics", "Benching", "Cartoon", "Dance", "Eat", "Family Game", 
  "Video Game", "Hacker News", "Ice Breaker", "Juggling", "Karaoke", "Laugh", "Music", "Netflix", 
  "Occulus", "Play instrument", "Barbeque", "Run a mile", "Snacks", "Tik Tok", "Find UFO", "TV", "Walk", 
  "Crossfit", "Dash a yard", "Zoom Call a friend"});
  
  static std::vector<std::string> commentMap({"Burn those calories!", "Become a monster!", 
  "Invoke your inner kid", "You don't need wings to fly!", "What else could be better?", 
  "Family always comes first!", "Your best friend in quarantine.", "YCombinator rocks!", 
  "Don't be shy to make new friends!", "We all juggle in our daily lives!", "Sing your soul out!", 
  "You don't care laugh line!", "Country or Rap?", "Time to binge-watching!", "Immerse into VR.", 
  "Guitar or piano makes you chill!", "Get yourself somking hot!", "Can you finish in 8 mins?", 
  "Watch your waistline, please!", "Who needs Instagram?", "The truth is out there!", 
  "Being old-school is cool!", "Enjoy gorgeous sunset!", "Things don't kill you make you stronger!", 
  "That feels like \"the longest yard!\"", "Stay connected and engaged!"});

  std::vector<int> selectedItem{};
}

PomodoroWidget::PomodoroWidget(const std::string &name)
  : WContainerWidget(),
    name_(name),
    badGuesses_(0)
{
  setContentAlignment(AlignmentFlag::Center);
  
  title_ = addWidget(cpp14::make_unique<WText>(tr("pomodoro.lottery")));

  itemWidget_ = addWidget(cpp14::make_unique<ItemWidget>());
  addWidget(cpp14::make_unique<WBreak>());
  statusText_ = addWidget(cpp14::make_unique<WText>());
  statusText_->addStyleClass("status");

  images_ = addWidget(cpp14::make_unique<ImagesWidget>(PicNumber));

  letters_ = addWidget(cpp14::make_unique<LettersWidget>());
  letters_->letterPushed().connect(this, &PomodoroWidget::registerGuess);

  addWidget(cpp14::make_unique<WBreak>());

  feelingLuckyButton_ = addWidget(cpp14::make_unique<WPushButton>(tr("pomodoro.feelingLucky")));
  feelingLuckyButton_->clicked().connect(this, &PomodoroWidget::draw);
}

void PomodoroWidget::draw()
{
  if (selectedItem.empty()) {
    return;
  }
  WString title(tr("pomodoro.enjoyBreak"));
  title_->setText(title.arg(name_));

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, selectedItem.size() - 1);
  
  RandomGuess = distrib(gen);
  images_->showImage(selectedItem[RandomGuess]);
  statusText_->setText(itemMap[selectedItem[RandomGuess]] + " - " + commentMap[selectedItem[RandomGuess]]);
  letters_->reset();
  selectedItem.clear();
  itemWidget_->clearTable();
  ItemSeq = 1;
}

void PomodoroWidget::registerGuess(char c)
{
  WString title(tr("pomodoro.lottery"));
  title_->setText(title.arg(name_));

  selectedItem.push_back(c - 'A');
  auto item = new Item(ItemSeq, widen(itemMap[c - 'A']), widen(commentMap[c - 'A']));
  itemWidget_->addItem(item);
  ItemSeq++;
}
