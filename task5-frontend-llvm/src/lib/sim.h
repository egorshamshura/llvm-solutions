#define SIM_X_SIZE 512
#define SIM_Y_SIZE 256

#ifndef __sim__
void simFlush();
void simPutPixel(int x, int y, int argb);
void putPixel(long long x, long long y, long long argb);
int simRand();
void dump(long long);
#endif

extern void simInit();
extern void app();
extern void simExit();
