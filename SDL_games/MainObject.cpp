#include "MainObject.h"

MainObject::MainObject()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val = 0;
}

MainObject::~MainObject()
{
	;
}

void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* bullte_sound[2])    /// xử lý cid chuột và âm thanh
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			y_val -= HEIGHT_MAIN_OBJECT / 4;//DICH LEN TREN BANG 1/4 CHIEU CAO NHAN VAT
			//TODO
			break;
		case SDLK_DOWN:
			y_val += HEIGHT_MAIN_OBJECT / 4;
			//TODO
			break;
		case SDLK_RIGHT:
			x_val_ += WIDTH_MAIN_OBJECT / 4;
			//TODO
			break;
		case SDLK_LEFT:
			x_val_ -= WIDTH_MAIN_OBJECT / 4;
			//TODO
			break;;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP: y_val += HEIGHT_MAIN_OBJECT / 4; break;
		case SDLK_DOWN: y_val -= HEIGHT_MAIN_OBJECT / 4; break;
		case SDLK_LEFT: x_val_ += WIDTH_MAIN_OBJECT / 4; break;
		case SDLK_RIGHT: x_val_ -= WIDTH_MAIN_OBJECT / 4; break;
		}
	}

	else if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		AmoObject* p_amo = new AmoObject();
		//ktr neu bam chuot trai
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			p_amo->SetWidthHeight(WIDTH_LASER, HEIGHT_LASER);			// hàm đọ rộng của hình súng
			p_amo->LoadImg("laser.png");								// hàm load ảnh súng lên màng hình
			p_amo->set_type(AmoObject::LASER);
			Mix_PlayChannel(-1, bullte_sound[0], 0);						// âm thanh của súng laser 
		}
		else if (events.button.button == SDL_BUTTON_RIGHT)
		{
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);			// hàm đọ rộng của hình súng
			p_amo->LoadImg("sphere.png");										// hàm load ảnh súng lên màng hình
			p_amo->set_type(AmoObject::SPHERE);
			Mix_PlayChannel(-1, bullte_sound[1], 0);						// âm thnah của súng sphere

		}

		//CAP NHAT VI TRI phai dua vien dan nam trong vung cua may bay
		p_amo->SetRect(this->rect_.x + this->rect_.w - 40, this->rect_.y + this->rect_.h*0.8);
		p_amo->set_is_move(true);
		p_amo->set_x_val(SPEED_MAIN_OBJECT);
		p_amo_list_.push_back(p_amo);

	}
	else if (events.type == SDL_MOUSEBUTTONUP)
	{

	}
}

void MainObject::MakeAmo(SDL_Surface* des)
{
	// xử lý đạn khi nó di chuyển
	for (int i = 0; i < p_amo_list_.size(); i++)     // kt coi đạn có trong máy bay chưa
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo != NULL)
		{
			if (p_amo->get_is_move())
			{
				p_amo->Show(des);       //  nhấp chuột thì đạn sẽ bắn ra
				//truyen kich thuoc vao man hinh
				p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);  // cho đạn di chuyển trong màn hình
			}
			//dan di qua gioi han thi xoa
			else
			{
				if (p_amo != NULL)   //  xét điều khiện khi đạn rea ngoài màng hình
				{
					p_amo_list_.erase(p_amo_list_.begin() + i);

					delete p_amo;    // xóa đạn
					p_amo = NULL;
				}
			}
		}
	}
}

void MainObject::HandleMove()       // hàm di chuyển
{
	// di chuyển ở mép trên cùng bên trái
	rect_.x += x_val_;

	if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH) //an lui mai
	{
		rect_.x -= x_val_;
	}

	rect_.y += y_val;
	if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 150) //gioi han may bay
	{
		rect_.y -= y_val;
	}
	
}

//viet ham remove dan
void MainObject::RemoveAmo(const int& idx)
{

	if (idx >= 0 && idx < p_amo_list_.size())//bam chuot ltuc nen size no dc cap phat ltuc thi idx phai dam bao luon nho hon
	{
		AmoObject* p_amo = p_amo_list_.at(idx);
		if (p_amo != NULL)
		{
			delete p_amo;
			p_amo = NULL;//sau khi xoa vien dan thi dan no dc vao cho trong
		}
		p_amo_list_.erase(p_amo_list_.begin() + idx);
	}

}
