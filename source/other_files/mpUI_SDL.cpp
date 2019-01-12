// mpUIRender.cpp
//////////////////////////////////////////////////////////

#include <SDL2/SDL_ttf.h>
#include <map>  
#include <iostream>

#include "mpUtil.h"
#include "mpUI_SDL.h"
#include "mpUI.h"
#include "SDL.h"

#include "mpDebugInclude.h"


// DISPLAY SETTINGS
enum {  
  DISPLAY_WIDTH  = 1600  
  , DISPLAY_HEIGHT = 1200  
  , UPDATE_INTERVAL = 1000/60  
  //, UPDATE_INTERVAL = 1000/30  
  , HERO_SPEED = 5  
};  



///////////////////////////////////////////////////////////////////
// CONSTRUCTOR
UIRender::UIRender( UIController* newUIController )  
{  
	uiController = newUIController;
	//timeOffset = 0;
	
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TEXT
    // Initialize SDL_ttf library
    if (TTF_Init() != 0)
    {
      std::cerr << "TTF_Init() Failed: " << TTF_GetError() << std::endl;
      SDL_Quit();
      exit(1);
    }

}  


//////////////////////////////////////////////////////////////////
// DESTRUCTOR
UIRender::~UIRender() 
{  
  this->stop();  

  TTF_Quit();
  
  //SDL_Quit() ;  
}  
  

#pragma mark -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ 


/////////////////////////////////////////////////////////////////////
void UIRender::startVideo() 
{  
  if( videoIsStarted == false )
  { 
    videoIsStarted = true;
    
    printf( "\n_____________________________________________________________\n" );
    printf( "(SDL)  -------- STARTING SDL ----------------\n" );
    //if( SDL_Init(SDL_INIT_EVERYTHING) )   
    if( SDL_Init(SDL_INIT_VIDEO) )   
    //if( SDL_Init(SDL_INIT_EVENTS) )  
    {
      printf( "ERROR: Could not init SDL\n" );
      return ;  
    }

    if( renderer == NULL ) 
    {  
      int flags = SDL_WINDOW_SHOWN ;  
      //int flags = SDL_WINDOW_HIDDEN ;  
      //int flags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_HIDDEN ;  

      //if( SDL_CreateWindowAndRenderer(DISPLAY_WIDTH, DISPLAY_HEIGHT, flags, &window, &renderer) ) 
      if( SDL_CreateWindowAndRenderer( uiController->screenFrame.width, uiController->screenFrame.height, flags, &window, &renderer) ) 
      {
        printf( "ERROR: SDL_CreateWindowAndRenderer\n" );
        return;  
      }
      
      // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TEXT

      // HIDE MOUSE CURSOR
      SDL_ShowCursor( false );
    } //*/
  }
  else 
  {
    printf( "(SDL) --------- SDL ALREADY STARTED -----------\n" );
  }
}  

/////////////////////////////////////////////////////////////////////
void UIRender::stopVideo()
{  
  if( videoIsStarted == true )
  {
    videoIsStarted = false;
    
    printf( "\n_________________________________________________________\n" );
    printf( "/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n" );
    printf( "(SDL) -------- STOPPING SDL --------------------\n" );
    if( renderer != NULL ) 
    {  
      SDL_DestroyRenderer(renderer);  
      renderer = NULL;  
    }  
  
    if( window != NULL ) 
    {  
      SDL_DestroyWindow(window);  
      window = NULL;  
    }  //*/ 

    SDL_Quit();  
  }
  else 
  {
    printf( "(SDL) ------ SDL ALREADY STOPPED --------------------\n" );
  }
}  

  
  
#pragma mark -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ 

  
///////////////////////////////////////////////////////////////////////////////
// STOP UI
void UIRender::stop() 
{  
  stopVideo();

  running = false; // ADDED THIS
}  


////////////////////////////////////////////////////////////////
void UIRender::onQuit() 
{  
  printf( "(SDL) ON QUIT\n" );
  //running = false; 
  uiController->stop();
}  

  
//////////////////////////////////////////////////////////////////
// RUN - RUNS "GAME" IN LOOP UNTIL running IS FALSE
/*void UIRender::run() 
{  
  running = true;
  int past = SDL_GetTicks();  
  int now = past, pastFps = past ;  
  int fps = 0, framesSkipped = 0 ;  
  SDL_Event event ;  
  startTime = getCurrentTimeMSec();
  //startTime = (unsigned)time(NULL);
  
  // RUN LOOP...
  while( running == true ) 
  {  
    int timeElapsed = 0 ;  
    
    // HANDLE ONE EVENT...
    if (SDL_PollEvent(&event)) 
    {  
      switch (event.type) {  
        case SDL_QUIT:    onQuit();            break;  
        case SDL_KEYDOWN: onKeyDown( &event ); break ;  
        case SDL_KEYUP:   onKeyUp( &event );   break ;  
        case SDL_MOUSEBUTTONDOWN:  
        case SDL_MOUSEBUTTONUP:  
        case SDL_MOUSEMOTION:  
          break ;  
      }  
    }  
    
    // DO UPDATE AND DO DRAW IF WE'VE REACHED THE NEXT FRAME...
    now = SDL_GetTicks(); 
    timeElapsed = now - past ;  
    if( timeElapsed >= UPDATE_INTERVAL  ) 
    {  
      past = now ;  
      update();  // <-------------------- update() is not used
      if( framesSkipped >= frameSkip ) 
      {  
        draw(); // <----------------------  draw()
        ++fps ;  
        framesSkipped = 0 ;  
      }  
      framesSkipped++;
    }  
    
    // FPS - WHAT DOES THIS DO?
    if ( now - pastFps >= 1000 ) 
    {  
      pastFps = now ;  
      fpsChanged( fps );  
      fps = 0 ;  
    }  
    
    // DELAY 1 MSEC
    SDL_Delay( 1 );  
  }  
}  //*/
  

  
#pragma mark -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ 


/////////////////////////////////////////////////////////////////////////////////
// DRAW SCREEN (CALLED EACH FRAME)  
void UIRender::render() 
{  
  if( renderer != NULL )
  {
    uiController->render( renderer );
    SDL_RenderPresent(renderer);  
  }
}  

  
#pragma mark -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ 


////////////////////////////////////////////////////////////////
void UIRender::fillRect(SDL_Rect* rc, int r, int g, int b ) 
{  
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);  
    SDL_RenderFillRect(renderer, rc);  
}  


//////////////////////////////////////////////////////////////////
void UIRender::fpsChanged( int fps ) 
{  
    char szFps[ 128 ] ;  
    sprintf( szFps, "%s: %d FPS", "SDL2 Base C++ - Use Arrow Keys to Move", fps );  
    SDL_SetWindowTitle(window, szFps);  
}  


  
  
//////////////////////////////////////////////////////////////////
// UPDATE - GAME PROCESSING, CALLED EACH FRAME
// THIS FUNCTION CAN PROBABLY BE DELETED
void UIRender::update() 
{  
    /*if ( keys[SDLK_LEFT] )  
    {

    }//*/
}  


#pragma mark -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ 



///////////////////////////////////////////////////////////////////////
// ON KEY DOWN  
void UIRender::onKeyDown( SDL_Event* evt ) 
{  
	// STORE WHICH KEYS ARE HELD TO PROCESS HELD KEYS IF NECESSARY...
  keys[ evt->key.keysym.sym ] = 1 ;  
    
  uiController->keyDownEvent( evt->key.keysym.sym );
}  
  
//////////////////////////////////////////////////////////////////////
// ON KEY UP
void UIRender::onKeyUp( SDL_Event* evt ) 
{  
    keys[ evt->key.keysym.sym ] = 0 ;  
}  




