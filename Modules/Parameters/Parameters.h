#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <map>
#include <armadillo>

template <typename T>
class Parameters : public std::map<char, arma::SpMat<T> >
{
    //public:
    //std::map<char, T> parameters;
};

#endif