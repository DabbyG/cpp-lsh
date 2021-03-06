#ifndef __METRICSPACE_HAMMING_DATASET_HPP__
#define __METRICSPACE_HAMMING_DATASET_HPP__

#include <iostream>
#include <cstdlib>
#include <string>

#include "Containers/Array.hpp"
#include "../Generic/DataSet.hpp"
#include "DataPoint.hpp"

namespace MetricSpace {
namespace Hamming
{
    class DataSet : public Generic::DataSet<DataPoint>
    {
     private:
        Array<Point> mVectors;
        unsigned mDim;

     public:
         DataSet(Array<Point>&& m, unsigned dim);

         DataSet(DataSet&& other);
         DataSet(const DataSet& other);

         DataSet& operator= (DataSet other);

         ConstPointRef operator[] (unsigned int i) const override;

         unsigned int getPointNum () const override;
         unsigned int getVectorDim() const;
    };
}}

#endif /* end of include guard: __METRICSPACE_HAMMING_DATASET_HPP__ */
