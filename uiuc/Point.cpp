/**
 * @file Point.cpp
 * @author Juan Duarte
 * @version 2023r1
 **/

#include <iostream>
#include <cassert>
#include <cmath>
#include "Point.h"

namespace uiuc
{
    void Point::_copy(Point const &other)
    {
        // Clear self
        delete[] cartesian_;
        delete[] cylindrical_;
        delete[] spherical_;

        // Copy `other` to self
        type_ = other.type_;
        magnitude_ = other.magnitude_;

        for (unsigned i = 0; i < 3; i++)
        {
            cartesian_[i] = other.cartesian_[i];
            cylindrical_[i] = other.cylindrical_[i];
            spherical_[i] = other.spherical_[i];
        }
    }

    void Point::_set_cartesian()
    {
        switch (type_)
        {
        case 1:
            float *rho = &cylindrical_[0];
            float *phi = &cylindrical_[1];
            float *zz = &cylindrical_[2];

            cartesian_[0] = *rho * cos(*phi); // x
            cartesian_[1] = *rho * sin(*phi); // y
            cartesian_[2] = *zz;              // z

            break;

        case 2:
            float *rr = &spherical_[0];
            float *phi = &spherical_[1];
            float *theta = &spherical_[2];

            cartesian_[0] = *rr * sin(*theta) * cos(*phi); // x
            cartesian_[1] = *rr * sin(*theta) * sin(*phi); // y
            cartesian_[2] = *rr * cos(*theta);             // z

            break;

        default:
            std::cerr << "ERROR: Invalid value type." << std::endl;
            break;
        }
    }

    void Point::_set_cylindrical()
    {
        // We assume that cartesian coordinates already exists
        float *x = &cartesian_[0];
        float *y = &cartesian_[1];
        float *z = &cartesian_[2];

        cylindrical_[0] = sqrt(*x * *x + *y * *y); // rho
        cylindrical_[1] = atan2(*y, *x);           // theta
        cylindrical_[2] = *z;                      // z
    }

    void Point::_set_spherical()
    {
        // We assume that cartesian coordinates already exists
        float *x = &cartesian_[0];
        float *y = &cartesian_[1];
        float *z = &cartesian_[2];

        spherical_[0] = sqrt(*x * *x + *y * *y + *z * *z); // r
        float *rr = &spherical_[0];
        spherical_[1] = acos(*x / *rr); // theta
        spherical_[2] = atan2(*y, *x);  // phi
    }

    Point::Point()
    {
        type_ = 0;
        magnitude_ = 0.0;
        for (unsigned i = 0; i < 3; i++)
        {
            cartesian_[i] = 0.0;
        }

        _set_cylindrical();
        _set_spherical();
    }

    Point::Point(float coords[3], unsigned int type)
    {
        type_ = type;
        switch (type_)
        {
        case 0:
            for (unsigned i = 0; i < 3; i++)
            {
                cartesian_[i] = coords[i];
            }
            _set_spherical();
            _set_cylindrical();
            break;

        case 1:
            for (unsigned i = 0; i < 3; i++)
            {
                cylindrical_[i] = coords[i];
            }
            _set_cartesian();
            _set_spherical();
            break;

        case 2:
            for (unsigned i = 0; i < 3; i++)
            {
                spherical_[i] = coords[i];
            }
            _set_cartesian();
            _set_cylindrical();
            break;

        default:
            std::cerr << "ERROR: Call to uiuc::Point generator made with invalid type coordinates." << std::endl;
            break;
        }

        magnitude_ = abs(spherical_[0]);
    }

    Point::Point(Point const &other)
    {
        for (unsigned i = 0; i < 3; i++)
        {
            cartesian_[i] = 0.0;
        }
        _set_cylindrical();
        _set_spherical();
        _copy(other);
    }

    Point::~Point()
    {
        delete[] cartesian_;
        delete[] cylindrical_;
        delete[] spherical_;
    }

    Point const &Point::operator=(Point const &other)
    {
        if (this != &other)
        {
            _copy(other);
        }
        return *this;
    }

    Point Point::operator+(Point const &other)
    {
        float *coords1;
        float *coords2;
        float newCoords[3];

        coords1 = cartesian();
        coords2 = other.cartesian();

        for (unsigned i = 0; i < 3; i++)
        {
            newCoords[i] = coords1[i] + coords2[i];
        }

        return Point(newCoords, 0);
    }

    Point Point::operator-(Point const &other)
    {
        float *coords1;
        float *coords2;
        float newCoords[3];

        coords1 = cartesian();
        coords2 = other.cartesian();

        for (unsigned i = 0; i < 3; i++)
        {
            newCoords[i] = coords1[i] - coords2[i];
        }

        return Point(newCoords, 0);
    }

    bool Point::operator==(Point const &other) const
    {
        // for equality we set a precision of 0.00001 in each cartesian coordinate
        float precision = 0.00001;
        for (unsigned i = 0; i < 3; i++)
        {
            if (!(other.cartesian_[i] - precision <= cartesian_[i] && cartesian_[i] <= other.cartesian_[i] + precision))
            {
                return false;
            }
        }
        if (!(other.magnitude_ - precision <= magnitude_ && magnitude_ <= other.magnitude_ + precision))
        {
            return false;
        }
        return true;
    }

    bool Point::operator!=(Point const &other) const
    {
        return !(*this == other);
    }

    float *Point::cartesian() const
    {
        float *coords = new float[3];

        for (unsigned i = 0; i < 3; i++)
        {
            coords[i] = cartesian_[i];
        }

        printf(">> Point: (x=%f, y=%f, z=%f)", coords[0], coords[1], coords[2]);

        return coords;
    }

    float *Point::cylindrical() const
    {
        float *coords = new float[3];

        for (unsigned i = 0; i < 3; i++)
        {
            coords[i] = cylindrical_[i];
        }

        printf(">> Point: (r=%f, phi=%f, z=%f)", coords[0], coords[1], coords[2]);

        return coords;
    }

    float *Point::spherical() const
    {
        float *coords = new float[3];

        for (unsigned i = 0; i < 3; i++)
        {
            coords[i] = spherical_[i];
        }

        printf(">> Point: (r=%f, phi=%f, theta=%f)", coords[0], coords[1], coords[2]);

        return coords;
    }

    float Point::magnitude() const
    {
        return magnitude_;
    }

}