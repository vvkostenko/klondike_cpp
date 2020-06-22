#pragma once

#include <memory>

struct Event;
class SolitaireComponent;

class ISolitaireRules
{
public:
    using Ptr = std::shared_ptr<ISolitaireRules>;

    virtual void Notify(const SolitaireComponent& pSender, const Event& evt) = 0;
};