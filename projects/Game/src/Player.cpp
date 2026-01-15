#pragma once

#include "Player.h"

#include <UniDx/Input.h>
#include <UniDx/Collider.h>
#include <UniDx/Time.h>

#include "MainGame.h"

using namespace DirectX;
using namespace UniDx;

namespace
{
}


void Player::OnEnable()
{
    rb = GetComponent<Rigidbody>(true);
    assert(rb != nullptr);

    rb->gravityScale = 1.5f;
    animFrame = 0.0f;
    GetComponent<Collider>(true)->bounciness = 0.0f;
}


void Player::Update()
{
    const float moveSpeed = 4;

    // 操作方向
    Vector3 cont;
    if (Input::GetKey(Keyboard::A))
    {
        cont.x = -1.0f;
    }
    else if (Input::GetKey(Keyboard::D))
    {
        cont.x = 1.0f;
    }
    else
    {
        cont.x = 0.0f;
    }

    if (Input::GetKey(Keyboard::S))
    {
        cont.z = -1.0f;
    }
    else if (Input::GetKey(Keyboard::W))
    {
        cont.z = 1.0f;
    }
    else
    {
        cont.z = 0.0f;
    }
    cont = cont.normalized();

    // カメラ方向を考慮して速度ベクトルを計算
    Vector3 camF = Camera::main->transform->forward;
    float camAngle = std::atan2(camF.x, camF.z) * UniDx::Rad2Deg;
    Vector3 velocity = (cont.normalized() * moveSpeed) * Quaternion::AngleAxis(camAngle, Vector3::up);
    //float vAngle = std::atan2(velocity.x, velocity.z) * UniDx::Rad2Deg;

    rb->linearVelocity = velocity;

    rb->rotation = Quaternion::Euler(0, camAngle, 0);

    if (cont != Vector3::zero)
    {
        
    }

    // アニメ（未対応）
    animFrame += cont.magnitude();
}


void Player::OnTriggerEnter(Collider* other)
{
}


void Player::OnTriggerStay(Collider* other)
{
}


void Player::OnTriggerExit(Collider* other)
{
}


void Player::OnCollisionEnter(const Collision& collision)
{
    if (collision.collider->name == StringId::intern("Coin"))
    {
        MainGame::getInstance()->AddScore(1);
        Destroy(collision.collider->gameObject);
    }
}


void Player::OnCollisionStay(const Collision& collision)
{
}

void Player::OnCollisionExit(const Collision& collision)
{
}

