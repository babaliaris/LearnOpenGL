#ifndef CLIENT_TEST_COMPONENT_H
#define CLIENT_TEST_COMPONENT_H
#include "../../engine/Component.h"

class TestComponent : public Engine::Component
{
    public:

    virtual void OnStart() override;
    virtual void OnUpdate() override;
};

#endif