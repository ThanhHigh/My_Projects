#ifndef Points_hpp
#define Points_hpp

#include <string>
#include <iostream>

class Points
{

    public:
        //Constructor
        Points(float X = 0, float Y = 0) : x(X), y(Y){}

        //addition +
        inline Points operator+(const Points& p2) const
        {
            return Points(x + p2.x, y + p2.y);
        }
        //addition +=
        inline friend Points operator+=(Points& p1, Points& p2)
        {
            p1.x += p2.x;
            p1.y += p2.y;
            return p1;
        }
        //subtruction -
        inline Points operator-(const Points& p2) const 
        {
            return Points(x - p2.x, y - p2.y);
        }

        //subtruction -=
        inline friend Points operator-=(Points& p1, Points& p2)
        {
            p1.x -= p2.x;
            p1.y -= p2.y;
            return p1;
        }
        //multication
        inline Points operator*(const float scalar) const
        {
            return Points(x*scalar, y*scalar);
        }

        //Log to screen
        void Log(std::string msg = "")
        {
            std::cout << msg << "(X Y) " << "( " << x << " " << y << ")" << std::endl;
        }
    public:
        float x, y;
        
};


#endif //Points_hpp