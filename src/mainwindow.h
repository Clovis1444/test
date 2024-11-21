#pragma once

#include <qcheckbox.h>
#include <qgridlayout.h>
#include <qobjectdefs.h>
#include <qpushbutton.h>
#include <qtextbrowser.h>

#include <QDoubleSpinBox>
#include <QMainWindow>

#include "fileInput.h"
#include "fileMaskInput.h"
#include "overwriteOptionsInput.h"
#include "saveFileInput.h"
#include "timerDurationInput.h"
#include "xorVariableInput.h"

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

   private slots:
    void onFileInputButtonPressed();
    void onFileInputValueChanged();
    void onSaveFileInputValueChanged();

    void onStartButtonPressed();
    void onStartTimerButtonPressed();

    void onTimerTimeout();

   private:
    static QString currentTime();

    bool isDeleteToggled() const;
    QString getFileMask() const;
    QString getInputFile() const;
    QString getOutputFile() const;
    int getTimerDuration() const;
    QByteArray getXORVariableValue() const;
    OverwriteOptionsInput::Option overwriteOption() const;

    bool getFileContent(QByteArray &content_buffer) const;
    void doWork(QByteArray &file_content) const;
    bool saveFile(const QByteArray &file_content);
    void deleteInputFile();

    static QString getNewFilePath(const QString &file_name);

    Ui::MainWindow *ui_;

    QGridLayout *layout_;

    FileMaskInput *fileMaskInput_;
    XORVariableInput *xorVariableInput_;
    TimerDurationInput *timerDurationInput_;
    OverwriteOptionsInput *overwriteOptionsInput_;
    QCheckBox *deleteCheckBox_;

    FileInput *fileInput_;
    SaveFileInput *saveFileInput_;

    QPushButton *startButton_;
    QPushButton *startTimerButton_;

    QTextBrowser *logWidget_;

    QTimer *timer_;
};
