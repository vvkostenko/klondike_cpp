#include <cassert>

#include "Klondike.h"

#include "SolitaireComponent.h"
#include "Store.h"
#include "Event.h"

void Klondike::Notify(const SolitaireComponent& pSender, const Event& evt)
{
    switch (evt.posSrc)
    {
    case CardInfo::CardPosition::Field:
    {
        switch (evt.posDest)
        {
        case CardInfo::CardPosition::Field:
            _FromFieldToField(pSender, evt);
            break;

        case CardInfo::CardPosition::Store:
            _FromFieldToStore(pSender, evt);
            break;
        
        default:
            assert(false);
            break;
        }
        
        break;
    }

    case CardInfo::CardPosition::Stock:
    {
        
        switch (evt.posDest)
        {
        case CardInfo::CardPosition::Field:
            _FromStockToField(pSender, evt);
            break;

        case CardInfo::CardPosition::Store:
            _FromStockToStore(pSender, evt);
            break;
        
        default:
            assert(false);
            break;
        }
        
        break;
    }

    case CardInfo::CardPosition::Store:
    {
        switch (evt.posDest)
        {
        case CardInfo::CardPosition::Field:
            _FromStoreToField(pSender, evt);
            break;
        default:
            assert(false);
            break;
        }

        break;
    }
    default:
        assert(false);
        break;
    }   
}

void Klondike::_FromFieldToField(const SolitaireComponent& pSender, const Event& evt)
{
    auto src = dynamic_cast<Column*>(const_cast<SolitaireComponent*>(&pSender));   
    if(!src)
        return;
    
    auto dest = dynamic_cast<Column*>(evt.Destination.get());
    if(!dest)
        return;

    if(dest->GetColumn()->empty())
    {
        if(evt.Source.front().Rank() == CardInfo::CardRank::King)
        {
            for(const auto& card : evt.Source)
            {
                src->GetColumn()->pop_back();
            }

            src->OpenLast();
            dest->Accept(evt.Source);
            std::cout << "OK" << std::endl;
            return;   
        }
        else
        {
            std::cerr << "Wrong Command" << std::endl;
            return;
        }
    }

    if(_CheckMoveToField(dest, evt))
    {

        for(const auto& card : evt.Source)
        {
            src->GetColumn()->pop_back();
        }

        src->OpenLast();
        dest->Accept(evt.Source);
        std::cout << "OK" << std::endl;
    }
    else
    {
        std::cerr << "Wrong Command" << std::endl;
    }
}

void Klondike::_FromFieldToStore(const SolitaireComponent& pSender, const Event& evt)
{
    auto src = dynamic_cast<Column*>(const_cast<SolitaireComponent*>(&pSender));   
    if(!src)
    {
        std::cerr << "Wrong Command" << std::endl;
        return;
    }

    auto dest = dynamic_cast<Store*>(evt.Destination.get());
    if(!dest)
        return;

    auto srcCard = evt.Source.back();
    auto dstHeap = dest->GetHeap(srcCard.Suite());
   if ( _CheckMoveToStore(dstHeap.get(), srcCard) )
    {
        src->GetColumn()->pop_back();
        src->OpenLast();
        dest->Accept(evt.Source.back());
        std::cout << "OK" << std::endl;
    }
    else
    {
        std::cerr << "Wrong Command" << std::endl;
    }
}

void Klondike::_FromStockToField(const SolitaireComponent& pSender, const Event& evt)
{
    auto src = dynamic_cast<Stock*>(const_cast<SolitaireComponent*>(&pSender));   
    if(!src)
        return;
    
    auto dest = dynamic_cast<Column*>(evt.Destination.get());
    if(!dest)
        return;

    if(dest->GetColumn()->empty())
    {
        if(evt.Source.front().Rank() == CardInfo::CardRank::King)
        {
            src->Pop();
            dest->Accept(evt.Source);
            std::cout << "OK" << std::endl;
            return;   
        }
        else
        {
            std::cerr << "Wrong Command" << std::endl;
            return;
        }
    }

    if(_CheckMoveToField(dest, evt))
    {
        src->Pop();
        dest->Accept(evt.Source);
        std::cout << "OK" << std::endl;
    }
    else
    {
        std::cerr << "Wrong Command" << std::endl;
    }
}

void Klondike::_FromStockToStore(const SolitaireComponent& pSender, const Event& evt)
{
    auto src = dynamic_cast<Stock*>(const_cast<SolitaireComponent*>(&pSender));   
    if(!src)
    {
        std::cerr << "Wrong Command" << std::endl;
        return;
    }
    
    auto dest = dynamic_cast<Store*>(evt.Destination.get());
    if(!dest)
        return;
    
    auto srcCard = evt.Source.back();
    auto dstHeap = dest->GetHeap(srcCard.Suite());
    if ( _CheckMoveToStore(dstHeap.get(), srcCard) )
    {
        src->Pop();
        dest->Accept(evt.Source.back());
        std::cout << "OK" << std::endl;
    }
    else
    {
        std::cerr << "Wrong Command" << std::endl;
    }
}

void Klondike::_FromStoreToField(const SolitaireComponent& pSender, const Event& evt)
{
    auto src = dynamic_cast<Store*>(const_cast<SolitaireComponent*>(&pSender));   
    if(!src)
        return;
    
    auto dest = dynamic_cast<Column*>(evt.Destination.get());
    if(!dest)
        return;

    if(dest->GetColumn()->empty())
    {
        if(evt.Source.front().Rank() == CardInfo::CardRank::King)
        {
            src->GetHeap(evt.Source.front().Suite())->pop_back();
            dest->Accept(evt.Source);
            std::cout << "OK" << std::endl;
            return;   
        }
        else
        {
            std::cerr << "Wrong Command" << std::endl;
            return;
        }
    }

    if(_CheckMoveToField(dest, evt))
    {
        src->GetHeap(evt.Source.front().Suite())->pop_back();
        dest->Accept(evt.Source);
        std::cout << "OK" << std::endl;
    }
    else
    {
        std::cerr << "Wrong Command" << std::endl;
    }
}

bool Klondike::_CheckMoveToField(const Column* dest, const Event& evt) const
{
    return (dest->GetColumn()->back().Color() != evt.Source.front().Color()
            && dest->GetColumn()->back().Rank() == CardInfo::CardRank(uint8_t(evt.Source.front().Rank()) + 1));
}

bool Klondike::_CheckMoveToStore(const std::list<Card>* dstHeap, const Card& srcCard) const
{
    return (dstHeap->empty() && srcCard.Rank() == CardInfo::CardRank::Ace ) 
            || ( !dstHeap->empty() && dstHeap->back().Rank() == CardInfo::CardRank(uint8_t(srcCard.Rank()) - 1));
}