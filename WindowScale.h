#pragma once
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>


struct WindowScaler {
	int Width, Height;
	RECT recDisplay;
	HWND hDeskWnd;

	void GetWindwScale(struct WindowScaler* p) {
		p->hDeskWnd = GetDesktopWindow();
		GetWindowRect(p->hDeskWnd, &p->recDisplay);
		
		p->Width = p->recDisplay.right * 0.8;
		p->Height = p->recDisplay.bottom * 0.8;
	}

};