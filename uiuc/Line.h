/**
 * @file Line.h
 * @author Juan Duarte
 * @version 2023r1
 **/

#pragma once
#include <iostream>
#include <sstream>
#include "Point.h"

namespace uiuc
{
    class Line
    {
    public:
        // Creates a line between two different points
        Line(Point &p1, Point &p2);

        // Copies a line
        Line(Line const &other);

        // Destroys a line with the points
        ~Line();

        // Assignment
        Line const &operator=(Line const &other);

        // Sum
        Line operator+(Line const &other);

        // Minus
        Line operator-(Line const &other);

        // Equality
        bool operator==(Line const &other) const;

        // Inequality
        bool operator!=(Line const &other) const;

        // Gets points in a given coordinate system
        Point *points() const;

        // Get length
        float length() const;

    private:
        Point *p1_;
        Point *p2_;
        float length_;

        void _copy(Line const &other);

        void _set_length();
    };

    // Here we can set how to print lines
}