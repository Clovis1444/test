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

class FileInput : public QFrame {
    Q_OBJECT

   public:
    explicit FileInput(QWidget* parent = nullptr)
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

        // Fill layout
        layout_->addWidget(label_, 0, 0);
        layout_->addWidget(lineEdit_, 1, 0);
        layout_->addWidget(button_, 1, 1);

        // Widgets setup
        label_->setText("Choose input file:");
        lineEdit_->setFixedSize(Settings::kDefaultLineEditSize);
        lineEdit_->setReadOnly(true);
        button_->setFixedSize(Settings::kDefaultButtonSize);
        button_->setIcon(
            QApplication::style()->standardIcon(QStyle::SP_FileIcon));

        setFrameShape(QFrame::Box);

        QSize frame_size{lineEdit_->width() + button_->width() + 2,
                         label_->height() + lineEdit_->height() + 2};
        setFixedSize(frame_size);

        // Connects
        QObject::connect(button_, &QPushButton::pressed, this,
                         &FileInput::onButtonPressed);
    }

    bool openFileDialog(const QString& file_mask) {
        const QString file_name = QFileDialog::getOpenFileName(
            this, "Select file", "",
            file_mask.isEmpty() ? "" : QString{"Files (%1)"}.arg(file_mask));

        if (!file_name.isEmpty()) {
            lineEdit_->setText(file_name);

            emit valueChanged();
        }

        return true;
    }

    QString value() const { return lineEdit_->text(); }

   signals:
    void valueChanged();
    void buttonPressed();

   private slots:
    void onButtonPressed() { emit buttonPressed(); }

   private:
    QGridLayout* layout_;
    QLabel* label_;
    QLineEdit* lineEdit_;
    QPushButton* button_;
};
