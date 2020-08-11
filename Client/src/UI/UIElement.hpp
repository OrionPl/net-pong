#pragma once

#include <SDL/SDL.h>
#include< <string>

#include "UI.hpp"

// TODO Anchor ui elements to different parts of the window (also relative to that part of the window)
#define ANCHOR_TOPLEFT 0
#define ANCHOR_TOPMIDDLE 1
#define ANCHOR_TOPRIGHT 2
#define ANCHOR_MIDDLELEFT 3
#define ANCHOR_MIDDLEMIDDLE 4
#define ANCHOR_MIDDLERIGHT 5
#define ANCHOR_BOTTOMLEFT 6
#define ANCHOR_BOTTOMMIDDLE 7
#define ANCHOR_BOTTOMRIGHT 8

#define UI_BACKGROUND_TEXTURED 0
#define UI_BACKGROUND_RECT_UNFILLED 1
#define UI_BACKGROUND_RECT_FILLED 2

// TODO Make it available to make a colored rectangle as background

class UIElement {
public:
    UIElement(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, UI* _ui);
    UIElement(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, UI* _ui);

    void Draw();

    void SetName(std::string _name) { name = _name; };
    std::string GetName() { return name; };

    void SetActive(bool _active) { active = _active; };
    bool GetActive() { return active; };

    void SetPosition(int x, int y) { xPos = x; yPos = y; };
    int* GetPosition() { int[2] a; a[0] = xPos; a[1] = yPos; return a; };

    void SetSize(int x, int y) { xSize = x; ySize = y; };
    int* GetSize() { int[2] a; a[0] = xSize; a[1] = ySize; return a; };

    void SetAnchor(int anchor) { uiAnchor = anchor; };
    int GetAnchor() { return uiAnchor; };

    void SetTexture(SDL_Texture* _texture) { texture = _texture; };
    SDL_Texture* GetTexture() { return texture; };

    void SetFilled(bool _filled) { filled = _filled; };
    bool GetFilled() { return filled; };

    void SetColor(SDL_Color _color) { color = _color; };
    SDL_Color GetColor() { color = _color; };

    void SetBackgroundType(int type) { backgroundType = type; };
    int GetBackgroundType() { return backgroundType; };

private:
    std::string name;
    bool active;
    UI* ui;
    SDL_Texture* texture;
    bool filled;
    SDL_Color color;
    int backgroundType;

    // Positions of top left corner, relative to anchor
    int xPos, yPos;
    int xSize, ySize;
    int uiAnchor;
}