#ifndef IBASEENTITY_FLAGS
#define IBASEENTITY_FLAGS

#define BF(i) (1UL << i)
#define FL_NODAMAGE				BF(0)	//ignores all damage whatsoever
#define FL_INVINCIBLE			BF(1)	//damage events happen, but never actually dies
#define FL_ROUND_PRESERVE		BF(2)	//if set, round restarts don't respawn this entity
#define FL_ROUND_DESTROY		BF(3)	//if set, round restarts destroy this entity
#define FL_IGNORE_USE			BF(4)	//if set, this entity ignores generic "+Use" functionality
#define FL_INGORE_INPUT			BF(5)	//if set, this entity ignores all player controller input whatsoever
#define FL_IS_COOL				BF(6)	//Sam's idea


#endif //IBASEENTITY_FLAGS
