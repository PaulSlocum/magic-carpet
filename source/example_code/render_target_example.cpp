
2 @TwinklebearTwinklebear/main.cpp
Last active 2 months ago • 
 
<script src="https://gist.github.com/Twinklebear/8265888.js"></script>
  
 Code  Revisions 2  Stars 15  Forks 2
Example of render to texture with SDL2
 main.cpp






#include <iostream>

#ifdef __linux__
#include <SDL2/SDL.h>
#elif defined(_WIN32)
#include <SDL.h>
#endif

const int WIN_WIDTH = 640;
const int WIN_HEIGHT = 480;

int main(int argc, char **argv){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
		return 1;
	}
	SDL_Window *win = SDL_CreateWindow("Rendering to a texture!", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	//Put your own bmp image here
	SDL_Surface *bmpSurf = SDL_LoadBMP("../res/image.bmp");
	SDL_Texture *bmpTex = SDL_CreateTextureFromSurface(renderer, bmpSurf);
	SDL_FreeSurface(bmpSurf);

	//Make a target texture to render too
	SDL_Texture *texTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, WIN_WIDTH, WIN_HEIGHT);
	
	//Now render to the texture
	SDL_SetRenderTarget(renderer, texTarget);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, bmpTex, NULL, NULL);
	//Detach the texture
	SDL_SetRenderTarget(renderer, NULL);

	//Now render the texture target to our screen, but upside down
	SDL_RenderClear(renderer);
	SDL_RenderCopyEx(renderer, texTarget, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL);
	SDL_RenderPresent(renderer);

	SDL_Delay(1000);
	SDL_DestroyTexture(texTarget);
	SDL_DestroyTexture(bmpTex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
