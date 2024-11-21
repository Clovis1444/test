#pragma once

#include <qmargins.h>
#include <qsize.h>

namespace Settings {
constexpr int kLayoutSpacing{10};
constexpr QMargins kLayoutMargins{10, 10, 10, 10};

constexpr QSize kDefaultButtonSize{25, 25};
constexpr QSize kDefaultLineEditSize{300, kDefaultButtonSize.height()};

const QString kDefaultDateTimeFormat{"dd.MM.yy_hh:mm:ss"};

const QString kStartTimerButtonStyleSheet{
    "background-color: lightgreen; color: black"};
const QString kStopTimerButtonStyleSheet{"background-color: red; color: black"};
}  // namespace Settings
