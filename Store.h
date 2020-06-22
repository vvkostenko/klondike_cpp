#pragma once

#include <array>

#include "SolitaireComponent.h"
#include "Card.h"

class Store : public SolitaireComponent
{
public:
    using Ptr = std::shared_ptr<Store>;

private:
    std::array<std::shared_ptr<std::list<Card>>, size_t(CardInfo::CardSuite::Count)> m_aCards;

public:
    Store() = delete;

    Store(ISolitaireRules::Ptr pSolitaire)
        : SolitaireComponent(pSolitaire)
    {
        for(auto& cards : m_aCards)
            cards = std::make_shared<std::list<Card>>();
    }

    void Accept(const Card& card)
    {
        m_aCards[size_t(card.Suite())]->push_back(card);
    }

    std::shared_ptr<std::list<Card>> GetHeap(const CardInfo::CardSuite heapSuite) const
    {
        return m_aCards[size_t(heapSuite)];
    }

    size_t HeapSize(const CardInfo::CardSuite heapSuite) const
    {
        return m_aCards[size_t(heapSuite)]->size();
    }

    decltype(m_aCards) GetStore() const
    {
        return m_aCards;
    }
    
};