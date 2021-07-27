#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

bool checkSymbols(char symb) {
  return (symb != 'O' && symb != 'X' && symb != '.') ? false : true;
}

char checkDiagonal(std::string field) {
  if ((field[0] == field[4]) && (field[4] == field[8]) && field[0] != '.'){
    return field[0];
  } else if ((field[2] == field[4]) && (field[4] == field[6]) && field[2] != '.'){
    return field[2];
  }
  return '!';
}

char checkHorizontal(std::string field) {
  for (int i = 0; i < field.size(); i = i + 3) {
    if ((field[i] == field[i+1]) && (field[i+1] == field[i+2]) && field[i] != '.') {
      return field[i];
    }
  }
  return checkDiagonal(field);
}

char checkVertical(std::string field) {
  for (int i = 0; i < 3; ++i) {
    if ((field[i] == field[i+3]) && (field[i+3] == field[i+6]) && field[i] != '.') {
      return field[i];
    }
  }
  return checkHorizontal(field);
}

std::string checkWon(std::string field) {
  int countX = count(field.begin(), field.end(), 'X');
  int countO = count(field.begin(), field.end(), 'O');
  int countDot = count(field.begin(), field.end(), '.');

  if (countX == countO || (countX - 1) == countO) {
    if (checkVertical(field) == 'X') {
      return ((countX - 1) == countO) ? "Petya won." : "Incorrect";
    } else if (checkVertical(field) == 'O') {
      return (countX == countO) ? "Vanya won." : "Incorrect";
    } else {
      return "Nobody";
    }
  }
  return "Incorrect";
}

std::string checkField(std::string field) {
  for (int i = 0 ; i < field.size() ; ++i) {
    if (!checkSymbols(field[i])) {
      return "Incorrect";
    }
  }
  return checkWon(field);
}

void test() {
  std::vector<std::string> playingField = {
                                          "X..OXOOOO", // Incorrect
                                          "X...X.OO.", // Nobody
                                          "XXOOOXXOX", // Nobody
                                          "XO.XO.X.O", // Incorrect
                                          "OX.XOXX.O", // Incorrect
                                          "..XOX.X.O", // Petya won.
                                          "0........"  // Incorrect
                                          };
  for (int i = 0; i < playingField.size(); ++i) {
    std::cout << (playingField[i].size() != 9 ? "Incorrect" : checkField(playingField[i]));
    std::cout << std::endl;
  }
}

int main() {
  //test();
  std::string playingField;
  std::string topLine, midLine, botLine;
  std::getline(std::cin, topLine);
  std::getline(std::cin, midLine);
  std::getline(std::cin, botLine);
  std::cout << (topLine.size() != 3 && midLine.size() != 3 && botLine.size() != 3 ? "Incorrect" : checkField(topLine+midLine+botLine));
}

/*
Что нужно сделать
Петя и Вася играли в крестики-нолики и не стёрли результаты своей игры. Теперь перед вами табличка 3 × 3, которая осталась после их поединка. Вы хотите понять, выиграл ли кто-то из них или они не доиграли.
На вход программе даётся три строки, кодирующие верхнюю, среднюю и нижнюю строчки игрового поля. Крестик обозначается символом X (английская заглавная буква X), нолик — символом O (заглавная латинская буква O), пустая клетка — точкой.
Если ввод некорректен, то есть такая таблица не могла получиться в ходе настоящей игры, то надо написать в ответ слово Incorrect.
Если таблица корректна и выиграли крестики, то нужно вывести в ответ слова Petya won, если нолики — то Vanya won, а иначе (то есть они не доиграли или сыграли вничью) надо написать Nobody.
*/