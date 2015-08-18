#ifndef GRAPH_HH
#define GRAPH_HH

#define SIDE 25
#define WIDTH SIDE
#define HEIGHT SIDE

#define BOX 'b'
#define BOMB 'x'
#define FLAMES 'f'
#define WALL 'w'
#define PLAYER 'p'
#define NONE ' '

typedef enum direction{
    UP = 0,
    LEFT,
    RIGHT,
    DOWN,
    ESC,
    STAY,
    SPACE
} direction;

typedef enum state{
    START,
    RUN,
    STOP,
    DEFAULT
} state;

#endif // GRAPH_HH
