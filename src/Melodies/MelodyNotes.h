#ifndef CASTLEJUMP_MELODYNOTES_H
#define CASTLEJUMP_MELODYNOTES_H

#include "Notes.hpp"
#include "Note.h"

Note melodyCoin[] = {{NOTE_B5, 100},
					 {0,       100},
					 {NOTE_E6, 150},
					 {0,       100}
};
Note melodyWin[] = {{NOTE_A5, 100},
					{0,       100},
					{NOTE_B5, 150},
					{0,       100},
					{NOTE_C5, 100},
					{0,       100},
					{NOTE_A5, 150},
					{0,       100},
					{NOTE_B5, 100},
					{0,       100},
					{NOTE_C5, 150},
					{0,       100},
					{NOTE_A5, 100},
					{0,       100},
					{NOTE_B5, 150},
					{0,       100},
					{NOTE_C5, 100},
					{0,       100},
					{NOTE_C5, 200}

};
Note melodyDead[] = {{NOTE_E2, 500},
					 {0, 100},
					 {NOTE_C2, 500},
					 {0, 100}

};
Note melodyGame[] = {{NOTE_D6, 200},
					 {0, 100},
					 {NOTE_B5, 200},
					 {0, 100},
					 {NOTE_A5, 200},
					 {0, 100},
					 {NOTE_G5, 200},
					 {0, 100},
					 {NOTE_A5, 200},
					 {0, 100},
					 {NOTE_B5, 200},
					 {0, 100},
					 {NOTE_D6, 100}


};
Note melodyHit[] = {{NOTE_E5, 100}

};
Note melodyMenu[] = {{NOTE_B4, 100},
					  {0, 100},
					  {NOTE_B4, 100},
					  {0, 100},
					  {NOTE_B4, 100},
					  {0, 100},
					  {NOTE_A4, 150}


};


#endif //CASTLEJUMP_MELODYNOTES_H
