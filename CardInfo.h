#pragma once

#include <unordered_map>

namespace CardInfo
{
    enum class CardPosition
    {
        Field,
        Stock,
        Store,
    };

    enum class CardSuite : uint8_t
    {
        Hearts,
        Diamonds,
        Clubs,
        Spades,

        Count,
    };

    enum class CardRank : uint8_t
    {
        Ace,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King,

        Count,
    };

    enum class CardColor : uint8_t
    {
        Red,
        Black,

        Count,
    };

    enum class CardType : uint8_t
    {
        //  Hearts
        HA,
        H2,
        H3,
        H4,
        H5,
        H6,
        H7,
        H8,
        H9,
        H10,
        HJ,
        HQ,
        HK,

        //  Diamonds
        DA,
        D2,
        D3,
        D4,
        D5,
        D6,
        D7,
        D8,
        D9,
        D10,
        DJ,
        DQ,
        DK,

        //  Clubs
        CA,
        C2,
        C3,
        C4,
        C5,
        C6,
        C7,
        C8,
        C9,
        C10,
        CJ,
        CQ,
        CK,

        //  Spades
        SA,
        S2,
        S3,
        S4,
        S5,
        S6,
        S7,
        S8,
        S9,
        S10,
        SJ,
        SQ,
        SK,

        Count,
    };

    static const std::unordered_map<std::string, CardType> CardDesc
    {
        //  Hearts
        { "HA", CardType::HA },
        { "H2", CardType::H2 },
        { "H3", CardType::H3 },
        { "H4", CardType::H4 },
        { "H5", CardType::H5 },
        { "H6", CardType::H6 },
        { "H7", CardType::H7 },
        { "H8", CardType::H8 },
        { "H9", CardType::H9 },
        { "H10", CardType::H10 },
        { "HJ", CardType::HJ },
        { "HQ", CardType::HQ },
        { "HK", CardType::HK },

        //  Diamonds
        { "DA", CardType::DA },
        { "D2", CardType::D2 },
        { "D3", CardType::D3 },
        { "D4", CardType::D4 },
        { "D5", CardType::D5 },
        { "D6", CardType::D6 },
        { "D7", CardType::D7 },
        { "D8", CardType::D8 },
        { "D9", CardType::D9 },
        { "D10", CardType::D10 },
        { "DJ", CardType::DJ },
        { "DQ", CardType::DQ },
        { "DK", CardType::DK },

        //  Clubs
        { "CA", CardType::CA },
        { "C2", CardType::C2 },
        { "C3", CardType::C3 },
        { "C4", CardType::C4 },
        { "C5", CardType::C5 },
        { "C6", CardType::C6 },
        { "C7", CardType::C7 },
        { "C8", CardType::C8 },
        { "C9", CardType::C9 },
        { "C10", CardType::C10 },
        { "CJ", CardType::CJ },
        { "CQ", CardType::CQ },
        { "CK", CardType::CK },

        //  Spades
        { "SA", CardType::SA },
        { "S2", CardType::S2 },
        { "S3", CardType::S3 },
        { "S4", CardType::S4 },
        { "S5", CardType::S5 },
        { "S6", CardType::S6 },
        { "S7", CardType::S7 },
        { "S8", CardType::S8 },
        { "S9", CardType::S9 },
        { "S10", CardType::S10 },
        { "SJ", CardType::SJ },
        { "SQ", CardType::SQ },
        { "SK", CardType::SK },
    };
}