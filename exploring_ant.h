#ifndef EXPLORING_ANT_H
#define EXPLORING_ANT_H

#include <vector>
#include "nest.h"
#include <string>

using namespace std;

class ExploringAnt {
    int x, y, energy;
    vector <ExploringAnt *> formiga_exp;
    static int sequence;
    const int nserie;
    Nest * nest;
public:
    ExploringAnt(int x, int y, Nest * n);

    int getEnergy() const {
        return energy;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    int getNserie() const {
        return nserie;
    }
    void addExploringAnt(int x, int y);
    std::string toString();
};

#endif
