#ifndef PS_UTILS_HEADER_H
#define PS_UTILS_HEADER_H

#define FUNC_IMPL

#pragma once
typedef unsigned long long int ulld;
#define MAX_BIT_N 65536
#define N 1024
class CUSTOM_BITSET {
private:
    ulld a[N];
    static int cnt;
public:
    CUSTOM_BITSET();
    CUSTOM_BITSET(const CUSTOM_BITSET& z);
    
    CUSTOM_BITSET& operator =(const CUSTOM_BITSET& z);
    void operator &=(const CUSTOM_BITSET& z);
    void operator |=(const CUSTOM_BITSET& z);
    void operator ^=(const CUSTOM_BITSET& z);
    void operator <<=(const int xx);
    void operator >>=(const int xx);
    
    void setbit(int i, bool v);
    void setvalue(int i, ulld x);
    bool getbit(int i);
    
    static int getcnt();
};

#include <stdio.h>
#include <time.h>
#include <random>

CUSTOM_BITSET::CUSTOM_BITSET() { for ( int i = 0; i < N; i++)a[i] = 0; }
CUSTOM_BITSET::CUSTOM_BITSET(const CUSTOM_BITSET &z) { for ( int i = 0; i < N; i++)a[i] = z.a[i]; }

CUSTOM_BITSET& CUSTOM_BITSET::operator =(const CUSTOM_BITSET& z) {
    for ( int i = 0; i < N; i++)a[i] = z.a[i];
    return *this;
}

void CUSTOM_BITSET::operator &=(const CUSTOM_BITSET& z) {
    for ( int i = 0; i < N; i++) {
        a[i] &= z.a[i];
    }
}
void CUSTOM_BITSET::operator |=(const CUSTOM_BITSET& z) {
    for ( int i = 0; i < N; i++) {
        a[i] |= z.a[i];
    }
}
void CUSTOM_BITSET::operator ^=(const CUSTOM_BITSET& z) {
    for ( int i = 0; i < N; i++) {
        a[i] ^= z.a[i];
    }
}
void CUSTOM_BITSET::operator <<=(const int xx) {
    if (xx <= 0)return;
    if (xx >= MAX_BIT_N) {
        for ( int i = 0; i < N; i++)a[i] = 0;
        return;
    }
    int big_step = xx >> 6;
    int small_step = xx & 63;
    if (small_step == 0) {
        for ( int i = N - 1; i >= big_step; i--) {
            a[i] = a[i - big_step];
        }
        for ( int i = big_step - 1; i >= 0; i--) {
            a[i] = 0;
        }
        return;
    }
    ulld small_mask = (1uLL << small_step) - 1;
    for ( int i = N - 1; i - big_step - 1 >= 0; i--) {
        a[i] = (a[i - big_step] << small_step) | ((a[i - big_step - 1] >> (64 - small_step)) & small_mask);
    }
    {
         int i = big_step;
        a[i] = (a[i - big_step] << small_step);
    }
    for ( int i = big_step - 1; i >= 0; i--) {
        a[i] = 0;
    }
}
void CUSTOM_BITSET::operator >>=(const int xx) {
    if (xx <= 0)return;
    if (xx >= MAX_BIT_N) {
        for ( int i = 0; i < N; i++)a[i] = 0;
        return;
    }
    int big_step = xx >> 6;
    int small_step = xx & 63;
    if (small_step == 0) {
        for ( int i = 0; i < N - big_step; i++) {
            a[i] = a[i + big_step];
        }
        for ( int i = N - big_step; i < N; i++) {
            a[i] = 0;
        }
        return;
    }
    ulld small_mask = (1uLL << small_step) - 1;
    ulld rev_mask = (1uLL << (64 - small_step)) - 1;
    for ( int i = 0; i + big_step + 1 < N; i++) {
        a[i] = ((a[i + big_step] >> small_step) & rev_mask) | ((a[i + big_step + 1] & small_mask) << (64 - small_step));
    }
    {
         int i = N - big_step - 1;
        a[i] = (a[i + big_step] >> small_step) & rev_mask;
    }
    for ( int i = N - big_step; i < N; i++) {
        a[i] = 0;
    }
}

void CUSTOM_BITSET::setbit(int i, bool v) {
    if (v) { a[i >> 6] |= 1uLL << (i & 63); }
    else { a[i >> 6] &= ~(1uLL << (i & 63)); }
}
void CUSTOM_BITSET::setvalue(int i, ulld x) {
    a[i] = x;
}
bool CUSTOM_BITSET::getbit(int i) {
    cnt++;
    return (a[i >> 6] >> (i & 63)) & 1;
}
int CUSTOM_BITSET::getcnt() {
    return cnt;
}
int CUSTOM_BITSET::cnt = 0;

static std::mt19937 rnd;
static void setseed(unsigned long long int seed) {
    rnd = std::mt19937(seed);
}
static int nextint(int s, int t) {
    return (int)(rnd() % (t - s + 1)) + s;
}

const static int T = 100;
static int TC_PARAM[T][2] = {
        {0, 0},	{16, 16}, {0, 3},
        {4, 7},	{8, 11}, {12, 15},
        {0, 1}, {15, 16}, {8, 8},
        {2, 3}, {5, 11}, {1, 15},
        {0, 16}, {-1, -1},
};
static int TC_ORDER[T];

static int VALUE_CNT_CACHE[65536];
static int VALUE_TABLE[17][65536];
static int VL[17];
static void local_init(int t) {
    // init VALUE_TABLE
    for ( int i = 0; i <= 16; i++) {
        VL[i] = 0;
    }
    VALUE_CNT_CACHE[0] = 0;
    VALUE_TABLE[0][VL[0]++] = 0;
    for ( int i = 1; i < (1 << 16); i++) {
        VALUE_CNT_CACHE[i] = VALUE_CNT_CACHE[i & (i - 1)] + 1;
        VALUE_TABLE[VALUE_CNT_CACHE[i]][VL[VALUE_CNT_CACHE[i]]++] = i;
    }
    
    for ( int i = 0; i < t; i++) {
        if (TC_PARAM[i][0] == -1) {
            while (i < t) {
                TC_PARAM[i][0] = TC_PARAM[i - 1][0];
                TC_PARAM[i][1] = TC_PARAM[i - 1][1];
                i++;
            }
        }
    }
    for ( int i = 0; i < t; i++) {
        TC_ORDER[i] = i;
    }
    for ( int i = 0; i < t - 1; i++) {
         int ti = nextint(i, t - 1);
        if (i != ti) {
            int tmp = TC_ORDER[i];
            TC_ORDER[i] = TC_ORDER[ti];
            TC_ORDER[ti] = tmp;
        }
    }
}

static int tv;
static int ans;
static CUSTOM_BITSET aa;
static void build()
{
    ans = 0;
    for ( int i = 0; i < N; i++) {
        ulld x = 0;
        for ( int j = 0; j < 4; j++) {
            int ti = TC_ORDER[tv];
            int cnt = nextint(TC_PARAM[ti][0], TC_PARAM[ti][1]);
            ans += cnt;
            x <<= 16;
            x |= VALUE_TABLE[cnt][nextint(0, VL[cnt] - 1)];
        }
        aa.setvalue(i, x);
    }
}

extern int __builtout_popcount(CUSTOM_BITSET& a);

static int run()
{
    int prev_cnt = CUSTOM_BITSET::getcnt();
    int ret = __builtout_popcount(aa);
    int next_cnt = CUSTOM_BITSET::getcnt();
    if (next_cnt - prev_cnt > 20) return 0;
    return ret == ans ? 1 : 0;
}
int main()
{
    setseed(time(NULL));
    int t;
    scanf("%d", &t);
    local_init(t);
    while (tv < t) {
        build();
        if (run() == 0) {
            break;
        }
        tv++;
    }
    
    printf("%s\n", (tv == t) ? "PASS" : "FAIL");
    
    return 0;
}


#endif
