#include <iostream>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <sstream>
#include <vector>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;

typedef CGAL::Exact_predicates_exact_constructions_kernel exactKernel;
typedef exactKernel::Point_2 ExactPoint_2;
typedef std::vector<ExactPoint_2> Points;
int main()
{
    {
        Point_2 p(0, 0.3), q(1, 0.6), r(2, 0.9);
        std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
    }

    {
        Point_2 p(0, 1.0/3.0), q(1, 2.0/3.0), r(2,1);
        std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
    }

    {
        Point_2 p(0,0), q(1,1), r(2,2);
        std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
    }

    std::cout << "\n\n with Exact Construction Kernel \n\n";
    ExactPoint_2 p(0, 0.3), q, r(2,0.9);
    {
        q = ExactPoint_2(1, 0.6);
        std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
    }

    {
        std::istringstream input("0 0.3    1 0.6    2 0.9");
        input >> p >> q >> r;
        std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
    }

    {
        q = CGAL::midpoint(p,r);
        std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
    }

    std::cout <<"\n\n Convex Hull \n\n";

    ExactPoint_2 points[5] = {ExactPoint_2(0,0), ExactPoint_2(10,0), ExactPoint_2(10,10), ExactPoint_2(6,5), ExactPoint_2(4,1)};
    ExactPoint_2 result[5];
    ExactPoint_2 *ptr = CGAL::convex_hull_2(points , points+5, result);
    std::cout << ptr - result << " points on the convex hull : " << std::endl;
    for(int i=0; i< ptr - result; i++)
    {
        std::cout << result[i] << std::endl;
    }

    std::cout <<"\n\n Vector \n\n";
    Points vpoints, vresult;
    vpoints.push_back(ExactPoint_2(0,0));
    vpoints.push_back(ExactPoint_2(10,0));
    vpoints.push_back(ExactPoint_2(10,10));
    vpoints.push_back(ExactPoint_2(6,5));
    vpoints.push_back(ExactPoint_2(4,1));

    CGAL::convex_hull_2(vpoints.begin(), vpoints.end(), std::back_inserter(vresult));
    std::cout << vresult.size() << " points on the convex hull" << std::endl;

    return 0;
}
