#pragma once

#include "CardInfo.h"

class Card
{
private: 
    CardInfo::CardType m_cardType;
    bool m_isClosed;

public:
    Card() = delete;

    Card(CardInfo::CardType type) 
        : m_cardType(type)
        , m_isClosed(true)
    {
        
    }

    void Open()
    {
        m_isClosed = false;
    }

    void Close()
    {
        m_isClosed = true;
    }
    
    bool IsClosed() const
    {
        return m_isClosed;
    }

    CardInfo::CardType Type() const
    {
        return m_cardType;
    }

    CardInfo::CardSuite Suite() const
    {
        return CardInfo::CardSuite(uint8_t(m_cardType) / uint8_t(CardInfo::CardRank::Count));
    }

    CardInfo::CardRank Rank() const
    {
        return CardInfo::CardRank(uint8_t(m_cardType) % uint8_t(CardInfo::CardRank::Count));
    }

    CardInfo::CardColor Color() const
    {
        return CardInfo::CardColor(uint8_t(m_cardType) / (uint8_t(CardInfo::CardType::Count) / 2));
    }
};