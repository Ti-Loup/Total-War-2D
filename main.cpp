
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
//to render a circle
struct Circle { float circleX, circleY, radius; };

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

    TTF_Font *StartFont = nullptr;
    TTF_Font *TutorialFont = nullptr;
    TTF_Font *OptionsFont = nullptr;
    TTF_Font *QuitFont = nullptr;
    TTF_Font *CreditsFont = nullptr;
    TTF_Text *textStart = nullptr;
    TTF_Text *textTutorial = nullptr;
    TTF_Text *textOptions = nullptr;
    TTF_Text *textQuit = nullptr;
    TTF_Text *textCredits = nullptr;

    //Bouton Menu
    SDL_FRect BoutonPlay = {760, 600, 400, 80};
    SDL_FRect BoutonTutorial = {785, 700, 350, 70};
    SDL_FRect BoutonOptions = {810, 790, 300, 60};
    SDL_FRect BoutonQuit = {835, 870, 250, 50};
    SDL_FRect BoutonCredits = {860, 940, 200, 40};

    // -> Choose Faction <-
    TTF_Font *factionSelectionTitleFont = nullptr;
    TTF_Text *factionSelectionTitleText = nullptr;
    TTF_Font *factionSelectionFactionBonusFont = nullptr;
    TTF_Text *factionSelectionFactionBonusText = nullptr;
    TTF_Font *factionSelectionGeneralKnightFont = nullptr;
    TTF_Font *factionSelectionGeneralVikingFont = nullptr;
    TTF_Font *factionSelectionGeneralSamuraiFont = nullptr;
    TTF_Text *factionSelectionGeneralKnightText = nullptr;
    TTF_Text *factionSelectionLoreknightText = nullptr;
    TTF_Text *factionSelectionGeneralVikingText = nullptr;
    TTF_Text *factionSelectionLoreVikingText = nullptr;
    TTF_Text *factionSelectionGeneralSamuraiText = nullptr;
    TTF_Text *factionSelectionLoreSamuraiText = nullptr;
    TTF_Text *factionSelectionStartCampaignText = nullptr;

    SDL_FRect BoutonKnight = {400, 150, 100,100};
    SDL_FRect BoutonViking = {900, 150, 100, 100};
    SDL_FRect BoutonSamurai = {1400, 150, 100, 100};
    SDL_FRect BoutonStartCampaign = {850, 1000, 250, 40};

    int selectedFaction = 0;

    // -> OPTION <-
    struct VolumeSlider {
        float x, y, width, height;  // volume bar
        float value;
        bool bCursorIsSliding = false;
    };
    //slider for the music
    VolumeSlider volumeMusicSlider = {650,500,600,20,0.5f};

    TTF_Font *optionsTitleFont = nullptr;
    TTF_Font *optionsMusicFont = nullptr;
    TTF_Text *optionsTitleText = nullptr;
    TTF_Text *optionsMusicText = nullptr;

    // -> GAME <-

    // -> CREDITS <-
    TTF_Font *creditsTitleFont = nullptr;
    TTF_Text *creditsTitleText = nullptr;
    TTF_Font *creditsRoleTitleFont = nullptr;
    TTF_Text *creditsRoleTitleText = nullptr;
    TTF_Font *creditsRoleNameFont = nullptr;
    TTF_Text *creditsRoleNameText = nullptr;

    // -> OTHER <-
    TTF_Font *fpsFont = nullptr;
    TTF_Text *fpsText = nullptr;
    TTF_TextEngine *textEngine = nullptr;

    //Return Menu Button
    Circle BoutonReturn = {1875,1025,30};

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

    //AUDIO
    MIX_Mixer *mixer = nullptr;
    MIX_Track *trackMusique = nullptr;
    MIX_Track *trackGame = nullptr;
    MIX_Track *trackSFX = nullptr;

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
        }
        //SDL INIT
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == false) {
            SDL_LogCritical(1, "failed to initialize SDL %s", SDL_GetError());
            abort();
        }
        //TTF_INIT
        if (TTF_Init() == false) {
            SDL_LogCritical(1, "SDL_ttf failed to initialize! %s", SDL_GetError());
            abort();
        }
        //Music Menu
        if (!MIX_Init()) {
            SDL_LogCritical(1, "SDL_mixer failed to initialize! %s", SDL_GetError());
            abort();
        }
        mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
        if (!mixer) {
            SDL_LogWarn(0, "Couldn't create mixer: %s", SDL_GetError());
        }

        // Musique Menu
        char *pathMenu = nullptr;
        SDL_asprintf(&pathMenu, "assets/The Fall of Arcana.mp3", SDL_GetBasePath());
        MIX_Audio *audioMenu = MIX_LoadAudio(mixer, pathMenu, false);
        if (audioMenu == nullptr) {
            SDL_Log("impossible de charger audio de audioMenu%s", SDL_GetError());
        } else {
            SDL_Log("audio is working");
        }
        SDL_free(pathMenu);

        if (audioMenu) {
            trackMusique = MIX_CreateTrack(mixer);
            MIX_SetTrackAudio(trackMusique, audioMenu);
            MIX_PlayTrack(trackMusique, -1); //loop infini
            MIX_SetTrackGain(trackMusique, 0.5f);//volume
        }




        // -> MENU <-
        menuFont = TTF_OpenFont("assets/KnightFont.ttf",108);
        if (menuFont == nullptr) {
            SDL_LogCritical(1, "Failed to load font: %s", SDL_GetError());
            abort();
        }
        menuText = TTF_CreateText(textEngine, menuFont, "Total Battle 2D", 25);
        if (menuText == nullptr) {
            SDL_LogWarn(0,"failed to create text for menuText", SDL_GetError());
        }
        if (TTF_SetTextColor(menuText, 0,0,0,255)==false) {
            SDL_LogWarn(1,"failed to set the color of menuText", SDL_GetError());
        }
        //bouton Menu
        StartFont = TTF_OpenFont("assets/font.ttf",75);
        TutorialFont = TTF_OpenFont("assets/font.ttf",60);
        OptionsFont = TTF_OpenFont("assets/font.ttf",50);
        QuitFont = TTF_OpenFont("assets/font.ttf",40);
        CreditsFont = TTF_OpenFont("assets/font.ttf",30);

        textStart = TTF_CreateText(textEngine, StartFont, "Start", 25);
        if (textStart == nullptr) {
            SDL_LogWarn(1,"failed to create text for textStart", SDL_GetError());
        }
        textTutorial = TTF_CreateText(textEngine, TutorialFont, "Tutorial", 25);
        if (textTutorial == nullptr) {
            SDL_LogWarn(1,"failed to create text for textTutorial", SDL_GetError());
        }
        textOptions = TTF_CreateText(textEngine, OptionsFont, "Options", 25);
        if (textOptions == nullptr) {
            SDL_LogWarn(1,"failed to create text for textOptions", SDL_GetError());
        }
        textQuit = TTF_CreateText(textEngine, QuitFont, "Quit", 25);
        if (textQuit == nullptr) {
            SDL_LogWarn(1,"failed to create text for textQuit", SDL_GetError());
        }
        textCredits = TTF_CreateText(textEngine, CreditsFont, "Credits", 25);
        if (textCredits == nullptr) {
            SDL_LogWarn(1,"failed to create text for textCredits", SDL_GetError());
        }

        // -> Faction Selection <-
        factionSelectionTitleFont = TTF_OpenFont("assets/font.ttf",50);
        factionSelectionFactionBonusFont = TTF_OpenFont("assets/font.ttf",40);
        factionSelectionGeneralKnightFont = TTF_OpenFont("assets/KnightFont.ttf",35);
        factionSelectionGeneralVikingFont = TTF_OpenFont("assets/VikingFont.otf",30);
        factionSelectionGeneralSamuraiFont = TTF_OpenFont("assets/SamuraiFont.ttf",15);
        factionSelectionTitleText = TTF_CreateText(textEngine,factionSelectionTitleFont, "Faction Selection", 25);
        if (factionSelectionTitleText == nullptr) {
            SDL_LogWarn(0,"failed to load the text of factionSelectionTitleText ", SDL_GetError());
        }
        factionSelectionFactionBonusText = TTF_CreateText(textEngine, factionSelectionFactionBonusFont,"Faction Bonus", 25);
        if (factionSelectionFactionBonusText == nullptr) {
            SDL_LogWarn(0, "failed to lad the text of factionSelectionFactionBonus");
        }
        factionSelectionGeneralKnightText = TTF_CreateText(textEngine, factionSelectionGeneralKnightFont, "----- + 5 \n ----- + 2 \n ----- + 2 \n ", 50);
        if (factionSelectionGeneralKnightText == nullptr) {
            SDL_LogWarn(0, "failed to load the text of factionSelectionGeneralKnightText", SDL_GetError());
        }
        factionSelectionLoreknightText = TTF_CreateText(textEngine, factionSelectionGeneralKnightFont,"Dans un monde de constante guerre ... \nles knights sont des ", 50);
        if (factionSelectionLoreknightText == nullptr) {
            SDL_LogWarn(0,"failed to load the text of factionSelectionLoreKnightText", SDL_GetError());
        }
        factionSelectionGeneralVikingText = TTF_CreateText(textEngine, factionSelectionGeneralVikingFont, "----- + 5 \n ----- + 2 \n ----- + 2 \n ", 50);
        if (factionSelectionGeneralVikingText == nullptr) {
            SDL_LogWarn(0, "failed to load the text of factionSelectionGeneralVikingText", SDL_GetError());
        }
        factionSelectionLoreVikingText = TTF_CreateText(textEngine, factionSelectionGeneralVikingFont,"Dans un monde de constante guerre ... \nles Vikings sont des ...", 50);
        if (factionSelectionLoreVikingText == nullptr) {
            SDL_LogWarn(0,"failed to load the text of factionSelectionLoreVikingText", SDL_GetError());
        }
        factionSelectionGeneralSamuraiText = TTF_CreateText(textEngine, factionSelectionGeneralSamuraiFont, "----- + 5 \n ----- + 2 \n ----- + 2 \n ", 50);
        if (factionSelectionGeneralSamuraiText == nullptr) {
            SDL_LogWarn(0, "failed to load the text of factionSelectionGeneralSamuraiText", SDL_GetError());
        }
        factionSelectionLoreSamuraiText = TTF_CreateText(textEngine, factionSelectionGeneralSamuraiFont,"Dans un monde de constante guerre ... \nles Samurai sont des ", 50);
        if (factionSelectionLoreSamuraiText == nullptr) {
            SDL_LogWarn(0,"failed to load the text of factionSelectionLoreSamuraiText", SDL_GetError());
        }
        factionSelectionStartCampaignText = TTF_CreateText(textEngine, factionSelectionGeneralKnightFont, "Start Campaign",25);
        if (factionSelectionStartCampaignText == nullptr) {

        }

        // -> OPTION <-
        optionsTitleFont = TTF_OpenFont("assets/font.ttf", 50);
        optionsMusicFont = TTF_OpenFont("assets/font.ttf", 20);
        optionsTitleText = TTF_CreateText(textEngine, optionsTitleFont,"Options", 25);
        optionsMusicText = TTF_CreateText(textEngine, optionsMusicFont,"Volume Music", 25);
        // -> GAME <-

        // -> CREDITS <-
        creditsTitleFont = TTF_OpenFont("assets/font.ttf", 50);
        creditsRoleTitleFont = TTF_OpenFont("assets/font.ttf", 40);
        creditsRoleNameFont = TTF_OpenFont("assets/font.ttf", 30);
        creditsTitleText = TTF_CreateText(textEngine, creditsTitleFont,"Credits", 20);
        if (creditsTitleText == nullptr) {
            SDL_LogWarn(0,"failed to load the text of creditsTitleText");
        }
        creditsRoleTitleText = TTF_CreateText(textEngine, creditsRoleTitleFont,"Programmer", 25);
        if (creditsRoleTitleText == nullptr) {
            SDL_LogWarn(0,"failed to load the text of creditsRoleTitleText");
        }
        creditsRoleNameText = TTF_CreateText(textEngine, creditsRoleNameFont, "Louis-Philippe Gauvin", 25);
        if (creditsRoleNameText == nullptr) {
            SDL_LogWarn(0,"failed to load the text of creditsRoleNameText");
        }
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
    // ---------------------------------
        TTF_CloseFont(fpsFont);
        TTF_CloseFont(menuFont);
        TTF_CloseFont(StartFont);
        TTF_CloseFont(TutorialFont);
        TTF_CloseFont(OptionsFont);
        TTF_CloseFont(QuitFont);
        TTF_CloseFont(CreditsFont);
        TTF_CloseFont(factionSelectionTitleFont);
        TTF_CloseFont(factionSelectionFactionBonusFont);
        TTF_CloseFont(factionSelectionGeneralKnightFont);
        TTF_CloseFont(factionSelectionGeneralVikingFont);
        TTF_CloseFont(factionSelectionGeneralSamuraiFont);
        TTF_CloseFont(creditsTitleFont);
        TTF_CloseFont(creditsRoleTitleFont);
        TTF_CloseFont(creditsRoleNameFont);
        TTF_CloseFont(optionsTitleFont);
        TTF_CloseFont(optionsMusicFont);
    // ---------------------------------
        TTF_DestroyText(fpsText);
        TTF_DestroyText(menuText);
        TTF_DestroyText(textStart);
        TTF_DestroyText(textTutorial);
        TTF_DestroyText(textOptions);
        TTF_DestroyText(textQuit);
        TTF_DestroyText(textCredits);
        TTF_DestroyText(factionSelectionTitleText);
        TTF_DestroyText(factionSelectionFactionBonusText);
        TTF_DestroyText(factionSelectionGeneralKnightText);
        TTF_DestroyText(factionSelectionLoreknightText);
        TTF_DestroyText(factionSelectionGeneralVikingText);
        TTF_DestroyText(factionSelectionLoreVikingText);
        TTF_DestroyText(factionSelectionGeneralSamuraiText);
        TTF_DestroyText(factionSelectionLoreSamuraiText);
        TTF_DestroyText(factionSelectionStartCampaignText);
        TTF_DestroyText(creditsTitleText);
        TTF_DestroyText(creditsRoleTitleText);
        TTF_DestroyText(creditsRoleNameText);
        TTF_DestroyText(optionsTitleText);
        TTF_DestroyText(optionsMusicText);
    // ---------------------------------
    }

    //to render the Buttons
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

    //To render the sliders
    void RenderSlider(const VolumeSlider &volumeSlider, const char *music) {
        //empty part
        SDL_SetRenderDrawColor(renderer, 255, 204, 204, 255);
        SDL_FRect emptySlider = {volumeSlider.x, volumeSlider.y, volumeSlider.width, volumeSlider.height};
        SDL_RenderFillRect(renderer, &emptySlider);
        //full part
        SDL_SetRenderDrawColor(renderer, 255, 102, 102, 255);
        SDL_FRect fullSlider = {volumeSlider.x, volumeSlider.y, volumeSlider.width * volumeSlider.value, volumeSlider.height};
        SDL_RenderFillRect(renderer, &fullSlider);

        float handleX = volumeSlider.x + volumeSlider.width * volumeSlider.value - 10;
        float handleY = volumeSlider.y - 10;
        SDL_FRect handle = {handleX, handleY, 20,40};
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
        SDL_RenderFillRect(renderer, &handle);
        std::string percentage = std::to_string((int)(volumeSlider.value * 100)) + "%";
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



        //Boutons menu
        RenderBoutons(BoutonPlay, textStart, 20, 20, 20);
        RenderBoutons(BoutonTutorial, textTutorial, 20, 20, 20);
        RenderBoutons(BoutonOptions, textOptions, 20, 20, 20);
        RenderBoutons(BoutonQuit, textQuit, 20, 20, 20);
        RenderBoutons(BoutonCredits, textCredits, 20, 20, 20);


        TTF_DrawRendererText(menuText, 700,150);
        TTF_DrawRendererText(fpsText, 1800, 10);
        SDL_RenderPresent(renderer);
    }

    //Choose Character
    void ChooseCharacter(float deltaTime) {
        UpdateBackgroundTint(deltaTime);


        //clear everything out
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //title
        TTF_DrawRendererText(factionSelectionTitleText, 750, 50);
        TTF_DrawRendererText(factionSelectionFactionBonusText, 1600,400);
        RenderBoutons(BoutonKnight, nullptr, 255,255,0);
        RenderBoutons(BoutonViking, nullptr, 0,0,255);
        RenderBoutons(BoutonSamurai, nullptr, 255,0,0);
        RenderBoutons(BoutonStartCampaign, factionSelectionStartCampaignText, 60,60,60);

        if (selectedFaction == 0) {
            TTF_DrawRendererText(factionSelectionGeneralKnightText, 1600,500);
            TTF_DrawRendererText(factionSelectionLoreknightText, 200, 900);
        }
        else if (selectedFaction == 1) {
            TTF_DrawRendererText(factionSelectionGeneralVikingText, 1600,500);
            TTF_DrawRendererText(factionSelectionLoreVikingText, 200, 900);
        }
        else if (selectedFaction == 2) {
            TTF_DrawRendererText(factionSelectionGeneralSamuraiText, 1600,500);
            TTF_DrawRendererText(factionSelectionLoreSamuraiText, 200, 900);
        }

        RenderBoutonCercle(BoutonReturn, nullptr, nullptr,80, 80, 80);
        SDL_RenderPresent(renderer);
    }
    //Game
    void Game(float deltaTime) {
        UpdateBackgroundTint(deltaTime);


        //clear everything out
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }

    //Tutorial
    void Tutorial (float deltaTime) {
        UpdateBackgroundTint(deltaTime);
        //clear everything out
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        RenderBoutonCercle(BoutonReturn, nullptr, nullptr,80, 80, 80);
        SDL_RenderPresent(renderer);
    }
    //Options
    void Options(float deltaTime) {
        UpdateBackgroundTint(deltaTime);


        //clear everything out
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        TTF_DrawRendererText(optionsTitleText, 850,50);
        TTF_DrawRendererText(optionsMusicText, 660,450);
        RenderSlider(volumeMusicSlider, "Volume Music");

        RenderBoutonCercle(BoutonReturn, nullptr, nullptr,80, 80, 80);
        SDL_RenderPresent(renderer);
    }

    void Credits(float deltaTime) {
        UpdateBackgroundTint(deltaTime);


        //clear everything out
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        TTF_DrawRendererText(creditsTitleText, 850,50);
        //role 1
        TTF_DrawRendererText(creditsRoleTitleText, 1500,400);
        TTF_DrawRendererText(creditsRoleNameText, 1450, 500);

        RenderBoutonCercle(BoutonReturn, nullptr, nullptr,80, 80, 80);
        SDL_RenderPresent(renderer);
    }


public:
    //To render the circles
    void RenderCircle(float circleX, float circleY, float radius) {
        for (float y = -radius; y <= radius; y++) {
            float distanceX = sqrtf(radius * radius - y * y);
            SDL_RenderLine(renderer, circleX - distanceX, circleY + y, circleX + distanceX,circleY + y);
        }
    }
    void RenderBoutonCercle(const Circle &circle, TTF_Text *buttonText, SDL_Texture *texture,Uint8 buttonr, Uint8 buttong, Uint8 buttonb) {
        SDL_SetRenderDrawColor(renderer, 120,40,120,255);
        RenderCircle(circle.circleX, circle.circleY, circle.radius);

        // Render texture
        if (texture != nullptr) {
            SDL_FRect dst = {
                circle.circleX - circle.radius,
                circle.circleY - circle.radius,
                circle.radius * 2,
                circle.radius * 2
            };
            SDL_RenderTexture(renderer, texture, nullptr, &dst);
        }

        if (buttonText != nullptr) {
            int textW, textH;
            TTF_GetTextSize(buttonText, &textW, &textH);
            TTF_DrawRendererText(buttonText, circle.circleX - textW/2, circle.circleY - textH/2 );
        }
    }
    //if circle been clicked
    bool ClickInsideCircle(float mouseX, float mouseY, const Circle &circle) {
        float distanceX = mouseX - circle.circleX;
        float distanceY = mouseY - circle.circleY;
        return (distanceX* distanceX + distanceY * distanceY) <= (circle.radius * circle.radius);
    }

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
                if (trackMusique && !MIX_TrackPlaying(trackMusique)) {
                    MIX_PlayTrack(trackMusique, -1);
                }
                Menu(deltaTime);
                break;
            case State::ChooseCharacter:
                ChooseCharacter(deltaTime);
                break;
            case State::Game:
                Game(deltaTime);
                break;
            case State::Tutorial:
                Tutorial(deltaTime);
                break;
            case State::Options:
                Options(deltaTime);
                break;
            case State::Credits:
                Credits(deltaTime);
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

    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && event->button.button == SDL_BUTTON_LEFT) {
        //Les variables
        float nouveauX, nouveauY;

        //new variables if fullScreen vs window mod
        SDL_RenderCoordinatesFromWindow(app.renderer, event->button.x, event->button.y, &nouveauX, &nouveauY);
        SDL_FPoint MousePT = {nouveauX, nouveauY};

        //IF IN MENU
        if (app.StateActuel == State::Menu) {
            if (SDL_PointInRectFloat(&MousePT, &app.BoutonPlay)) {
                app.StateActuel = State::ChooseCharacter;
            }
            if (SDL_PointInRectFloat(&MousePT, &app.BoutonTutorial)) {
                app.StateActuel = State::Tutorial;
            }
            if (SDL_PointInRectFloat(&MousePT, &app.BoutonOptions)) {
                app.StateActuel = State::Options;
            }
            if (SDL_PointInRectFloat(&MousePT, &app.BoutonQuit)) {
                app.StateActuel = State::Quit;
            }
            if (SDL_PointInRectFloat(&MousePT, &app.BoutonCredits)) {
                app.StateActuel = State::Credits;
            }
        }
        //IF IN CHOOSE FACTION
        if (app.StateActuel == State::ChooseCharacter) {
            if (SDL_PointInRectFloat(&MousePT, &app.BoutonKnight)) {
                app.selectedFaction = 0;
            }
            if (SDL_PointInRectFloat(&MousePT, &app.BoutonViking)) {
                app.selectedFaction = 1;
            }
            if (SDL_PointInRectFloat(&MousePT, &app.BoutonSamurai)) {
                app.selectedFaction = 2;
            }
            if (SDL_PointInRectFloat(&MousePT, &app.BoutonStartCampaign)) {
                app.StateActuel= State::Game;
            }
            //Circle
            if (app.ClickInsideCircle(nouveauX, nouveauY, app.BoutonReturn)) {
                app.StateActuel = State::Menu;
            }
        }
        //TUTORIAL
        if (app.StateActuel == State::Tutorial) {
            if (app.ClickInsideCircle(nouveauX, nouveauY, app.BoutonReturn)) {
                app.StateActuel = State::Menu;
            }
        }

        //IF IN OPTIONS
        if (app.StateActuel == State::Options) {
            if (app.ClickInsideCircle(nouveauX, nouveauY, app.BoutonReturn)) {
                app.StateActuel = State::Menu;
            }
            GameApp::VolumeSlider &s = app.volumeMusicSlider;
            SDL_FRect sliderRect = {s.x, s.y - 10, s.width, s.height + 20};
            SDL_FPoint pt = {nouveauX, nouveauY};
            if (SDL_PointInRectFloat(&pt, &sliderRect)) {
                s.bCursorIsSliding = true;
                s.value = std::clamp((nouveauX - s.x) / s.width, 0.0f, 1.0f);
                MIX_SetTrackGain(app.trackMusique, s.value);//the value of the gain of the music is changing based of the slider
            }
        }
        //IF IN CREDITS
        if (app.StateActuel == State::Credits) {
            if (app.ClickInsideCircle(nouveauX, nouveauY, app.BoutonReturn)) {
                app.StateActuel = State::Menu;
            }
        }
    }
    if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
        app.volumeMusicSlider.bCursorIsSliding = false;
    }
    //for the slider
    if (event->type == SDL_EVENT_MOUSE_MOTION && app.volumeMusicSlider.bCursorIsSliding) {
        float mouseX, mouseY;
        SDL_RenderCoordinatesFromWindow(app.renderer, event->motion.x, event->motion.y, &mouseX, &mouseY);
        app.volumeMusicSlider.value = std::clamp((mouseX - app.volumeMusicSlider.x) / app.volumeMusicSlider.width, 0.0f, 1.0f);
        MIX_SetTrackGain(app.trackMusique, app.volumeMusicSlider.value);
    }

    if (event->type == SDL_EVENT_KEY_DOWN) {
        //To put game in fullscreen
        if (event->key.scancode == SDL_SCANCODE_F) {
            //flag
            Uint32 FullScreenflag = SDL_GetWindowFlags(app.window);

            //si on est en plein ecran alors on retourne en fenetrer
            if (FullScreenflag & SDL_WINDOW_FULLSCREEN) {
                SDL_SetWindowFullscreen(app.window, 0); //0 -> fenetrer
            }
            //Sinon on va en fullscreen
            else {
                SDL_SetWindowFullscreen(app.window, SDL_WINDOW_FULLSCREEN);
            }
        }
        //To escape
        if (event->key.scancode == SDL_SCANCODE_ESCAPE) {
            app.StateActuel = State::Quit;
        }
    }

    //If pressed on windowX -> Exit
    if (event->type == SDL_EVENT_QUIT) {
        app.StateActuel = State::Quit;
        return SDL_APP_CONTINUE;
    }

    return SDL_APP_CONTINUE;
}
SDL_AppResult
SDL_AppIterate(void *appstate) {
    return GameApp::GetInstance().RunCallBacks();
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    TTF_Quit();
}

