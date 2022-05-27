
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "../include/CommonFunction.h"

class BaseObject {
    public:
        BaseObject();
        ~BaseObject();
        void SetRect(SDL_Rect nRect) {
            rect = nRect;
        }
        SDL_Rect GetRect() const {
            return rect;
        }
        SDL_Texture* GetObject() const {
            return p_object;
        }

        void setX(int _x) {rect.x = _x;}
        void setY(int _y) {rect.y = _y;}
        void setW(int _w) {rect.w = _w;}
        void setH(int _h) {rect.h = _h;}

        int getX() {return rect.x;}
        int getY() {return rect.y;}
        int getW() {return rect.w;}
        int getH() {return rect.h;}

        bool LoadImg(string path, SDL_Renderer* screen);
        void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
        void Free();

    protected:
        SDL_Texture* p_object;
        SDL_Rect rect;
};

#endif // BASE_OBJECT_H_
