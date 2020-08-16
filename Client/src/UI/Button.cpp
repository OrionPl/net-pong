#include "Button.hpp"

Button::Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, UI* _ui) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _texture, _ui) {
    
}

Button::Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, UI* _ui, void (*_eventHandler)) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _texture, _ui) {

}

Button::Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, UI* _ui, void (*_eventHandler), std::string text) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _texture, _ui) {

}

Button::Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, SDL_Texture* _texture, UI* _ui, std::string text) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _texture, _ui) {

}

Button::Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, UI* _ui) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _filled, _color, _ui) {

}

Button::Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, UI* _ui, void (*_eventHandler)) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _filled, _color, _ui) {
    
}

Button::Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, UI* _ui, void (*_eventHandler), std::string text) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _filled, _color, _ui) {
    
}

Button::Button(std::string _name, bool _active,  int _uiAnchor, int _xPos, int _yPos, int _xSize, int _ySize, bool _filled, SDL_Color _color, UI* _ui, std::string text) : UIElement(_name, _active, _uiAnchor, _xPos, _yPos, _xSize, _ySize, _filled, _color, _ui) {
    
}