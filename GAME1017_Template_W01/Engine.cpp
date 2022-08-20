#include <iostream>
#include <ctime>
#include "Engine.h"
#include "TextureManager.h"
#define WIDTH 1024
#define HEIGHT 768
#define FPS 60
using namespace std;

Engine::Engine():m_bRunning(false){	cout << "Engine class constructed!" << endl; }
Engine::~Engine(){}

bool Engine::Init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	cout << "Initializing game..." << endl;
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Create the window.
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != nullptr) // Window init success.
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != nullptr) // Renderer init success.
			{
				TEMA::Init();
				// TEMA::Load Background
				TEMA::Load("img/BG.png", "bg");
			}
			else return false; // Renderer init fail.
		}
		else return false; // Window init fail.
	}
	else return false; // SDL init fail.
	m_fps = (Uint32)round((1 / (double)FPS) * 1000); // Sets FPS in milliseconds and rounds.
	m_iKeystates = SDL_GetKeyboardState(nullptr);
	srand((unsigned)time(NULL)); // Seed random number sequence.
	
	// Create the vector now.
	m_vec.reserve(10);

	// Backgrounds.
	m_vec.push_back(new Background( {0, 0, 1024, 768}, {0, 0, 1024, 768}, 1));
	m_vec.push_back(new Background( {0, 0, 1024, 768}, {1024, 0, 1024, 768}, 1));

	// Midgrounds.
	m_vec.push_back(new Background({1024, 0, 256, 512 }, { 0, 0, 256, 512 }, 3));
	m_vec.push_back(new Background({1024, 0, 256, 512 }, { 256, 0, 256, 512 }, 3));
	m_vec.push_back(new Background({1024, 0, 256, 512 }, { 512, 0, 256, 512 }, 3));
	m_vec.push_back(new Background({1024, 0, 256, 512 }, { 768, 0, 256, 512 }, 3));
	m_vec.push_back(new Background({1024, 0, 256, 512 }, { 1024, 0, 256, 512 }, 3));

	// Foregrounds.
	m_vec.push_back(new Background({ 1024, 512, 512, 256 }, { 0, 512, 512, 256 }, 4));
	m_vec.push_back(new Background({ 1024, 512, 512, 256 }, { 512, 512, 512, 256 }, 4));
	m_vec.push_back(new Background({ 1024, 512, 512, 256 }, { 1024, 512, 512, 256 }, 4));
	
	m_bRunning = true; // Everything is okay, start the engine.
	cout << "Init success!" << endl;
	return true;
}

void Engine::Wake()
{
	m_start = SDL_GetTicks();
}

void Engine::Sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start;
	if (m_delta < m_fps) // Engine has to sleep.
		SDL_Delay(m_fps - m_delta);
}

void Engine::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // User pressed window's 'x' button.
			m_bRunning = false;
			break;
		case SDL_KEYDOWN: // Try SDL_KEYUP instead.
			if (event.key.keysym.sym == SDLK_ESCAPE)
				m_bRunning = false;
			break;
		}
	}
}

// Keyboard utility function.
bool Engine::KeyDown(SDL_Scancode c)
{
	if (m_iKeystates != nullptr)
	{
		if (m_iKeystates[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}

void Engine::Update()
{
	// Update the backgrounds
	for (size_t i = 0; i < m_vec.size(); i++)
	{
		m_vec[i]->Update();
	}
		
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer); // Clear the screen with the draw color.
	// Render the backgrounds.
	for (size_t i = 0; i < m_vec.size(); i++)
	{
		m_vec[i]->Render();
	}
	// Draw anew.
	SDL_RenderPresent(m_pRenderer);
}

void Engine::Clean()
{
	cout << "Cleaning game." << endl;
	// Clean the backgrounds.
	
	for (size_t i = 0; i < m_vec.size(); i++)
	{
		delete m_vec[i];
		m_vec[i] = nullptr;
	}
	m_vec.clear();
	m_vec.shrink_to_fit();

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	TEMA::Quit();
	IMG_Quit();
	SDL_Quit();
}

int Engine::Run()
{
	if (m_bRunning) // What does this do and what can it prevent?
		return -1; 
	if (Init("GAME1017 Engine Template", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false)
		return 1;
	while (m_bRunning) // Main engine loop.
	{
		Wake();
		HandleEvents();
		Update();
		Render();
		if (m_bRunning)
			Sleep();
	}
	Clean();
	return 0;
}

Engine& Engine::Instance()
{
	static Engine instance; // C++11 will prevent this line from running more than once. Magic statics.
	return instance;
}

SDL_Renderer* Engine::GetRenderer() { return m_pRenderer; }
