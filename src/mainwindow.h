#pragma once

#include <qcheckbox.h>
#include <qgridlayout.h>
#include <qpushbutton.h>
#include <qtextbrowser.h>

#include <QDoubleSpinBox>
#include <QMainWindow>

#include "fileInput.h"
#include "fileMaskInput.h"
#include "saveFileInput.h"
#include "timerDurationInput.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

   private:
    Ui::MainWindow *ui_;

    QGridLayout *layout_;

    FileMaskInput *fileMaskInput_;
    TimerDurationInput *timerDurationInput_;
    QCheckBox *deleteCheckBox_;

    FileInput *fileInput_;
    SaveFileInput *saveFileInput_;

    QPushButton *startButton_;
    QPushButton *startTimerButton_;

    QTextBrowser *logWidget_;
};
