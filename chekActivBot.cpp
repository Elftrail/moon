#include "chekActivBot.h"

bool chekActivBot(int mx, int my, sf::RectangleShape bot)
{
    int botPX = bot.getPosition().x;
    int botPY = bot.getPosition().y;
    int botSX = bot.getSize().x;
    int botSY = bot.getSize().y;

    if(mx>botPX&&mx<(botPX+botSX))
    {
        if (my > botPY && my < (botPY + botSY))
        {
            return true;
        }
        else { return false; }
    }
    else { return false; }
}
