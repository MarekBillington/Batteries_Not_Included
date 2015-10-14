#ifndef __BUFF_H__
#define __BUFF_H__

#include "entity.h"

class Buff	: public Entity
{
public:
	Buff();
	~Buff();

private:

	int bu_itemNo;
	int bu_duration;
	

};



#endif // !__BUFF_H__
