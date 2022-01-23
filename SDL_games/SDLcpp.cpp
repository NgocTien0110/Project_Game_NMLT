
#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

int SPEED_THREAT = 8;

TTF_Font* g_font_text = NULL;
bool Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return false;
    }
    g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if (g_screen == NULL)
    {
        return false;
    }

    if (TTF_Init() == -1)
    {
        return false;
    }

   // khai báo âm thanh
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        return false;
    // đọc file audio
    g_sound_bullet[0] = Mix_LoadWAV("danlaser.wav");
    g_sound_bullet[1] = Mix_LoadWAV("dancau.wav");
    g_sound_exp[0] = Mix_LoadWAV("Explosion.wav");
    g_sound_exp[1] = Mix_LoadWAV("Eplosionthreat");



    g_font_text = TTF_OpenFont("Fresco Stamp.ttf", 50);//truyen font vao voi kich thuoc 40
    if (g_font_text == NULL)
    {
        return false;
    }
    return true;
}



#undef main
//khai bien cho diem
unsigned int die_number = 0;
unsigned int mark_value = 0;
int main(int arc, char* argv[])
{
AGAIN:


    int bkgn_x = 0;
    bool is_quit = false;
    if (Init() == false)
    {
        return 0;
    }
    g_background = SDLCommonFunc::LoadImage("bg600.png");

if (g_background == NULL)
{
    return 0;
}

//mang
TextObject alive_game;
alive_game.SetColor(TextObject::BLACK_TEXT);

//diem
TextObject mark_game;
mark_game.SetColor(TextObject::BLACK_TEXT);

//tgian
TextObject time_game;
time_game.SetColor(TextObject::BLACK_TEXT);

TextObject ins_game;
ins_game.SetColor(TextObject::BLACK_TEXT);

MainObject plane_object;
plane_object.SetRect(100, 200);
bool ret = plane_object.LoadImg("plane_fly.png");
if (!ret)
{
    return 0;
}

//Init explosion object
ExplosionObject exp_main;//doi tuong rieng k can con tro
ret = exp_main.LoadImg("exp_main.png");
exp_main.set_clip();//goi clip
if (!ret) 
    return 0;


//Make ThreatObject

ThreatObject* p_threats = new ThreatObject[NUM_THREATS];

srand((int)time(0));
for (int t = 0; t < NUM_THREATS; t++)
{
    ThreatObject* p_threat = (p_threats + t);//khoi tao doi tuong
    if (p_threat)
    {
        ret = p_threat->LoadImg("af1.png");
        if (ret == false)
        {
            return 0;
        }

        //set vtri ngau nhien
        int rand_y = rand() % 400;
        if (rand_y > SCREEN_HEIGHT - 200)
        {
            rand_y = SCREEN_HEIGHT * 0.3;
        }


        p_threat->SetRect(SCREEN_WIDTH + t * 400, SCREEN_HEIGHT * 0.3);
        p_threat->set_x_val(SPEED_THREAT);//TOC DO THREATS

        //nap dan cho doi tuong amo
        //AmoObject* p_amo = new AmoObject();
        //p_threat->InitAmo(p_amo);
    }

}

int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_text);//tra ve gia tri showmenu tra
    if (ret_menu == 1)
        is_quit = true;
    
int alive = 3;
while (!is_quit)
{
    while (SDL_PollEvent(&g_even))
    {
        if (g_even.type == SDL_QUIT)
        {
            is_quit = true;
            break;
        }
        plane_object.HandleInputAction(g_even, g_sound_bullet);
    }

    //apply backgr
    bkgn_x -= 2;//moi lan while no thoa man hinh bi dich sang trai mot khoang la 2
    SDLCommonFunc::ApplySurface(g_background, g_screen, bkgn_x, 0);
    SDLCommonFunc::ApplySurface(g_background, g_screen, bkgn_x + SCREEN_WIDTH, 0);
    if (bkgn_x <= -SCREEN_WIDTH)//ktr khi bkgn 1 no dich het sang phai thi gan lai x no = 0 de no dich chuyen tiep
    {
        bkgn_x = 0;
    }
    //main object
    plane_object.HandleMove();
    plane_object.Show(g_screen);
    plane_object.MakeAmo(g_screen);


    //RUN THREAT
    for (int tt = 0; tt < NUM_THREATS; tt++)
    {
        ThreatObject* p_threat = (p_threats + tt);
        if (p_threat)
        {
            p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
            p_threat->Show(g_screen);
            p_threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

            if (SDL_Flip(g_screen) == -1)
                return 0;

            //sau khi vien dan di chuyen xog se ktr va cham giua main va threats

            bool is_col = SDLCommonFunc::CheckCollision(plane_object.GetRect(), p_threat->GetRect());
            if (is_col)
            {
                alive--;
                die_number++;
                p_threat->Reset(SCREEN_WIDTH + tt * 400);
                //va cham thanh cog thi xay ra vu no
                for (int ex = 0; ex < 4; ex++)
                {
                    //vtri cua vu no
                    int x_pos = (plane_object.GetRect().x + plane_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;//tru cho chieu dai va chieu rong de ngay tam vu no
                    int y_Pos = (plane_object.GetRect().y + plane_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;

                    exp_main.set_frame(ex);
                    exp_main.SetRect(x_pos, y_Pos);
                    exp_main.ShowEx(g_screen); //show hinh vu no len
                    SDL_Delay(100);
                    //update screen len

                    if (SDL_Flip(g_screen) == -1)
                    {
                        delete[] p_threats;             // XÓA THREAT
                        SDLCommonFunc::CleanUp();
                        SDL_Quit();
                        return 0;
                    }

                    Mix_PlayChannel(-1, g_sound_exp[0], 0);    // âm thanh g_sound_exp[0](được định nghĩa ở trên ) 0 là lặp lại
                }

                //Mạng
                    if (alive != 0)
                    {
                        if (alive == 2)
                        {
                            if (MessageBox(NULL, L"Bạn còn 2 mạng", L"NGU", MB_OK) == IDOK);
                        }
                        else if (alive == 1)
                            if (MessageBox(NULL, L"Bạn còn 1 mạng", L"NGU", MB_OK) == IDOK);
                     
                        plane_object.SetRect(0, 320 );
                        bool ret = plane_object.LoadImg("plane_fly.png");
                        if (!ret)
                        {
                            return 0;
                        }

                    }
                    else
                    {
                         if (MessageBox(NULL, L"MÀY ĐÃ THUA, CÓ MUỐN CHƠI LẠI KHÔNG?", L"NGU", MB_YESNO) == IDYES)
                         {
                            //XOA CON TRO
                            delete[] p_threats;
                            SDLCommonFunc::CleanUp();
                            goto AGAIN;
                         }
                         else
                         {
                             //XOA CON TRO
                             delete[] p_threats;
                             SDLCommonFunc::CleanUp();
                             SDL_Quit();
                             return 0;
                         }
                    }
                    
            }

            //ktr va cham dan cua main vs threats
            std::vector<AmoObject*> amo_list = plane_object.GetAmoList(); //goi ham dan
            for (int im = 0; im < amo_list.size(); im++)
            {
                AmoObject* p_amo = amo_list.at(im);
                if (p_amo != NULL)
                {
                    //ktr neu va cham dan
                    bool ret_col = SDLCommonFunc::CheckCollision(p_amo->GetRect(), p_threat->GetRect());
                    if (ret_col)//true 
                    {
                        mark_value += 10;
                        //khi hai object va cham nhau thi threat dc set ve vtri bdau
                        p_threat->Reset(SCREEN_WIDTH + tt * 400);
                        //vien dan main bi xoa bo
                        plane_object.RemoveAmo(im);
                        Mix_PlayChannel(-1, g_sound_exp[1], 0);   // âm thanh g_sound_exp[1](được định nghĩa ở trên ) 0 là lặp lại
                        if (mark_value == 100)
                        {
                            if (MessageBox(NULL, L"BẠN ĐÃ QUA MÀN 1", L"GIỎI", MB_OK) == IDOK)
                            {
                                SPEED_THREAT = 15;
                                for (int t = 0; t < NUM_THREATS; t++)
                                {
                                    ThreatObject* p_threat = (p_threats + t);//khoi tao doi tuong
                                    if (p_threat)
                                    {
                                        ret = p_threat->LoadImg("af1.png");
                                        if (ret == false)
                                        {
                                            return 0;
                                        }
                                    }

                                    int rand_y = rand() % 400;
                                    if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
                                    {
                                        rand_y = SCREEN_HEIGHT * 0.25;
                                    }
                                    p_threat->SetRect(SCREEN_WIDTH + t * 400, SCREEN_HEIGHT * 0.3);
                                    p_threat->set_x_val(SPEED_THREAT);//TOC DO THREATS
                                }
                            }                           
                        }
                        if (mark_value == 150)
                        {
                            if (MessageBox(NULL, L"BẠN ĐÃ QUA MÀN 2", L"Giỏi", MB_OK) == IDOK)
                            {
                                SPEED_THREAT = 20;
                                for (int t = 0; t < NUM_THREATS; t++)
                                {
                                    ThreatObject* p_threat = (p_threats + t);//khoi tao doi tuong
                                    if (p_threat)
                                    {
                                        ret = p_threat->LoadImg("af1.png");
                                        if (ret == false)
                                        {
                                            return 0;
                                        }
                                    }
                                    int rand_y = rand() % 400;
                                    if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
                                    {
                                        rand_y = SCREEN_HEIGHT * 0.3;
                                    }
                                    p_threat->SetRect(SCREEN_WIDTH + t * 400, SCREEN_HEIGHT * 0.3);
                                    p_threat->set_x_val(SPEED_THREAT);//TOC DO THREATS
                                }
                            }
                        }

                    }
                }
            }

        }
    }

    //Show time
    std::string str_time = "Time : ";
    Uint32 time_val = SDL_GetTicks() / 1000;
    std::string str_val = std::to_string(time_val);
    str_time += str_val;//CONG CHUOI

    time_game.SetText(str_time);
    time_game.SetRect(SCREEN_WIDTH - 300, 550);
    time_game.CreateGameText(g_font_text, g_screen);
    //show alive
    std::string val_str_alive = std::to_string(die_number);
    std::string strAlive("DEATH: ");
    strAlive += val_str_alive;

    alive_game.SetText(strAlive);//truyen gtri strMark vao
    alive_game.SetRect(0, 40);
    alive_game.CreateGameText(g_font_text, g_screen);

    if (SDL_Flip(g_screen) == -1)
    {
        return 0;
    }

    //Show mark
    std::string val_str_mark = std::to_string(mark_value);
    std::string strMark("POINT: ");
    strMark += val_str_mark;

    mark_game.SetText(strMark);//truyen gtri strMark vao
    mark_game.CreateGameText(g_font_text, g_screen);

        if (SDL_Flip(g_screen) == -1)
        {
            return 0;
        }
    }

    delete[] p_threats;
    SDLCommonFunc::CleanUp();
    SDL_Quit();
	return 1;

}