#ifndef Transform_hpp
#define Transform_hpp

#include "Vector2D.hpp"

class Transform  //To direct object's position
{
    public:
        float X, Y;

    public:
        Transform(float x = 0, float y = 0) : X(x), Y(y) {}

        //Debug
        void Log(std::string mif = "")
        {
            std::cout << mif << "(X Y) = " << X << ", " << Y << ";" << std::endl;
        }
    public:
        inline void transLateX(float x) { X += x; }
        inline void transLateY(float y) { Y += y; }
        inline void translate(Vector2D v) { X += v.X; Y += v.Y; }

};  


#endif //Transform_hpp
