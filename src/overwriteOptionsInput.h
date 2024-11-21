#pragma once

#include <qboxlayout.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <qsizepolicy.h>
#include <qtmetamacros.h>

#include "settings.h"

class OverwriteOptionsInput : public QFrame {
    Q_OBJECT

   public:
    explicit OverwriteOptionsInput(QWidget* parent = nullptr)
        : QFrame{parent},
          layout_{new QVBoxLayout{this}},
          label_{new QLabel{this}},
          comboBox_{new QComboBox{this}} {
        setLayout(layout_);
        layout_->setSpacing(0);
        layout_->setContentsMargins(0, 0, 0, 0);
        layout_->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

        layout_->addWidget(label_);
        layout_->addWidget(comboBox_);

        label_->setText("Choose overwrite option: ");
        comboBox_->setFixedSize(Settings::kDefaultLineEditSize);

        // Improtant: all items in comboBox_ must be listed in Option enum
        comboBox_->addItem("Overwrite");
        comboBox_->addItem("Create new file");

        // setFrameShape(QFrame::Box);

        QSize frame_size{comboBox_->width() + 2,
                         label_->height() + comboBox_->height() + 2};
        setFixedSize(frame_size);
    }

    // Improtant: all items in comboBox_ must be listed here
    enum Option {
        kOverwrite,
        kNewFile,
        // Insert new entries here
        kEnumLength
    };

    Option currentOption() const {
        return static_cast<Option>(comboBox_->currentIndex());
    }
    QString optionText(Option opt) const { return comboBox_->itemText(opt); }
    QString currentText() const { return comboBox_->currentText(); }

   private:
    QVBoxLayout* layout_;
    QLabel* label_;
    QComboBox* comboBox_;
};
