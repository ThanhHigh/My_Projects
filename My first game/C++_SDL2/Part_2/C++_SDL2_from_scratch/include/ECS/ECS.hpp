//ECS [Head]
#ifndef ECS_hpp
#define ECS_hpp

//C++ lib
#include <iostream>
#include <memory>
#include <algorithm>
#include <bitset>
#include <vector>
#include <string>

class Component;
class Entity;

//ID for each thing in Game
using ComponentID = std::size_t;


inline ComponentID getComponentTypeID() //inline: put the function where it called
{
    static ComponentID lastID = 0; //Remeber what is lastID everytime we call it
    return lastID++; //everytimes we call it we get the last one
}

//Create Template make sure everythings have its ID
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

//If Entity has Component attached
constexpr std::size_t maxCpmponents = 32;

using ComponentBitSet = std::bitset<maxCpmponents>; //Check whether Entity <-> Component has in set or not
using ComponentArray = std::array<Component*, maxCpmponents>; //Array pr component pointers

//Create base class for Component
class Component
{
    public:
        Entity* entity;

        virtual void init() {}

        virtual void update() {}

        virtual void draw() {}


        virtual ~Component() {}
};

class Entity
{
    private:
        bool active = true;

        //list of components that entitis is holding
        std::vector <std::unique_ptr<Component>> components;

        ComponentArray componentArray;

        ComponentBitSet componentBitSet;

    public:
        void update()
        {
            //Entities loop through all components
            for (auto& c : components) c->update();
            
        }

        void draw()
        {
            for (auto& c : components) c->draw();
        }

        bool isActive() { return active; }

        void destroy() { active = false; }

        //Check Entity has Components or not
        template <typename T> bool hasComponent() const
        {
            return componentBitSet[getComponentTypeID<T>()];
        }

        //Add components to entities
        template <typename T, typename... TArgs>
        T& addComponent(TArgs&&...mArgs)
        {
            T* c = new T(std::forward<TArgs>(mArgs)...); 
            c->entity = this;
            std::unique_ptr<Component> uPtr{ c };
            components.emplace_back(std::move(uPtr));

            componentArray[getComponentTypeID<T>()] = c;
            componentBitSet[getComponentTypeID<T>()] = true;

            c->init();
            return *c;
        }

        //Get the Component function   
        template<typename T> T& getComponent() const
        {
            auto ptr(componentArray[getComponentTypeID<T>()]);
            return *static_cast<T*>(ptr);
        }
};

//Manager to keep all list of Entities
class Manager
{
    private:
        std::vector<std::unique_ptr<Entity>> entities;
    public:
        void update()
        {
            for (auto& e : entities) e->update();
        }
        void draw()
        {
            for (auto& e : entities) e->draw();
        }

    //Every frames move through Entities
    void refresh()
    {
        entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity)
        {
            return !mEntity-> isActive();
        }), 
        std::end(entities));
    }

    //Add entites to Game through Manager class
    Entity& addEntity()
    {
        Entity* e = new Entity();
        std::unique_ptr<Entity> uPtr{ e };

        //Update entites to our entity list
        entities.emplace_back(std::move(uPtr));

        return *e;
    }
};




#endif //ECS_hpp