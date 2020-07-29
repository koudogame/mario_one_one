#pragma once

/*NewするClass*/
#include "ui_map.hpp"
#include "ui_coin.hpp"
#include "ui_time.hpp"

class UIManager
{
public:
    void initialize();
    void update( bool );
    void draw();
    void finalize();

    void coinCheck( int );
    
    // 時間内か時間外を伝える
    inline bool timeLimit() { return time_.timeLimit(); }

private:
    int texture_;   // テクスチャ
    UIMap map_;     // Mapの管理
    UICoin coin_;   // Coinの管理
    UITime time_;   // Timeの管理
};