
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
#include "TileMap.h"
#include "Camera.h"
#include "Province.h"
#include "Settlements.h"
#include "Player.h"

/*
 *TODO LIST For version 0.1.0
 *
 *To DO :
 *Buildings of a region + UI of that region
 *Money System
 *Population System
 *Turn base system
 *Roads
 *----------------------------------------------
 *Character +Movement Maximum per turn
 *
 *Finished:
 *TileMap
 *Camera (missing mouse touch edge)
 *
 */



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
    //cursor
    SDL_Cursor *cursor = nullptr;

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
    //kingdomNames
    TTF_Font *gameKingdomNameFont = nullptr;
    TTF_Text *gameKingdomKnightNameText = nullptr;
    TTF_Text *gameKingdomVikingNameText = nullptr;
    TTF_Text *gameKingdomSamuraiNameText = nullptr;
    TTF_Font *gameGeneralFont = nullptr;
    TTF_Text *gameCurrentMoneyUiText = nullptr;
    TTF_Text *gameAnticipatedMoneyUiText = nullptr;
    TTF_Text *gameNumberOfTurnText = nullptr;
    TTF_Font *gameBuildingCostUIFont = nullptr;
    TTF_Text *gameBuildingCostUIText = nullptr;
    //Buttons UI
    bool bButtonUIBuildingIsPressed = true;
    bool bButtonUIGarrisonIsPressed = false;
    float firstButton = 800.f;
    SDL_FRect provinceButtonUIBuilding = {firstButton,1030.f,40.f,40.f};
    SDL_FRect provinceButtonUIGarrison = {firstButton + 50.f,1030.f,40.f,40.f};
    SDL_Texture *provinceTextureUIBuilding = nullptr;
    SDL_Texture *provinceTextureUIGarrison = nullptr;
    Circle NextTurnButton = {1825.f, 1000.f, 55};

    //End Turn
    int currentTurn = 1;
    FactionZone currentFactionTurn = FactionZone::Knight;//start with player


    //Buildings Texture
    //hammer
    SDL_Texture *hammerUIBuildingUpgradeTexture = nullptr;
    //                 ~ KNIGHT ~
    //capital
    SDL_Texture *capitalBuildingUpgrade1Knight = nullptr;
    SDL_Texture *capitalBuildingUpgrade2Knight = nullptr;
    SDL_Texture *capitalBuildingUpgrade3Knight = nullptr;
    SDL_Texture *capitalBuildingUpgrade4Knight = nullptr;
    SDL_Texture *capitalBuildingUpgrade5Knight = nullptr;
    //castle
    SDL_Texture *castleBuildingUpgrade1Knight = nullptr;
    SDL_Texture *castleBuildingUpgrade2Knight = nullptr;
    SDL_Texture *castleBuildingUpgrade3Knight = nullptr;
    SDL_Texture *castleBuildingUpgrade4Knight = nullptr;
    SDL_Texture *castleBuildingUpgrade5Knight = nullptr;
    //Village
    SDL_Texture *villageBuildingUpgrade1Knight = nullptr;
    SDL_Texture *villageBuildingUpgrade2Knight = nullptr;
    SDL_Texture *villageBuildingUpgrade3Knight = nullptr;
    //                 ~ VIKING ~
    //capital
    SDL_Texture *capitalBuildingUpgrade1Viking = nullptr;
    SDL_Texture *capitalBuildingUpgrade2Viking = nullptr;
    SDL_Texture *capitalBuildingUpgrade3Viking = nullptr;
    SDL_Texture *capitalBuildingUpgrade4Viking = nullptr;
    SDL_Texture *capitalBuildingUpgrade5Viking = nullptr;
    //Castle
    SDL_Texture *castleBuildingUpgrade1Viking = nullptr;
    SDL_Texture *castleBuildingUpgrade2Viking = nullptr;
    SDL_Texture *castleBuildingUpgrade3Viking = nullptr;
    SDL_Texture *castleBuildingUpgrade4Viking = nullptr;
    SDL_Texture *castleBuildingUpgrade5Viking = nullptr;
    //Village
    SDL_Texture *villageBuildingUpgrade1Viking = nullptr;
    SDL_Texture *villageBuildingUpgrade2Viking = nullptr;
    SDL_Texture *villageBuildingUpgrade3Viking = nullptr;
    //                 ~ SAMURAI ~
    //capital
    SDL_Texture *capitalBuildingUpgrade1Samurai = nullptr;
    SDL_Texture *capitalBuildingUpgrade2Samurai = nullptr;
    SDL_Texture *capitalBuildingUpgrade3Samurai = nullptr;
    SDL_Texture *capitalBuildingUpgrade4Samurai = nullptr;
    SDL_Texture *capitalBuildingUpgrade5Samurai = nullptr;
    //castle
    SDL_Texture *castleBuildingUpgrade1Samurai = nullptr;
    SDL_Texture *castleBuildingUpgrade2Samurai = nullptr;
    SDL_Texture *castleBuildingUpgrade3Samurai = nullptr;
    SDL_Texture *castleBuildingUpgrade4Samurai = nullptr;
    SDL_Texture *castleBuildingUpgrade5Samurai = nullptr;
    //village
    SDL_Texture *villageBuildingUpgrade1Samurai = nullptr;
    SDL_Texture *villageBuildingUpgrade2Samurai = nullptr;
    SDL_Texture *villageBuildingUpgrade3Samurai = nullptr;
    //UI TextFont
    TTF_Font *gameStatUITitleFont = nullptr;

    TTF_Font *gameStatUIFont = nullptr;
    TTF_Text *gameStatUITitleText = nullptr;
    TTF_Text *gameStatUIText = nullptr;

    //texture provinces when Unzoom
    SDL_Texture *provinceKnightBannerTexture = nullptr;
    SDL_Texture *provinceVikingBannerTexture = nullptr;
    SDL_Texture *provinceSamuraiBannerTexture = nullptr;
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

    //For the tileMap
    TileMap* tileMap = nullptr;
    //For the camera
    Camera camera;
    bool bIsMovingCamera = false;
    float lastMouseX = 0;
    float lastMouseY = 0;

    std::vector<Settlement> settlements;

    // UI Campaign
    bool bHasClickedOnASettlement = false;
    int selectedSettlementIndex = -1;
    int hoveredSettlementIndex = -1;
    int hoveredSlotIndex = -1;
    int buildMenuSlotIndex       = -1;
    int buildMenuSettlementIndex = -1;
    int hoveredCategory          = -1;
    int hoveredCardIndex = -1;
    // 0=Military 1=AdvMilitary 2=Defence 3=Economy 4=Religion
    BuildingType hoveredBuilding = BuildingType::None;
    std::vector<SDL_FRect> mainBuildingSlotRects;
    SDL_FRect mainBuildingPopupRect = {0,0,0,0};

    //Provinces name + Faction Zone + which region is a capital
    std::vector<Province> provinces = {
        //knight
        {0, "NameRegion1", FactionZone::Knight, true},
        {1, "NameRegion2", FactionZone::Knight, false},//north
        {2, "NameRegion3", FactionZone::Knight, false},//south
        //viking
        {3, "NameRegion1", FactionZone::Viking, true},
        {4, "NameRegion2", FactionZone::Viking, false},//west
        {5, "NameRegion3", FactionZone::Viking, false},//est
        //samurai
        {6, "NameRegion1", FactionZone::Samurai,true},
        {7, "NameRegion2", FactionZone::Samurai,false},//est
        {8, "NameRegion3", FactionZone::Samurai,false},//west
    };

    std::vector<SDL_FRect> tierPopupRects; // 1 rect per building
    int tierPopupMaxTier = 0;

    //Player
    Player player;

private://constructor
    GameApp() {

        //SDL INIT
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == false) {
            SDL_LogCritical(1, "failed to initialize SDL %s", SDL_GetError());
            abort();
        }
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
        //TTF_INIT
        if (TTF_Init() == false) {
            SDL_LogCritical(1, "SDL_ttf failed to initialize! %s", SDL_GetError());
            abort();
        }
        //cursor
        SDL_Surface* cursorSurface = IMG_Load("assets/cursor.png");
        if (cursorSurface) {
            // Scale to desired size (e.g. 64x64)
            SDL_Surface* scaledSurface = SDL_ScaleSurface(cursorSurface, 32, 32, SDL_SCALEMODE_NEAREST);
            SDL_DestroySurface(cursorSurface);

            if (scaledSurface) {
                cursor = SDL_CreateColorCursor(scaledSurface, 0, 0);
                SDL_DestroySurface(scaledSurface);
                SDL_SetCursor(cursor);
            }
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
        factionSelectionGeneralKnightText = TTF_CreateText(textEngine, factionSelectionGeneralKnightFont, "Strong start economie\nand crossbows\nFaith is all \n ", 50);
        if (factionSelectionGeneralKnightText == nullptr) {
            SDL_LogWarn(0, "failed to load the text of factionSelectionGeneralKnightText", SDL_GetError());
        }
        factionSelectionLoreknightText = TTF_CreateText(textEngine, factionSelectionGeneralKnightFont,"The Knight are a very respected and a united country\nWith strong crossbow and cavalry, They're putting all their ennemy to their knees\nThey will fight anyone who denies they're rightful King", 250);
        if (factionSelectionLoreknightText == nullptr) {
            SDL_LogWarn(0,"failed to load the text of factionSelectionLoreKnightText", SDL_GetError());
        }
        factionSelectionGeneralVikingText = TTF_CreateText(textEngine, factionSelectionGeneralVikingFont, "Raiding Bonuses \nHas access to strong berserkers\nCan call Odin \nWeak settlements incomes ", 150);
        if (factionSelectionGeneralVikingText == nullptr) {
            SDL_LogWarn(0, "failed to load the text of factionSelectionGeneralVikingText", SDL_GetError());
        }
        factionSelectionLoreVikingText = TTF_CreateText(textEngine, factionSelectionGeneralVikingFont,"These proud fighters of the north,The Vikings, are strong warriors who's melee skills exceeds all.\nStrenght is the only answer\nThey are ready to fight anyone who denies their jarl ", 250);
        if (factionSelectionLoreVikingText == nullptr) {
            SDL_LogWarn(0,"failed to load the text of factionSelectionLoreVikingText", SDL_GetError());
        }
        factionSelectionGeneralSamuraiText = TTF_CreateText(textEngine, factionSelectionGeneralSamuraiFont, "Ambush Bonuses\nPowerful Religion Bonuses \nStrong Powder Units \n ", 50);
        if (factionSelectionGeneralSamuraiText == nullptr) {
            SDL_LogWarn(0, "failed to load the text of factionSelectionGeneralSamuraiText", SDL_GetError());
        }
        factionSelectionLoreSamuraiText = TTF_CreateText(textEngine, factionSelectionGeneralSamuraiFont,"The Samurai have a great respect for tradition and honor\nThey are great fighter with very strong Katana units and strong cavalery\nThey are ready to fight anyone Who denies they're Shogun   ", 250);
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
        //CREATION OF TILES
        tileMap = new TileMap("assets/TileMap.png",16);
        tileMap->BakeToTexture(renderer);
        tileMap->LoadProvinceMap("assets/ProvinceMap.png");
        //UI Font
        gameStatUITitleFont = TTF_OpenFont("assets/Rubik.ttf", 25);
        gameStatUIFont = TTF_OpenFont("assets/Rubik.ttf", 20);
        gameBuildingCostUIFont = TTF_OpenFont("assets/Rubik.ttf", 15);
        gameStatUITitleText = TTF_CreateText(textEngine, gameStatUITitleFont,"GameStatue", 25);
        if (gameStatUITitleText == nullptr) {
            SDL_LogWarn(0,"failed to create the text gameStatUITitleText",SDL_GetError());
        }
        gameStatUIText = TTF_CreateText(textEngine, gameStatUIFont, "GameStatue", 25);
        if (gameStatUIText == nullptr) {
            SDL_LogWarn(0,"failed to create the text gameStatUIText",SDL_GetError());
        }
        gameGeneralFont = TTF_OpenFont("assets/Rubik.ttf", 20);
        gameCurrentMoneyUiText = TTF_CreateText(textEngine, gameGeneralFont, "0", 25);
        if (gameCurrentMoneyUiText == nullptr) {
            SDL_LogWarn(0, "failed to create the text gameCurrentMoneyUiText",SDL_GetError());
        }
        gameAnticipatedMoneyUiText = TTF_CreateText(textEngine, gameGeneralFont, "(0)", 25);
        if (gameAnticipatedMoneyUiText == nullptr) {
            SDL_LogWarn(0,"failed to create the text gameAnticipatedMoneyUiText", SDL_GetError());
        }
        gameNumberOfTurnText = TTF_CreateText(textEngine, gameGeneralFont, "0", 25);
        if (gameNumberOfTurnText == nullptr) {
            SDL_LogWarn(0,"failed to create the text gameNumberOfTurn",SDL_GetError());
        }
        gameBuildingCostUIText = TTF_CreateText(textEngine, gameBuildingCostUIFont, "0", 25);
        if (gameBuildingCostUIText == nullptr) {
            SDL_LogWarn(0,"failed to create the text gameBuildingCostUIText", SDL_GetError());
        }

        //CREATION OF THE SETTLEMENTS
        //KNIGHT
        //CAPITAL REGION
        settlements.emplace_back(SettlementType::Capital, 0, 42, 50, FactionZone::Knight);
        settlements.back().settlementData.cityName = "Patate";
        settlements.emplace_back(SettlementType::Village, 0, 46, 35, FactionZone::Knight);
        settlements.back().settlementData.cityName = "Patate2";
        settlements.emplace_back(SettlementType::Village, 0, 52, 42, FactionZone::Knight);
        settlements.back().settlementData.cityName = "Patate3";
        settlements.emplace_back(SettlementType::Village, 0, 37, 61, FactionZone::Knight);
        settlements.back().settlementData.cityName = "Patate4";
        //NORTH REGION
        settlements.emplace_back(SettlementType::Castle, 1, 22, 28, FactionZone::Knight);
        settlements.emplace_back(SettlementType::Village, 1, 16, 12, FactionZone::Knight);
        settlements.emplace_back(SettlementType::Village, 1, 29, 34, FactionZone::Knight);
        settlements.emplace_back(SettlementType::Village, 1, 25, 46, FactionZone::Knight);
        //SOUTH REGION
        settlements.emplace_back(SettlementType::Castle, 2, 61,56, FactionZone::Knight);
        settlements.emplace_back(SettlementType::Village, 2, 67, 50, FactionZone::Knight);
        settlements.emplace_back(SettlementType::Village, 2, 56, 67, FactionZone::Knight);

        // Vikings
        //NORTH CAPITAL
        settlements.emplace_back(SettlementType::Capital, 3, 60, 10, FactionZone::Viking);
        settlements.emplace_back(SettlementType::Village, 3, 50, 15, FactionZone::Viking);
        settlements.emplace_back(SettlementType::Village, 3, 70, 8, FactionZone::Viking);
        settlements.emplace_back(SettlementType::Village, 3, 83, 15, FactionZone::Viking);
        //OUEST REGION
        settlements.emplace_back(SettlementType::Castle, 4, 63, 25, FactionZone::Viking);
        settlements.emplace_back(SettlementType::Village, 4, 36, 21, FactionZone::Viking);
        settlements.emplace_back(SettlementType::Village, 4, 64, 34, FactionZone::Viking);
        settlements.emplace_back(SettlementType::Village, 4, 68, 16, FactionZone::Viking);
        //EST REGION
        settlements.emplace_back(SettlementType::Castle, 5, 78, 34, FactionZone::Viking);
        settlements.emplace_back(SettlementType::Village, 5, 88, 30, FactionZone::Viking);
        settlements.emplace_back(SettlementType::Village, 5, 97, 24, FactionZone::Viking);

        // Samurai
        //CAPITAL REGION
        settlements.emplace_back(SettlementType::Capital, 6, 103, 53, FactionZone::Samurai);
        settlements.emplace_back(SettlementType::Village, 6, 108, 66, FactionZone::Samurai);
        settlements.emplace_back(SettlementType::Village, 6, 101, 44, FactionZone::Samurai);
        settlements.emplace_back(SettlementType::Village, 6, 89, 41, FactionZone::Samurai);
        //EST REGION
        settlements.emplace_back(SettlementType::Castle, 7, 80, 50, FactionZone::Samurai);
        settlements.emplace_back(SettlementType::Village, 7, 72, 62, FactionZone::Samurai);
        settlements.emplace_back(SettlementType::Village, 7, 80, 71, FactionZone::Samurai);
        settlements.emplace_back(SettlementType::Village, 7, 87, 64, FactionZone::Samurai);
        //OUEST REGION
        settlements.emplace_back(SettlementType::Castle, 8, 107, 29, FactionZone::Samurai);
        settlements.emplace_back(SettlementType::Village, 8, 119, 59, FactionZone::Samurai);
        settlements.emplace_back(SettlementType::Village, 8, 118, 18, FactionZone::Samurai);


        gameKingdomNameFont = TTF_OpenFont("assets/KnightFont.ttf", 40);
        gameKingdomKnightNameText = TTF_CreateText(textEngine, gameKingdomNameFont, "Knight\nKingdom", 25);
        if (gameKingdomKnightNameText == nullptr) {
            SDL_LogWarn(0,"failed to load the text of gameKingdomKnightNameText");
        }
        gameKingdomVikingNameText = TTF_CreateText(textEngine, gameKingdomNameFont, "Viking\nKingdom", 25);
        if (gameKingdomVikingNameText == nullptr) {
            SDL_LogWarn(0,"failed to load the text of gameKingdomVikingNameText");
        }
        gameKingdomSamuraiNameText = TTF_CreateText(textEngine, gameKingdomNameFont, "Samurai\nKingdom", 25);
        if (gameKingdomSamuraiNameText == nullptr) {
            SDL_LogWarn(0,"failed to load the text of gameKingdomSamuraiNameText");
        }

        //texture Province dezoom texture
        provinceKnightBannerTexture = IMG_LoadTexture(renderer, "assets/KnightProvinceTexture.png");
        if (provinceKnightBannerTexture == nullptr) {
            SDL_LogWarn (0,"failed to load the texture of provinceKnightBannerTexture");
        }
        provinceSamuraiBannerTexture = IMG_LoadTexture(renderer, "assets/SamuraiProvinceTexture.png");
        if (provinceSamuraiBannerTexture == nullptr) {
            SDL_LogWarn(0,"failed to load the provinceSamuraiBannerTexture");
        }
        SDL_SetTextureScaleMode(provinceKnightBannerTexture, SDL_SCALEMODE_NEAREST);
        SDL_SetTextureScaleMode(provinceSamuraiBannerTexture, SDL_SCALEMODE_NEAREST);

        //Texture Bouton UI Province
        provinceTextureUIBuilding = IMG_LoadTexture(renderer, "assets/BuildingUILogo.png");
        if (provinceTextureUIBuilding == nullptr) {
            SDL_LogWarn(0,"failed to load the texture of provinceTextureUIBuilding", SDL_GetError());
        }
        provinceTextureUIGarrison = IMG_LoadTexture(renderer, "assets/GarrisonUILogo.png");
        if (provinceTextureUIGarrison == nullptr) {
            SDL_LogWarn(0,"failed to load the texture of provinceTextureUIGarrison", SDL_GetError());
        }
        SDL_SetTextureScaleMode(provinceTextureUIBuilding, SDL_SCALEMODE_NEAREST);
        SDL_SetTextureScaleMode(provinceTextureUIGarrison, SDL_SCALEMODE_NEAREST);

        //Texture construction Hammer
        hammerUIBuildingUpgradeTexture = IMG_LoadTexture(renderer, "assets/UIHammer.png");
        if (hammerUIBuildingUpgradeTexture == nullptr) {
            SDL_LogWarn(0,"failed to load the texture of hammerUIBuildingUpgradeTexture",SDL_GetError());
        }
        SDL_SetTextureScaleMode(hammerUIBuildingUpgradeTexture, SDL_SCALEMODE_NEAREST);

        // BUILDING UIS
        //                  ! KNIGHT !
        //capitals
        capitalBuildingUpgrade1Knight = IMG_LoadTexture(renderer, "assets/Knight/CapitalBuildingUpgrade1Knight.png");
        if (capitalBuildingUpgrade1Knight == nullptr) {
            SDL_LogWarn(0, "failed to load the texture of capitalBuildingUpgrade1Knight", SDL_GetError());
        }
        SDL_SetTextureScaleMode(capitalBuildingUpgrade1Knight, SDL_SCALEMODE_NEAREST);
        capitalBuildingUpgrade2Knight = IMG_LoadTexture(renderer, "assets/Knight/CapitalBuildingUpgrade2Knight.png");
        if (capitalBuildingUpgrade2Knight == nullptr) {
            SDL_LogWarn(0, "failed to load the texture of capitalBuildingUpgrade2Knight", SDL_GetError());
        }
        SDL_SetTextureScaleMode(capitalBuildingUpgrade2Knight, SDL_SCALEMODE_NEAREST);
        capitalBuildingUpgrade3Knight = IMG_LoadTexture(renderer, "assets/Knight/CapitalBuildingUpgrade3Knight.png");
        if (capitalBuildingUpgrade3Knight == nullptr) {
            SDL_LogWarn(0, "failed to load the texture of capitalBuildingUpgrade3Knight", SDL_GetError());
        }
        SDL_SetTextureScaleMode(capitalBuildingUpgrade3Knight, SDL_SCALEMODE_NEAREST);
        capitalBuildingUpgrade4Knight = IMG_LoadTexture(renderer, "assets/Knight/CapitalBuildingUpgrade4Knight.png");
        if (capitalBuildingUpgrade4Knight == nullptr) {
            SDL_LogWarn(0, "failed to load the texture of capitalBuildingUpgrade4Knight", SDL_GetError());
        }
        SDL_SetTextureScaleMode(capitalBuildingUpgrade4Knight, SDL_SCALEMODE_NEAREST);
        capitalBuildingUpgrade5Knight = IMG_LoadTexture(renderer, "assets/Knight/CapitalBuildingUpgrade5Knight.png");
        if (capitalBuildingUpgrade5Knight == nullptr) {
            SDL_LogWarn(0, "failed to load the texture of capitalBuildingUpgrade5Knight", SDL_GetError());
        }
        SDL_SetTextureScaleMode(capitalBuildingUpgrade5Knight, SDL_SCALEMODE_NEAREST);
        //castle
        castleBuildingUpgrade1Knight = IMG_LoadTexture(renderer, "assets/Knight/CastleBuildingUpgrade1Knight.png");
        if (castleBuildingUpgrade1Knight == nullptr) {
            SDL_LogWarn(0,"failed to load the texture of castleBuildingUpgrade1Knight", SDL_GetError());
        }
        SDL_SetTextureScaleMode(castleBuildingUpgrade1Knight, SDL_SCALEMODE_NEAREST);
        castleBuildingUpgrade2Knight = IMG_LoadTexture(renderer, "assets/Knight/CastleBuildingUpgrade2Knight.png");
        if (castleBuildingUpgrade2Knight == nullptr) {
            SDL_LogWarn(0,"failed to load the texture of castleBuildingUpgrade2Knight", SDL_GetError());
        }
        SDL_SetTextureScaleMode(castleBuildingUpgrade2Knight, SDL_SCALEMODE_NEAREST);
        castleBuildingUpgrade3Knight = IMG_LoadTexture(renderer, "assets/Knight/CastleBuildingUpgrade3Knight.png");
        if (castleBuildingUpgrade3Knight == nullptr) {
            SDL_LogWarn(0,"failed to load the texture of castleBuildingUpgrade3Knight", SDL_GetError());
        }
        SDL_SetTextureScaleMode(castleBuildingUpgrade3Knight, SDL_SCALEMODE_NEAREST);
        castleBuildingUpgrade4Knight = IMG_LoadTexture(renderer, "assets/Knight/CastleBuildingUpgrade4Knight.png");
        if (castleBuildingUpgrade4Knight == nullptr) {
            SDL_LogWarn(0,"failed to load the texture of castleBuildingUpgrade4Knight", SDL_GetError());
        }
        SDL_SetTextureScaleMode(castleBuildingUpgrade4Knight, SDL_SCALEMODE_NEAREST);
        castleBuildingUpgrade5Knight = IMG_LoadTexture(renderer, "assets/Knight/CastleBuildingUpgrade5Knight.png");
        if (castleBuildingUpgrade5Knight == nullptr) {
            SDL_LogWarn(0,"failed to load the texture of castleBuildingUpgrade5Knight", SDL_GetError());
        }
        SDL_SetTextureScaleMode(castleBuildingUpgrade5Knight, SDL_SCALEMODE_NEAREST);
        //village
        villageBuildingUpgrade1Knight = IMG_LoadTexture(renderer, "assets/Knight/VillageBuildingUpgrade1Knight.png");
        if (villageBuildingUpgrade1Knight == nullptr) {
            SDL_LogWarn(0,"failed to load the texture of villageBuildingUpgrade1knight",SDL_GetError());
        }
        SDL_SetTextureScaleMode(villageBuildingUpgrade1Knight, SDL_SCALEMODE_NEAREST);
        villageBuildingUpgrade2Knight = IMG_LoadTexture(renderer, "assets/Knight/VillageBuildingUpgrade2Knight.png");
        if (villageBuildingUpgrade2Knight == nullptr) {
            SDL_LogWarn(0,"failed to load the texture of villageBuildingUpgrade2knight",SDL_GetError());
        }
        SDL_SetTextureScaleMode(villageBuildingUpgrade2Knight, SDL_SCALEMODE_NEAREST);
        villageBuildingUpgrade3Knight = IMG_LoadTexture(renderer, "assets/Knight/VillageBuildingUpgrade3Knight.png");
        if (villageBuildingUpgrade3Knight == nullptr) {
            SDL_LogWarn(0,"failed to load the texture of villageBuildingUpgrade3knight",SDL_GetError());
        }
        SDL_SetTextureScaleMode(villageBuildingUpgrade3Knight, SDL_SCALEMODE_NEAREST);
        //                  ! VIKING !
        //capitals
        capitalBuildingUpgrade1Viking = IMG_LoadTexture(renderer, "assets/Viking/CapitalBuildingUpgrade1Viking.png");
        if (capitalBuildingUpgrade1Viking == nullptr) {
            SDL_LogWarn(0,"failed to load texture capitalBuildingUpgrade1Viking", SDL_GetError());
        }
        SDL_SetTextureScaleMode(capitalBuildingUpgrade1Viking, SDL_SCALEMODE_NEAREST);
        capitalBuildingUpgrade2Viking = IMG_LoadTexture(renderer, "assets/Viking/CapitalBuildingUpgrade2Viking.png");
        if (capitalBuildingUpgrade2Viking == nullptr) {
            SDL_LogWarn(0,"failed to load texture capitalBuildingUpgrade2Viking", SDL_GetError());
        }
        SDL_SetTextureScaleMode(capitalBuildingUpgrade2Viking, SDL_SCALEMODE_NEAREST);
        capitalBuildingUpgrade3Viking = IMG_LoadTexture(renderer, "assets/Viking/CapitalBuildingUpgrade3Viking.png");
        if (capitalBuildingUpgrade3Viking == nullptr) {
            SDL_LogWarn(0,"failed to load texture capitalBuildingUpgrade3Viking", SDL_GetError());
        }
        SDL_SetTextureScaleMode(capitalBuildingUpgrade3Viking, SDL_SCALEMODE_NEAREST);
        capitalBuildingUpgrade4Viking = IMG_LoadTexture(renderer, "assets/Viking/CapitalBuildingUpgrade4Viking.png");
        if (capitalBuildingUpgrade4Viking == nullptr) {
            SDL_LogWarn(0,"failed to load texture capitalBuildingUpgrade4Viking", SDL_GetError());
        }
        SDL_SetTextureScaleMode(capitalBuildingUpgrade4Viking, SDL_SCALEMODE_NEAREST);
        capitalBuildingUpgrade5Viking = IMG_LoadTexture(renderer, "assets/Viking/CapitalBuildingUpgrade5Viking.png");
        if (capitalBuildingUpgrade5Viking == nullptr) {
            SDL_LogWarn(0,"failed to load texture capitalBuildingUpgrade5Viking", SDL_GetError());
        }
        SDL_SetTextureScaleMode(capitalBuildingUpgrade5Viking, SDL_SCALEMODE_NEAREST);
        //Castles
        castleBuildingUpgrade1Viking = IMG_LoadTexture(renderer, "assets/Viking/CastleBuildingUpgrade1Viking.png");
        if (castleBuildingUpgrade1Viking == nullptr) {
            SDL_LogWarn(0,"failed to load texture castleBuildingUpgrade1Viking",SDL_GetError());
        }
        SDL_SetTextureScaleMode(castleBuildingUpgrade1Viking, SDL_SCALEMODE_NEAREST);
        castleBuildingUpgrade2Viking = IMG_LoadTexture(renderer, "assets/Viking/CastleBuildingUpgrade2Viking.png");
        if (castleBuildingUpgrade2Viking == nullptr) {
            SDL_LogWarn(0,"failed to load texture castleBuildingUpgrade2Viking", SDL_GetError());
        }
        SDL_SetTextureScaleMode(castleBuildingUpgrade2Viking, SDL_SCALEMODE_NEAREST);
        castleBuildingUpgrade3Viking = IMG_LoadTexture(renderer, "assets/Viking/CastleBuildingUpgrade3Viking.png");
        if (castleBuildingUpgrade3Viking == nullptr) {
            SDL_LogWarn(0,"failed to load texture castleBuildingUpgrade3Viking", SDL_GetError());
        }
        SDL_SetTextureScaleMode(castleBuildingUpgrade3Viking, SDL_SCALEMODE_NEAREST);
        castleBuildingUpgrade4Viking = IMG_LoadTexture(renderer, "assets/Viking/CastleBuildingUpgrade4Viking.png");
        if (castleBuildingUpgrade4Viking == nullptr) {
            SDL_LogWarn(0,"failed to load texture castleBuildingUpgrade4Viking", SDL_GetError());
        }
        SDL_SetTextureScaleMode(castleBuildingUpgrade4Viking, SDL_SCALEMODE_NEAREST);
        castleBuildingUpgrade5Viking = IMG_LoadTexture(renderer, "assets/Viking/CastleBuildingUpgrade5Viking.png");
        if (castleBuildingUpgrade5Viking == nullptr) {
            SDL_LogWarn(0,"failed to load texture castleBuildingUpgrade5Viking", SDL_GetError());
        }
        SDL_SetTextureScaleMode(castleBuildingUpgrade5Viking, SDL_SCALEMODE_NEAREST);
        //Villages
        villageBuildingUpgrade1Viking = IMG_LoadTexture(renderer, "assets/Viking/VillageBuildingUpgrade1Viking.png");
        if (villageBuildingUpgrade1Viking == nullptr) {
            SDL_LogWarn(0,"failed to load texture villageBuildingUpgrade1Viking", SDL_GetError());
        }
        SDL_SetTextureScaleMode(villageBuildingUpgrade1Viking, SDL_SCALEMODE_NEAREST);
        villageBuildingUpgrade2Viking = IMG_LoadTexture(renderer, "assets/Viking/VillageBuildingUpgrade2Viking.png");
        if (villageBuildingUpgrade2Viking == nullptr) {
            SDL_LogWarn(0,"failed to load texture villageBuildingUpgrade2Viking", SDL_GetError());
        }
        SDL_SetTextureScaleMode(villageBuildingUpgrade2Viking, SDL_SCALEMODE_NEAREST);
        villageBuildingUpgrade3Viking = IMG_LoadTexture(renderer, "assets/Viking/VillageBuildingUpgrade3Viking.png");
        if (villageBuildingUpgrade3Viking == nullptr) {
            SDL_LogWarn(0,"failed to load texture villageBuildingUpgrade3Viking", SDL_GetError());
        }
        SDL_SetTextureScaleMode(villageBuildingUpgrade3Viking, SDL_SCALEMODE_NEAREST);
        //                  ! SAMURAI !
        //capitals
        capitalBuildingUpgrade1Samurai = IMG_LoadTexture(renderer, "assets/Samurai/CapitalBuildingUpgrade1Samurai.png");
        if (capitalBuildingUpgrade1Samurai == nullptr) {
            SDL_LogWarn(0, "failed to load texture capitalBuildingUpgrade1Samurai");
        }
        SDL_SetTextureScaleMode(capitalBuildingUpgrade1Samurai, SDL_SCALEMODE_NEAREST);
        capitalBuildingUpgrade2Samurai = IMG_LoadTexture(renderer, "assets/Samurai/CapitalBuildingUpgrade2Samurai.png");
        if (capitalBuildingUpgrade2Samurai == nullptr) {
            SDL_LogWarn(0, "failed to load texture capitalBuildingUpgrade2Samurai");
        }
        SDL_SetTextureScaleMode(capitalBuildingUpgrade2Samurai, SDL_SCALEMODE_NEAREST);
        capitalBuildingUpgrade3Samurai = IMG_LoadTexture(renderer, "assets/Samurai/CapitalBuildingUpgrade3Samurai.png");
        if (capitalBuildingUpgrade3Samurai == nullptr) {
            SDL_LogWarn(0, "failed to load texture capitalBuildingUpgrade3Samurai");
        }
        SDL_SetTextureScaleMode(capitalBuildingUpgrade3Samurai, SDL_SCALEMODE_NEAREST);
        capitalBuildingUpgrade4Samurai = IMG_LoadTexture(renderer, "assets/Samurai/CapitalBuildingUpgrade4Samurai.png");
        if (capitalBuildingUpgrade4Samurai == nullptr) {
            SDL_LogWarn(0, "failed to load texture capitalBuildingUpgrade4Samurai");
        }
        SDL_SetTextureScaleMode(capitalBuildingUpgrade4Samurai, SDL_SCALEMODE_NEAREST);
        capitalBuildingUpgrade5Samurai = IMG_LoadTexture(renderer, "assets/Samurai/CapitalBuildingUpgrade5Samurai.png");
        if (capitalBuildingUpgrade5Samurai == nullptr) {
            SDL_LogWarn(0, "failed to load texture capitalBuildingUpgrade5Samurai");
        }
        SDL_SetTextureScaleMode(capitalBuildingUpgrade5Samurai, SDL_SCALEMODE_NEAREST);
        //castles
        castleBuildingUpgrade1Samurai = IMG_LoadTexture(renderer, "assets/Samurai/CastleBuildingUpgrade1Samurai.png");
        if (castleBuildingUpgrade1Samurai == nullptr) {
            SDL_LogWarn(0, "failed to load texture castleBuildingUpgrade1Samurai", SDL_GetError());
        }
        SDL_SetTextureScaleMode(castleBuildingUpgrade1Samurai, SDL_SCALEMODE_NEAREST);
        castleBuildingUpgrade2Samurai = IMG_LoadTexture(renderer, "assets/Samurai/CastleBuildingUpgrade2Samurai.png");
        if (castleBuildingUpgrade2Samurai == nullptr) {
            SDL_LogWarn(0, "failed to load texture castleBuildingUpgrade2Samurai", SDL_GetError());
        }
        SDL_SetTextureScaleMode(castleBuildingUpgrade2Samurai, SDL_SCALEMODE_NEAREST);
        castleBuildingUpgrade3Samurai = IMG_LoadTexture(renderer, "assets/Samurai/CastleBuildingUpgrade3Samurai.png");
        if (castleBuildingUpgrade3Samurai == nullptr) {
            SDL_LogWarn(0, "failed to load texture castleBuildingUpgrade3Samurai", SDL_GetError());
        }
        SDL_SetTextureScaleMode(castleBuildingUpgrade3Samurai, SDL_SCALEMODE_NEAREST);
        castleBuildingUpgrade4Samurai = IMG_LoadTexture(renderer, "assets/Samurai/CastleBuildingUpgrade4Samurai.png");
        if (castleBuildingUpgrade4Samurai == nullptr) {
            SDL_LogWarn(0, "failed to load texture castleBuildingUpgrade4Samurai", SDL_GetError());
        }
        SDL_SetTextureScaleMode(castleBuildingUpgrade4Samurai, SDL_SCALEMODE_NEAREST);
        castleBuildingUpgrade5Samurai = IMG_LoadTexture(renderer, "assets/Samurai/CastleBuildingUpgrade5Samurai.png");
        if (castleBuildingUpgrade5Samurai == nullptr) {
            SDL_LogWarn(0, "failed to load texture castleBuildingUpgrade5Samurai", SDL_GetError());
        }
        SDL_SetTextureScaleMode(castleBuildingUpgrade5Samurai, SDL_SCALEMODE_NEAREST);
        //villages
        villageBuildingUpgrade1Samurai = IMG_LoadTexture(renderer, "assets/Samurai/VillageBuildingUpgrade1Samurai.png");
        if (villageBuildingUpgrade1Samurai == nullptr) {
            SDL_LogWarn(0,"failed to load texture villageBuildingUpgrade1Samurai", SDL_GetError());
        }
        SDL_SetTextureScaleMode(villageBuildingUpgrade1Samurai, SDL_SCALEMODE_NEAREST);
        villageBuildingUpgrade2Samurai = IMG_LoadTexture(renderer, "assets/Samurai/VillageBuildingUpgrade2Samurai.png");
        if (villageBuildingUpgrade2Samurai == nullptr) {
            SDL_LogWarn(0,"failed to load texture villageBuildingUpgrade2Samurai", SDL_GetError());
        }
        SDL_SetTextureScaleMode(villageBuildingUpgrade2Samurai, SDL_SCALEMODE_NEAREST);
        villageBuildingUpgrade3Samurai = IMG_LoadTexture(renderer, "assets/Samurai/VillageBuildingUpgrade3Samurai.png");
        if (villageBuildingUpgrade3Samurai == nullptr) {
            SDL_LogWarn(0,"failed to load texture villageBuildingUpgrade3Samurai", SDL_GetError());
        }
        SDL_SetTextureScaleMode(villageBuildingUpgrade3Samurai, SDL_SCALEMODE_NEAREST);
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
        TTF_CloseFont(gameKingdomNameFont);
        TTF_CloseFont(gameStatUITitleFont);
        TTF_CloseFont(gameStatUIFont);
        TTF_CloseFont(gameGeneralFont);
        TTF_CloseFont(gameBuildingCostUIFont);
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
        TTF_DestroyText(gameKingdomKnightNameText);
        TTF_DestroyText(gameKingdomVikingNameText);
        TTF_DestroyText(gameKingdomSamuraiNameText);
        TTF_DestroyText(gameStatUITitleText);
        TTF_DestroyText(gameStatUIText);
        TTF_DestroyText(gameCurrentMoneyUiText);
        TTF_DestroyText(gameAnticipatedMoneyUiText);
        TTF_DestroyText(gameNumberOfTurnText);
        TTF_DestroyText(gameBuildingCostUIText);
    // ---------------------------------
        SDL_DestroyTexture(provinceKnightBannerTexture);
        SDL_DestroyTexture(provinceVikingBannerTexture);
        SDL_DestroyTexture(provinceSamuraiBannerTexture);
        SDL_DestroyTexture(provinceTextureUIBuilding);
        SDL_DestroyTexture(provinceTextureUIGarrison);
        SDL_DestroyTexture(hammerUIBuildingUpgradeTexture);
        SDL_DestroyTexture(capitalBuildingUpgrade1Knight);
        SDL_DestroyTexture(capitalBuildingUpgrade2Knight);
        SDL_DestroyTexture(capitalBuildingUpgrade3Knight);
        SDL_DestroyTexture(capitalBuildingUpgrade4Knight);
        SDL_DestroyTexture(capitalBuildingUpgrade5Knight);
        SDL_DestroyTexture(castleBuildingUpgrade1Knight);
        SDL_DestroyTexture(castleBuildingUpgrade2Knight);
        SDL_DestroyTexture(castleBuildingUpgrade3Knight);
        SDL_DestroyTexture(castleBuildingUpgrade4Knight);
        SDL_DestroyTexture(castleBuildingUpgrade5Knight);
        SDL_DestroyTexture(villageBuildingUpgrade1Knight);
        SDL_DestroyTexture(villageBuildingUpgrade2Knight);
        SDL_DestroyTexture(villageBuildingUpgrade3Knight);
        SDL_DestroyTexture(capitalBuildingUpgrade1Viking);
        SDL_DestroyTexture(capitalBuildingUpgrade2Viking);
        SDL_DestroyTexture(capitalBuildingUpgrade3Viking);
        SDL_DestroyTexture(capitalBuildingUpgrade4Viking);
        SDL_DestroyTexture(capitalBuildingUpgrade5Viking);
        SDL_DestroyTexture(castleBuildingUpgrade1Viking);
        SDL_DestroyTexture(castleBuildingUpgrade2Viking);
        SDL_DestroyTexture(castleBuildingUpgrade3Viking);
        SDL_DestroyTexture(castleBuildingUpgrade4Viking);
        SDL_DestroyTexture(castleBuildingUpgrade5Viking);
        SDL_DestroyTexture(villageBuildingUpgrade1Viking);
        SDL_DestroyTexture(villageBuildingUpgrade2Viking);
        SDL_DestroyTexture(villageBuildingUpgrade3Viking);
        SDL_DestroyTexture(capitalBuildingUpgrade1Samurai);
        SDL_DestroyTexture(capitalBuildingUpgrade2Samurai);
        SDL_DestroyTexture(capitalBuildingUpgrade3Samurai);
        SDL_DestroyTexture(capitalBuildingUpgrade4Samurai);
        SDL_DestroyTexture(capitalBuildingUpgrade5Samurai);
        SDL_DestroyTexture(castleBuildingUpgrade1Samurai);
        SDL_DestroyTexture(castleBuildingUpgrade2Samurai);
        SDL_DestroyTexture(castleBuildingUpgrade3Samurai);
        SDL_DestroyTexture(castleBuildingUpgrade4Samurai);
        SDL_DestroyTexture(castleBuildingUpgrade5Samurai);
        SDL_DestroyTexture(villageBuildingUpgrade1Samurai);
        SDL_DestroyTexture(villageBuildingUpgrade2Samurai);
        SDL_DestroyTexture(villageBuildingUpgrade3Samurai);
    // ---------------------------------
        SDL_DestroyCursor(cursor);
        delete tileMap;

    }
    //to render the Buttons
    void RenderBoutons(const SDL_FRect &rect, TTF_Text *buttonText, Uint8 buttonr, Uint8 buttong, Uint8 buttonb, Uint8 buttona) {
        SDL_SetRenderDrawColor(renderer, buttonr, buttong, buttonb, buttona);
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

    //For the rendering on screen of the settlements. Texture to do
    void RenderSettlements() {
        for (const auto& s : settlements) {
            float positionX = (float)(s.tileCol * tileMap->tileSize) * camera.zoom - camera.startX * camera.zoom;
            float positionY = (float)(s.tileRow * tileMap->tileSize) * camera.zoom - camera.startY * camera.zoom;
            float size = (float)tileMap->tileSize * camera.zoom;

            FactionZone zone = provinces[s.settlementData.provinceID].owner;

            //Square color based of faction Color
            SDL_Color factionColor;
            if (zone == FactionZone::Knight) {
                factionColor = {255, 215, 0,   255};
            }
            else if (zone == FactionZone::Viking) {
                factionColor = {255, 0,   0,   255};
            }
            else if (zone == FactionZone::Samurai) {
                factionColor = {0, 200, 160, 255};
            }
            else {
                factionColor = {150, 150, 150, 255};
            }

            // size of the building based of what they are
            float displaySize = size;
            if (s.settlementData.type == SettlementType::Capital) {
                displaySize = size * 4.f; //4x4
            }
            else if (s.settlementData.type == SettlementType::Castle) {
                displaySize = size * 3.f; //3x3
            }
            else if (s.settlementData.type == SettlementType::Village) {
                displaySize = size * 2.f; //2x2
            }
            //aligns all sizes to the grid
            SDL_FRect dst = {
                positionX,
                positionY,
                displaySize,
                displaySize
            };


            SDL_SetRenderDrawColor(renderer, factionColor.r, factionColor.g, factionColor.b, 255);
            SDL_RenderFillRect(renderer, &dst);

            // Bordure noire
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderRect(renderer, &dst);

            //UI elements to show (Public order / Current income of this settlement / Population )
           if (camera.zoom >= 1.1f) {
            // center of the settlement for the UI to show
    float centerX = positionX + displaySize / 2.f;
    float bottomY = positionY + displaySize;

    // size of all UI elements
    float barW   = 110.f;
    float barH   = 20.f;
    float barGap = 3.f;
    float barX   = centerX - barW / 2.f;
    float barY   = bottomY + barGap;

    // the name of the settlement
    TTF_SetTextString(gameStatUITitleText, s.settlementData.cityName.c_str(), 0);
    TTF_SetTextColor(gameStatUITitleText, 255, 255, 255, 255);
    int nameW = 0, nameH = 0;
    TTF_GetTextSize(gameStatUITitleText, &nameW, &nameH);
    float nameX = centerX - nameW / 2.f;
    float nameY = barY - nameH - 2.f; // collé au-dessus de la barre

    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 200);
    SDL_FRect nameBackground = {nameX - 4.f, nameY - 2.f, (float)nameW + 4.f, (float)nameH + 2.f};
    SDL_RenderFillRect(renderer, &nameBackground);
    SDL_SetRenderDrawColor(renderer, factionColor.r, factionColor.g, factionColor.b, 160);
    SDL_RenderRect(renderer, &nameBackground);
    TTF_DrawRendererText(gameStatUITitleText, nameX, nameY);

    // INFO BAR
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 210);
    SDL_FRect infoBar = {barX, barY, barW, barH};
    SDL_RenderFillRect(renderer, &infoBar);
    SDL_SetRenderDrawColor(renderer, factionColor.r, factionColor.g, factionColor.b, 180);
    SDL_RenderRect(renderer, &infoBar);

    float iconSize = 11.f;
    float cursor = barX + 5.f;
    float iconY = barY + (barH - iconSize) / 2.f;
    float textY = barY - 2.f;

    // iconeIncome gold
    SDL_SetRenderDrawColor(renderer, 220, 180, 40, 255);
    SDL_FRect incomeIcon = {cursor, iconY, iconSize, iconSize};
    SDL_RenderFillRect(renderer, &incomeIcon);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_RenderRect(renderer, &incomeIcon);
    cursor += iconSize + 3.f;
    //the number that shows the income per settlement(baseIncome)
    std::string incomeStr = std::to_string(s.settlementData.baseIncome);
    TTF_SetTextString(gameStatUIText, incomeStr.c_str(), 0);
    TTF_SetTextColor(gameStatUIText, 180, 230, 100, 255);
    TTF_DrawRendererText(gameStatUIText, cursor, textY);
    int incW = 0, incH = 0;
    TTF_GetTextSize(gameStatUIText, &incW, &incH);
    cursor += incW + 7.f;


    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderLine(renderer, cursor, barY + 3.f, cursor, barY + barH - 3.f);
    cursor += 6.f;

    // public order icon
    int publicOrder    = s.settlementData.publicOrder;
    Uint8 poR = publicOrder > 0 ? 80  : (publicOrder < 0 ? 220 : 130);
    Uint8 poG = publicOrder > 0 ? 200 : (publicOrder < 0 ? 50  : 130);
    SDL_SetRenderDrawColor(renderer, poR, poG, 80, 255);
    SDL_FRect publicOrderIcon = {cursor, iconY, iconSize, iconSize};
    SDL_RenderFillRect(renderer, &publicOrderIcon);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_RenderRect(renderer, &publicOrderIcon);
    cursor += iconSize + 3.f;

    std::string orderStr = std::to_string(publicOrder);
    TTF_SetTextString(gameStatUIText, orderStr.c_str(), 0);
    TTF_SetTextColor(gameStatUIText, poR, poG, 80, 255);//color change in fonction if it's positive or negative. Texture to do
    TTF_DrawRendererText(gameStatUIText, cursor, textY);
        }
        }
    }
    //UI of the region with their castle/villages when you click on a settlement from that province ID
    void RenderProvinceUI() {
    if (!bHasClickedOnASettlement || selectedSettlementIndex < 0) return;

    const Settlement& clickedSettlement = settlements[selectedSettlementIndex];
    int provinceID = clickedSettlement.settlementData.provinceID;//name of the province
    const Province& province = provinces[provinceID];

    std::vector<const Settlement*> provinceSettlements;
    for (const auto& s : settlements)
        if (s.settlementData.provinceID == provinceID)provinceSettlements.push_back(&s);

    int incomeTotal = 0;
    int populationTotal = 0;
    int publicOrderTotal = 0;
    for (auto* s : provinceSettlements) {
        incomeTotal += s->settlementData.baseIncome;
        populationTotal += s->settlementData.basePopulation;
        publicOrderTotal = s->settlementData.publicOrder;
    }
    //set the color
    SDL_Color factionColor;
    if(province.owner == FactionZone::Knight) {
        factionColor = {255, 215, 0,   255};
    }
    else if (province.owner == FactionZone::Viking) {
        factionColor = {255,0,0,255};
    }
    else if (province.owner == FactionZone::Samurai) {
        factionColor = {0,255, 215,255};
    }
    else {
        factionColor = {150, 150, 150, 255};
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // LEFT UI PART
        //PROVINCE
    float leftW = 250.f, leftH = 380.f;//size
    float leftX = 0.f,   leftY = 700.f;//position

    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 210);
    SDL_FRect leftPanel = {leftX, leftY, leftW, leftH};
    SDL_RenderFillRect(renderer, &leftPanel);

    // Title Province Name
    SDL_SetRenderDrawColor(renderer, factionColor.r, factionColor.g, factionColor.b, 180);
    SDL_FRect titleBar = {leftX, leftY, leftW, 40.f};
    SDL_RenderFillRect(renderer, &titleBar);
    SDL_SetRenderDrawColor(renderer, factionColor.r, factionColor.g, factionColor.b, 255);
    SDL_RenderRect(renderer, &leftPanel);

    // Name province
    TTF_SetTextString(gameStatUITitleText, province.name.c_str(), 0);
    TTF_SetTextColor(gameStatUITitleText, 255, 255, 255, 255);
    TTF_DrawRendererText(gameStatUITitleText, leftX + 10.f, leftY + 8.f);

    // Stats
    float statY = leftY + 55.f;

// GROWTH TITLE SELECTION
        if (province.owner == FactionZone::Knight) {
            SDL_SetRenderDrawColor(renderer, 60, 40, 20, 200);
        }
        else if (province.owner == FactionZone::Viking) {
            SDL_SetRenderDrawColor(renderer, 60, 20, 20, 200);
        }
        else if (province.owner == FactionZone::Samurai) {
            SDL_SetRenderDrawColor(renderer, 20, 60, 45, 200);
        }
SDL_FRect growthBar = {leftX + 5.f, statY, leftW - 10.f, 28.f};
SDL_RenderFillRect(renderer, &growthBar);
TTF_SetTextString(gameStatUITitleText, "Growth", 0);
TTF_SetTextColor(gameStatUITitleText, 71, 255, 164, 255);
TTF_DrawRendererText(gameStatUITitleText, leftX + 10.f, statY + 2.f);
statY += 35.f;

// Green Icone + growth amount
SDL_SetRenderDrawColor(renderer, 80, 200, 80, 255);
SDL_FRect popIcon = {leftX + 8.f, statY + 3.f, 14.f, 14.f};
SDL_RenderFillRect(renderer, &popIcon);
SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
SDL_RenderRect(renderer, &popIcon);
TTF_SetTextString(gameStatUIText, "Growth:", 0);
TTF_SetTextColor(gameStatUIText, 180, 180, 180, 255);
TTF_DrawRendererText(gameStatUIText, leftX + 28.f, statY);
TTF_SetTextString(gameStatUIText, std::to_string(populationTotal).c_str(), 0);
TTF_SetTextColor(gameStatUIText, 180, 230, 100, 255);
TTF_DrawRendererText(gameStatUIText, leftX + 170.f, statY);
statY += 34.f;

// TAXE PROVINCE TITLE
        if (province.owner == FactionZone::Knight) {
            SDL_SetRenderDrawColor(renderer, 60, 40, 20, 200);
        }
        else if (province.owner == FactionZone::Viking) {
            SDL_SetRenderDrawColor(renderer, 60, 20, 20, 200);
        }
        else if (province.owner == FactionZone::Samurai) {
            SDL_SetRenderDrawColor(renderer, 20, 60, 45, 200);
        }
SDL_FRect taxBar = {leftX + 5.f, statY, leftW - 10.f, 28.f};
SDL_RenderFillRect(renderer, &taxBar);
TTF_SetTextString(gameStatUITitleText, "Tax Province", 0);
TTF_SetTextColor(gameStatUITitleText, 220, 180, 60, 255);
TTF_DrawRendererText(gameStatUITitleText, leftX + 10.f, statY + 2.f);
statY += 35.f;

// income + gold icone
SDL_SetRenderDrawColor(renderer, 220, 180, 40, 255);
SDL_FRect incomeIconRect = {leftX + 8.f, statY + 3.f, 14.f, 14.f};
SDL_RenderFillRect(renderer, &incomeIconRect);
SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
SDL_RenderRect(renderer, &incomeIconRect);
TTF_SetTextString(gameStatUIText, "Income", 0);
TTF_SetTextColor(gameStatUIText, 180, 180, 180, 255);
TTF_DrawRendererText(gameStatUIText, leftX + 28.f, statY);
TTF_SetTextString(gameStatUIText, std::to_string(incomeTotal).c_str(), 0);
TTF_SetTextColor(gameStatUIText, 180, 230, 100, 255);
TTF_DrawRendererText(gameStatUIText, leftX + 170.f, statY);
statY += 34.f;

// public Order Icon
Uint8 poR  = publicOrderTotal > 0 ? 80  : (publicOrderTotal < 0 ? 220 : 130);
Uint8 poG  = publicOrderTotal > 0 ? 200 : (publicOrderTotal < 0 ? 50  : 130);
Uint8 poB2 = 80;
SDL_SetRenderDrawColor(renderer, poR, poG, poB2, 255);
SDL_FRect poIconRect = {leftX + 8.f, statY + 3.f, 14.f, 14.f};
SDL_RenderFillRect(renderer, &poIconRect);
SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
SDL_RenderRect(renderer, &poIconRect);
TTF_SetTextString(gameStatUIText, "Public order", 0);
TTF_SetTextColor(gameStatUIText, 180, 180, 180, 255);
TTF_DrawRendererText(gameStatUIText, leftX + 28.f, statY);
TTF_SetTextString(gameStatUIText, std::to_string(publicOrderTotal).c_str(), 0);
TTF_SetTextColor(gameStatUIText, poR, poG, poB2, 255);
TTF_DrawRendererText(gameStatUIText, leftX + 170.f, statY);
statY += 34.f;

// Capital
TTF_SetTextString(gameStatUIText, "Capital:", 0);
TTF_SetTextColor(gameStatUIText, 180, 180, 180, 255);
TTF_DrawRendererText(gameStatUIText, leftX + 28.f, statY);
TTF_SetTextString(gameStatUIText, province.isCapital ? "Yes" : "No", 0);
TTF_SetTextColor(gameStatUIText, 255, 215, 0, 255);
TTF_DrawRendererText(gameStatUIText, leftX + 170.f, statY);

    //Province UI Different Buttons (buildings, garrison, All buildings, recruit a lord, recruit a hero)
    //Render those Buttons
    RenderBoutons(provinceButtonUIBuilding, nullptr,40,40,40,100);
    SDL_RenderTexture(renderer,provinceTextureUIBuilding,nullptr,&provinceButtonUIBuilding);
    RenderBoutons(provinceButtonUIGarrison, nullptr,40,40,40,100);
    SDL_RenderTexture(renderer,provinceTextureUIGarrison,nullptr,&provinceButtonUIGarrison);




    //-> BOTTOM UI PANNEL <-
            int   count = (int)provinceSettlements.size();
            float cardW = 280.f;
            float cardH = 200.f;
            float cardGap = 16.f;
            float totalW = count * cardW + (count - 1) * cardGap;
            float startX = (1920.f - totalW) / 2.f;
            float panelY = 1080.f - cardH - 65.f;
            //clear mainBuildingSlot before the for
            mainBuildingSlotRects.clear();
             mainBuildingSlotRects.resize(count, {0,0,0,0});
            for (int i = 0; i < count; i++) {
                const Settlement* s = provinceSettlements[i];
                bool isSelected = (s == &clickedSettlement);

                float cx = startX + i * (cardW + cardGap);

                // Fond carte
                SDL_SetRenderDrawColor(renderer, isSelected ? 40 : 25, isSelected ? 40 : 25, isSelected ? 40 : 25, 220);
                SDL_FRect card = {cx, panelY, cardW, cardH};
                SDL_RenderFillRect(renderer, &card);

                // Border
                if (isSelected)
                    SDL_SetRenderDrawColor(renderer, factionColor.r, factionColor.g, factionColor.b, 255);
                else
                    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
                SDL_RenderRect(renderer, &card);

                // title of each settlement UI changes the color
                SDL_Color typeColor;
                std::string typeName;
                if (s->settlementData.type == SettlementType::Capital) {
                    if (province.owner == FactionZone::Knight) {
                        typeColor = {255,215,  0,255}; typeName = "Capital";
                    }
                    else if (province.owner == FactionZone::Samurai) {
                        typeColor = {0,255, 215,255}; typeName = "Capital";
                    }
                    else if (province.owner == FactionZone::Viking) {
                        typeColor = {255,0,0,255}; typeName = "Capital";
                    }
                }
                else if (s->settlementData.type == SettlementType::Castle) {
                    if (province.owner == FactionZone::Knight) {
                        typeColor = {255,215,0,255}; typeName = "Castle";
                    }
                    else if (province.owner == FactionZone::Samurai) {
                        typeColor = {0,255, 215,255}; typeName = "Castle";
                    }
                    else if (province.owner == FactionZone::Viking) {
                        typeColor = {255,0,0,255}; typeName = "Castle";
                    }
                }
                else if (s->settlementData.type == SettlementType::Village) {
                    if (province.owner == FactionZone::Knight) {
                        typeColor = {255,215,0,255}; typeName = "Village";
                    }
                    else if (province.owner == FactionZone::Samurai) {
                        typeColor = {0,255, 215,255}; typeName = "Village";
                    }
                    else if (province.owner == FactionZone::Viking) {
                        typeColor = {255,0,0,255}; typeName = "Village";
                    }
                }

                SDL_SetRenderDrawColor(renderer, typeColor.r/3, typeColor.g/3, typeColor.b/3, 200);
                SDL_FRect cardTitle = {cx, panelY, cardW, 38.f};
                SDL_RenderFillRect(renderer, &cardTitle);

                // Icon
                SDL_SetRenderDrawColor(renderer, typeColor.r, typeColor.g, typeColor.b, 255);
                SDL_FRect icon = {cx + 10.f, panelY + 10.f, 18.f, 18.f};
                SDL_RenderFillRect(renderer, &icon);
                //each settlement Title ->
                TTF_SetTextString(gameStatUITitleText, s->settlementData.cityName.c_str(), 0);
                TTF_SetTextColor(gameStatUITitleText, 230, 230, 230, 255);
                TTF_DrawRendererText(gameStatUITitleText, cx + 36.f, panelY + 9.f);

                // building slots
                if (bButtonUIBuildingIsPressed) {
                    float slotSize = 60.f;
                    float slotGap  = 6.f;
                    int cols = 0;
                    if      (s->settlementData.type == SettlementType::Village) cols = 2;
                    else if (s->settlementData.type == SettlementType::Castle)  cols = 3;
                    else if (s->settlementData.type == SettlementType::Capital) cols = 4;

                    float gridW      = cols * slotSize + (cols - 1) * slotGap;
                    float slotStartX = cx + (cardW - gridW) / 2.f;
                    float row0Y      = panelY + cardH - (slotSize * 2 + slotGap) - 12.f;
                    float row1Y      = row0Y + slotSize + slotGap;

                    for (int b = 0; b < (int)s->settlementData.buildings.size(); b++) {
                        BuildingType buildingType = s->settlementData.buildings[b];

                        int col = b % cols;
                        int row = b / cols;

                        float sx = slotStartX + col * (slotSize + slotGap); // ← sx défini ici
                        float sy = (row == 0) ? row0Y : row1Y;              // ← sy défini ici

                        // unique building per faction
                        //slot 0
                        if (b == 0) {
                            if (buildingType == BuildingType::Settlement_Village_Knight||buildingType == BuildingType::Settlement_Castle_Knight||buildingType == BuildingType::Settlement_Capital_Knight) {
                                SDL_SetRenderDrawColor(renderer, 255, 215, 0,   255); // or
                            }
                            else if (buildingType == BuildingType::Settlement_Village_Viking ||buildingType == BuildingType::Settlement_Castle_Viking  ||buildingType == BuildingType::Settlement_Capital_Viking) {
                                SDL_SetRenderDrawColor(renderer, 255, 50,  50,  255); // rouge
                            }
                            else if (buildingType == BuildingType::Settlement_Village_Samurai||buildingType == BuildingType::Settlement_Castle_Samurai||buildingType == BuildingType::Settlement_Capital_Samurai) {
                                SDL_SetRenderDrawColor(renderer, 0,   200, 160, 255); // teal
                            }
                            else {
                                SDL_SetRenderDrawColor(renderer, 255, 0,   255, 255); // pink is error
                            }
                        } else {
                            bool built = (buildingType != BuildingType::None);
                            SDL_SetRenderDrawColor(renderer, built ? 80 : 45,built ? 160 : 45,built ? 80 : 45, 255);
                        }

                        //texture
                        if (province.owner == FactionZone::Knight) {
                            if (s->settlementData.type == SettlementType::Capital) {
                                if (s->settlementData.settlementTier == 1) {
                                    SDL_RenderTexture(renderer, capitalBuildingUpgrade1Knight, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 2) {
                                    SDL_RenderTexture(renderer, capitalBuildingUpgrade2Knight, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 3) {
                                    SDL_RenderTexture(renderer, capitalBuildingUpgrade3Knight, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 4) {
                                    SDL_RenderTexture(renderer, capitalBuildingUpgrade4Knight, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 5) {
                                    SDL_RenderTexture(renderer, capitalBuildingUpgrade5Knight, nullptr, &mainBuildingSlotRects[i]);
                                }
                            }
                            else if (s->settlementData.type == SettlementType::Castle) {
                                if (s->settlementData.settlementTier == 1) {
                                    SDL_RenderTexture(renderer, castleBuildingUpgrade1Knight, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 2) {
                                    SDL_RenderTexture(renderer, castleBuildingUpgrade2Knight, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 3) {
                                    SDL_RenderTexture(renderer, castleBuildingUpgrade3Knight, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 4) {
                                    SDL_RenderTexture(renderer, castleBuildingUpgrade4Knight, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 5) {
                                    SDL_RenderTexture(renderer, castleBuildingUpgrade5Knight, nullptr, &mainBuildingSlotRects[i]);
                                }
                            }
                            else if (s->settlementData.type == SettlementType::Village) {
                                if (s->settlementData.settlementTier == 1) {
                                    SDL_RenderTexture(renderer, villageBuildingUpgrade1Knight,nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 2) {
                                    SDL_RenderTexture(renderer, villageBuildingUpgrade2Knight,nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 3) {
                                    SDL_RenderTexture(renderer, villageBuildingUpgrade3Knight,nullptr, &mainBuildingSlotRects[i]);
                                }
                            }

                        }
                        //viking
                        //texture
                        if (province.owner == FactionZone::Viking) {
                            if (s->settlementData.type == SettlementType::Capital) {
                                if (s->settlementData.settlementTier == 1) {
                                    SDL_RenderTexture(renderer, capitalBuildingUpgrade1Viking, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 2) {
                                    SDL_RenderTexture(renderer, capitalBuildingUpgrade2Viking, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 3) {
                                    SDL_RenderTexture(renderer, capitalBuildingUpgrade3Viking, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 4) {
                                    SDL_RenderTexture(renderer, capitalBuildingUpgrade4Viking, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 5) {
                                    SDL_RenderTexture(renderer, capitalBuildingUpgrade5Viking, nullptr, &mainBuildingSlotRects[i]);
                                }
                            }
                            else if (s->settlementData.type == SettlementType::Castle) {
                                if (s->settlementData.settlementTier == 1) {
                                    SDL_RenderTexture(renderer, castleBuildingUpgrade1Viking, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 2) {
                                    SDL_RenderTexture(renderer, castleBuildingUpgrade2Viking, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 3) {
                                    SDL_RenderTexture(renderer, castleBuildingUpgrade3Viking, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 4) {
                                    SDL_RenderTexture(renderer, castleBuildingUpgrade4Viking, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 5) {
                                    SDL_RenderTexture(renderer, castleBuildingUpgrade5Viking, nullptr, &mainBuildingSlotRects[i]);
                                }
                            }
                            else if (s->settlementData.type == SettlementType::Village) {
                                if (s->settlementData.settlementTier == 1) {
                                    SDL_RenderTexture(renderer, villageBuildingUpgrade1Viking,nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 2) {
                                    SDL_RenderTexture(renderer, villageBuildingUpgrade2Viking,nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 3) {
                                    SDL_RenderTexture(renderer, villageBuildingUpgrade3Viking,nullptr, &mainBuildingSlotRects[i]);
                                }
                            }

                        }
                        //samurai
                        //texture
                        if (province.owner == FactionZone::Samurai) {
                            if (s->settlementData.type == SettlementType::Capital) {
                                if (s->settlementData.settlementTier == 1) {
                                    SDL_RenderTexture(renderer, capitalBuildingUpgrade1Samurai, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 2) {
                                    SDL_RenderTexture(renderer, capitalBuildingUpgrade2Samurai, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 3) {
                                    SDL_RenderTexture(renderer, capitalBuildingUpgrade3Samurai, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 4) {
                                    SDL_RenderTexture(renderer, capitalBuildingUpgrade4Samurai, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 5) {
                                    SDL_RenderTexture(renderer, capitalBuildingUpgrade5Samurai, nullptr, &mainBuildingSlotRects[i]);
                                }
                            }
                            else if (s->settlementData.type == SettlementType::Castle) {
                                if (s->settlementData.settlementTier == 1) {
                                    SDL_RenderTexture(renderer, castleBuildingUpgrade1Samurai, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 2) {
                                    SDL_RenderTexture(renderer, castleBuildingUpgrade2Samurai, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 3) {
                                    SDL_RenderTexture(renderer, castleBuildingUpgrade3Samurai, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 4) {
                                    SDL_RenderTexture(renderer, castleBuildingUpgrade4Samurai, nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 5) {
                                    SDL_RenderTexture(renderer, castleBuildingUpgrade5Samurai, nullptr, &mainBuildingSlotRects[i]);
                                }
                            }
                            else if (s->settlementData.type == SettlementType::Village) {
                                if (s->settlementData.settlementTier == 1) {
                                    SDL_RenderTexture(renderer, villageBuildingUpgrade1Samurai,nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 2) {
                                    SDL_RenderTexture(renderer, villageBuildingUpgrade2Samurai,nullptr, &mainBuildingSlotRects[i]);
                                }
                                else if (s->settlementData.settlementTier == 3) {
                                    SDL_RenderTexture(renderer, villageBuildingUpgrade3Samurai,nullptr, &mainBuildingSlotRects[i]);
                                }
                            }

                        }




                        SDL_FRect slot = {sx, sy, slotSize, slotSize};
                        SDL_RenderFillRect(renderer, &slot);
                        SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
                        SDL_RenderRect(renderer, &slot);
                        //Main settlement (0)
                        if (b == 0) {
                            std::string tierStr = "T" + std::to_string(s->settlementData.settlementTier);
                            TTF_SetTextString(gameStatUIText, tierStr.c_str(), 0);
                            TTF_SetTextColor(gameStatUIText, 255, 255, 255, 255);
                            TTF_DrawRendererText(gameStatUIText, sx + 4.f, sy + 4.f);

                            int maxTierCheck = 3;
                            if (s->settlementData.type == SettlementType::Castle)  maxTierCheck = 5;
                            if (s->settlementData.type == SettlementType::Capital) maxTierCheck = 5;

                            //if not full tier than the hammer shows
                            BuildingType mainBuilding = s->settlementData.buildings[0];
                            int upgradeCost = player.GetUpgradeCost(s->settlementData.settlementTier, mainBuilding);
                            if (provinces[s->settlementData.provinceID].owner == player.faction) {
                                if (s->settlementData.settlementTier < maxTierCheck && hammerUIBuildingUpgradeTexture && player.currentGold >= upgradeCost) {
                                    SDL_FRect hammerRect = {
                                        sx + slotSize - 30.f,
                                        sy + 4.f,
                                        35.f, 35.f
                                    };
                                    SDL_RenderTexture(renderer, hammerUIBuildingUpgradeTexture, nullptr, &hammerRect);
                                }
                            }

                                mainBuildingSlotRects[i] = slot;
                            //which card is the mouse on
                            float mx, my;
                            SDL_GetMouseState(&mx, &my);
                            float lx, ly;
                            SDL_RenderCoordinatesFromWindow(renderer, mx, my, &lx, &ly);
                            SDL_FPoint mousePt = {lx, ly};
                            SDL_FRect slotCheck = {sx, sy, slotSize, slotSize};
                            if (SDL_PointInRectFloat(&mousePt, &slotCheck)) {
                                hoveredCardIndex = i;
                            }
                        }
                    }
                }
            }
        //TIER CHAIN POPUP
    if (hoveredSlotIndex == 0 && bButtonUIBuildingIsPressed && hoveredCardIndex >= 0) {
        const Settlement* sel = provinceSettlements[hoveredCardIndex];
    int currentTier = sel->settlementData.settlementTier;
    int maxTier = 3;//for the villages
    //for castle and capital its 5
    if (sel->settlementData.type == SettlementType::Castle || sel->settlementData.type == SettlementType::Capital) {
        maxTier = 5;
    }


    float tileW  = 64.f;
    float tileH  = 64.f;
    float arrowH = 22.f;
    float totalH = maxTier * tileH + (maxTier - 1) * arrowH;

    float popX = mainBuildingSlotRects[hoveredCardIndex].x + (mainBuildingSlotRects[hoveredCardIndex].w - tileW) / 2.f;
    float popY = mainBuildingSlotRects[hoveredCardIndex].y - totalH - 15.f;
    if (popY < 5.f) popY = 5.f;

    // Fond du popup
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 230);
    SDL_FRect bgRect = {popX - 12.f, popY - 8.f, tileW + 24.f, totalH + 16.f};
    SDL_RenderFillRect(renderer, &bgRect);
    mainBuildingPopupRect = bgRect;
    SDL_SetRenderDrawColor(renderer, factionColor.r, factionColor.g, factionColor.b, 120);
    SDL_RenderRect(renderer, &bgRect);

    // Tier 5 en haut → Tier 1 en bas
    for (int t = maxTier; t >= 1; t--) {
        int idx = maxTier - t;  // 0 = tier5(top), 4 = tier1(bas)
        float tierSquareY = popY + idx * (tileH + arrowH);

        bool isCurrent  = (t == currentTier);
        bool isNext = t == currentTier + 1 && currentTier < maxTier;
        bool isUnlocked = (t < currentTier);

        // Carré du tier
        if (isCurrent) {
            SDL_SetRenderDrawColor(renderer, factionColor.r, factionColor.g, factionColor.b, 255);
        }
        else if (isNext) {
            SDL_SetRenderDrawColor(renderer, factionColor.r/2,factionColor.g/2,factionColor.b/2,255);
        }
        else if (isUnlocked) {
            SDL_SetRenderDrawColor(renderer, factionColor.r,factionColor.g,factionColor.b,255);
        }
        else
            SDL_SetRenderDrawColor(renderer, 22, 22, 22, 255);

        SDL_FRect tierRect = {popX, tierSquareY, tileW, tileH};
        SDL_RenderFillRect(renderer, &tierRect);

        SDL_Texture* tierTexturePopUp = nullptr;
if (province.owner == FactionZone::Knight) {
    if (sel->settlementData.type == SettlementType::Capital) {
        if (t == 1) tierTexturePopUp = capitalBuildingUpgrade1Knight;
        else if (t == 2) tierTexturePopUp = capitalBuildingUpgrade2Knight;
        else if (t == 3) tierTexturePopUp = capitalBuildingUpgrade3Knight;
        else if (t == 4) tierTexturePopUp = capitalBuildingUpgrade4Knight;
        else if (t == 5) tierTexturePopUp = capitalBuildingUpgrade5Knight;
    }
    else if (sel->settlementData.type == SettlementType::Castle) {
        if (t == 1) tierTexturePopUp = castleBuildingUpgrade1Knight;
        else if (t == 2) tierTexturePopUp = castleBuildingUpgrade2Knight;
        else if (t == 3) tierTexturePopUp = castleBuildingUpgrade3Knight;
        else if (t == 4) tierTexturePopUp = castleBuildingUpgrade4Knight;
        else if (t == 5) tierTexturePopUp = castleBuildingUpgrade5Knight;
    }
    else if (sel->settlementData.type == SettlementType::Village) {
        if (t == 1) tierTexturePopUp = villageBuildingUpgrade1Knight;
        else if (t == 2) tierTexturePopUp = villageBuildingUpgrade2Knight;
        else if (t == 3) tierTexturePopUp = villageBuildingUpgrade3Knight;
    }
}
else if (province.owner == FactionZone::Viking) {
    if (sel->settlementData.type == SettlementType::Capital) {
        if (t == 1) tierTexturePopUp = capitalBuildingUpgrade1Viking;
        else if (t == 2) tierTexturePopUp = capitalBuildingUpgrade2Viking;
        else if (t == 3) tierTexturePopUp = capitalBuildingUpgrade3Viking;
        else if (t == 4) tierTexturePopUp = capitalBuildingUpgrade4Viking;
        else if (t == 5) tierTexturePopUp = capitalBuildingUpgrade5Viking;
    }
    else if (sel->settlementData.type == SettlementType::Castle) {
        if (t == 1) tierTexturePopUp = castleBuildingUpgrade1Viking;
        else if (t == 2) tierTexturePopUp = castleBuildingUpgrade2Viking;
        else if (t == 3) tierTexturePopUp = castleBuildingUpgrade3Viking;
        else if (t == 4) tierTexturePopUp = castleBuildingUpgrade4Viking;
        else if (t == 5) tierTexturePopUp = castleBuildingUpgrade5Viking;
    }
    else if (sel->settlementData.type == SettlementType::Village) {
        if (t == 1) tierTexturePopUp = villageBuildingUpgrade1Viking;
        else if (t == 2) tierTexturePopUp = villageBuildingUpgrade2Viking;
        else if (t == 3) tierTexturePopUp = villageBuildingUpgrade3Viking;
    }
}
else if (province.owner == FactionZone::Samurai) {
    if (sel->settlementData.type == SettlementType::Capital) {
        if (t == 1) tierTexturePopUp = capitalBuildingUpgrade1Samurai;
        else if (t == 2) tierTexturePopUp = capitalBuildingUpgrade2Samurai;
        else if (t == 3) tierTexturePopUp = capitalBuildingUpgrade3Samurai;
        else if (t == 4) tierTexturePopUp = capitalBuildingUpgrade4Samurai;
        else if (t == 5) tierTexturePopUp = capitalBuildingUpgrade5Samurai;
    }
    else if (sel->settlementData.type == SettlementType::Castle) {
        if (t == 1) tierTexturePopUp = castleBuildingUpgrade1Samurai;
        else if (t == 2) tierTexturePopUp = castleBuildingUpgrade2Samurai;
        else if (t == 3) tierTexturePopUp = castleBuildingUpgrade3Samurai;
        else if (t == 4) tierTexturePopUp = castleBuildingUpgrade4Samurai;
        else if (t == 5) tierTexturePopUp = castleBuildingUpgrade5Samurai;
    }
    else if (sel->settlementData.type == SettlementType::Village) {
        if (t == 1) tierTexturePopUp = villageBuildingUpgrade1Samurai;
        else if (t == 2) tierTexturePopUp = villageBuildingUpgrade2Samurai;
        else if (t == 3) tierTexturePopUp = villageBuildingUpgrade3Samurai;
    }
}

// Appliquer transparence si verrouillé
if (tierTexturePopUp) {
    Uint8 alpha = isCurrent ? 255 : (isNext ? 180 : 60);
    SDL_SetTextureAlphaMod(tierTexturePopUp, alpha);
    SDL_RenderTexture(renderer, tierTexturePopUp, nullptr, &tierRect);
    SDL_SetTextureAlphaMod(tierTexturePopUp, 255); // reset
}


        // Bordure
        SDL_SetRenderDrawColor(renderer,
            isCurrent ? factionColor.r : 65,
            isCurrent ? factionColor.g : 65,
            isCurrent ? factionColor.b : 65, 255);
        SDL_RenderRect(renderer, &tierRect);

        // Chiffre romain
        const char* rn[] = {"I", "II", "III", "IV", "V"};
        TTF_SetTextString(gameStatUIText, rn[t - 1], 0);
        Uint8 la = isCurrent ? 255 : (isUnlocked ? 180 : 80);
        TTF_SetTextColor(gameStatUIText, la, la, la, 255);
        int tw = 0, th = 0;
        TTF_GetTextSize(gameStatUIText, &tw, &th);
        TTF_DrawRendererText(gameStatUIText,popX + (tileW - tw) / 2.f,tierSquareY + tileH - th - 5.f);


        if (t > currentTier && t <= maxTier) {
            BuildingType mainBuilding = sel->settlementData.buildings[0];
            int cost = player.GetUpgradeCost(t - 1, mainBuilding);
            std::string costString = std::to_string(cost);
            TTF_SetTextString(gameBuildingCostUIText, costString.c_str(), 0);

            //green if can purchase and red if to expensive
            if (player.currentGold >= cost) {
                TTF_SetTextColor(gameBuildingCostUIText, 127, 255, 0, 255);
            }else {
                TTF_SetTextColor(gameBuildingCostUIText, 220, 60, 60, 255);
            }
            int costW = 0, costH = 0;
            TTF_GetTextSize(gameBuildingCostUIText, &costW, &costH);
            TTF_DrawRendererText(gameBuildingCostUIText,popX + (tileW - costW) -2.f,tierSquareY + 45.f);

            //texture gold
            float iconSize = 12.f;
            float totalRowW = iconSize + 3.f + costW;
            float rowStartX = popX + (tileW - totalRowW) / 2.f;

            SDL_FRect goldUI = {rowStartX + 57.f, tierSquareY + 48.f, iconSize, iconSize};
            SDL_SetRenderDrawColor(renderer, 220, 180, 40, 255);
            SDL_RenderFillRect(renderer, &goldUI);
            SDL_SetRenderDrawColor(renderer, 180, 140, 20, 255);
            SDL_RenderRect(renderer, &goldUI);
        }






        // up arrow between this current and next building upgrade
        if (t > 1) {
            float cx  = popX + tileW / 2.f;
            float tipY = tierSquareY + tileH + 2.f;
            float baseY = tierSquareY + tileH + arrowH - 2.f;
            SDL_SetRenderDrawColor(renderer, 0, 180, 0, 200);
            SDL_RenderLine(renderer, (int)cx, (int)tipY,  (int)cx, (int)baseY);
            SDL_RenderLine(renderer, (int)cx, (int)tipY,  (int)(cx - 6), (int)(tipY + 8));
            SDL_RenderLine(renderer, (int)cx, (int)tipY,  (int)(cx + 6), (int)(tipY + 8));
        }
        // Sauvegarder le rect pour la détection de clic
        if ((int)tierPopupRects.size() < maxTier)
            tierPopupRects.resize(maxTier);
        tierPopupRects[t - 1] = tierRect;
        tierPopupMaxTier = maxTier;

    }
}

        if (bButtonUIGarrisonIsPressed) {
            //To Do later the garrison with Their Unit cards
        }
        // Title bottomProvince Title
        float middleTitlePositionX = 835.f;
        float middleTitlePositionY = 770.f;
        SDL_SetRenderDrawColor(renderer, factionColor.r, factionColor.g, factionColor.b, 180);
        SDL_FRect titleBottomBar = {middleTitlePositionX, middleTitlePositionY, 250.f, 40.f};
        SDL_RenderFillRect(renderer, &titleBottomBar);
        // Name province for bottomProvince Title
        TTF_SetTextString(gameStatUITitleText, province.name.c_str(), 0);
        TTF_SetTextColor(gameStatUITitleText, 255, 255, 255, 255);
        TTF_DrawRendererText(gameStatUITitleText, middleTitlePositionX + 50.f, middleTitlePositionY + 2.f);

    // Restore
    TTF_SetTextColor(gameStatUITitleText, 255, 255, 255, 255);

}
    //The top UI bar for the money / turn area
    void RenderGeneralUI(){
    //rectangle of the top ui part
        // Bordure
        float thickness = 5.0f;
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_FRect borderRect = {600, 0, 800, 40};
        SDL_RenderFillRect(renderer, &borderRect);

       //inner UI rectangle
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        SDL_FRect contentRect = {600 + thickness,0 + thickness,800 - (thickness * 2),40 - (thickness * 2)};
        SDL_RenderFillRect(renderer, &contentRect);

        //icon Gold
        SDL_FRect goldIcon = {contentRect.x + 50.f, borderRect.y + 13.f,15.f,15.f};
        SDL_SetRenderDrawColor(renderer, 255,234,90,255);
        SDL_RenderFillRect(renderer, &goldIcon);

        //current Gold
        std::string goldStr = std::to_string(player.currentGold);
        TTF_SetTextString(gameCurrentMoneyUiText, goldStr.c_str(), 0);
        TTF_SetTextColor(gameCurrentMoneyUiText, 255, 255, 255, 255); // keep in white
        TTF_DrawRendererText (gameCurrentMoneyUiText, contentRect.x + 70.f, contentRect.y + 4.f);

        //calculate gold next turn
        player.nextTurnGold = 0;
        for (const auto& s: settlements) {
            if (provinces[s.settlementData.provinceID].owner == player.faction) {
                player.nextTurnGold += s.settlementData.baseIncome;
            }
        }
        //Gold Next turn + (green) - (red)
        std::string nextTurnStr = "(+" + std::to_string(player.nextTurnGold) + ")";
        TTF_SetTextString(gameAnticipatedMoneyUiText, nextTurnStr.c_str(), 0);
        TTF_SetTextColor(gameAnticipatedMoneyUiText, 127, 255, 0, 255);
        TTF_DrawRendererText(gameAnticipatedMoneyUiText,contentRect.x + 125.f, contentRect.y + 4.f);


        //circle  button for the NextTurn Button
        SDL_SetRenderDrawColor(renderer, 0,80,255,255);
        RenderBoutonCercle(NextTurnButton, nullptr, nullptr,180, 180, 180);
        //text to show the current Turn
        std::string endTurn = std::to_string(currentTurn);
        TTF_SetTextString(gameNumberOfTurnText, endTurn.c_str(), 0);
        TTF_SetTextColor(gameNumberOfTurnText, 255, 255, 255, 255);
        TTF_DrawRendererText(gameNumberOfTurnText, NextTurnButton.circleX+45.f, NextTurnButton.circleY+35.f);

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
        RenderBoutons(BoutonPlay, textStart, 20, 20, 20,255);
        RenderBoutons(BoutonTutorial, textTutorial, 20, 20, 20,255);
        RenderBoutons(BoutonOptions, textOptions, 20, 20, 20,255);
        RenderBoutons(BoutonQuit, textQuit, 20, 20, 20,255);
        RenderBoutons(BoutonCredits, textCredits, 20, 20, 20,255);


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
        RenderBoutons(BoutonKnight, nullptr, 255,255,0,255);
        RenderBoutons(BoutonViking, nullptr, 0,0,255,255);
        RenderBoutons(BoutonSamurai, nullptr, 255,0,0,255);
        RenderBoutons(BoutonStartCampaign, factionSelectionStartCampaignText, 60,60,60,255);

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
        // camera wasd movement
        const bool* keys = SDL_GetKeyboardState(nullptr);
        float baseSpeed = 400.f;
        float multiplierSpeed = 2.f;
        float currentSpeed = baseSpeed;
        if (keys[SDL_SCANCODE_LSHIFT]) {
            currentSpeed *= multiplierSpeed;
        }
        if (keys[SDL_SCANCODE_W]) camera.Movement(0, -currentSpeed * deltaTime);
        if (keys[SDL_SCANCODE_S]) camera.Movement(0,  currentSpeed * deltaTime);
        if (keys[SDL_SCANCODE_A]) camera.Movement(-currentSpeed * deltaTime, 0);
        if (keys[SDL_SCANCODE_D]) camera.Movement( currentSpeed* deltaTime, 0);
        //camera mouse on edge
        float mouseX;
        float mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        float logicX, logicY;
        SDL_RenderCoordinatesFromWindow(renderer, mouseX,mouseY,&logicX,&logicY);

        float speed = 400.f;
        float edgeSize = 25.f;
        //left
        if (logicX < edgeSize) {
            camera.Movement(-speed * deltaTime, 0);
        }
        if (logicX > 1920 - edgeSize) {
            camera.Movement(speed * deltaTime, 0);
        }
        if (logicY < edgeSize) {
            camera.Movement(0, -speed * deltaTime);
        }
        if (logicY > 1080 - edgeSize) {
            camera.Movement(0, speed* deltaTime);
        }

        //clear everything out
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        //tilemap
        if (tileMap) tileMap->Render(renderer, camera);
        //provinces map
        if (tileMap) tileMap->RenderProvinceBorders(renderer, provinces, camera);

        //Render the settlements
        RenderSettlements();

        //if camera is far enough the texts of kingdoms + their texture shows
        if (camera.zoom < 1.8f && tileMap) {
            //faction names inside Territory
            struct FactionLabel {
                int      startProvince;
                int      endProvince;
                TTF_Text* text;
            };

            auto getFactionCenter = [&](int p1, int p2, int p3) -> SDL_FPoint {
                SDL_FPoint c1 = tileMap->GetProvinceCenter(p1);
                SDL_FPoint c2 = tileMap->GetProvinceCenter(p2);
                SDL_FPoint c3 = tileMap->GetProvinceCenter(p3);
                return {
                    (c1.x + c2.x + c3.x) / 3.f,
                    (c1.y + c2.y + c3.y) / 3.f
                };
            };

            // alpha based on zoom
            float alpha = std::clamp((1.1f - camera.zoom) / 0.3f, 0.f, 1.f);
            Uint8 a = (Uint8)(alpha * 255.f);

            SDL_FPoint knightCenter  = getFactionCenter(0, 1, 2);
            SDL_FPoint vikingCenter  = getFactionCenter(3, 4, 5);
            SDL_FPoint samuraiCenter = getFactionCenter(6, 7, 8);

            auto worldToScreen = [&](SDL_FPoint wp) -> SDL_FPoint {
                return {
                    wp.x * camera.zoom - camera.startX * camera.zoom,
                    wp.y * camera.zoom - camera.startY * camera.zoom
                };
            };

            SDL_FPoint kScreen = worldToScreen(knightCenter);
            SDL_FPoint vScreen = worldToScreen(vikingCenter);
            SDL_FPoint sScreen = worldToScreen(samuraiCenter);

            //Banner position for the kight
            auto renderKnightBanner = [&](SDL_Texture* provincesTexture, SDL_FPoint screenPos, Uint8 alpha) {
                if (!provincesTexture) return;
                SDL_FRect dst = {
                    screenPos.x - 145.f,
                    screenPos.y - 70.f,
                    275.f, 150.f
                };
                SDL_SetTextureAlphaMod(provincesTexture, alpha);
                SDL_SetTextureBlendMode(provincesTexture, SDL_BLENDMODE_BLEND);
                SDL_RenderTexture(renderer, provincesTexture, nullptr, &dst);
            };
            //render for the samurai
            auto renderSamuraiBanner = [&](SDL_Texture* provincesTexture, SDL_FPoint screenPos, Uint8 alpha) {
                if (!provincesTexture) return;
                SDL_FRect dst = {
                    screenPos.x - 140.f,
                    screenPos.y - 75.f,
                    275.f, 150.f
                };
                SDL_SetTextureAlphaMod(provincesTexture, alpha);
                SDL_SetTextureBlendMode(provincesTexture, SDL_BLENDMODE_BLEND);
                SDL_RenderTexture(renderer, provincesTexture, nullptr, &dst);
            };
            //render for the viking
            auto renderVikingBanner = [&](SDL_Texture* provincesTexture, SDL_FPoint screenPos, Uint8 alpha) {
                if (!provincesTexture) return;
                SDL_FRect dst = {
                    screenPos.x - 100.f,
                    screenPos.y - 70.f,
                    275.f, 150.f
                };
                SDL_SetTextureAlphaMod(provincesTexture, alpha);
                SDL_SetTextureBlendMode(provincesTexture, SDL_BLENDMODE_BLEND);
                SDL_RenderTexture(renderer, provincesTexture, nullptr, &dst);
            };

            renderKnightBanner(provinceKnightBannerTexture,  kScreen, a);
            //renderVikingBanner(vikingBanner,  vScreen, a);
            renderSamuraiBanner(provinceSamuraiBannerTexture, sScreen, a);


            TTF_SetTextColor(gameKingdomKnightNameText, 140, 100, 42,   a);
            TTF_SetTextColor(gameKingdomVikingNameText, 220,50,50, a);
            TTF_SetTextColor(gameKingdomSamuraiNameText,0, 200,  160,  a);

            int textW, textH;

            TTF_GetTextSize(gameKingdomKnightNameText, &textW, &textH);
            TTF_DrawRendererText(gameKingdomKnightNameText, kScreen.x - textW/2.f, kScreen.y - textH/2.f);

            TTF_GetTextSize(gameKingdomVikingNameText, &textW, &textH);
            TTF_DrawRendererText(gameKingdomVikingNameText, vScreen.x - textW/2.f, vScreen.y - textH/2.f);

            TTF_GetTextSize(gameKingdomSamuraiNameText, &textW, &textH);
            TTF_DrawRendererText(gameKingdomSamuraiNameText, sScreen.x - textW/2.f, sScreen.y - textH/2.f);;
        }

        //Render the UI of provinces
        RenderProvinceUI();
        RenderGeneralUI();

        //fps
        TTF_DrawRendererText(fpsText, 10, 10);
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
        //SDL_SetRenderDrawColor(renderer, 120,40,120,255);
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

    //fonction to end a turn
    void EndTurn() {
        player.AddGold(player.nextTurnGold);

        // Order of who's playing first
        std::vector<FactionZone> turnOrder = {
            FactionZone::Knight,
            FactionZone::Viking,
            FactionZone::Samurai
        };

        //Always start new turn with the player
        // Player = Viking -> order = Viking, Samurai, Knight
        // Player = Samurai -> order = Samurai, Knight, Viking
        // Player = Knight -> order = Knight, Viking, Samurai
        int playerIndex = 0;
        for (int i = 0; i < (int)turnOrder.size(); i++) {
            if (turnOrder[i] == player.faction) {
                playerIndex = i;
                break;
            }
        }

        // //play the turns of the AI
        for (int i = 1; i < (int)turnOrder.size(); i++) {
            FactionZone aiTurn = turnOrder[(playerIndex + i) % turnOrder.size()];
            // IA placeholder
            SDL_Log("AI turn: faction %d", (int)aiTurn);
            //AIPlayTurn(aiTurn);
        }

        currentTurn++;
        SDL_Log("Turn %d || your turn (%d)", currentTurn, (int)player.faction);
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
                if (app.selectedFaction == 0) {
                    app.player.faction = FactionZone::Knight;
                }
                else if (app.selectedFaction == 1) {
                    app.player.faction = FactionZone::Viking;
                }
                else if (app.selectedFaction == 2) {
                    app.player.faction = FactionZone::Samurai;
                }
                app.StateActuel= State::Game;
            }
            //Circle
            if (app.ClickInsideCircle(nouveauX, nouveauY, app.BoutonReturn)) {
                app.StateActuel = State::Menu;
            }
        }
        //IF IN GAME
        //When pressded it shows the position of 1 tile
        if (app.StateActuel == State::Game) {
    float worldX = (nouveauX + app.camera.startX * app.camera.zoom) / app.camera.zoom;
    float worldY = (nouveauY + app.camera.startY * app.camera.zoom) / app.camera.zoom;
    int tileC = (int)(worldX / app.tileMap->tileSize);
    int tileR = (int)(worldY / app.tileMap->tileSize);
    SDL_Log("Tile: col=%d, row=%d", tileC, tileR);

    if (app.bHasClickedOnASettlement) {
        SDL_FPoint pt = {nouveauX, nouveauY};
        if (SDL_PointInRectFloat(&pt, &app.provinceButtonUIBuilding)) {
            app.bButtonUIBuildingIsPressed = true;
            app.bButtonUIGarrisonIsPressed = false;
            return SDL_APP_CONTINUE; // ← stop ici, pas de reset
        }
        if (SDL_PointInRectFloat(&pt, &app.provinceButtonUIGarrison)) {
            app.bButtonUIGarrisonIsPressed = true;
            app.bButtonUIBuildingIsPressed = false;
            return SDL_APP_CONTINUE; // ← stop ici, pas de reset
        }
    }

            // Clic sur un tier du popup
            if (app.bHasClickedOnASettlement &&
                app.hoveredSlotIndex == 0 &&
                app.hoveredCardIndex >= 0 &&
                !app.tierPopupRects.empty())
            {
                SDL_FPoint pt = {nouveauX, nouveauY};
                for (int t = 1; t <= app.tierPopupMaxTier; t++) {
                    if (SDL_PointInRectFloat(&pt, &app.tierPopupRects[t - 1])) {
                        // Récupérer le settlement survolé
                        // Rebuild provinceSettlements pour trouver le bon
                        const Settlement& clicked = app.settlements[app.selectedSettlementIndex];
                        int provID = clicked.settlementData.provinceID;
                        std::vector<Settlement*> provS;
                        for (auto& s : app.settlements)
                            if (s.settlementData.provinceID == provID)
                                provS.push_back(&s);

                        if (app.hoveredCardIndex < (int)provS.size()) {
                            Settlement* sel = provS[app.hoveredCardIndex];
                            // Upgrade seulement si c'est le tier suivant + faction player
                            if (t == sel->settlementData.settlementTier + 1 && t <= app.tierPopupMaxTier) {
                                //continue if not player Faction
                                int provID = clicked.settlementData.provinceID;
                                if (app.provinces[provID].owner != app.player.faction) {
                                    return SDL_APP_CONTINUE;
                                }

                                BuildingType mainBuilding = sel->settlementData.buildings[0];
                                //cost of each settlement + if money of player is higher than the price -> can purchase other it doesnt
                                int cost = app.player.GetUpgradeCost(sel->settlementData.settlementTier, mainBuilding);
                                if (app.player.SpendGold(cost)) {
                                    sel->settlementData.settlementTier = t;
                                    SDL_Log("Upgraded to tier %d, gold remaining: %d", t, app.player.currentGold);
                                } else {
                                    SDL_Log("Not enough gold! Need %d, have %d", cost, app.player.currentGold);
                                }
                            }
                        }
                        return SDL_APP_CONTINUE;
                    }
                }
            }

    // dection if clicked a settlement
    bool bClickedOutsideOfUI = false;
    for (int i = 0; i < (int)app.settlements.size(); i++) {
        const auto &s = app.settlements[i];
        int settlementSize = 2;
        if (s.settlementData.type == SettlementType::Capital) settlementSize = 4;
        else if (s.settlementData.type == SettlementType::Castle) settlementSize = 3;

        if (tileC >= s.tileCol && tileC < s.tileCol + settlementSize &&
            tileR >= s.tileRow && tileR < s.tileRow + settlementSize) {
            app.bHasClickedOnASettlement = true;
            app.selectedSettlementIndex = i;
            bClickedOutsideOfUI = true;
            break;
        }
    }
    if (!bClickedOutsideOfUI) {
        app.bHasClickedOnASettlement = false;
        app.bButtonUIBuildingIsPressed = true;//so it always go back to the base one
        app.selectedSettlementIndex = -1;
        app.hoveredSlotIndex = -1;
    }


    if (app.ClickInsideCircle(nouveauX,nouveauY, app.NextTurnButton)) {
        app.EndTurn();
        return SDL_APP_CONTINUE;
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
    //holding mouse wheel to move the camera
    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN &&event->button.button == SDL_BUTTON_MIDDLE &&app.StateActuel == State::Game) {
        app.bIsMovingCamera = true;
        SDL_RenderCoordinatesFromWindow(app.renderer,event->button.x, event->button.y,&app.lastMouseX, &app.lastMouseY);
    }
    if (event->type == SDL_EVENT_MOUSE_BUTTON_UP &&event->button.button == SDL_BUTTON_MIDDLE) {
        app.bIsMovingCamera= false;
        }
    if (event->type == SDL_EVENT_MOUSE_MOTION &&app.bIsMovingCamera &&app.StateActuel == State::Game) {
        float mx, my;
        SDL_RenderCoordinatesFromWindow(app.renderer,event->motion.x, event->motion.y, &mx, &my);
        app.camera.Movement(-(mx - app.lastMouseX), -(my - app.lastMouseY));
        app.lastMouseX = mx;
        app.lastMouseY = my;
    }// Hover slot of the principal building
    if (event->type == SDL_EVENT_MOUSE_MOTION &&app.StateActuel == State::Game &&app.bHasClickedOnASettlement &&app.bButtonUIBuildingIsPressed)
    {
        float mx, my;
        SDL_RenderCoordinatesFromWindow(app.renderer, event->motion.x, event->motion.y, &mx, &my);
        SDL_FPoint pt = {mx, my};

        bool onAnySlot = false;
        for (int i = 0; i < (int)app.mainBuildingSlotRects.size(); i++) {
            if (SDL_PointInRectFloat(&pt, &app.mainBuildingSlotRects[i])) {
                app.hoveredSlotIndex = 0;
                app.hoveredCardIndex = i;
                onAnySlot = true;
                break;
            }
        }
        //little gap for the popup
        SDL_FRect popupWithGap = app.mainBuildingPopupRect;
        popupWithGap.h += 20.f; // couvre le gap de 15px + marge
        bool onPopup = SDL_PointInRectFloat(&pt, &popupWithGap);
        if (!onAnySlot && !onPopup) {
            app.hoveredSlotIndex = -1;
            app.hoveredCardIndex = -1;
        }
    }

    // Zoom
    if (event->type == SDL_EVENT_MOUSE_WHEEL && app.StateActuel == State::Game) {
        float factor = (event->wheel.y > 0) ? 1.1f : 0.9f;
        app.camera.Zoom(factor);
        }
    //When Mouse touch a edge it



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

        //to make the game on pause P

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

