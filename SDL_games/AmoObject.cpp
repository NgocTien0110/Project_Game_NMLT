#include "AmoObject.h"

AmoObject::AmoObject()
{
	rect_.x = 0;
	rect_.y = 0;
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
	amo_type_ = NONE;
	p_object_ = NULL;
}

AmoObject::~AmoObject()
{


}

void AmoObject::HandleMove(const int& x_border, const int& y_border)
{
	//rect_.x += x_val_;//dan ban thang mot luong la x_val_
	//phai ktr dan ban den gioi han screen

	if (rect_.y % 2 == 0)
	{
		rect_.x = rect_.x + x_val_;
		rect_.y = rect_.y + 21;
	}
	else
	{
		rect_.x = rect_.x + x_val_;
		rect_.y = rect_.y - 21;
	}
	if (rect_.x > x_border)
	{
		is_move_ = false;
	}
}


void AmoObject::HandleMoveRightToLeft()
{
	rect_.x -= x_val_;
	if (rect_.x < 0)
	{
		is_move_ = false;
	}
}

//void AmoObject::HandleInputAction(SDL_Event events)
//{
//
//}
