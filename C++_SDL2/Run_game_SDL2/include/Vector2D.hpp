#ifndef Vector2D_hpp
#define Vector2D_hpp

#include <string>
#include <iostream>

class Vector2D
{
    public:
        float X, Y;
    public:
        //Set up default vector to (0,0)
        Vector2D(float x = 0, float y = 0) : X(x), Y(y) {}

    public:
        //Overide operator to convinient for caculation
        //add function
        inline Vector2D operator+(const Vector2D &v2) const 
        {
            return Vector2D(X + v2.X, Y + v2.Y);
        }

        //sub function
        inline Vector2D operator-(const Vector2D &v2) const
        {
            return Vector2D(X - v2.X, Y - v2.Y);
        }

        //multiplication
        inline Vector2D operator*(const float scalar) const
        {
            return Vector2D(X*scalar, Y*scalar);
        }

        //Log function for debug
        void Log(std::string mif = "")
        {
            std::cout << mif << "(X Y) = " << X << ", " << Y << ";" << std::endl;
        }


    private:
    
};


#endif //Vector2D_hpp