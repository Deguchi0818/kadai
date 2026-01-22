#include "Enemy.h"
#include <UniDx/GameObject.h>
#include <UniDx/Time.h>
#include <UniDx/Camera.h>

using namespace UniDx;

void Enemy::OnEnable() {
    rb = GetComponent<Rigidbody>(true);
}

void Enemy::Update() {
    if (!playerObj) {
        Transform* root = transform->parent; 
        if (root) {
            while (root->parent != nullptr) {
                root = root->parent;
            }
            playerObj = root->gameObject->Find([](GameObject* g) {
                return g->name == StringId::intern(u8"プレイヤー");
                });
        }
    }

    Vector3 toPlayer = playerObj->transform->position - transform->position;
    float dist = toPlayer.magnitude();

    if (dist < detectDist) {
        toPlayer = toPlayer.normalized();
        rb->linearVelocity = Vector3(toPlayer.x * speed, rb->linearVelocity.y, toPlayer.z * speed);

        float angle = std::atan2(toPlayer.x, toPlayer.z) * UniDx::Rad2Deg;
        rb->rotation = Quaternion::Euler(0, angle, 0);
    }
    else {
        rb->linearVelocity = Vector3(0, rb->linearVelocity.y, 0);
    }
}

void Enemy::OnCollisionEnter(const Collision& collision) {
    if (collision.collider->name == StringId::intern(u8"プレイヤー")) {
    }
}