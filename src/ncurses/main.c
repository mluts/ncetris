#include "ts_loop.h"
#include "ts_game.h"
#include "ncurses/ui.h"
#include <sys/time.h>

int main()
{
  ts_Game *game = ts_Game_new(12, 22);
  ts_GameLoop *loop = ts_GameLoop_new(
      (struct timeval){ 0, 1000000/200 }
      );
  ts_ui *ui = ts_ui_new(game->board->width, game->board->height);

  int ticks = 0;
  char result[512];

  while(!(game->finished || ui->exitRequested)) {
    ticks = (ticks + 1) % GRAVITY_PER_LEVEL(ui->level);

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

  snprintf(result, 512, "Your score is: %d\n", ui->scorenum);

  ts_Game_destroy(game);
  ts_GameLoop_destroy(loop);
  ts_ui_destroy(ui);

  printf(result);
}
