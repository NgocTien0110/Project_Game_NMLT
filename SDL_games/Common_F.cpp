
#include "Common_Function.h"
#include "TextObject.h"

bool SDLCommonFunc::CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
    if (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}

int SDLCommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font)
{
    g_img_menu = LoadImage("menu2.bmp");
    if (g_img_menu == NULL)
    {
        return 1;//exit
    }

    const int kMenuItemNum = 3;
    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x = 200;
    pos_arr[0].y = 400;
    pos_arr[1].x = 200;
    pos_arr[1].y = 300;

    TextObject text_menu[kMenuItemNum];

    text_menu[0].SetText("Play Game");
    text_menu[0].SetColor(TextObject::BLACK_TEXT);
    text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);
    text_menu[1].SetText("Exit");
    text_menu[1].SetColor(TextObject::BLACK_TEXT);
    text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

    //ktr luc nhan chuot
    bool selected[kMenuItemNum] = { 0, 0 };
    int xm = 0;
    int ym = 0;

    //lấy vòng skien của con chuột vì con chuột di chueeyenr ltuc
    SDL_Event m_event;
    while (true)
    {
        SDLCommonFunc::ApplySurface(g_img_menu, des, 0, 0);//load ảnh menu lên
        for (int i = 0; i < kMenuItemNum; i++)
        {
            text_menu[i].CreateGameText(font, des);
        }

        //vòng skien
        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT://cái mũi tên thoát
                return 1;
            case SDL_MOUSEMOTION:
            {
                //lay toa do cua con chuot
                xm = m_event.motion.x;
                ym = m_event.motion.y;

                //ktra con chuột nó có nằm trog vùng item menu k
                for (int i = 0; i < kMenuItemNum; i++)
                {
                    if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))//đã được ktr ở trên
                    {
                        if (selected[i] == false)
                        {
                            selected[i] == true;//nằm trog vùng thì đúng
                            text_menu[i].SetColor(TextObject::RED_TEXT);
                        }
                    }
                    else
                    {
                        if (selected[i] == true)
                        {
                            selected[i] = 0;
                            text_menu[i].SetColor(TextObject::BLACK_TEXT);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m_event.button.x;
                ym = m_event.button.y;
                for (int i = 0; i < kMenuItemNum; i++)
                {
                    if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
                    {
                        return i;
                    }
                }
            }
            break;
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 1;
                }
            default:
                break;
            }
            }
        }
        SDL_Flip(des);
    }
    return 1;
}

SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path)
{
    SDL_Surface* load_image = NULL;
    SDL_Surface* optimize_image = NULL;
    load_image = IMG_Load(file_path.c_str());
    if (load_image != NULL)
    {
        optimize_image = SDL_DisplayFormat(load_image);
        SDL_FreeSurface(load_image);

        if (optimize_image != NULL)
        {
            UINT32 color_key = SDL_MapRGB(optimize_image->format, 0xFF, 0xAE, 0xC9);
            SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
        }
    }
    return optimize_image;
}

SDL_Rect SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(src, NULL, des, &offset);

    return offset;
}

void SDLCommonFunc::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(src, clip, des, &offset);
}

//ktr va cham giua 2 object
bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}

void SDLCommonFunc::CleanUp()
{
    SDL_FreeSurface(g_screen);
    SDL_FreeSurface(g_background);
}
