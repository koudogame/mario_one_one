#pragma once

class UIBase
{
public:
    virtual void initialize() {};
    virtual void update() {};
    virtual void draw( int ) {};
    virtual void finalize() {};

protected:
};
