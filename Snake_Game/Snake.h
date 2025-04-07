#pragma once

void gotoxy(short x, short y);
void print_map();
const char SNAKE_SIGN = 'O';
const char FOOD_SIGN = '*';
bool GAME_CONTINUES = true;
const short MAP_LENGTH = 20;
const short MAP_WIDTH = 9;
char map[MAP_WIDTH][MAP_LENGTH] = {"-------------------",
                                   "|                 |",
                                   "|                 |",
                                   "|                 |",
                                   "|                 |",
                                   "|                 |",
                                   "|                 |",
                                   "|                 |",
                                   "-------------------"};
namespace direction_of_movement {
const short UP = 1;
const short DOWN = 2;
const short LEFT = 3;
const short RIGHT = 4;
};

class Snake {
  std::vector<std::pair<unsigned short, unsigned short>> snake_tail;
  unsigned short direction = direction_of_movement::UP;
  std::pair<unsigned short, unsigned short> food;

 public:

  explicit Snake(unsigned short x_pos = MAP_WIDTH / 2, unsigned short y_pos = (MAP_LENGTH - 1) / 2) : food{
      1 + rand() % (MAP_WIDTH - 2), 1 + rand() % (MAP_LENGTH - 3)} {
    snake_tail.emplace_back(x_pos, y_pos);
  }

  [[noreturn]] void console() {
    clock_t tStart = clock();
    while (GAME_CONTINUES) {
      change_move();
      the_food_is_eaten();
      if ((double) (clock() - tStart) / CLOCKS_PER_SEC >= 0.7
          && (direction == direction_of_movement::UP || direction == direction_of_movement::DOWN) ||
          (double) (clock() - tStart) / CLOCKS_PER_SEC >= 0.3
              && (direction == direction_of_movement::LEFT || direction == direction_of_movement::RIGHT)) {
        tStart = clock();
        move();
        if (is_game_over()) {
          gotoxy(0, 0);
          std::cout << "-------Snake-------\n";
          std::cout << "Score: " << snake_tail.size() - 1;
          map[food.first][food.second] = FOOD_SIGN;
          std::cout << '\n';
          for (size_t i = 0; i < snake_tail.size(); i++) {
            map[snake_tail[i].first][snake_tail[i].second] = SNAKE_SIGN;
          }
          print_map();
          for (size_t i = 0; i < snake_tail.size(); i++) {
            map[snake_tail[i].first][snake_tail[i].second] = ' ';
          }

        } else {
          GAME_CONTINUES = false;
          gotoxy(0, 11);
          std::cout << "YOU LOSE\n";
        }
      }
    }
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max());
//    getchar();
//    system("pause");
  }

  void move() {
    for (int i = snake_tail.size() - 1; i > 0; i--) {
      snake_tail[i] = snake_tail[i - 1];
    }
    switch (direction) {
      case direction_of_movement::UP:snake_tail[0].first--;
        break;
      case direction_of_movement::DOWN:snake_tail[0].first++;
        break;
      case direction_of_movement::RIGHT:snake_tail[0].second++;
        break;
      case direction_of_movement::LEFT:snake_tail[0].second--;
        break;
    }
  }

  void change_move() {
    if (GetKeyState('W') & 0x8000 && direction != direction_of_movement::DOWN) {
      direction = direction_of_movement::UP;
    }
    if (GetKeyState('S') & 0x8000 && direction != direction_of_movement::UP) {
      direction = direction_of_movement::DOWN;
    }
    if (GetKeyState('A') & 0x8000 && direction != direction_of_movement::RIGHT) {
      direction = direction_of_movement::LEFT;
    }
    if (GetKeyState('D') & 0x8000 && direction != direction_of_movement::LEFT) {
      direction = direction_of_movement::RIGHT;
    }
  }

  bool is_game_over() {
    bool conflict = true;
    for (size_t i = 1; i < snake_tail.size() && conflict; i++) {
      if (snake_tail[0] == snake_tail[i]) {
        conflict = false;
      }
    }
    if (conflict) {
      conflict = !(snake_tail[0].first == 0 || snake_tail[0].first == MAP_WIDTH - 1 || snake_tail[0].second == 0
          || snake_tail[0].second == MAP_LENGTH - 1);
    }
    return conflict;
  }

  void generate_food() {
    bool flag = true;
    while (flag) {
      food.first = 1 + rand() % (MAP_WIDTH - 2);
      food.second = 1 + rand() % (MAP_LENGTH - 3);
      flag = false;
      for (int i = 0; i < snake_tail.size() && !flag; i++) {
        if (food == snake_tail[i]) {
          flag = true;
        }
      }
    }
  }

  void the_food_is_eaten() {
    if (food == snake_tail[0]) {
      generate_food();
      snake_tail.emplace_back();
    }
  }

};

void gotoxy(short x, short y) {
  COORD pos = {x, y};
  HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(output, pos);
}

void print_map() {
  for (int i = 0; i < MAP_WIDTH; i++) {
    for (int j = 0; j < MAP_LENGTH; j++) {
      std::cout << map[i][j];
    }
    std::cout << '\n';
  }
}
