#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Domain.h"
#include "IDomain.h"

FractalEncoding::Domain::Domain(unsigned int aLength)
    : _dataForwardDirection(new double[aLength]),
      _dataBackDirection(new double[aLength]),
      _length(aLength)

{
}

FractalEncoding::Domain::~Domain()
{
    delete []_dataForwardDirection;

    delete []_dataBackDirection;
}

const double* FractalEncoding::Domain::getForwardDirectionData() {
    return this->_dataForwardDirection;
}

const double* FractalEncoding::Domain::getBackDirectionData() {
    return this->_dataBackDirection;
}

void FractalEncoding::Domain::populate(double* aData, unsigned int aDoubleLength) {

    double lTempValue;

    this->_sum = 0.0;

    this->_beta = 0.0;

    unsigned int lrangeLength = aDoubleLength >> 1;

    unsigned int loffsetDackDirection = lrangeLength - 1;

    unsigned int lPos = 0;

    for(unsigned int index = 0;
        index < aDoubleLength;
        index += 2)
    {
        lPos = index >> 1;

        lTempValue = (aData[index] + aData[index + 1]) * 0.5;

        this->_dataForwardDirection[lPos] = lTempValue;

        this->_dataBackDirection[loffsetDackDirection - lPos] = lTempValue;

        this->_sum += lTempValue;

        this->_beta += lTempValue * lTempValue;
    }

    this->_aver = this->_sum/lrangeLength;

    this->_beta *= lrangeLength;

    this->_beta -= this->_sum * this->_sum;
}

double FractalEncoding::Domain::getAver() {
	return this->_aver;
}

double FractalEncoding::Domain::getSum() {
	return this->_sum;
}

double FractalEncoding::Domain::getBeta() {
	return this->_beta;
}


























