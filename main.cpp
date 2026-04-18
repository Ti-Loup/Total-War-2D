
#define SDL_MAIN_USE_CALLBACKS

//La librairie
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <algorithm>
#include <cmath>
//les classes
#include "State.h"
#include "Entity.h"


//Fonction FPS
static Uint32 TimerCallback(void *userdata, SDL_TimerID timerID, Uint32 interval) {
    bool *updateFlag = static_cast<bool *>(userdata);
    *updateFlag = true;
    return interval;
}
//rgb
Uint8 r = 0, g = 0, b = 0;
class GameApp final {
public:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *spritesheet = nullptr;
    //Ajout du state Menu
    State StateActuel = State::Menu;
    float colorTime = 0.0f;


    //TEXT ET FONT
    // -> MENU <-
    TTF_Font *menuFont = nullptr;
    TTF_Text *menuText = nullptr;
    // -> OPTION <-

    // -> GAME <-

    // -> AUTRE <-
    TTF_Font *fpsFont = nullptr;
    TTF_Text *fpsText = nullptr;
    TTF_TextEngine *textEngine = nullptr;

    //Pour le FPS
    std::vector<float> frameTimes;
    const size_t MAX_SAMPLES = 100;
    bool shouldUpdateText = false;
    SDL_TimerID fpsTimerID;
    SDL_TimerID ShootTimerID;
    float currentFPS = 0.0f;

    float deltaTime = 0.f;


    //PATRON DE CONCEPTION SINGLETON
    static GameApp &GetInstance() {
        static GameApp instance;
        return instance;
    }

    GameApp(GameApp const &) = delete;

    void operator=(GameApp const &) = delete;

private://constructor
    GameApp() {
        //window + renderer
        window = SDL_CreateWindow("Total Battle 2D",1280,720,0);
        if (window == nullptr) {
            SDL_LogCritical(1,"SDL failed to create the window! &s", SDL_GetError());
            abort();
        }
        renderer = SDL_CreateRenderer(window, nullptr);
        if (renderer == nullptr) {
            SDL_LogCritical(1,"SDL failed to create the renderer &s", SDL_GetError());
            abort();
        }
        //Pour mettre en fullscreen
        SDL_SetRenderLogicalPresentation(renderer, 1920,1080, SDL_LOGICAL_PRESENTATION_LETTERBOX);
        //Pour render les text
        textEngine = TTF_CreateRendererTextEngine(renderer);
        if (textEngine == nullptr) {
            SDL_LogCritical(1, "Failed to create textEngine", SDL_GetError());
        }//TTF_INIT
        if (TTF_Init() == false) {
            SDL_LogCritical(1, "SDL_ttf failed to initialize! %s", SDL_GetError());
            abort();
        }
        // -> MENU <-
        menuFont = TTF_OpenFont("assets/font.ttf",75);
        if (menuFont == nullptr) {
            SDL_LogCritical(1, "Failed to load font: %s", SDL_GetError());
            abort();
        }
        menuText = TTF_CreateText(textEngine, menuFont, "TOTAL BATTLE 2D", 25);
        if (menuText == nullptr) {
            SDL_LogWarn(0,"failed to create text for menuText", SDL_GetError());
        }
        if (TTF_SetTextColor(menuText, 0,0,0,255)==false) {
            SDL_LogWarn(1,"failed to set the color of menuText", SDL_GetError());
        }
        // -> OPTION <-

        // -> GAME <-

        // -> CREDITS <-

        //Autre
        fpsFont = TTF_OpenFont("assets/font.ttf", 24);
        fpsText = TTF_CreateText(textEngine, fpsFont, "FPS: 0", 20);
        if (fpsText == nullptr) {
            SDL_LogWarn(0,"failed to create text for fpsText FPS: 0", SDL_GetError());
        }
        if (TTF_SetTextColor(fpsText, 255,255,255,255)==false) {
            SDL_LogWarn(1,"failed to set the color of fpsText",SDL_GetError());
        }
        fpsTimerID = SDL_AddTimer(250, TimerCallback, &shouldUpdateText);

    }

    //DESTRUCTEUR
    ~GameApp() {
        //renderer
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        // Timer
        SDL_RemoveTimer(fpsTimerID);
        //text et fonts
        TTF_CloseFont(fpsFont);
        TTF_CloseFont(menuFont);
        TTF_DestroyText(fpsText);
        TTF_DestroyText(menuText);
        //Texture
    }

    //Boutons
    void RenderBoutons(const SDL_FRect &rect, TTF_Text *buttonText, Uint8 buttonr, Uint8 buttong, Uint8 buttonb) {
        SDL_SetRenderDrawColor(renderer, buttonr, buttong, buttonb, 255);
        SDL_RenderFillRect(renderer, &rect);
        //Dessiner Texte au centre du boutton
        if (buttonText != nullptr) {
            int textW, textH; //Longeur/Largeur
            TTF_GetTextSize(buttonText, &textW, &textH);


            float textX = rect.x + (rect.w - textW) / 2.0f;
            float textY = rect.y + (rect.h - textH) / 2.0f;

            TTF_DrawRendererText(buttonText, textX, textY);
        }
    }

    void UpdateBackgroundTint(const float deltaTime) {
        constexpr float speed = 5.0f;
        colorTime += deltaTime * speed;

        constexpr float Amplitude = 60.0f;
        constexpr float MidPoint = 144.0f;

        r = static_cast<Uint8>(std::clamp(std::sin(colorTime) * Amplitude + MidPoint, 0.0f, 255.0f));
        g = static_cast<Uint8>(std::clamp(std::sin(colorTime + 2.0f) * Amplitude + MidPoint, 0.0f, 255.0f));
        b = static_cast<Uint8>(std::clamp(std::sin(colorTime + 4.0f) * Amplitude + MidPoint, 0.0f, 255.0f));
    }
//To calculate the fps ingame
    void CalculateFPS(const float deltaTime) {
        frameTimes.push_back(deltaTime);
        if (frameTimes.size() > MAX_SAMPLES) {
            frameTimes.erase(frameTimes.begin());
        }
        const float sum = std::accumulate(frameTimes.begin(), frameTimes.end(), 0.0f);
        const float avgDelta = sum / static_cast<float>(frameTimes.size());
        currentFPS = (avgDelta > 0) ? 1.0f / avgDelta : 0;

        if (shouldUpdateText) {
            std::string fpsStr = "FPS: " + std::to_string(static_cast<int>(currentFPS));
            TTF_SetTextString(fpsText, fpsStr.c_str(), 0);
            shouldUpdateText = false; // Reset the flag
        }
    }

    //Menu
    void Menu(float deltaTime) {
        SDL_Event MenuEvents;

        UpdateBackgroundTint(deltaTime);
        TTF_SetTextColor(menuText, r,g,b,255);

        //clear everything out
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        //Background menu

        TTF_DrawRendererText(menuText, 700,300);
        TTF_DrawRendererText(fpsText, 1800, 10);
        SDL_RenderPresent(renderer);
    }
    //Choose Character
    void ChooseCharacter(float deltaTime) {

    }
    //Game
    void Game(float deltaTime) {

    }
    //Options
    void Options(float deltaTime) {

    }


public:
    SDL_AppResult RunCallBacks() {
        static uint64_t lastTime = SDL_GetTicks();
        //temps global
        const uint64_t currentTime = SDL_GetTicks();
        deltaTime = static_cast<float>(currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        //fps
        CalculateFPS(deltaTime);
        switch (StateActuel) {
            case State::Menu:
                Menu(deltaTime);
            break;
            case State::ChooseCharacter:
                ChooseCharacter(deltaTime);
                break;
            case State::Game:
                Game(deltaTime);
            break;
            case State::Options:
                Options(deltaTime);
                break;
            case State::Quit:
                return SDL_APP_SUCCESS;
        }
        return SDL_APP_CONTINUE;
    }

};

SDL_AppResult
SDL_AppInit(void **appstate, int argc, char *argv[]) {
    GameApp &app = GameApp::GetInstance();
    return SDL_APP_CONTINUE;
}
//les events touches etc
SDL_AppResult
SDL_AppEvent(void *appstate, SDL_Event *event) {
    GameApp &app = GameApp::GetInstance();

    return SDL_APP_CONTINUE;
}
SDL_AppResult
SDL_AppIterate(void *appstate) {
    return GameApp::GetInstance().RunCallBacks();
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    TTF_Quit();
}

