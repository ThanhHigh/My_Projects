#ifndef Timer_hpp
#define Timer_hpp

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Timer
{
    public:
    inline static Timer* GetInstance()
    {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer();
    }

    inline float getDeltaTime() { return m_DeltaTime; }
    
    void timerTicks();

    private:
        Timer(){}
        static Timer* s_Instance;
        float m_DeltaTime; //Present the time occurs between two Events
        float m_LastTime;
};




#endif //Timer_hpp