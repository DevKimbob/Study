#define SEED 17
int MULT = 25173;
int INC = 13849;
int MOD = 65536;

static unsigned int seed = SEED;

unsigned random_i() {
    seed = (MULT * seed + INC) % MOD;
    return seed;
}

double random_f() {
    seed = (MULT * seed + INC) % MOD;
    return seed / (double)MOD;
}