#pragma once

#include <qboxlayout.h>
#include <qframe.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <qsizepolicy.h>
#include <qspinbox.h>
#include <qtmetamacros.h>

class TimerDurationInput : public QFrame {
    Q_OBJECT

   public:
    explicit TimerDurationInput(QWidget* parent = nullptr)
        : QFrame{parent},
          layout_{new QVBoxLayout{this}},
          label_{new QLabel{this}},
          spin_box_{new QDoubleSpinBox{this}} {
        setLayout(layout_);
        layout_->setSpacing(0);
        layout_->setContentsMargins(0, 0, 0, 0);
        layout_->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

        layout_->addWidget(label_);
        layout_->addWidget(spin_box_);

        label_->setText("Timer duration(seconds):");

        // Note: max limit is 100 days(1 day is 86400 seconds)
        spin_box_->setMaximum(8640000);
    }

   private:
    QVBoxLayout* layout_;
    QLabel* label_;
    QDoubleSpinBox* spin_box_;
};
