/**
 * @file Point.h
 * @author Juan Duarte
 * @version 2023r1
 **/

#pragma once
#include <iostream>
#include <sstream>

namespace uiuc
{
    class Point
    {
    public:
        // Creates a point in the origin 0,0,0
        Point();

        // Creates a point in a given type of coordinates
        // 0 -> x,y,z       (cartesian coordinates)
        // 1 -> r,phi,z     (cylindrical coordinates)
        // 2 -> r,phi,theta (spherical coordinates)
        Point(float coords[3], unsigned int type);

        // Copies a point
        Point(Point const &other);

        // Destroys a point
        ~Point();

        // Assignment
        Point const &operator=(Point const &other);

        // Sum
        Point operator+(Point const &other);

        // Minus
        Point operator-(Point const &other);

        // Equality
        bool operator==(Point const &other) const;

        // Inequality
        bool operator!=(Point const &other) const;

        // Gets the cartesian coordinates
        float *cartesian() const;

        // Gets the cylindrical coordinates
        float *cylindrical() const;

        // Gets the spherical coordinates
        float *spherical() const;

        // Gets magnitude
        float magnitude() const;

    private:
        float cartesian_[3];   /*Cartesian coordinates*/
        float cylindrical_[3]; /*cylindrical coordinates*/
        float spherical_[3];   /*Spherical coordinates*/
        unsigned int type_;    /*Type of input coordinates (0,1,2)*/
        float magnitude_;      /*Distance from origin*/

        void _copy(Point const &other);

        void _set_cartesian();
        void _set_cylindrical();
        void _set_spherical();
    };

    // Here we can set how to print points
}