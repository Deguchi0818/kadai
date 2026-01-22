#pragma once

#include "Player.h"

#include <UniDx/Input.h>
#include <UniDx/Collider.h>
#include <UniDx/Time.h>
#include <UniDx/PrimitiveRenderer.h>

#include "MainGame.h"

using namespace DirectX;
using namespace UniDx;

namespace
{
    const StringId CoinName = StringId::intern("Coin");

    // „Ç¢„Éã„É°„Ç∑„Éß„Éº„É≥„Åï„Åõ„Çã„Éú„Éº„É≥Âêç
    const StringId BoneName[] =
    {
        StringId::intern("LeftUpperArm"),
        StringId::intern("RightUpperArm"),
        StringId::intern("LeftUpperLeg"),
        StringId::intern("RightUpperLeg"),
        StringId::intern("Tail")
    };
    // „Ç¢„Éã„É°„Éº„Ç∑„Éß„É≥„Åï„Åõ„ÇãËßíÂ∫¶„ÅÆÁØÑÂõ≤Ôºàpitch, yaw, rollÔºâ
    const Vector3 Range[] =
    {
        Vector3( 80,  0,  0),
        Vector3(-80,  0,  0),
        Vector3( 30,  0, 45),
        Vector3(-30,  0, 45),
        Vector3( 30,  0,  0),
    };
    // „Ç¢„Éã„É°„Éº„Ç∑„Éß„É≥„Åï„Åõ„ÇãËßíÂ∫¶„ÅÆ„Ç™„Éï„Çª„ÉÉ„ÉàÔºàpitch, yaw, rollÔºâ
    const Vector3 Offset[] =
    {
        Vector3(  0,  0, 30),
        Vector3(  0,  0,-30),
        Vector3(  0,  5,  0),
        Vector3(  0, -5,  0),
        Vector3( 20,  0,  0),
    };
    constexpr size_t BoneMax = sizeof(BoneName) / sizeof(StringId);
    constexpr float animSpeed = 0.05f;
}


void Player::OnEnable()
{
    rb = GetComponent<Rigidbody>(true);
    assert(rb != nullptr);

    rb->gravityScale = 1.5f;
    animFrame = 0.0f;
    GetComponent<Collider>(true)->bounciness = 0.0f;
    auto& children = transform->getChildGameObjects();
    for (auto& child : children)
    {
        flashlight = child->GetComponent<Light>();
        if (flashlight) break;
    }
}


void Player::Update()
{
    const float moveSpeed = 4;

    // ëÄçÏï˚å¸
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

    // ÉJÉÅÉâï˚å¸Ççló∂ÇµÇƒë¨ìxÉxÉNÉgÉãÇåvéZ
    Vector3 camF = Camera::main->transform->forward;
    float camAngle = std::atan2(camF.x, camF.z) * UniDx::Rad2Deg;
    Vector3 velocity = (cont.normalized() * moveSpeed) * Quaternion::AngleAxis(camAngle, Vector3::up);
    //float vAngle = std::atan2(velocity.x, velocity.z) * UniDx::Rad2Deg;

    rb->linearVelocity = velocity;

    rb->rotation = Quaternion::Euler(0, camAngle, 0);

    if (cont != Vector3::zero)
    {
        
    }

    // ÉAÉjÉÅÅiñ¢ëŒâûÅj
    animFrame += cont.magnitude();

    // ÉâÉCÉgÇÃéqÉIÉuÉWÉFÉNÉgÇíTÇ∑
    if (!flashlight)
    {
        auto& children = transform->getChildGameObjects();
        for (auto& child : children)
        {
            flashlight = child->GetComponent<Light>();
            if (flashlight) break;
        }
    }

    // â˘íÜìdìîÇÃèàóù
    if (flashlight) 
    {
        if (Input::GetKeyDown(Keyboard::F))
        {
            isLightOn = !isLightOn;
        }
        if (isLightOn && battery > 0.0f)
        {
            battery -= Time::deltaTime * 0.016f;
            flashlight->intensity = 2.0f;
        }
        if (!isLightOn || battery <= 0) 
        {
            flashlight->intensity = 0;
        }
        MainGame::getInstance()->UpdetBattery(battery);
    }
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


// „Ç≥„É©„Ç§„ÉÄ„Éº„Å´ÂΩì„Åü„Å£„Åü„Å®„Åç„ÅÆ„Ç≥„Éº„É´„Éê„ÉÉ„ÇØ
void Player::OnCollisionEnter(const Collision& collision)
{
    if (collision.collider->name == CoinName)
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

