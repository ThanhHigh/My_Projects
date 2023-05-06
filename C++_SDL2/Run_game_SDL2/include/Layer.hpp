#ifndef Layer_hpp
#define Layer_hpp

class Layer
{
    public:
        virtual void render() = 0; //Use for other class to create Map - Parents class
        virtual void render(int p_x, int p_y) = 0; //Use to render map start from direct position
        virtual void update() = 0; //Gonna be update by it's child class
        // virtual void clean() = 0;
};


#endif //Layer_hpp