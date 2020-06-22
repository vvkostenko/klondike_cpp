#pragma once

#include <iostream>
#include <memory>

#include "ISolitaireRules.h"

struct Event;

class SolitaireComponent
{
public:
    using Ptr = std::shared_ptr<SolitaireComponent>;

protected:
    ISolitaireRules::Ptr m_pSolitaire;

public:
    SolitaireComponent() = delete;

    SolitaireComponent(ISolitaireRules::Ptr pSolitaire)
        : m_pSolitaire(pSolitaire)
    {

    }

    virtual ~SolitaireComponent()
    {

    }

    void MoveCard(const Event& evt)
    {
        m_pSolitaire->Notify(*this, evt);
    }

};