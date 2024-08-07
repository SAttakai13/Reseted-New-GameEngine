#include "Player.h"
#include "Engine.h"
#include <iostream>

void Player::Update(float dt)
{
	//movement
	float thrust = 0;
	Vector2 direction{ 0, 0 };
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_UP)) thrust = m_speed;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -m_speed;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) m_transform.rotation -= Math::DegToRad(100) * dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) m_transform.rotation += Math::DegToRad(100) * dt;

	m_velocity += Vector2{ thrust, 0.0f }.Rotate(m_transform.rotation);
	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	// fire
	//m_fireTimer -= dt:
	
	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	/*if (actor->GetTag() == "Enemy")
	{
		m_destroy == true;
	}*/
}
