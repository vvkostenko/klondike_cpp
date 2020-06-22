#pragma once

#include <list>

#include "Card.h"
#include "SolitaireComponent.h"
#include "Klondike.h"

struct Event
{
    std::list<Card> Source;
    CardInfo::CardPosition posSrc;
    SolitaireComponent::Ptr Destination;
    CardInfo::CardPosition posDest;
};