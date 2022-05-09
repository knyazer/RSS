#include <include/core/EPA.hpp>

namespace rss
{
    EPA::Edge EPA::findClosestEdgeFast(Simplex simplex, int prevBestIndex)
    {
        size_t size = simplex.vertices.size();
        if (size < 5)
            return findClosestEdgeSlow(simplex, prevBestIndex);
        
        Edge closest;
        closest.distance = INFINITY;

        for (int index = prevBestIndex - 2; index < prevBestIndex + 3; index++) 
        {
            int i = index;
            while (i < 0)
                i += size;
            while (i >= size)
                i -= size;

            // compute the next points index
            int j = (i + 1 == size) ? 0 : (i + 1);
            // get the current point and the next one
            Vec2 a = simplex[i];
            Vec2 b = simplex[j];
            // create the edge vector
            Vec2 e = b - a; // or a.to(b);
            // get the vector from the origin to a
            Vec2 oa = a; // or a - ORIGIN
            // get the vector from the edge towards the origin
            // Vec2 n = Vec2::tripleProduct(e, oa, e);
            Vec2 n = Vec2(-e.y, e.x);
            // normalize the vector
            n = n.norm();
            // calculate the distance from the origin to the edge
            double d = n.dot(a); // could use b or a here
            // check the distance against the other distances
            if (d < closest.distance) 
            {
                // if this edge is closer then use it
                closest.distance = d;
                closest.normal = n;
                closest.index = j;
            }
        }

        // return the closest edge we found
        return closest;
    }

    EPA::Edge EPA::findClosestEdgeSlow(Simplex simplex, int prevBestIndex)
    {
        Edge closest;
        closest.distance = INFINITY;
        size_t size = simplex.vertices.size();
        
        for (int i = 0; i < size; i++) 
        {
            // compute the next points index
            int j = (i + 1 == size) ? 0 : (i + 1);
            // get the current point and the next one
            Vec2 a = simplex[i];
            Vec2 b = simplex[j];
            // create the edge vector
            Vec2 e = b - a; // or a.to(b);
            // get the vector from the origin to a
            Vec2 oa = a; // or a - ORIGIN
            // get the vector from the edge towards the origin
            Vec2 n = Vec2::tripleProduct(e, oa, e);
            // normalize the vector
            n = n.norm();
            // calculate the distance from the origin to the edge
            double d = n.dot(a); // could use b or a here
            // check the distance against the other distances
            if (d < closest.distance) 
            {
                // if this edge is closer then use it
                closest.distance = d;
                closest.normal = n;
                closest.index = j;
            }
        }

        // return the closest edge we found
        return closest;
    }
}