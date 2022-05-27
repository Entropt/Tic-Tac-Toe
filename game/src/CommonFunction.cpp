
#include "../include/CommonFunction.h"


bool inRect(int x, int y, SDL_Rect rect)
{
    return (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h);
}

string int2str(int num)
{
    if(num == 0) return "0";
    std::string res;
    while(num > 0){
        res = char(num%10 + 48) + res;
        num /= 10;
    }
    return res;
}
