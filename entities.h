#ifndef ENTITIES_H
#define ENTITIES_H

class solidObject {
public:
    solidObject(){}

    solidObject(float pos[2], float vel[2]) {
        m_pos[0] = pos[0];
        m_pos[1] = pos[1];
        m_vel[0] = vel[0];
        m_vel[1] = vel[1];
    }

    void setPosX(float x) {m_pos[0] = x;}

    void setPosY(float y) {m_pos[1] = y;}

    float getPosX() {return m_pos[0];}

    float getPosY() {return m_pos[1];}

    void setVelX(float x) {m_vel[0] = x;}

    void setVelY(float y) {m_vel[1] = y;}

    float getVelX() {return m_vel[0];}

    float getVelY() {return m_vel[1];}

    virtual void collide(solidObject* obj) = 0;

    void integrate(float dt) {
        m_pos[0] += m_vel[0]*dt;
        m_pos[1] += m_vel[1]*dt;
    }

protected:
    float m_pos[2];
    float m_vel[2];

};

#endif // ENTITIES_H
