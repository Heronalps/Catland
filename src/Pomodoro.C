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
  pomodoro_(0),
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

  title_ = addWidget(std::move(cpp14::make_unique<WText>("<h1>Catland</h1>")));

  logicPic_ = addWidget(std::move(cpp14::make_unique<WImage>("icons/login.png")));
  logicPic_->setStyleClass("front");

  addWidget(std::move(authWidget));

  mainStack_ = new WStackedWidget();
  mainStack_->setStyleClass("mainstack");
  addWidget(std::unique_ptr<WStackedWidget>(mainStack_));

  links_ = new WContainerWidget();
  links_->setStyleClass("links");
  links_->hide();
  addWidget(std::unique_ptr<WContainerWidget>(links_));

  WApplication::instance()->internalPathChanged()
    .connect(this, &Pomodoro::handleInternalPath);

  authWidgetPtr->processEnvironment();
}

void Pomodoro::onAuthEvent()
{
  if (session_.login().loggedIn()) {  
    logicPic_->hide();
    title_->hide();
    handleInternalPath(WApplication::instance()->internalPath());
  } else {
    mainStack_->clear();
    links_->hide();
    logicPic_->show();
    title_->show();
  }
}

void Pomodoro::handleInternalPath(const std::string &internalPath)
{
  if (session_.login().loggedIn()) {
    if (internalPath == "/pomodoro")
      showPomodoro();
    else if (internalPath == "/history")
      showHistory();
    else
      WApplication::instance()->setInternalPath("/pomodoro",  true);
  }
}

void Pomodoro::showHistory()
{
  if (!scores_)
    scores_ = mainStack_->addWidget(cpp14::make_unique<HistoryWidget>(&session_));

  mainStack_->setCurrentWidget(scores_);
  scores_->update();

  pomodoroAnchor_->removeStyleClass("selected-link");
  historyAnchor_->addStyleClass("selected-link");
}

void Pomodoro::showPomodoro()
{
  if (!pomodoro_) {
    pomodoro_ = mainStack_->addWidget(cpp14::make_unique<PomodoroWidget>(session_.userName()));
    pomodoro_->scoreUpdated().connect(std::bind(&Session::addToScore,&session_,std::placeholders::_1));
  }

  mainStack_->setCurrentWidget(pomodoro_);
}
