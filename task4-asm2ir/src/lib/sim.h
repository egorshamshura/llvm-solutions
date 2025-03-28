#define SIM_X_SIZE 512
#define SIM_Y_SIZE 256

#ifndef __sim__
void simFlush();
void simPutPixel(int x, int y, int argb);
int simRand();
long long simRand64();
void dump(long long);
#endif

extern void simInit();
extern void app();
extern void simExit();
