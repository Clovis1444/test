#pragma once

#include <qboxlayout.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qnamespace.h>
#include <qsizepolicy.h>
#include <qtmetamacros.h>

#include "settings.h"

class XORVariableInput : public QFrame {
    Q_OBJECT

   public:
    explicit XORVariableInput(QWidget* parent = nullptr)
        : QFrame{parent},
          layout_{new QVBoxLayout{this}},
          label_{new QLabel{this}},
          lineEdit_{new QLineEdit{this}} {
        setLayout(layout_);
        layout_->setSpacing(0);
        layout_->setContentsMargins(0, 0, 0, 0);
        layout_->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

        layout_->addWidget(label_);
        layout_->addWidget(lineEdit_);

        label_->setText("Enter an 8-byte value for XOR operation:");
        lineEdit_->setFixedSize(Settings::kDefaultLineEditSize);
        lineEdit_->setPlaceholderText("Enter an 8-byte value");

        // setFrameShape(QFrame::Box);

        QSize frame_size{lineEdit_->width() + 2,
                         label_->height() + lineEdit_->height() + 2};
        setFixedSize(frame_size);
    }

    QString value() const { return lineEdit_->text(); }

   private:
    QVBoxLayout* layout_;
    QLabel* label_;
    QLineEdit* lineEdit_;
};
