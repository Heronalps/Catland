// This may look like C code, but it's really -*- C++ -*-
/* 
 * Copyright (C) 2011 Emweb bv, Herent, Belgium
 *
 * See the LICENSE file for terms of use.
 */

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
  WAnchor           *backToGameAnchor_;
  WAnchor           *scoresAnchor_;

  Session session_;

  void onAuthEvent();
  void showGame();
  void showHistory();
};

#endif //POMODORO_H_
