#ifndef POMODORO_WIDGET_H_
#define POMODORO_WIDGET_H_

#include <vector>

#include <Wt/WContainerWidget.h>

class Session;
class ItemWidget;
class ImagesWidget;
class LettersWidget;

class PomodoroWidget: public Wt::WContainerWidget
{
public:
  PomodoroWidget(const std::string &name);

  Wt::Signal<int>& scoreUpdated() { return scoreUpdated_; }
  
private:
  Wt::WText                 *title_;

  ItemWidget                *itemWidget_;
  ImagesWidget              *images_;
  LettersWidget             *letters_;

  Wt::WText                 *statusText_;
  Wt::WComboBox             *language_;
  Wt::WPushButton           *newGameButton_;

  Wt::Signal<int>            scoreUpdated_;

  std::string                name_;

  int                        badGuesses_;
  
  void registerGuess(char c);

  void newGame();
};

#endif //POMODORO_WIDGET_H_
