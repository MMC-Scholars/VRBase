// This software is under partial ownership by The Ohio State University, for it
// is a product of student employees. For official policy, see
// https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf or contact The
// Ohio State University's Office of Legal Affairs.

#pragma once

#define BF(i)             (1UL << i)
#define FL_NODAMAGE       BF(0) // ignores all damage whatsoever
#define FL_INVINCIBLE     BF(1) // damage events happen, but never actually dies
#define FL_ROUND_PRESERVE BF(2) // round restarts don't respawn this entity
#define FL_ROUND_DESTROY  BF(3) // round restarts destroy this entity
#define FL_IGNORE_USE     BF(4) // entity ignores generic "+Use" functionality
#define FL_INGORE_INPUT                                                             \
    BF(5) // entity ignores all player controller input whatsoever
#define FL_EXTRA   BF(6)
#define FL_EXTRA_2 BF(7)
