#pragma once

#include <vector>
#include <algorithm>
#include <random>

#include "Card.h"

class Deck
{
    std::vector<Card> m_vCards;

public:
    Deck()
    {
        uint8_t cardsCount = uint8_t(CardInfo::CardType::Count);

        m_vCards.reserve(cardsCount);

        for (uint8_t i = 0; i < cardsCount; ++i)
            m_vCards.push_back(Card(CardInfo::CardType(i)));

    }

    void Shuffle()
    {
        std::random_device rd;
        std::mt19937 generator(rd());

        std::shuffle(m_vCards.begin(), m_vCards.end(), generator);
    }

    Card Pop()
    {
        auto res = m_vCards.front();
        m_vCards.erase(m_vCards.begin());
        return res;
    }

    size_t Count() const
    {
        return m_vCards.size();
    }
};