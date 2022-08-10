#pragma once
#include"SimplePad.h"
#include<optional>

class HotKeys
{
public:
	HotKeys();
	~HotKeys();

	std::optional<QKeyEvent*> keysProcessing(SimplePad* sP, QKeyEvent* pe);
};