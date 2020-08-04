#pragma once 

class GoalFire
{
public :
    const int kFireAX = 960;
    const int kFireAY = 90;
    const int kFireBX = 1120;
    const int kFireBY = 210;
    const int kFireCX = 840;
    const int kFireCY = 150;

    void initialize();
    void draw();
    void finalize();

    bool numCheck( int Number );
    void createFire();

    inline int getNumber() { return number_; }
    inline bool getSceneFlag() { return scene_flag_; }

private:
    int number_;
    int texture_;
    int animation_cnt_;
    bool ignition_;
    bool scene_flag_;

    Rect<int> rect_;
    Position<int> position_[ 6 ];
   
};