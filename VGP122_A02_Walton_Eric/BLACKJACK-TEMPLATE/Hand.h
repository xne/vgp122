#pragma once

#include "Card.h"

class Hand {
public:
    void addCard(Card* card);
    std::vector<Card*> getCards() const;

    int getValue() const;

    size_t size() const;

    void clear();

    bool canSplit() const;

private:
    std::vector<Card*> cards;
};