/*
 * Copyright (C) 2011 Emweb bv, Herent, Belgium
 *
 * See the LICENSE file for terms of use.
 */

#include <Wt/WAnchor.h>
#include <Wt/WText.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WApplication.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/RegistrationModel.h>

#include "Pomodoro.h"
#include "PomodoroWidget.h"
#include "HistoryWidget.h"

Pomodoro::Pomodoro():
  WContainerWidget(),
  game_(0),
  scores_(0)
{
  session_.login().changed().connect(this, &Pomodoro::onAuthEvent);

  std::unique_ptr<Auth::AuthModel> authModel
      = cpp14::make_unique<Auth::AuthModel>(Session::auth(), session_.users());
  authModel->addPasswordAuth(&Session::passwordAuth());
  authModel->addOAuth(Session::oAuth());

  std::unique_ptr<Auth::AuthWidget> authWidget
      = cpp14::make_unique<Auth::AuthWidget>(session_.login());
  auto authWidgetPtr = authWidget.get();
  authWidget->setModel(std::move(authModel));
  authWidget->setRegistrationEnabled(true);

  std::unique_ptr<WText> title(cpp14::make_unique<WText>("<h1>Pomodoro Lottery</h1>"));
  addWidget(std::move(title));

  addWidget(std::move(authWidget));

  mainStack_ = new WStackedWidget();
  mainStack_->setStyleClass("gamestack");
  addWidget(std::unique_ptr<WStackedWidget>(mainStack_));

  links_ = new WContainerWidget();
  links_->setStyleClass("links");
  links_->hide();
  addWidget(std::unique_ptr<WContainerWidget>(links_));

  backToGameAnchor_ = links_->addWidget(cpp14::make_unique<WAnchor>("/play", "Gaming Grounds"));
  backToGameAnchor_->setLink(WLink(LinkType::InternalPath, "/play"));

  scoresAnchor_ = links_->addWidget(cpp14::make_unique<WAnchor>("/History", "History"));
  scoresAnchor_->setLink(WLink(LinkType::InternalPath, "/history"));

  WApplication::instance()->internalPathChanged()
    .connect(this, &Pomodoro::handleInternalPath);

  authWidgetPtr->processEnvironment();
}

void Pomodoro::onAuthEvent()
{
  if (session_.login().loggedIn()) {  
    links_->show();
    handleInternalPath(WApplication::instance()->internalPath());
  } else {
    mainStack_->clear();
    game_ = 0;
    scores_ = 0;
    links_->hide();
  }
}

void Pomodoro::handleInternalPath(const std::string &internalPath)
{
  if (session_.login().loggedIn()) {
    if (internalPath == "/play")
      showGame();
    else if (internalPath == "/history")
      showHistory();
    else
      WApplication::instance()->setInternalPath("/play",  true);
  }
}

void Pomodoro::showHistory()
{
  if (!scores_)
    scores_ = mainStack_->addWidget(cpp14::make_unique<HistoryWidget>(&session_));

  mainStack_->setCurrentWidget(scores_);
  scores_->update();

  backToGameAnchor_->removeStyleClass("selected-link");
  scoresAnchor_->addStyleClass("selected-link");
}

void Pomodoro::showGame()
{
  if (!game_) {
    game_ = mainStack_->addWidget(cpp14::make_unique<PomodoroWidget>(session_.userName()));
    game_->scoreUpdated().connect(std::bind(&Session::addToScore,&session_,std::placeholders::_1));
  }

  mainStack_->setCurrentWidget(game_);

  backToGameAnchor_->addStyleClass("selected-link");
  scoresAnchor_->removeStyleClass("selected-link");
}
