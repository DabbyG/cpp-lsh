#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

#include "MetricSpace/Euclidean/DataSet.hpp"
#include "Containers/Array.hpp"
#include "MetricSpace/Euclidean/L2/Metric.hpp"
#include "MetricSpace/Euclidean/Euclidean.hpp"
#include "LocalitySensitiveHashing/HashSet.hpp"
#include "Util/Random.hpp"

int main(int argc, char const* argv[])
{
    using namespace MetricSpace::Euclidean;

    auto dataSet = DataSetParser().parse(argv[1]);

    L2::HashFunction hashFunc(10, 10, 100, 2.0f);

    L2::DistanceFunction distFunc;

    lsh::HashSet<DataPoint> hashSet(hashFunc, distFunc, 4, dataSet);

    hashSet.add(dataSet);

    Array<int> found;

    std::clock_t begin = std::clock();

    auto sum = hashSet.forEachPointInRange(1300.0f, dataSet[2], [&] (unsigned int x)
    {
        std::cout << x << std::endl;
        found.emplaceBack(x);
    });

    std::clock_t end = std::clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    std::cout << "time: " << elapsed_secs << " sum: " << sum << std::endl;

    std::clock_t begin2 = std::clock();

    for (unsigned int i = 0; i < dataSet.getPointNum(); ++i)
    {
        auto x = distFunc(dataSet[i], dataSet[2]);
        if (x < 1300.0f)
        {
            std::cout << i << " : " << x << "\t" << ((found.contains(i)) ? "[OK]" : "[FAIL]") << std::endl;
        }
    }

    std::clock_t end2 = std::clock();
    double elapsed_secs2 = double(end2 - begin2) / CLOCKS_PER_SEC;

    std::cout << "time: " << elapsed_secs2 << std::endl;

    //std::cout << 4294967291 << std::endl;

    return 0;
}

/*
int main (int argc, char* argv[])
{
    L2::HashFunction func(2, 4, 5, 2.0f);

    L2::Point p;

    p.reserve(5);

    for (unsigned int i = 0; i < 5; ++i)
    {
        p.pushBack((double)std::rand()/RAND_MAX + 5.0f);
    }

    std::cout << p << std::endl;

    for (auto x : func(p))
    {
        std::cout << x << std::endl;
    }

	return 0;
}
*/
