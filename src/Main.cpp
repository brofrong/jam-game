#include "App.h"

#include <cmath>
#include "RoomEntity.h"
#include <iostream>
#include <algorithm>
#include <cstring>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

static NGame::TApp *app = nullptr;

static void InitApp(void) {
    app = NGame::TApp::Instance();

    app->EntityManager().RegisterEntity<THero>("Hero");
    app->EntityManager().RegisterEntity<TDirtEntity>("DirtEntity");
    app->EntityManager().RegisterEntity<TGrassEntity>("GrassEntity");
    app->EntityManager().RegisterEntity<TPlankEntity>("PlankEntity");
    app->EntityManager().RegisterEntity<TStoneEntity>("StoneEntity");
    app->EntityManager().RegisterEntity<TLadderEntity>("LadderEntity");
    app->EntityManager().RegisterEntity<TExplosionEntity>("ExplosionEntity");
    app->EntityManager().RegisterEntity<TKeyEntity>("KeyEntity");
    app->EntityManager().RegisterEntity<TMineEntity>("MineEntity");
    app->EntityManager().RegisterEntity<TCurseEntity>("CurseEntity");
    app->EntityManager().RegisterEntity<TSpikeEntity>("SpikeEntity");
    app->EntityManager().RegisterEntity<TEntranceEntity>("EntranceEntity");
    app->EntityManager().RegisterEntity<TExitEntity>("ExitEntity");
    app->EntityManager().RegisterEntity<TFloatingTextEntity>("FloatingTextEntity");
    app->EntityManager().RegisterEntity<TBackgroundTiler>("BackgroundTiler");
    app->EntityManager().RegisterEntity<TRoomEntity>("RoomEntity");

    app->EntityManager().MakeEntityByName("RoomEntity");
    app->EntityManager().MakeEntityByName("BackgroundTiler");

    auto h = app->EntityManager().MakeEntityByName("Hero");
    h->SetPosition({0, -64});
    app->EntityManager().UpdateCollision(h);
}

static void MainLoop(void) {
    if (app) {
        app->Run();
    } else {
        InitApp();
    }
}

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    
    srand(time(NULL));
    
    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(MainLoop, -1, true);
    #else
    while (true) { MainLoop(); }
    #endif

    return 0;
}

