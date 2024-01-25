#ifndef _DN2000F_H
#define _DN2000F_H

#include <stdbool.h>

#include "global.h"

enum dn2000f_play_mode
{
	Single,
	Continuous
};


struct dn2000f_deck_state
{
	byte Number;
	bool DrawerOpen;
	bool Loaded;
	byte Track;
	byte TimeMode;
	enum dn2000f_play_mode PlayMode;
	bool PitchOn;
	byte Pitch;
};

#endif /* _DN2000F_H */