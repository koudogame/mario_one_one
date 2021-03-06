#pragma once
#include "namespace.hpp"

/*NewするClass*/
#include "ui_map.hpp"
#include "ui_coin.hpp"
#include "ui_time.hpp"
#include "ui_score.hpp"

class UIManager
{
public:
    void initialize();
    void update( PlayerData );
    void draw();
    void finalize();

    // 時間を受け取りスコアに変換する
    void timeScore();

    // 引数からコイン枚数描画
    void coinCheck( int );
    
    // 時間内か時間外を伝える
    inline bool timeLimit() { return time_.timeLimit(); }

    // 残り時間を伝える
    inline int getTime() { return time_.getTime(); }

private:
    int texture_;     // テクスチャ
    UIMap map_;       // Mapの管理
    UICoin coin_;     // Coinの管理
    UITime time_;     // Timeの管理
    UIScore score_;   // Scoreの管理
};