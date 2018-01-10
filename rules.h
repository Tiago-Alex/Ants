#ifndef RULES_H
#define RULES_H

#include "ant.h"

void aprroach_ray(Ant *a, int x, int y, bool run_away);
void ChasesRule(Ant *a);
void EatCrumbRule(Ant *a);
void GoToNestRule(Ant *a);
void move_ant(Ant *a, int x, int y);
void ProtectRule(Ant *a);
void RideRule(Ant *a);
void RobsRule(Ant *a);
void RunRule(Ant *a);
void SearchCrumbRule(Ant *a);

#endif
