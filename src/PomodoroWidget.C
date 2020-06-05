#include "PomodoroWidget.h"

#include <Wt/WBreak.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WAny.h>

#include "Session.h"
#include "Dictionary.h"
#include "WordWidget.h"
#include "ImagesWidget.h"
#include "LettersWidget.h"

using namespace Wt;

namespace {
  const int MaxGuesses = 9;
}

PomodoroWidget::PomodoroWidget(const std::string &name)
  : WContainerWidget(),
    name_(name),
    badGuesses_(0)
{
  setContentAlignment(AlignmentFlag::Center);
  
  title_ = addWidget(cpp14::make_unique<WText>(tr("pomodoro.readyToPlay")));

  word_ = addWidget(cpp14::make_unique<WordWidget>());
  statusText_ = addWidget(cpp14::make_unique<WText>());
  images_ = addWidget(cpp14::make_unique<ImagesWidget>(MaxGuesses));

  letters_ = addWidget(cpp14::make_unique<LettersWidget>());
  letters_->letterPushed().connect(this, &PomodoroWidget::registerGuess);

  language_ = addWidget(cpp14::make_unique<WComboBox>());
  language_->addItem(tr("pomodoro.englishWords").arg(18957));
  language_->addItem(tr("pomodoro.dutchWords").arg(1688));

  addWidget(cpp14::make_unique<WBreak>());

  newGameButton_ = addWidget(cpp14::make_unique<WPushButton>(tr("pomodoro.newGame")));
  newGameButton_->clicked().connect(this, &PomodoroWidget::newGame);

  letters_->hide();
}

void PomodoroWidget::newGame()
{
  WString title(tr("Pomodoro.guessTheWord"));
  title_->setText(title.arg(name_));

  language_->hide();
  newGameButton_->hide();

  /*
   * Choose a new secret word and reset the game
   */
  Dictionary dictionary = (Dictionary) language_->currentIndex();
  word_->init(RandomWord(dictionary));
  letters_->reset();
  badGuesses_ = 0;
  images_->showImage(badGuesses_);
  statusText_->setText("");
}

void PomodoroWidget::registerGuess(char c)
{
  if (badGuesses_ < MaxGuesses) {
    bool correct = word_->guess(c);

    if (!correct) {
      ++badGuesses_;
      images_->showImage(badGuesses_);
    }
  }

  if (badGuesses_ == MaxGuesses) {
    WString status = tr("Pomodoro.youHang");
    statusText_->setText(status.arg(word_->word()));

    letters_->hide();
    language_->show();
    newGameButton_->show();

    scoreUpdated_.emit(-10);
  } else if (word_->won()) {
    statusText_->setText(tr("Pomodoro.youWin"));
    images_->showImage(ImagesWidget::HURRAY);

    letters_->hide();
    language_->show();
    newGameButton_->show();

    scoreUpdated_.emit(20 - badGuesses_);
  }
}
