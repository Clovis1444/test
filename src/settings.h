#pragma once

#include <qmargins.h>
#include <qsize.h>

namespace Settings {
constexpr int kLayoutSpacing{10};
constexpr QMargins kLayoutMargins{10, 10, 10, 10};

constexpr QSize kDefaultButtonSize{25, 25};
constexpr QSize kDefaultLineEditSize{300, kDefaultButtonSize.height()};
}  // namespace Settings
