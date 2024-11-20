#pragma once

#include <qapplication.h>
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
          line_edit_{new QLineEdit{this}},
          button_{new QPushButton{this}} {
        setLayout(layout_);
        layout_->setSpacing(0);
        layout_->setContentsMargins(0, 0, 0, 0);
        layout_->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

        layout_->addWidget(label_, 0, 0);
        layout_->addWidget(line_edit_, 1, 0);
        layout_->addWidget(button_, 1, 1);

        label_->setText("Save file as:");
        line_edit_->setFixedSize(Settings::kDefaultLineEditSize);
        line_edit_->setReadOnly(true);
        button_->setFixedSize(Settings::kDefaultButtonSize);
        button_->setIcon(
            QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton));

        setFrameShape(QFrame::Box);

        QSize frame_size{line_edit_->width() + button_->width() + 2,
                         label_->height() + line_edit_->height() + 2};
        setFixedSize(frame_size);
    }

   private:
    QGridLayout* layout_;
    QLabel* label_;
    QLineEdit* line_edit_;
    QPushButton* button_;
};
