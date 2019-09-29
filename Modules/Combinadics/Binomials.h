#ifndef BINOMIALS_H
#define BINOMIALS_H

#include <armadillo>
#include <vector>

// Binomials setting
const int binomialsNo = 30;
typedef unsigned int binint;
typedef std::vector< std::vector<binint> > binomialArray;

class Binomials
{
    public:
        // returns binomial L over N
        Binomials()
        {
            FillBinomials(binomialsNo);
        }
        binint binom(int L, int N);

    private:
        binomialArray binomials;
        void FillBinomials(int L);

};

#endif