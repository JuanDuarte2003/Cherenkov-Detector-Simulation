/**
 * @file Point.cpp
 * @author Juan Duarte
 * @version 2023r1
 **/

#include <iostream>
#include <cassert>
#include <cmath>
#include "Point.h"
#include "Line.h"

namespace uiuc
{
    void Line::_copy(Line const &other)
    {
        // Clear self
        delete p1_;
        delete p2_;

        p1_ = other.p1_;
        p2_ = other.p2_;
        length_ = other.length_;
    }

    void Line::_set_length()
    {
        Point diff = *p1_ - *p2_;
        length_ = diff.magnitude();
    }

    Line::Line(Point &p1, Point &p2)
    {
        p1_ = &p1;
        p2_ = &p2;
        _set_length();
    }

    Line::Line(Line const &other)
    {
        p1_ = NULL;
        p2_ = NULL;
        length_ = 0.0;
        _copy(other);
    }

    Line::~Line()
    {
        delete p1_;
        delete p2_;
    }

    Line const &Line::operator=(Line const &other)
    {
        if (this != &other)
        {
            _copy(other);
        }
        return *this;
    }

    Line Line::operator+(Line const &other)
    {
    }
}