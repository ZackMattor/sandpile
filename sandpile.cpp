#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

//term colors
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

int width = 200;
int height = 200;

void set_color(int num) {
  switch(num) {
    case 0:
      cout << BLACK;
      break;
    case 1:
      cout << GREEN;
      break;
    case 2:
      cout << YELLOW;
      break;
    case 3:
      cout << WHITE;
      break;
  }
}

void draw_grid(int **grid) {
  system("clear");
  for(int y=0; y<height; y++) {
    for(int x=0; x<width; x++) {
      if(grid[y][x] < 10) {
        set_color(grid[y][x]);
        cout << grid[y][x];
      } else {
        cout << "X";
      }
    }
    cout << endl;
  }
}

int** make_grid() {
  int **grid;

  grid = new int*[height];

  for(int y=0; y<height; y++) {
    grid[y] = new int[width];

    for(int x=0; x<width; x++) {
      grid[y][x] = 0;

      if(x == width/2 && y == height/2) {
        grid[y][x] = 50000;
      }
    }
  }

  return grid;
}

int** process_grid(int **grid) {
  for(int y=0; y<height; y++) {
    for(int x=0; x<width; x++) {
      if(grid[y][x] >= 4) {
        grid[y][x] -= 4;

        if(x != width-1) {
          grid[y][x+1] += 1;
        }

        if(x != 0) {
          grid[y][x-1] += 1;
        }

        if(y != height-1) {
          grid[y+1][x] +=1;
        }

        if(y != 0) {
          grid[y-1][x] +=1;
        }
      }
    }
  }

  return grid;
}

void loop(int **grid) {
  int count = 0;

  while(1) {
    count ++;
    if(count == 1000) {
      draw_grid(grid);
      this_thread::sleep_for(std::chrono::milliseconds(100));
      count = 0;
    }

    grid = process_grid(grid);
  }
}

int main() {
  int **grid = make_grid();

  loop(grid);

  return 0;
}
