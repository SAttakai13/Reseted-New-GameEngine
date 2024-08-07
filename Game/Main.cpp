#include "Engine.h"
#include "Scene.h"
#include "Player.h"

#include <iostream>
#include <vector>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	g_engine.Initialize();

	// add audio sounds
	g_engine.GetAudio().AddSound("bass.wav");
	g_engine.GetAudio().AddSound("snare.wav");
	g_engine.GetAudio().AddSound("open-hat.wav");
	g_engine.GetAudio().AddSound("clap.wav");
	g_engine.GetAudio().AddSound("cowbell.wav");
	g_engine.GetAudio().AddSound("close-hat.wav");

	Time time;

	std::vector<Particle> particles;

	float offset = 0;

	std::vector<Vector2> points;
	points.push_back(Vector2{ 5, 0 });
	points.push_back(Vector2{ -5, -5 });
	points.push_back(Vector2{ -5, 5 });
	points.push_back(Vector2{ 5, 0 });
	Model* model = new Model{ points, Color{ 1, 0, 0 } };

	Scene* scene = new Scene();
	for (int i = 0; i < 100; i++)
	{
		Transform transform{ Vector2{ randomf(0,800), randomf(0,600)}, 0, randomf(1,5) };
		Player* player = new Player(randomf(1, 5), transform, model);
		player->SetDamping(2.0f);
		scene->AddActor(player);
	}

	// main loop
	bool quit = false;
	while (!quit)
	{
		g_engine.GetAudio().Update();

		time.Tick();
		//std::cout << time.GetTime() << std::endl;

		// input
		// update
		// draw

		// INPUT
		g_engine.GetInput().Update();

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		//transform.rotation = velocity.Angle();//rotation + time.GetDeltaTime();

		// UPDATE
		scene->Update(time.GetDeltaTime());

		Vector2 mousePosition = g_engine.GetInput().GetMousePosition();

		if (g_engine.GetInput().GetMouseButtonDown(0))
		{
			particles.push_back(Particle{ {mousePosition}, randomOnUnitCircle() * randomf(50, 300), randomf(1 ,3) });
		}

		for (Particle& particle : particles)
		{
			particle.Update(time.GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
			if (particle.position.y > 600) particle.position.y = 0;
			if (particle.position.y < 0) particle.position.y = 600;
		}

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_Q))
		{
			g_engine.GetAudio().PlaySound("bass.wav");
		}
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_W))
		{
			g_engine.GetAudio().PlaySound("snare.wav");
		}
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_E))
		{
			g_engine.GetAudio().PlaySound("open-hat.wav");
		}
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_R) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_E))
		{
			g_engine.GetAudio().PlaySound("clap.wav");
		}
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_T) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_E))
		{
			g_engine.GetAudio().PlaySound("cowbell.wav");
		}
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Y) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_E))
		{
			g_engine.GetAudio().PlaySound("close-hat.wav");
		}

		// DRAW
		//// clear screen
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		g_engine.GetRenderer().SetColor(255, 255, 255, 0);

		float radius = 100;
		offset += (90 * time.GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 30)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.01f) * radius;
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Cos((offset + angle) * 0.01f) * radius;

			g_engine.GetRenderer().SetColor(rand() % 256, rand() % 256, rand() % 256, 0);
			//renderer.DrawRect(400 + x, 300 + y, randomf(1, 40), randomf(1, 40));
		}

		//draw particles
		for (Particle particle : particles)
		{
			g_engine.GetRenderer().SetColor(rand() % 256, rand() % 256, rand() % 256, 0);

			particle.Draw(g_engine.GetRenderer());
		}

		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		scene->Draw(g_engine.GetRenderer());

		//// show screen
		g_engine.GetRenderer().EndFrame();
	}

	return 0;
}