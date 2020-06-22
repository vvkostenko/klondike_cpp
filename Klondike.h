#pragma once

#include <memory>

#include "ISolitaireRules.h"
#include "Column.h"
#include "Store.h"
#include "Stock.h"

class Klondike : public ISolitaireRules
{
public:
    using Ptr = std::shared_ptr<Klondike>;

    using Field = std::vector<Column::Ptr>;
    using FieldPtr = std::shared_ptr<Field>;

    static const size_t ColumnsCount = 7;

private:
    bool m_isInitialised;

    FieldPtr m_pColumns;
    Stock::Ptr m_pStock;
    Store::Ptr m_pStore;

    void _FromFieldToField(const SolitaireComponent& pSender, const Event& evt);
    void _FromFieldToStore(const SolitaireComponent& pSender, const Event& evt);

    void _FromStockToField(const SolitaireComponent& pSender, const Event& evt);
    void _FromStockToStore(const SolitaireComponent& pSender, const Event& evt);

    void _FromStoreToField(const SolitaireComponent& pSender, const Event& evt);

    bool _CheckMoveToField(const Column* dest, const Event& evt) const;
    bool _CheckMoveToStore(const std::list<Card>* dstHeap, const Card& srcCard) const;

public:
    Klondike()
        : m_isInitialised(false)
    {
        std::cout << "Klondike!" << std::endl;
    }

    void Init(const FieldPtr columns, const Stock::Ptr stock, const Store::Ptr store)
    {
        m_pColumns = columns;
        m_pStock = stock;
        m_pStore = store;

        m_isInitialised = true;
    }

    bool CheckEndGame()
    {
        size_t nCardsInStore = 0;
        for(size_t i = 0; i < size_t(CardInfo::CardSuite::Count); ++i)
            nCardsInStore += m_pStore->HeapSize(CardInfo::CardSuite(i));
        
        return nCardsInStore == size_t(CardInfo::CardType::Count);
    }

    // ISolitaireRules
    virtual void Notify(const SolitaireComponent& pSender, const Event& evt) override;
};