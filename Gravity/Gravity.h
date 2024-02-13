#ifndef Gravity_H
#define Gravity_H
class Gravity{
public:
Gravity(int size, char particleEmpty, char particleChar);
Gravity(int size, char particleEmpty, char particleChar, int envDown);
Gravity(int size, char particleEmpty, char particleChar, int envDown, int envLeft);
~Gravity();
void printEnv();
void drop(int dropX, int dropY);
void remove(int partX, int partY);
void iterate(int iterCount);
void updateParticle(int partX, int partY);
void populate(int partCount);
void populate(int seed, int partCount);
void toString();
private:

// Defaults
char PARTICLE_CHAR = '*';
char PARTICLE_EMPTY = ' ';
int ENV_SIZE  = 10;

// Change to affect whichw way particles fall
int ENV_DOWN = 1;    // Add to Y for down direction
int ENV_LEFT = -1;    // Add to X for left direction

char** enviroment;
// char** envCpy;  // Used to stage the next gen
};

#endif