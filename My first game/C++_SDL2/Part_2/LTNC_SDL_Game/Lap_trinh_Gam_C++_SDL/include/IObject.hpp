#ifndef IObject_hpp
#define IObject_hpp

class IObject
{
    public:
        //Basic method
        virtual void drawObject() = 0;
        virtual void updateObject(float deltaTime) = 0;
        virtual void cleanObject() = 0;
    private:
        
};

#endif //IObject_hpp