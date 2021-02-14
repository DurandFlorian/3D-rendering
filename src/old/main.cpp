#include "Vector2D.hpp"
#include "ControllablePoints.hpp"

int main()
{
    
    Point2D A{1,1};
    Point2D B{3,3};
    Vector2D C = Vector2D::vector_from_points(A,B);
    Vector2D D = Vector2D{0,0};
    int e = Vector2D::cross_product(C,D);
    e = e+e;
    Vector2D E = C + D;
    auto points = ControllablePoints();
    points.add(A);
    points.add(B);
    points.click(Point2D{1.5,1.5});
    points.move(Point2D{5,5});
    points.move(Point2D{2,2});
    return 0;
    
   return 0;
}
