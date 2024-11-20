#include "mainwindow.h"

#include <qcheckbox.h>
#include <qgridlayout.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qspinbox.h>

#include "./ui_mainwindow.h"
#include "fileMaskInput.h"
#include "settings.h"
#include "timerDurationInput.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent},
      ui_{new Ui::MainWindow{}},
      layout_{new QGridLayout{ui_->centralWidget_}},
      fileMaskInput_{new FileMaskInput{this}},
      timerDurationInput_{new TimerDurationInput{this}},
      deleteCheckBox_{new QCheckBox{"Delete input file? ", this}},
      fileInput_{new FileInput{this}},
      saveFileInput_{new SaveFileInput{this}},
      startButton_{new QPushButton{"Start"}},
      startTimerButton_{new QPushButton{"Start timer"}},
      logWidget_{new QTextBrowser{this}} {
    ui_->setupUi(this);

    ui_->centralWidget_->setLayout(layout_);
    layout_->setSpacing(Settings::kLayoutSpacing);
    layout_->setContentsMargins(Settings::kLayoutMargins);

    layout_->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

    layout_->addWidget(fileMaskInput_, 1, 1);
    layout_->addWidget(timerDurationInput_, 2, 1);
    layout_->setAlignment(timerDurationInput_, Qt::AlignLeft);
    layout_->addWidget(deleteCheckBox_, 2, 2);
    layout_->addWidget(fileInput_, 3, 1);
    layout_->addWidget(saveFileInput_, 3, 2);
    layout_->addWidget(startButton_, 4, 1);
    layout_->addWidget(startTimerButton_, 4, 2);
    layout_->addWidget(logWidget_, 5, 1, 1, 2);

    startButton_->setFixedHeight(Settings::kDefaultButtonSize.height());
    startTimerButton_->setFixedHeight(Settings::kDefaultButtonSize.height());

    logWidget_->setFixedWidth(fileInput_->width() + saveFileInput_->width() +
                              layout_->spacing());

    for (int i{}; i < 100; ++i) {
        logWidget_->insertPlainText("Hello!\nI am here!");
    }
}

MainWindow::~MainWindow() { delete ui_; }
