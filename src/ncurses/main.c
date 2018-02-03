#include "ts_loop.h"
#include "ts_game.h"
#include "ncurses/ui.h"
#include <sys/time.h>

int main()
{
  ts_Game *game = ts_Game_new(12, 22);
  ts_GameLoop *loop = ts_GameLoop_new(
      (struct timeval){ 0, 1000000/300 }
      );
  ts_ui *ui = ts_ui_new(game->board->width, game->board->height);
  ts_Board *board_copy = ts_Board_new(12,22);
  ts_Board_copy(game->board, board_copy);

  int ticks = 0;
  char result[512];


  while(!(game->finished || ui->exitRequested)) {
    ts_GameLoop_startFrame(loop);

    if(ticks == 0 && !ui->pause)
      ts_Game_fall(game);

    if(ts_ui_process_key(ui, game))
      ticks = GRAVITY_PER_LEVEL(ui->level)-1;

    if(ts_Board_changed(game->board, board_copy)) {
      ts_ui_draw(ui, game);
      ts_Board_copy(game->board, board_copy);
    }

    ts_GameLoop_stopFrame(loop);

    ticks = (ticks + 1) % GRAVITY_PER_LEVEL(ui->level);
  }

  snprintf(result, 512, "Your score is: %d\n", ui->scorenum);

  ts_Game_destroy(game);
  ts_GameLoop_destroy(loop);
  ts_ui_destroy(ui);
}
