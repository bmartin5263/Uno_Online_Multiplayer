
//
// Created by Brandon Martin on 8/12/18.
//

#ifndef UNO_ONLINE_MULTIPLAYER_CONSTANTS_H
#define UNO_ONLINE_MULTIPLAYER_CONSTANTS_H

enum class CardColors {
    RED, GREEN, BLUE, YELLOW, WILD
};

enum class CardValues {
    ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO, SKIP, REVERSE, PLUS2, PLUS4, WILD
};

const static int MINIMUM_PLAYERS = 2;

static CardColors CARD_COLORS[4] = {CardColors::BLUE, CardColors::RED, CardColors::GREEN, CardColors::YELLOW};
static CardValues CARD_VALUES[15] = {CardValues::ONE, CardValues::TWO, CardValues::THREE, CardValues::FOUR, CardValues::FIVE,
                              CardValues::SIX, CardValues::SEVEN, CardValues::EIGHT, CardValues::NINE, CardValues::ZERO,
                              CardValues::SKIP, CardValues::REVERSE, CardValues::PLUS2, CardValues::PLUS4, CardValues::WILD};

#endif //UNO_ONLINE_MULTIPLAYER_CONSTANTS_H
