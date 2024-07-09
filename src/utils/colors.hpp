#ifndef COLORS_HPP
#define COLORS_HPP

#include <functional>
#include <raylib.h>

static const Color backgroundColorPrimary = Color{219, 219, 255, 255};
static const Color backgroundColorSecondary = Color{248, 247, 253, 255};

static const Color playerColorOutline = Color{0, 0, 0, 255};
static const Color playerColorFill = Color{255, 0, 0, 255};

static const Color enemyColorOutline = Color{0, 0, 0, 255};
static const Color enemyColorFill = Color{8, 35, 249, 255};

static const Color coinColorOutline = Color{0, 0, 0, 255};
static const Color coinColorFill = Color{255, 204, 56, 255};

static const Color wallBlockColorOutline = Color{0, 0, 0, 255};
static const Color wallBlockColorFill = Color{178, 178, 254, 255};

static const Color keyColorOutline = Color{30, 28, 28, 255};
static const Color keyColorFill = Color{161, 161, 161, 255};

static const Color keyBlockColorOutline = Color{0, 0, 0, 255};
static const Color keyBlockColorFill = Color{160, 160, 160, 255};

static const Color conveyorColorArrow = Color{100, 100, 100, 255};
static const Color conveyorColorFill = Color{164, 164, 164, 255};

static const Color checkpointColorFill = Color{164, 254, 161, 255};

static const Color buttonWidgetBorderColor = Color{70, 70, 70, 255};
static const Color buttonWidgetSelectedBorderColor = Color{70, 125, 78, 255};
static const Color buttonWidgetGradientColor1 = Color{185, 185, 186, 255};
static const Color buttonWidgetGradientColor2 = Color{107, 107, 107, 255};

static const Color textFieldWidgetBorderColor = Color{70, 70, 70, 255};
static const Color textFieldWidgetFillColor = RAYWHITE;

static const Color enumWidgetBorderColor = Color{70, 70, 70, 255};
static const Color enumWidgetFillColor = RAYWHITE;

static const Color editorUIColor = Color{245, 245, 245, 255};
static const Color editorGradient1Color = Color{75, 75, 75, 255};
static const Color editorGradient2Color = Color{124, 124, 124, 255};
static const Color editorSelectColor = Color{0, 255, 0, 80};
static const Color editorOtherLayerColor = Color{255, 255, 255, 100};

struct ColorHash {
  std::size_t operator()(const Color& color) const {
    return ((std::hash<unsigned char>()(color.r) ^
    (std::hash<unsigned char>()(color.g) << 1)) >> 1) ^
    (std::hash<unsigned char>()(color.b) << 1) ^
    (std::hash<unsigned char>()(color.a) << 1);
  }
};

struct PairColorHash {
    std::size_t operator()(const std::pair<Color, Color>& pair) const {
        auto h1 = ColorHash{}(pair.first);
        auto h2 = ColorHash{}(pair.second);
        return h1 ^ (h2 << 1);
    }
};

inline bool operator==(const Color& lhs, const Color& rhs) {
  return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}

#endif
