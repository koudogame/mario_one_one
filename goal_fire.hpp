#pragma once 

class GoalFire
{
public :
    void initialize();
    void draw();
    void finalize();

    int numCheck( int Number );

private:
    int number_;
    int texture_;
    Position<int> position_[ 6 ];
};