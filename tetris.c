#include <stdio.h>
#include <curses.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

struct timeval startTime;
int shouldExit = 0,
    ticks = 0,
    cols, lines;

const float
  TICK_TIME = 1,
  RATE = 1/30.0,
  MILLION_F = 1000000000.0,
  BILLION_F = 1000000000000.0;

float nextTick;

float getTime()
{
struct timeval time;
float sec, msec;

  gettimeofday(&time, NULL);

  sec = time.tv_sec - startTime.tv_sec;
  msec = (time.tv_usec - startTime.tv_usec) / MILLION_F;
  return sec + msec;
}

struct obj {
  char **str;
  int y, x;
};

const unsigned int GAME_OBJECTS_SIZE = 32;
struct obj gameObjects[32] = { NULL };

char *line[] = { "###", NULL };
char *cube[] = { "##", "##", NULL };
char *z[] = { "## ", " ##", NULL };
char *s[] = { " ##", "## ", NULL };

const struct obj
  lineObj = { .str = line },
  cubeObj = { .str = cube },
  zObj = { .str = z },
  sObj = { .str = s };

const struct obj *availObjects[] = { &lineObj, &cubeObj, &zObj, &sObj, NULL };

void drawObjects(struct obj *objects, int size)
{
  for(int i = 0; i < size; i++)
  {
    struct obj o = objects[i];
    char *str;
    int i;
    if(o.str == NULL) { continue; }

    for(i = 0, str = o.str[i];
        str != NULL;
        i++, str = o.str[i])
    { mvaddstr(o.y + i, o.x, str); }
  }
}

int wlines() { return tigetnum("lines"); }
int wcols() { return tigetnum("cols"); }

void tick()
{
  ticks++;
  erase();
  drawObjects(gameObjects, GAME_OBJECTS_SIZE);
  for(int i = 0, size = 0; gameObjects[i].str != NULL; i++)
  {
    struct obj o = gameObjects[i];
    while(o.str[size] != NULL) size++;
    if(o.y+size < wcols()) o.y++;
  }
  if(ticks % 3 == 0) {
    int i = 0;
    while(gameObjects[i].str != NULL) i++;

    if(i < GAME_OBJECTS_SIZE) {
      gameObjects[i] = *availObjects[i%4];
    }
  }
  refresh();
}

void process()
{
  if(nextTick < getTime()) {
    tick();
    nextTick = getTime() + TICK_TIME;
  }
}

int main()
{
float frameStart, toSleep;
struct timespec requestSleep;

  gettimeofday(&startTime, NULL);

  initscr();
  cbreak();
  noecho();
  nonl();
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);

  while(!shouldExit) {
    frameStart = getTime();
    process();
    toSleep = RATE - getTime() - frameStart;
    if(toSleep > 0) {
      requestSleep.tv_sec = ceilf(toSleep);
      requestSleep.tv_nsec = (toSleep - requestSleep.tv_sec) * BILLION_F;
      nanosleep(&requestSleep, NULL);
    }
  }

  endwin();

  return 0;
}
