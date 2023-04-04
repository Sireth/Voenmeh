#ifndef TERM_2_COMPONENT_H
#define TERM_2_COMPONENT_H

class GameObject;
class Component {
public:
    GameObject *gameObject = nullptr;
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void fixedUpdate() = 0;
};


#endif //TERM_2_COMPONENT_H
