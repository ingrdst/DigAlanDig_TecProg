#include "TitleState.h"
#define INCLUDE_SDL
#include "SDL_include.h"

#include <stdio.h>
#include "Camera.h"
#include "Sound.h"
#include "Sprite.h"
#include "StageState.h"
#include "Text.h"
#include "TileMap.h"
#include "Vec2.h"

TitleState::TitleState() {}

void TitleState::LoadAssets() {
    GameObject* gm = new GameObject(Common::Layer::HUD);
    gm->worldReference = false;
    objectArray.emplace_back(gm);
    gm->AddComponent(new Sprite(*gm, "assets/img/titleAlan.jpg"));

    gm = new GameObject(Common::Layer::HUD);
    gm->box.SetCenter(Camera::Center().x, 30);
    gm->worldReference = false;
    objectArray.emplace_back(gm);
    gm->AddComponent(new Text(*gm, "assets/font/Roboto-Regular.ttf", 72,
                              Text::TextStyle::BLENDED, "Press Space to begin",
                              {0, 0, 0, 255}, 1));
    Game::GetInstance()->StartBeatTime();

    music.Open("assets/audio/menu.ogg");
}

void TitleState::Start() {
    if (!started) LoadAssets();

    StartArray();
}

void TitleState::Update(float dt) {
    if (input.ActionPress(input.ENTER))
        Game::GetInstance()->Push(new StageState());
    UpdateArray(dt);
}

void TitleState::Render() const { RenderArray(); }

void TitleState::RhythmUpdate() {
    if (!musicPlaying) {
        music.Play();
        musicPlaying = true;
    }
    RhythmUpdateArray();
    input.title = true;
}
