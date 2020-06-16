#include "field.hpp"
#include "release.hpp"

static constexpr int kSize = 64;
constexpr int kStartX = 256;
constexpr int kStartY = 576;
constexpr int kEndLine = 576;

// マリオの状態保存
enum Status
{
    kMario = 0,
    kSuperMario,
    kFireMario
};

class Player
{
public:
    Player();
    ~Player();
    bool initialize();
    void update();
    void draw();
    void finalize();

private:
    int texture_;           // テクスチャハンドル

    int pos_x_;             // 座標x
    int pos_y_;             // 座標y 

    int left_;                 // SrcX
    int top_;                 // SrcY

    int right_;               // Width
    int bottom_;           // Height

    int status_;            // マリオの状態

    int animation_;       // 動いているときの切り取り範囲
    bool direction_;       // true : 右向き, false : 左向き

    const int id_ = 0;    // ControllerId
};