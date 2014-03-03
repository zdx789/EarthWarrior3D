//
//  Player.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#include "Player.h"

bool Player::init()
{
    _Model = Sprite3D::create("DownNecker2.obj", "Done1.png");
    //_Model = Sprite3D::create("Scania4.obj", "car00.png");
    if(_Model)
    {
        _Model->setScale(5.3);
        addChild(_Model);
        _Model->setRotation3D(Vertex3F(90,0,90));
        _radius = 40;
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        scheduleUpdate();
        
        
        return true;
    }
    return false;
}
void Player::update(float dt)
{
    float smoothedAngle =fmin(fmax(targetAngle*(1-dt*returnSpeed*(rollReturnThreshold-fabsf(targetAngle)/maxRoll)),-maxRoll),maxRoll);
    setRotation3D(Vertex3F(fabsf(smoothedAngle)*0.15,smoothedAngle, 0));
    targetAngle = getRotation3D().y;
    
}
bool Player::onTouchBegan(Touch *touch, Event *event)
{
    
    return true;
}
void Player::onTouchMoved(Touch *touch, Event *event)
{
    Point prev = event->getCurrentTarget()->getPosition();
    Point delta =touch->getDelta();
    log("x=%f;y=%f;lastX=%f",this->getPosition3D().x,this->getPosition3D().y,lastPosition.x);
    if(this->getPosition3D().x<-210.0)
    {
        Vertex3F limitPosition = Vertex3F(-210,lastPosition.y,lastPosition.z);
        this->setPosition3D(limitPosition);
    }
    else if(this->getPosition3D().y<-362)
    {
        Vertex3F limitPosition = Vertex3F(lastPosition.x,-362,lastPosition.z);
        this->setPosition3D(limitPosition);
    }
    else if (this->getPosition3D().x>198)
    {
        Vertex3F limitPosition = Vertex3F(198,lastPosition.y,lastPosition.z);
        this->setPosition3D(limitPosition);
    }
    else if (this->getPosition3D().y>729)
    {
        Vertex3F limitPosition = Vertex3F(lastPosition.x,729,lastPosition.z);
        this->setPosition3D(limitPosition);
    }
    else
    {
        setPosition(delta+prev);
    }
    lastPosition = this->getPosition3D();
    setTargetAngle(targetAngle+delta.x*rollSpeed*(rollReturnThreshold-fabsf(targetAngle)/maxRoll));
    
}
void Player::onTouchEnded(Touch *touch, Event *event)
{
    
}