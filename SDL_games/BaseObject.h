#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "Common_Function.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void Show(SDL_Surface* des);//truyen vao man hinh
	bool LoadImg(const char* file_name);

	void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y;}
	SDL_Rect GetRect() const { return rect_;}
	//tra ra doi tuong surface
	SDL_Surface* GetObject() { return p_object_; }
	//cac lop con ke thua muon ke thua cac thuoc tinh cua thg nay thi phai dung protected
protected:
	SDL_Rect rect_;//_ duoi de phan biet cac lop thanh vien
	SDL_Surface* p_object_;
};

#endif
