#ifndef _STAT_H_
#define _STAT_H_

#include <algorithm>
#include <iostream>

#include <limits>

 
struct Stat;

Stat * stat_empty();

void stat_add(Stat & s, float x);
void stat_remove_last(Stat & s);
float stat_mean(const Stat & s);
float stat_max(const Stat & s);
void close_handle(const Stat * s);

#endif
