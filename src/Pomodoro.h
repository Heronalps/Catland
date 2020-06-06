#ifndef POMODORO_H_
#define POMODORO_H_

#include <Wt/WContainerWidget.h>

#include "Session.h"

using namespace Wt;

namespace Wt {
  class WStackedWidget;
  class WAnchor;
}

class PomodoroWidget;
class HistoryWidget;
class Session;

class Pomodoro : public WContainerWidget
{
public:
  Pomodoro();

  void handleInternalPath(const std::string &internalPath);

private:
  WStackedWidget    *mainStack_;
  PomodoroWidget    *game_;
  HistoryWidget     *scores_;
  WContainerWidget  *links_;
  WAnchor           *pomodoroAnchor_;
  WAnchor           *historyAnchor_;
  WImage            *logicPic_;
  Session           session_;

  void onAuthEvent();
  void showGame();
  void showHistory();
};

#endif //POMODORO_H_
