// gcc -Wall new_snake.c -o snake -lncurses -DNCURSES_STATIC -static

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h> // for toupper()

#define MIN_Y 2

enum
{
    LEFT = 1,
    UP,
    RIGHT,
    DOWN,
    STOP_GAME = KEY_F(10)
};

enum
{
    MAX_TAIL_SIZE = 100,
    START_TAIL_SIZE = 6,
    MAX_FOOD_SIZE = 20,
    FOOD_EXPIRE_SECONDS = 5
};

// Здесь храним коды управления змейкой
struct control_buttons
{
    int down;
    int up;
    int left;
    int right;
} control_buttons;

// Здесь храним еду:
typedef struct food
{
    int x;
    int y;
    time_t put_time;
    char point;
    uint8_t enable;
} food_t;

struct control_buttons default_controls = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT};

/*
 Голова змейки содержит в себе
 x,y - координаты текущей позиции
 direction - направление движения
 tsize - размер хвоста
 *tail -  ссылка на хвост
 */
typedef struct snake_t
{
    int x;
    int y;
    int direction;
    size_t tsize;
    struct tail_t *tail;
    struct control_buttons controls;
} snake_t;

/*
 Хвост это массив состоящий из координат x,y
 */
typedef struct tail_t
{
    int x;
    int y;
} tail_t;

// Инициализация хвоста
void initTail(struct tail_t t[], size_t size)
{
    struct tail_t init_t = {0, 0};
    for (size_t i = 0; i < size; i++)
    {
        t[i] = init_t;
    }
}

// Инициализация головы
void initHead(struct snake_t *head, int x, int y)
{
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
}

// Инициализация змейки
void initSnake(snake_t *head, size_t size, int x, int y)
{
    tail_t *tail = (tail_t *)malloc(MAX_TAIL_SIZE * sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail = tail; // прикрепляем к голове хвост
    head->tsize = size + 1;
    head->controls = default_controls;
}

// Инициализация еды
void initFood(food_t f[], size_t size)
{
    struct food init = {0, 0, 0, 0, 0};
    // int max_y = 0, max_x = 0;
    // getmaxyx(stdscr, max_y, max_x);
    for (size_t i = 0; i < size; i++)
    {
        f[i] = init;
    }
}

//  Движение головы с учетом текущего направления движения
void go(struct snake_t *head)
{
    char ch = '@';
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);  // macro - размер терминала
    mvprintw(head->y, head->x, " "); // очищаем один символ
    switch (head->direction)
    {
    case LEFT:
        if (head->x <= 0) // Циклическое движение, чтобы не
                          // уходить за пределы экрана
            head->x = max_x;
        mvprintw(head->y, --(head->x), "%c", ch);
        break;
    case RIGHT:
        if (head->x >= max_x)
            head->x = 0;
        mvprintw(head->y, ++(head->x), "%c", ch);
        break;
    case UP:
        if (head->y <= 0)
            head->y = max_y;
        mvprintw(--(head->y), head->x, "%c", ch);
        break;
    case DOWN:
        if (head->y >= max_y)
            head->y = 0;
        mvprintw(++(head->y), head->x, "%c", ch);
        break;
    default:
        break;
    }
    refresh();
}

// функция проверки корректности выбранного направления движения
int checkDirections(snake_t *snake, int32_t key)
{
    if (key == snake->controls.down || key == 's' || key == 'S')
    {
        if (snake->direction != UP)
            return 0;
    }

    else if (key == snake->controls.up || key == 'w' || key == 'W')
    {
        if (snake->direction != DOWN)
            return 0;
    }

    else if (key == snake->controls.right || key == 'd' || key == 'D')
    {
        if (snake->direction != LEFT)
            return 0;
    }

    else if (key == snake->controls.left || key == 'a' || key == 'A')
    {
        if (snake->direction != RIGHT)
            return 0;
    }
    return 1;
}

// доделать проверку на исключение наезда на свой хвост здесь!
void changeDirection(struct snake_t *snake, const int32_t key)
{
    if (!checkDirections(snake, key))
    {

        if (key == snake->controls.down || key == 's' || key == 'S')
        {
            snake->direction = DOWN;
        }

        else if (key == snake->controls.up || key == 'w' || key == 'W')
        {
            snake->direction = UP;
        }

        else if (key == snake->controls.right || key == 'd' || key == 'D')
        {
            snake->direction = RIGHT;
        }

        else if (key == snake->controls.left || key == 'a' || key == 'A')
        {
            snake->direction = LEFT;
        }
    }
}

/*
 Движение хвоста с учетом движения головы
 */
void goTail(struct snake_t *head)
{
    char ch = '*';
    mvprintw(head->tail[head->tsize - 1].y, head->tail[head->tsize - 1].x, " ");
    for (size_t i = head->tsize - 1; i > 0; i--)
    {
        head->tail[i] = head->tail[i - 1];
        if (head->tail[i].y || head->tail[i].x)
            mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);
    }
    head->tail[0].x = head->x;
    head->tail[0].y = head->y;
}

// функция поиска столкновений головы с хвостом
uint8_t is_intersection(struct snake_t *head)
{
    // Пропускаем первые 3 сегмента хвоста (ближайшие к голове),
    // чтобы избежать ложного срабатывания после поворота
    const size_t SAFE_OFFSET = 3;

    if (head->tsize <= SAFE_OFFSET)
    {
        return 0; // хвост слишком короткий для столкновения с собой
    }

    for (size_t i = SAFE_OFFSET; i < head->tsize; i++)
    {
        if (head->tail[i].x == head->x && head->tail[i].y == head->y)
        {
            return 1; // Столкновение обнаружено
        }
    }
    return 0; // Столкновений нет
}

/* Обновить/разместить текущее зерно на поле */
void putFoodSeed(food_t *fp)
{
    int max_x = 0, max_y = 0;
    char spoint[2] = {0};
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(fp->y, fp->x, " ");
    fp->x = rand() % (max_x - 1);
    fp->y = rand() % (max_y - 2) + 1; // Не занимаем верхнюю строку
    fp->put_time = time(NULL);
    fp->point = '$';
    fp->enable = 1;
    spoint[0] = fp->point;
    mvprintw(fp->y, fp->x, "%s", spoint);
}

/* Разместить еду на поле */
void putFood(food_t f[], size_t number_seeds)
{
    for (size_t i = 0; i < number_seeds; i++)
    {
        putFoodSeed(f + i);
    }
}

/*
 Обновление еды. Если через какое-то время(FOOD_EXPIRE_SECONDS) точка
устаревает, или же она была съедена(food[i].enable==0, то происходит её
повторная отрисовка и обновление времени — refreshFood(food,
SEED_NUMBER)
*/
void refreshFood(food_t f[], int nfood)
{
    // int max_x = 0, max_y = 0;
    // char spoint[2] = {0};
    // getmaxyx(stdscr, max_y, max_x);
    for (size_t i = 0; i < nfood; i++)
    {
        if (f[i].put_time)
        {
            if (!f[i].enable || (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS)
            {
                putFoodSeed(f + i);
            }
        }
    }
}

/*
 Съесть зерно
Такое событие возникает, когда координаты головы совпадают с координатой
зерна. В этом случае зерно помечается как enable=0.
Проверка того, является ли какое-то из зерен съеденным, происходит при
помощи функции логической функции haveEat в этом случае происходит
увеличение хвоста на 1 элемент.
 */
_Bool haveEat(snake_t *head, food_t f[])
{
    for (size_t i = 0; i < MAX_FOOD_SIZE; i++)
        if (f[i].enable && head->x == f[i].x && head->y == f[i].y)
        {
            f[i].enable = 0;
            return 1;
        }
    return 0;
}

// Таймер времени
void timer_s(double seconds)
{
    clock_t begin = clock();
    while (((double)(clock() - begin) / CLOCKS_PER_SEC) < seconds)
    {
    }
}

int main()
{
    food_t food[MAX_FOOD_SIZE];
    snake_t *snake = (snake_t *)malloc(sizeof(snake_t));
    int SEED_NUMBER = 10;
    initSnake(snake, START_TAIL_SIZE, 10, 10);
    initFood(food, MAX_FOOD_SIZE);
    initscr();
    putFood(food, SEED_NUMBER);
    keypad(stdscr, TRUE); // включаем кнопки калвиатуры
    raw();                // Откдючаем line buffering
    noecho();             // Отключаем echo() режим при вызове getch
    curs_set(FALSE);      // Отключаем курсор
    mvprintw(1, 0, "Use arrows for control. Press 'F10' for EXIT");
    timeout(0); // Отключаем таймаут после нажатия клавиши в цикле
    int key_pressed = 0;

    while (key_pressed != STOP_GAME)
    {
        key_pressed = getch(); // Считываем клавишу
        go(snake);
        goTail(snake);
        // timeout(80); // Задержка при отрисовке ***** пределать через time.h
        changeDirection(snake, key_pressed);
        refreshFood(food, SEED_NUMBER);
        timer_s(0.2);
        if (is_intersection(snake))
        {
            break;
        }
        refresh();
    }
    free(snake->tail);
    free(snake);
    endwin(); // Завершаем режим curses mod
    return 0;
}
