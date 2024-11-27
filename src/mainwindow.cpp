#include "mainwindow.h"

#include <qcheckbox.h>
#include <qdatetime.h>
#include <qgridlayout.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qtimer.h>
#include <qtypes.h>

#include "./ui_mainwindow.h"
#include "fileMaskInput.h"
#include "overwriteOptionsInput.h"
#include "settings.h"
#include "timerDurationInput.h"
#include "xorVariableInput.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////PUBLIC////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent},
      ui_{new Ui::MainWindow{}},
      layout_{new QGridLayout{ui_->centralWidget_}},
      fileMaskInput_{new FileMaskInput{this}},
      xorVariableInput_{new XORVariableInput{this}},
      timerDurationInput_{new TimerDurationInput{this}},
      overwriteOptionsInput_{new OverwriteOptionsInput{this}},
      deleteCheckBox_{new QCheckBox{"Delete input file? ", this}},
      fileInput_{new FileInput{this}},
      saveFileInput_{new SaveFileInput{this}},
      startButton_{new QPushButton{"Start"}},
      startTimerButton_{new QPushButton{"Start timer"}},
      logWidget_{new QTextBrowser{this}},
      timer_{new QTimer{this}} {
    ui_->setupUi(this);

    // Layout
    ui_->centralWidget_->setLayout(layout_);
    layout_->setSpacing(Settings::kLayoutSpacing);
    layout_->setContentsMargins(Settings::kLayoutMargins);

    layout_->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

    // Fill layout
    layout_->addWidget(fileMaskInput_, 1, 1);
    layout_->addWidget(xorVariableInput_, 1, 2);
    layout_->addWidget(timerDurationInput_, 2, 1);
    layout_->setAlignment(timerDurationInput_, Qt::AlignLeft);
    layout_->addWidget(overwriteOptionsInput_, 2, 2);
    layout_->addWidget(deleteCheckBox_, 3, 1);
    layout_->addWidget(fileInput_, 4, 1);
    layout_->addWidget(saveFileInput_, 4, 2);
    layout_->addWidget(startButton_, 5, 1);
    layout_->addWidget(startTimerButton_, 5, 2);
    layout_->addWidget(logWidget_, 6, 1, 1, 2);

    // Widgets setup
    startButton_->setFixedHeight(Settings::kDefaultButtonSize.height());
    startTimerButton_->setFixedHeight(Settings::kDefaultButtonSize.height());
    startTimerButton_->setStyleSheet(Settings::kStartTimerButtonStyleSheet);

    logWidget_->setFixedWidth(fileInput_->width() + saveFileInput_->width() +
                              layout_->spacing());

    // Connects
    QObject::connect(fileInput_, &FileInput::buttonPressed, this,
                     &MainWindow::onFileInputButtonPressed);
    QObject::connect(fileInput_, &FileInput::valueChanged, this,
                     &MainWindow::onFileInputValueChanged);
    QObject::connect(saveFileInput_, &SaveFileInput::valueChanged, this,
                     &MainWindow::onSaveFileInputValueChanged);
    QObject::connect(startButton_, &QPushButton::pressed, this,
                     &MainWindow::onStartButtonPressed);
    QObject::connect(startTimerButton_, &QPushButton::pressed, this,
                     &MainWindow::onStartTimerButtonPressed);

    QObject::connect(timer_, &QTimer::timeout, this,
                     &MainWindow::onTimerTimeout);
}

MainWindow::~MainWindow() { delete ui_; }

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////PRIVATE SLOTS//////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void MainWindow::onFileInputButtonPressed() {
    fileInput_->openFileDialog(getFileMask());
}

void MainWindow::onFileInputValueChanged() {
    logWidget_->insertPlainText(currentTime());
    logWidget_->insertPlainText(" Change input file to: ");
    logWidget_->insertPlainText(getInputFile());

    logWidget_->insertPlainText("\n");
}
void MainWindow::onSaveFileInputValueChanged() {
    logWidget_->insertPlainText(currentTime());
    logWidget_->insertPlainText(" Change output file to: ");
    logWidget_->insertPlainText(getOutputFile());

    logWidget_->insertPlainText("\n");
}

void MainWindow::onStartButtonPressed() {
    QByteArray file_content{};

    if (!getFileContent(file_content)) {
        return;
    };

    doWork(file_content);

    if (!saveFile(file_content)) {
        return;
    };

    deleteInputFile();
}
void MainWindow::onStartTimerButtonPressed() {
    // If timer is on
    if (timer_->isActive()) {
        startTimerButton_->setText("Start timer");
        startTimerButton_->setStyleSheet(Settings::kStartTimerButtonStyleSheet);

        timer_->stop();

        logWidget_->insertPlainText(currentTime());
        logWidget_->insertPlainText(QString{" Stop timer"});

        logWidget_->insertPlainText("\n");
    }
    // If timer is off
    else {
        if (getTimerDuration() == 0) {
            logWidget_->insertPlainText(currentTime());
            logWidget_->insertPlainText(
                " Failed to start timer: timer duration must be set");

            logWidget_->insertPlainText("\n");

            return;
        }

        startTimerButton_->setText(
            QString{"Stop timer(%1 seconds)"}.arg(getTimerDuration()));
        startTimerButton_->setStyleSheet(Settings::kStopTimerButtonStyleSheet);

        timer_->start(getTimerDuration() * 1000);

        logWidget_->insertPlainText(currentTime());
        logWidget_->insertPlainText(
            QString{" Start timer with %1 seconds interval"}.arg(
                getTimerDuration()));

        logWidget_->insertPlainText("\n");
    }
}

void MainWindow::onTimerTimeout() {
    QByteArray file_content{};

    if (!getFileContent(file_content)) {
        return;
    };

    doWork(file_content);

    if (!saveFile(file_content)) {
        return;
    };

    deleteInputFile();
};

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////PRIVATE////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QString MainWindow::currentTime() {
    QString time{QDateTime::currentDateTime().toString(
        Settings::kDefaultDateTimeFormat)};
    time.push_front('[');
    time.push_back(']');

    return time;
}

bool MainWindow::isDeleteToggled() const {
    return deleteCheckBox_->isChecked();
}
QString MainWindow::getFileMask() const { return fileMaskInput_->value(); };
QString MainWindow::getInputFile() const { return fileInput_->value(); };
QString MainWindow::getOutputFile() const { return saveFileInput_->value(); };
int MainWindow::getTimerDuration() const {
    return timerDurationInput_->value();
};
QByteArray MainWindow::getXORVariableValue() const {
    QString text{xorVariableInput_->value()};

    QByteArray val{text.toUtf8()};
    val = QByteArray::fromHex(val);

    // If less than 8 bytes
    if (val.size() < 8) {
        val.resize(8, 0);
    }

    // If More than 8 bytes
    val = val.first(8);

    return val;
};

OverwriteOptionsInput::Option MainWindow::overwriteOption() const {
    return overwriteOptionsInput_->currentOption();
};

bool MainWindow::getFileContent(QByteArray& content_buffer) const {
    QFile file{getInputFile()};

    // Return false if file does not exists
    if (file.isOpen()) {
        logWidget_->insertPlainText(currentTime());
        logWidget_->insertPlainText(" Error: input file \"");
        logWidget_->insertPlainText(getInputFile());
        logWidget_->insertPlainText("\" is already opened");

        return false;
    }

    // Return false if failed to open a file
    if (!file.open(QIODevice::ReadOnly)) {
        logWidget_->insertPlainText(currentTime());
        logWidget_->insertPlainText(" Error: ");
        logWidget_->insertPlainText(file.errorString());
        logWidget_->insertPlainText("\n");

        return false;
    }

    // Get file content
    content_buffer = file.readAll();
    file.close();

    return true;
};
void MainWindow::doWork(QByteArray& file_content) const {
    QByteArray key{getXORVariableValue()};

    for (qsizetype i{}; i < file_content.size(); ++i) {
        file_content[i] = file_content[i] ^ key[i % key.size()];
    }
};
bool MainWindow::saveFile(const QByteArray& file_content) {
    QFile file{getOutputFile()};

    // Return false if file is already open
    if (file.isOpen()) {
        logWidget_->insertPlainText(currentTime());
        logWidget_->insertPlainText(" Error: output file \"");
        logWidget_->insertPlainText(getOutputFile());
        logWidget_->insertPlainText("\" is already opened");

        return false;
    }

    if (file.exists()) {
        switch (overwriteOption()) {
            case OverwriteOptionsInput::kNewFile:
                file.setFileName(getNewFilePath(getOutputFile()));
                break;
            case OverwriteOptionsInput::kOverwrite:
            case OverwriteOptionsInput::kEnumLength:
                break;
        }
    }

    // Return false if failed to open file
    if (!file.open(QIODevice::WriteOnly)) {
        logWidget_->insertPlainText(currentTime());
        logWidget_->insertPlainText(" Error: ");
        logWidget_->insertPlainText(file.errorString());
        logWidget_->insertPlainText("\n");

        return false;
    }

    // Write content to file
    file.write(file_content);
    file.close();

    logWidget_->insertPlainText(currentTime());
    logWidget_->insertPlainText(" File \"");
    logWidget_->insertPlainText(getInputFile());
    logWidget_->insertPlainText("\" was successfully modified and saved as \"");
    logWidget_->insertPlainText(file.fileName());
    logWidget_->insertPlainText("\"\n");

    return true;
};
void MainWindow::deleteInputFile() {
    if (!isDeleteToggled() ||
        overwriteOption() == OverwriteOptionsInput::kOverwrite) {
        return;
    }

    QFile file{getInputFile()};

    if (!file.remove()) {
        logWidget_->insertPlainText(currentTime());
        logWidget_->insertPlainText(" Failed to delete input file: ");
        logWidget_->insertPlainText(file.errorString());
        logWidget_->insertPlainText("\n");

        return;
    }

    logWidget_->insertPlainText(currentTime());
    logWidget_->insertPlainText(" Input file \"");
    logWidget_->insertPlainText(file.fileName());
    logWidget_->insertPlainText("\" was successfully deleted\n");
};

QString MainWindow::getNewFilePath(const QString& file_name) {
    QFile file{file_name};

    QString file_path{QFileInfo{file}.absolutePath()};
    QString file_without_ext{QFileInfo{file}.baseName()};
    QString file_ext{QFileInfo{file}.completeSuffix()};

    QString file_name_tmplt{file_path + '/' + file_without_ext + "(%1)." +
                            file_ext};

    int count{1};

    while (QFile{file_name_tmplt.arg(count)}.exists()) {
        ++count;
    }

    return file_name_tmplt.arg(count);
};
