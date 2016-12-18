#include "ts_loop.h"
#include "ts_game.h"
#include "ncurses/ui.h"
#include <sys/time.h>

#define TICKS_PER_FALL 50

int main()
{
  ts_Game *game = ts_Game_new(20, 28);
  ts_GameLoop *loop = ts_GameLoop_new(
      (struct timeval){ 0, 1000000/100 }
      );
  ts_ui *ui = ts_ui_new(game->board->width, game->board->height);

  int ticks = 0;

  while(!game->finished) {
    ticks = (ticks + 1) % TICKS_PER_FALL;

    ts_GameLoop_startFrame(loop);

    if(ticks == 0)
    {
      ts_Game_fall(game);
    }
    else if(ts_ui_process_key(ui, game))
    {
      ticks = 0;
      ts_Game_fall(game);
    }
    ts_ui_draw(ui, game);
    ts_GameLoop_stopFrame(loop);
  }

  ts_Game_destroy(game);
  ts_GameLoop_destroy(loop);
  ts_ui_destroy(ui);
}
