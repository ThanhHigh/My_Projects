#ifndef State_hpp
#define State_hpp

class GameState
{

    public:
        virtual bool init() = 0;
        virtual bool exit() = 0;

        virtual void update() = 0;
        virtual void render() = 0;
    protected:
        SDL_Renderer* m_Ctxt; //Context
};

#endif //State_hpp