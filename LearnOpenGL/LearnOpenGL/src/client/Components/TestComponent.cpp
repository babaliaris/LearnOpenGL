#include "pch.h"
#include "TestComponent.h"
#include "Engine.h"

void TestComponent::OnStart()
{
    LOG_INFO("self.position = ({0}, {1}, {2})", self->transform.position.x, self->transform.position.y, self->transform.position.z);
    LOG_INFO("Window Title: {0}", core->GetWindow().GetTitle());
}


void TestComponent::OnUpdate()
{
}