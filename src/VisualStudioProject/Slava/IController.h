#pragma once
#ifndef ICONTROLLER_H
#define ICONTROLLER_H
#include "Character.h"

namespace slava
{
	class Character;

	class IController
	{
	public:
		virtual void control(slava::Character*) = 0;
		// Note to us: Razmazila nas java/python/c#, misli detaljnije, misli koda si iskompleksiran etf-ovac da ne bi bilo memory leakova
		virtual ~IController() {};
	
	};

}

#endif
