#pragma once

#include <qapplication.h>
#include <qfiledialog.h>
#include <qframe.h>
#include <qgridlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qstyle.h>
#include <qtmetamacros.h>

#include "settings.h"

class SaveFileInput : public QFrame {
    Q_OBJECT

   public:
    explicit SaveFileInput(QWidget* parent = nullptr)
        : QFrame{parent},
          layout_{new QGridLayout{this}},
          label_{new QLabel{this}},
          lineEdit_{new QLineEdit{this}},
          button_{new QPushButton{this}} {
        // Layout
        setLayout(layout_);
        layout_->setSpacing(0);
        layout_->setContentsMargins(0, 0, 0, 0);
        layout_->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

        // Layout fill
        layout_->addWidget(label_, 0, 0);
        layout_->addWidget(lineEdit_, 1, 0);
        layout_->addWidget(button_, 1, 1);

        // Widgets setup
        label_->setText("Save file as:");
        lineEdit_->setFixedSize(Settings::kDefaultLineEditSize);
        lineEdit_->setReadOnly(true);
        button_->setFixedSize(Settings::kDefaultButtonSize);
        button_->setIcon(
            QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton));

        setFrameShape(QFrame::Box);

        QSize frame_size{lineEdit_->width() + button_->width() + 2,
                         label_->height() + lineEdit_->height() + 2};
        setFixedSize(frame_size);

        // Connects
        QObject::connect(button_, &QPushButton::pressed, this,
                         &SaveFileInput::onButtonPress);
    }

    bool openFileDialog() {
        const QString file_name{
            QFileDialog::getSaveFileName(this, "Save file as", {}, {}, nullptr,
                                         QFileDialog::DontConfirmOverwrite)};

        if (!file_name.isEmpty()) {
            lineEdit_->setText(file_name);

            emit valueChanged();
        }

        return file_name.isEmpty();
    }

    QString value() const { return lineEdit_->text(); }

   signals:
    void valueChanged();

   private slots:
    void onButtonPress() { openFileDialog(); };

   private:
    QGridLayout* layout_;
    QLabel* label_;
    QLineEdit* lineEdit_;
    QPushButton* button_;
};
