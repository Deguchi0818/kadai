#pragma once
#include <UniDx.h>
#include <UniDx/Rigidbody.h>

class Enemy : public UniDx::Behaviour
{
public:
    virtual void OnEnable() override;
    virtual void Update() override;
    virtual void OnCollisionEnter(const UniDx::Collision& collision) override;

private:
    UniDx::Rigidbody* rb = nullptr;
    UniDx::GameObject* playerObj = nullptr;
    float speed = 2.0f;
    float detectDist = 10.0f;
};