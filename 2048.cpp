#include <iostream>
#include <SDL.h>
#include "2048.h"
#include <ctime>
#include <SDL_Mixer.h>

using namespace std;

const int SCREEN_WIDTH = 542;
const int SCREEN_HEIGHT = 720;
const string WINDOW_TITLE = "2048";

const int column[4] = {35, 156, 277, 398};
const int row[4] = {195, 316, 437, 558};

const int PICTURE_WIDTH = 107;
const int PICTURE_HEIGHT = 107;

void logSDLError(ostream& os, const string &msg, bool fatal = false);

void logSDLError(ostream& os, const string &msg, bool fatal) {
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void playGame() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    Mix_Music* music =NULL;
    initSDL(window, renderer);
    startGameBackground(renderer);

    waitUntilKeyPressed();

    musicBackground(music);

    srand(time(0));

    int valueBoard [4][4] = {0};
    SDL_Event e;
    makeRandomNumber(valueBoard);
    makeRandomNumber(valueBoard);
    renderGame (renderer, valueBoard);

    while (true) {
        SDL_Delay(200);
        if ( SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_ESCAPE) break;
            if (e.key.keysym.sym == SDLK_UP) {
                up(valueBoard);

            }
            if (e.key.keysym.sym == SDLK_DOWN) {
                down(valueBoard);

            }
            if (e.key.keysym.sym == SDLK_LEFT) {
                left(valueBoard);

            }
            if (e.key.keysym.sym == SDLK_RIGHT) {
                right(valueBoard);

            }
            makeRandomNumber(valueBoard);
            renderGame(renderer, valueBoard);
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (valueBoard[i][j] == 2048) renderWinGame(renderer);
            }
        }
        if (checkGame(valueBoard) == false) {
            SDL_Delay(600);
            break;
        }
    }
    renderGameOver(renderer);
    waitUntilKeyPressed();
    quitSDL(window, renderer);
//    Mix_FreeMusic (music);
  //  Mix_Quit();
}
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer) {
    //
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    //
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

//    if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
  //      cout << "SDL_Mixer could not intialize! Error: " << Mix_GetError() ;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed();

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

SDL_Texture* loadTexture(const string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = nullptr;
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == nullptr){
			logSDLError(cout, "CreateTextureFromSurface");
		}
	} else {
		logSDLError(cout, "LoadBMP");
	}
	return texture;
}

void startGameBackground (SDL_Renderer * renderer) {
    SDL_Texture *startGame = loadTexture("image\\2048_pic.bmp", renderer);
    SDL_RenderClear(renderer);
    renderTexture(startGame, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent(renderer);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void makeRandomNumber (int valueBoard[][4]) {
    const int add_number[] = {2, 4};

    int rand_num = rand() % 2;
    int x, y;
    do {
        x = rand() % 4;
        y = rand() % 4;
    } while (valueBoard[x][y] != 0);
    valueBoard [x][y] = add_number[rand_num];
}

void renderGame (SDL_Renderer *renderer, int valueBoard [][4]) {

    SDL_Texture *background = loadTexture("image\\background.bmp", renderer);
    SDL_Texture *image_2 = loadTexture("image\\image_2.bmp", renderer);
    SDL_Texture *image_4 = loadTexture("image\\image_4.bmp", renderer);
    SDL_Texture *image_8 = loadTexture("image\\image_8.bmp", renderer);
    SDL_Texture *image_16 = loadTexture("image\\image_16.bmp", renderer);
    SDL_Texture *image_32 = loadTexture("image\\image_32.bmp", renderer);
    SDL_Texture *image_64 = loadTexture("image\\image_64.bmp", renderer);
    SDL_Texture *image_128 = loadTexture("image\\image_128.bmp", renderer);
    SDL_Texture *image_256 = loadTexture("image\\image_256.bmp", renderer);
    SDL_Texture *image_512 = loadTexture("image\\image_512.bmp", renderer);
    SDL_Texture *image_1024 = loadTexture("image\\image_1024.bmp", renderer);
    SDL_Texture *image_2048 = loadTexture("image\\image_2048.bmp", renderer);
    SDL_Texture *start_pic = loadTexture("image\\2048_pic.bmp", renderer);

    SDL_RenderClear (renderer);

    renderTexture (background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            switch (valueBoard[i][j]) {
            case 2:
                renderTexture(image_2, renderer, column[i], row[j], PICTURE_WIDTH, PICTURE_HEIGHT);
                break;
            case 4:
                renderTexture(image_4, renderer, column[i], row[j], PICTURE_WIDTH, PICTURE_HEIGHT);
                break;
            case 8:
				renderTexture(image_8, renderer, column[i], row[j], PICTURE_WIDTH, PICTURE_HEIGHT);
				break;
			case 16:
				renderTexture(image_16, renderer, column[i], row[j], PICTURE_WIDTH, PICTURE_HEIGHT);
				break;
			case 32:
				renderTexture(image_32, renderer, column[i], row[j], PICTURE_WIDTH, PICTURE_HEIGHT);
				break;
			case 64:
				renderTexture(image_64, renderer, column[i], row[j], PICTURE_WIDTH, PICTURE_HEIGHT);
				break;
			case 128:
				renderTexture(image_128, renderer, column[i], row[j], PICTURE_WIDTH, PICTURE_HEIGHT);
				break;
			case 256:
				renderTexture(image_256, renderer, column[i], row[j], PICTURE_WIDTH, PICTURE_HEIGHT);
				break;
			case 512:
				renderTexture(image_512, renderer, column[i], row[j], PICTURE_WIDTH, PICTURE_HEIGHT);
				break;
			case 1024:
				renderTexture(image_1024, renderer, column[i], row[j], PICTURE_WIDTH, PICTURE_HEIGHT);
				break;
			case 2048:
				renderTexture(image_2048, renderer, column[i], row[j], PICTURE_WIDTH, PICTURE_HEIGHT);
				break;
            }
        }
    }

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(image_2);
    SDL_DestroyTexture(image_4);
    SDL_DestroyTexture(image_8);
    SDL_DestroyTexture(image_16);
    SDL_DestroyTexture(image_32);
    SDL_DestroyTexture(image_64);
    SDL_DestroyTexture(image_128);
    SDL_DestroyTexture(image_256);
    SDL_DestroyTexture(image_512);
    SDL_DestroyTexture(image_1024);
    SDL_DestroyTexture(image_2048);
    SDL_DestroyTexture(start_pic);
}

void renderGameOver (SDL_Renderer *renderer) {
    SDL_Texture *game_over = loadTexture("image\\game_over.bmp", renderer);
    SDL_RenderClear(renderer);
    renderTexture(game_over, renderer, 0, 240, SCREEN_WIDTH, SCREEN_HEIGHT/3);
    SDL_RenderPresent(renderer);
}

void renderWinGame (SDL_Renderer *renderer) {
    SDL_Texture *win_game = loadTexture("image\\win.bmp", renderer);
    SDL_RenderClear(renderer);
    renderTexture(win_game, renderer, 0, 90, SCREEN_WIDTH, SCREEN_HEIGHT*3/4);
    SDL_RenderPresent(renderer);
}

void up(int valueBoard[][4]) {

    for(int cot = 0; cot < 4; cot++) {
		for(int hang = 1; hang < 4; hang++) {
			for(int x = hang - 1; x >= 0; x--) {
				if(valueBoard[cot][x] == 0) {
				    valueBoard[cot][x] = valueBoard[cot][x + 1];
                    valueBoard[cot][x + 1]=0;
                }
			}
		}
	}

	//Xet 2 gia tri ke nhau ma bang nhau thi cong 2 so lai roi xoa di 1 so
	for(int cot = 0; cot < 4; cot++) {
		for(int hang = 0; hang < 4; hang++) {
			if(valueBoard[cot][hang] == valueBoard[cot][hang + 1]) {
				valueBoard[cot][hang] += valueBoard[cot][hang];
				valueBoard[cot][hang + 1] = 0;
			}
		}
	}
	//Đổi lần 2
    for(int cot = 0; cot < 4; cot++) {
		for(int hang = 1; hang < 4; hang++) {
			for(int x = hang - 1; x >= 0; x--) {
				if(valueBoard[cot][x] == 0) {
				    valueBoard[cot][x] = valueBoard[cot][x + 1];
                    valueBoard[cot][x + 1]=0;
                }
			}
		}
	}
}

void down (int valueBoard[][4]) {
    for(int cot = 0; cot < 4; cot++) {
		for(int hang = 2; hang >= 0; hang--) {
			for(int x = hang + 1; x < 4; x++) {
				if(valueBoard[cot][x] == 0) {
				    valueBoard[cot][x] = valueBoard[cot][x - 1];
                    valueBoard[cot][x - 1] = 0;
				}
			}
		}
	}

	//Xet 2 gia tri ke nhau ma bang nhau thi cong 2 so lai roi xoa di 1 so
	for(int cot = 0; cot < 4; cot++) {
		for(int hang = 2; hang >= 0; hang--) {
			if (valueBoard[cot][hang] == valueBoard[cot][hang + 1]) {
				valueBoard[cot][hang + 1] += valueBoard[cot][hang + 1];
				valueBoard[cot][hang] = 0;
			}
		}
	}

	for(int cot = 0; cot < 4; cot++) {
		for(int hang = 2; hang >= 0; hang--) {
			for(int x = hang + 1; x < 4; x++) {
				if(valueBoard[cot][x] == 0) {
				    valueBoard[cot][x] = valueBoard[cot][x - 1];
                    valueBoard[cot][x - 1] = 0;
				}
			}
		}
	}
}

void left (int valueBoard[][4]) {
    for(int hang = 0; hang < 4; hang++) {
		for(int  cot = 1; cot < 4; cot++) {
			for(int x = cot - 1; x >= 0; x--) {
				if(valueBoard[x][hang] == 0) {
					valueBoard[x][hang] = valueBoard[x + 1][hang];
					valueBoard[x + 1][hang] = 0;
				}
			}
		}
	}

	//Xet 2 gia tri ke nhau ma bang nhau thi cong 2 so lai roi xoa di 1 so
	for (int hang = 0; hang < 4; hang++) {
		for (int cot = 1; cot < 4; cot++) {
			if (valueBoard[cot][hang] == valueBoard[cot - 1][hang]) {
				valueBoard[cot - 1][hang] += valueBoard[cot - 1][hang];
				valueBoard[cot][hang] = 0;
			}
		}
	}

	for(int hang = 0; hang < 4; hang++) {
		for(int  cot = 1; cot < 4; cot++) {
			for(int x = cot - 1; x >= 0; x--) {
				if(valueBoard[x][hang] == 0) {
					valueBoard[x][hang] = valueBoard[x + 1][hang];
					valueBoard[x + 1][hang] = 0;
				}
			}
		}
	}
}

void right (int valueBoard[][4]) {
    for(int hang = 0; hang < 4; hang++) {
		for(int  cot = 2; cot >= 0; cot--) {
			for(int x = cot + 1; x <= 3; x++) {
				if(valueBoard[x][hang] == 0) {
					valueBoard[x][hang] = valueBoard[x - 1][hang];
					valueBoard[x - 1][hang] = 0;
				}
			}
		}
	}

	//Xet 2 gia tri ke nhau ma bang nhau thi cong 2 so lai roi xoa di 1 so
	for (int hang = 0; hang < 4; hang++) {
		for (int cot = 3; cot >= 0; cot--) {
			if (valueBoard[cot][hang] == valueBoard[cot - 1][hang]) {
				valueBoard[cot][hang] += valueBoard[cot][hang];
				valueBoard[cot - 1][hang] = 0;
			}
		}
	}

	for(int hang = 0; hang < 4; hang++) {
		for(int  cot = 2; cot >= 0; cot--) {
			for(int x = cot + 1; x <= 3; x++) {
				if(valueBoard[x][hang] == 0) {
					valueBoard[x][hang] = valueBoard[x - 1][hang];
					valueBoard[x - 1][hang] = 0;
				}
			}
		}
	}
}

bool checkGame (int valueBoard[][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (valueBoard[i][j] == 0) return true;
        }
    }
    return false;
}

void musicBackground (Mix_Music *music) {
//    music = Mix_LoadMUS ("music.mp3");
    if (music == nullptr) logSDLError(cout, "MusicBackgroud");
  //  Mix_PlayMusic(music, -1);
}
