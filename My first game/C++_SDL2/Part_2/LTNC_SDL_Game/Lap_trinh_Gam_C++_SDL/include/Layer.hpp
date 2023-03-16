#ifndef Layer_hpp
#define Layer_hpp

class Layer
{
    public:
        virtual void render() = 0; //Use for other class to create Map - Parents class
        virtual void update() = 0; //Gonna be update by it's child class
};


#endif //Layer_hpp