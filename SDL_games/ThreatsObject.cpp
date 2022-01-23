#include "ThreatsObject.h"
#include "AmoObject.h"

ThreatObject::ThreatObject()
{
	//vtri ban dau xuat hien
	rect_.x = SCREEN_WIDTH;//mep phai man hinh
	rect_.y = SCREEN_HEIGHT * 0.5;//nam giua man hinh
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;
	x_val_ = 0;
	y_val_ = 0;
}

//dam bao cho giai phong tat ca bo nho
ThreatObject::~ThreatObject()
{
	if (p_amo_list_.size() > 0)
	{
		for (int i = 0; i < p_amo_list_.size(); i++)
		{
			AmoObject* p_amo = p_amo_list_.at(i);
			if (p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}
		p_amo_list_.clear();
	}
}

void ThreatObject::InitAmo(AmoObject* p_amo)
{
	/*if (p_amo)
	{
		bool ret = p_amo->LoadImg("sphere.png");
		if (ret)
		{
			p_amo->set_is_move(true);
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->set_type(AmoObject::SPHERE);
			p_amo->SetRect(rect_.x, rect_.y + rect_.h * 0.5);
			p_amo->set_x_val(SPEED_BULLET_THREATS);
			p_amo_list_.push_back(p_amo);
		}
	}*/
}

void ThreatObject::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	/*for (int i = 0; i < p_amo_list_.size(); i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo)
		{
			if (p_amo->get_is_move())
			{
				p_amo->Show(des);
				p_amo->HandleMoveRightToLeft();
			}
			//set vtri vien dan sau khi ban lien tuc
			else
			{
				p_amo->set_is_move(true);
				p_amo->SetRect(rect_.x , rect_.y + rect_.h * 0.5);
			}
		}
	}*/
}

void ThreatObject::HandleMove(const int& x_bordr, const int& y_border)
{
	rect_.x -= x_val_;
	if (rect_.x < 0)
	{
		rect_.x = SCREEN_WIDTH;
		//set vtri ngau nhien
		int rand_y = rand() % 400;
		if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
		{
			rand_y = SCREEN_HEIGHT * 0.3;
		}

		rect_.y = rand_y;
	}
}

void ThreatObject::HandleInputAction(SDL_Event events)
{

}

//reset threats
void ThreatObject::Reset(const int& xboder)
{
	rect_.x = xboder;
	//set vtri ngau nhien
	int rand_y = rand() % 400;
	if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
	{
		rand_y = SCREEN_HEIGHT * 0.3;
	}
	rect_.y = rand_y;

	//reste vi tri vien dan
	/*for (int i = 0; i < p_amo_list_.size(); i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo)
		{
			ResetAmo(p_amo);
		}
	}*/
}

void ThreatObject::ResetAmo(AmoObject* p_amo)
{
	//reset lai vtri vien dan
	//p_amo->SetRect(rect_.x, rect_.y + rect_.h * 0.5);
}