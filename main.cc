#include <iostream>
#include <unistd.h>
#include "PRNG.h"
#include "game.h"
using namespace std;
PRNG prng1;

int main(int argc, const char * argv[]) {
    uint32_t seed = getpid();       // start with a pseudo random-number
    prng1.seed(seed);
    Game g;
    if(argc == 1) {
      	g.defaultInit();
	    g.start();
    } else {
        g.Init(argv[1]);
        g.start();
    }
}


