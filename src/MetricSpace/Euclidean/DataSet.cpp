#include "DataSet.hpp"

using namespace MetricSpace::Euclidean;

DataSet::DataSet(Matrix<double>&& m) : mVectors(std::move(m)) {}

DataSet::DataSet(DataSet&& other) : mVectors(std::move(other.mVectors)) {}

DataSet::DataSet(const DataSet& other) : mVectors(other.mVectors) {}

DataSet& DataSet::operator= (DataSet other)
{
    std::swap(mVectors, other.mVectors);

    return *this;
}

DataSet::ConstPointRef DataSet::operator[] (unsigned int i) const
{
    return mVectors.row(i);
}

unsigned int DataSet::getPointNum() const
{
    return mVectors.getColSize();
}

unsigned int DataSet::getVectorDim() const
{
    return mVectors.getRowSize();
}
