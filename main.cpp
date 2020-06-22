#include <cstdlib>
#include <iostream>
#include <cctype>
#include <memory>
#include <cassert>
#include <sstream>
#include <string>
#include <signal.h>

#include "ISolitaireRules.h"
#include "SolitaireComponent.h"

#include "Deck.h"
#include "Column.h"
#include "Stock.h"
#include "Store.h"
#include "Event.h"

#include "Klondike.h"


std::vector<std::string> Tokenize(const std::string& comandLine)
{
    std::istringstream inputStream(comandLine);
    auto str = std::string{};
    std::vector<std::string> commands;
    commands.reserve(2);
    while (inputStream >> str)
    {
        if(commands.size() >= 2)
        {
            std::cerr << "Commands count must be less than 2!" << std::endl;
            commands.clear();
            break;
        }

        commands.push_back(str);
    }

    return commands;
}

void DrawCardsList(const std::list<Card>& cards)
{
    if (cards.size() == 0)
    {
        std::cout << "[ ]\t";
    }
    else
    {
        if (cards.back().IsClosed())
            std::cout << "[x]\t";
        else
        {
            auto card = std::find_if(CardInfo::CardDesc.begin(), CardInfo::CardDesc.end(), 
            [&cards](std::pair<std::string, CardInfo::CardType>&& it)
            {
                return it.second == cards.back().Type();
            });
            
            std::cout << card->first + "\t";
        }
    }
}

void DrawConsoleGame(const Klondike::FieldPtr field, const Stock::Ptr& stock, const Store::Ptr& store)
{
    DrawCardsList(*stock->HiddenCards());
    DrawCardsList(*stock->OpenCards());
    std::cout << "\t";
    for(auto cards : store->GetStore())
        DrawCardsList(*cards);

    std::cout << std::endl;
    std::cout << std::endl;

    size_t RowCount = 0;
    for (size_t i = 0; i < Klondike::ColumnsCount; ++i)
    {
        auto colSize = field->at(i)->GetColumn()->size();
        if (RowCount < colSize)
            RowCount = colSize;
    }

    for (size_t j = 0; j < RowCount; ++j)
    {
        for (size_t i = 0; i < Klondike::ColumnsCount; ++i)
        {
            if (field->at(i)->GetColumn()->size() <= j)
            {
                std::cout << " X \t";
            }
            else
            {
                auto col = field->at(i)->GetColumn();
                auto cardIt = col->begin();
                std::advance(cardIt, j);
                if (cardIt->IsClosed())
                    std::cout << "[x]\t";
                else
                {
                    auto cardInfo = std::find_if(CardInfo::CardDesc.begin(), CardInfo::CardDesc.end(), 
                    [&cardIt](std::pair<std::string, CardInfo::CardType>&& it)
                    {
                        return it.second == cardIt->Type();
                    });
                    std::cout << cardInfo->first << "\t";
                }
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

int main(int, char**) 
{
    Deck startDeck;
    startDeck.Shuffle();

    auto klondike = std::make_shared<Klondike>();

    auto field = std::make_shared<Klondike::Field>();
    field->reserve(Klondike::ColumnsCount);
    for (size_t i = 0; i < Klondike::ColumnsCount; ++i)
    {
        field->push_back({std::make_shared<Column>(klondike, startDeck, i)});
        field->at(i)->GetColumn()->back().Open();
    }
        
    auto stock = std::make_shared<Stock>(klondike, startDeck);
    auto store = std::make_shared<Store>(klondike);
    assert(startDeck.Count() == 0);

    klondike->Init(field, stock, store);

    while(!klondike->CheckEndGame())
    {
        DrawConsoleGame(field, stock, store);
        std::string input;
        std::getline(std::cin, input);

        if(std::cin.eof())
            return -1;

    #ifdef _WIN32
            system("cls");
    #else
            system("clear");
    #endif

        if(input.empty())
            std::cout << "Empty Command" << std::endl;

        auto commands = Tokenize(input);

        for(auto& command : commands)
        {
            std::transform(command.begin(), command.end(), command.begin(), 
                [](unsigned char c){ return std::toupper(c); }
                );
        }

        if (commands.size() == 1)
        {
            bool isCardFound = false;

            auto command = commands.front();
            if(command == "#")
            {
                isCardFound = true;
                stock->InternalMoveCard();
                std::cout << "OK" << std::endl;
            }
            else
            {
                auto cardType = CardInfo::CardDesc.find(command);
                if(cardType == CardInfo::CardDesc.end())
                {
                    std::cerr << "Wrong command" << std::endl;
                    continue;
                }

                if(!stock->OpenCards()->empty() && stock->OpenCards()->back().Type() == cardType->second)
                {
                    isCardFound = true;
                    Event evt 
                    {
                        {stock->OpenCards()->back()},
                        CardInfo::CardPosition::Stock,
                        store,
                        CardInfo::CardPosition::Store
                    };

                    stock->MoveCard(evt);
                    continue;
                }

                for(auto& col : *field)
                {
                    if(col->GetColumn()->empty())
                        continue;

                    if(col->GetColumn()->back().Type() == cardType->second)
                    {
                        isCardFound = true;
                        Event evt
                        {
                            { col->GetColumn()->back() },
                            CardInfo::CardPosition::Field,
                            store,
                            CardInfo::CardPosition::Store
                        };
                        col->MoveCard(evt);
                        break;
                    }
                }
            }

            if(!isCardFound)
            {
                std::cerr << "Wrong Command" << std::endl;
                continue;
            }

        }
        else if (commands.size() == 2)
        {
            auto cardFromType = CardInfo::CardDesc.find(commands[0]);
            if(cardFromType == CardInfo::CardDesc.end())
            {
                std::cerr << "Wrong Command" << std::endl;
                continue;
            }

            Column::Ptr colTo = nullptr;
            
            if(commands[1] == "X")
            {
                for(const auto& col : *field)
                {
                    if(col->GetColumn()->empty())
                    {
                        colTo = col;
                        break;
                    }
                }
            }
            else
            {
                auto cardToType = CardInfo::CardDesc.find(commands[1]);
                if(cardToType == CardInfo::CardDesc.end())
                {
                    std::cerr << "Wrong Command" << std::endl;
                    continue;
                }

                for(auto& col : *field)
                {
                    if(col->GetColumn()->empty())
                        continue;

                    if(col->GetColumn()->back().Type() == cardToType->second)
                        colTo = col;
                }
            }

            if(!colTo)
            {
                std::cerr << "Wrong Command" << std::endl;
                continue;
            }

            // Find in stock
            if(!stock->OpenCards()->empty() && stock->OpenCards()->back().Type() == cardFromType->second)
            {
                Event evt
                {
                    { stock->OpenCards()->back() },
                    CardInfo::CardPosition::Stock,
                    colTo,
                    CardInfo::CardPosition::Field
                };
                stock->MoveCard(evt);
                continue;
            }

            // Find in field
            Column::Ptr column = nullptr;
            for(auto& col : *field)
            {
                auto it = std::find_if(col->GetColumn()->begin(), col->GetColumn()->end(),
                    [&cardFromType](const Card& c){ return (c.Type() == cardFromType->second) && !c.IsClosed(); });

                if(it != col->GetColumn()->end())
                {
                    column = col;
                    break;
                }
            }

            if(column)
            {
                // It's a kind of magic
                std::list<Card> srcCards;
                for(auto card = column->GetColumn()->rbegin(); card != column->GetColumn()->rend(); ++card)
                {
                    srcCards.push_front(*card);
                    if(card->Type() == cardFromType->second)
                        break;
                }

                Event evt 
                {
                    std::move(srcCards),
                    CardInfo::CardPosition::Field,
                    colTo,
                    CardInfo::CardPosition::Field
                };

                column->MoveCard(evt);
                continue;
            }

            // Find in store
            std::shared_ptr<std::list<Card>> suiteStore = nullptr;
            for(auto& cards : store->GetStore())
            {
                if(cards->empty())
                    continue;

                if(cards->back().Type() == cardFromType->second)
                {
                    suiteStore = cards;
                    break;
                }
            }

            if(suiteStore)
            {
                Event evt
                {
                    *suiteStore,
                    CardInfo::CardPosition::Store,
                    colTo,
                    CardInfo::CardPosition::Field
                };
                store->MoveCard(evt);
                continue;
            }

            std::cerr << "Wrong Command" << std::endl;
        }
        else
        {
            continue;
        }
    }

    std::cout << "You won! Press 'Enter' to exit";
    std::string input;
    std::getline(std::cin, input);

    return 0;
}
