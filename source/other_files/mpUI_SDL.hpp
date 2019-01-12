// mpUIRender.h
////////////////////////////////////////////////


//class ScreenController;
class UIController;

class UIRender
{  
	public:  
		UIRender( UIController* newScreenController );  
		~UIRender();  
		// -  ~  -  ~  -  ~  -  ~  
		//void run();  
		void stop() ;  
		// -  ~  -  ~  -  ~  -  ~  
		void startVideo();  
		void stopVideo();  
		// -  ~  -  ~  -  ~  -  ~  
		void render();  
		// -  ~  -  ~  -  ~  -  ~  
		//long long timeOffset;

	private:  
		SDL_Renderer* renderer = NULL;  
		void update();  
		void onQuit();  
		void onKeyDown( SDL_Event* event );  
		void onKeyUp( SDL_Event* event );  
		void fillRect(SDL_Rect* rc, int r, int g, int b );  
		void fpsChanged( int fps );  
		// -  ~  -  ~  -  ~  -  ~  
		std::map<int,int> keys; // No SDLK_LAST. SDL2 migration guide suggests std::map  
		int frameSkip = 0;  
		int running = 0;  
		long long startTime;
		SDL_Window* window = NULL;  
		// -  ~  -  ~  -  ~  -  ~  
		UIController* uiController;
		// -  ~  -  ~  -  ~  -  ~  
    bool videoIsStarted = false;		
};  