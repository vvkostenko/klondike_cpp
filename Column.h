#pragma once

#include <list>
#include <memory>

#include "Deck.h"
#include "Card.h"
#include "SolitaireComponent.h"

class Column : public SolitaireComponent
{
public:
    using Ptr = std::shared_ptr<Column>;

private:
    std::shared_ptr<std::list<Card>> m_lCards;

public:
    Column() = delete;

    Column(ISolitaireRules::Ptr pSolitaire, Deck& deck, size_t cardsCnt)
        : SolitaireComponent(pSolitaire)
    {
        m_lCards = std::make_shared<std::list<Card>>();
        for (size_t i = 0; i <= cardsCnt; ++i)
        {
            m_lCards->push_back(deck.Pop());
        }
    }

    void Accept(const Card& card)
    {
        m_lCards->push_back(card);
    }

    void Accept(const std::list<Card>& cards)
    {
        m_lCards->insert(m_lCards->end(), cards.begin(), cards.end());
    }

    decltype(m_lCards) GetColumn() const
    {
        return m_lCards;
    }

    void OpenLast()
    {
        if(m_lCards->empty())
            return;

        m_lCards->back().Open();
    }
};