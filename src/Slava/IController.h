#ifndef __ICONTROLLER_H
#define __ICONTROLLER_H

namespace slava
{
	class Character;

	// Interfejs koji definise kontrolere, kao argument control metodi ide karakter koji se kontrolise,
	// Kontrolere uvijek koristiti u kombinaciji sa Characterom tako sto proslijedite referencu kontrolera Character instanci

	class IController
	{
	public:
		virtual void control(slava::Character*) = 0;
		// Note to us: Razmazila nas java/python/c#, misli detaljnije, misli koda si iskompleksiran etf-ovac da ne bi bilo memory leakova
		virtual ~IController() {};
	
	};

}

#endif