#include "queue.h"
#include "hw04structs.h"
#include "config.h"
extern int ROWS, COLS, E_init, D_mov, D_env;
extern int** MAP;
extern situation_t*** VISITED;
extern int MIN_STEPS;
extern queue_t* SITUATIONS;
extern point_t* FINISH;
#ifdef SHOW_MAP
extern int STEPS;
#endif // SHOW_MAP
