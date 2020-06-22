#pragma once

#include <list>

#include "SolitaireComponent.h"
#include "Card.h"


class Stock : public SolitaireComponent
{
public:
    using Ptr = std::shared_ptr<Stock>;

private:
    std::shared_ptr<std::list<Card>> m_lHiddenCards;
    std::shared_ptr<std::list<Card>> m_lOpenCards;

public:
    Stock() = delete;

    Stock(ISolitaireRules::Ptr pSolitaire, Deck& deck)
        : SolitaireComponent(pSolitaire)
    {
        m_lOpenCards = std::make_shared<std::list<Card>>();
        m_lHiddenCards = std::make_shared<std::list<Card>>();

        auto count = deck.Count();
        for (size_t i = 0; i < count; ++i)
        {
            m_lHiddenCards->push_back(deck.Pop());
        }
    }

    void InternalMoveCard()
    {
        if(m_lHiddenCards->size() == 0)
        {
            for(auto& card : *m_lOpenCards)
            {
                card.Close();
                m_lHiddenCards->push_back(card);
            }
        
            m_lOpenCards->clear();
        }
        else
        {
            auto& card = m_lHiddenCards->front();
            card.Open();
            m_lOpenCards->push_back(card);
            m_lHiddenCards->pop_front();
        }
    }

    decltype(m_lHiddenCards) HiddenCards() const
    {
        return m_lHiddenCards;
    }

    decltype(m_lOpenCards) OpenCards() const
    {
        return m_lOpenCards;
    }

    void Pop()
    {
        m_lOpenCards->pop_back();
    }
};