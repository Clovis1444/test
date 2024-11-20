#pragma once

#include <qboxlayout.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qnamespace.h>
#include <qsizepolicy.h>
#include <qtmetamacros.h>

#include "settings.h"

class FileMaskInput : public QFrame {
    Q_OBJECT

   public:
    explicit FileMaskInput(QWidget* parent = nullptr)
        : QFrame{parent},
          layout_{new QVBoxLayout{this}},
          label_{new QLabel{this}},
          line_edit_{new QLineEdit{this}} {
        setLayout(layout_);
        layout_->setSpacing(0);
        layout_->setContentsMargins(0, 0, 0, 0);
        layout_->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

        layout_->addWidget(label_);
        layout_->addWidget(line_edit_);

        label_->setText("Enter file mask:");
        line_edit_->setFixedSize(Settings::kDefaultLineEditSize);

        setFrameShape(QFrame::Box);

        QSize frame_size{line_edit_->width() + 2,
                         label_->height() + line_edit_->height() + 2};
        setFixedSize(frame_size);
    }

   private:
    QVBoxLayout* layout_;
    QLabel* label_;
    QLineEdit* line_edit_;
};
