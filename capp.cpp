#include "capp.h"

// Constructor
CApp::CApp()
{
  isRunning = true; 
  pWindow = NULL;
  pRenderer = NULL;
}

bool CApp::OnInit()
{
  if (SDL_init(SDL_INIT_EVERYTHING) < 0)
  {
    return false;
  }
  
  pWindow = SLD_CreateWindow("qbRaytracer - The Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
  
  if (pWindow != NULL)
  {
    pRenderer = SDL_CreateRenderer(pWindow, -1, 0); 
  }
  else
  {
    return false;
  }
  
  return true;
}

int CApp::OnExecute()
{
   SDL_Event event;
  
  if (OnInit() == false)
  {
    return -1
  }
  
  while (isRunning)
  {
    while (SDL_PollEvent(&event) != 0)
    {
      OnEvent(&event);
    }
    
    OnLoop();
    OnRender();
  }
}

void CApp::OnEvent
