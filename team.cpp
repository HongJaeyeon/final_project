#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;
int main(){
  int map = 0; //1번째 맵 다음으로 바뀌려면 map++
  int size = 100;
  int row = 0;
  int col = 0;
  int cpos = 0;//현재 캐릭터의 위치
  int tries = 0;
  int push = 0;
  char direct[10];//화살표 키 입력
  string position[] = {"34","74","57","58","66"};//캐릭터의 최초 위치, 꾸준한 수정필요, 맵이 종료될시 다음 인덱스의 위치로 넘어감
  string answer[] = {"4444444444441111444444130114444413001444441302144444112011144441020014444100001444410011144441111444",
  "4444444444444444444444111114444410001444441333144444122211444410000144441000014444111111444444444444",
  "4444444444444444444444444444444111111114413000001441032220144130000014411111001444444111144444444444",
  "4444444444444444444444111111144410000014441032301444102320144410323014441023201444100000144411111114",
  "4444444444444444444441111444444100111144410000011411011000141303100211100010220110031000011111111111"};
  string start_answer = answer[0];
  start_answer = start_answer[1];
  initscr();
  keypad(stdscr, TRUE);
  curs_set(0);
  noecho();
  resize_term(200,200);
  start_color();
  init_pair(1, COLOR_WHITE,COLOR_BLACK);//0
  init_pair(2, COLOR_WHITE,COLOR_YELLOW);//1
  init_pair(3, COLOR_WHITE,COLOR_RED);//2
  init_pair(4, COLOR_WHITE,COLOR_BLUE);//3 목적지
  init_pair(5, COLOR_WHITE,COLOR_GREEN);//4
for(map=0; map<5; map++){
  string reanswer = answer[map];
  string repos = position[map];
  int level = map+1;
  start_answer = answer[map];
  start_answer = start_answer[1];
  int step = 0;
  push = 0;
  row = 0;
  col = 0;
  int count = 0; // 목적지의 갯수
  for (int i = 0;i<size;i++){
    if (answer[map][i] == '3'){
      count += 1;
    }
  }
  clear();
  mvprintw(50,30,"press the q button to try again");
  mvprintw(51,30,"tries: %d",push);
  mvprintw(52,30,"pushes: %d",step);
  mvprintw(53,30,"level: %d",level);
  refresh();
  for (int i = 0;i<size;i++){//초기화면 출력과정
    WINDOW *win1;
    char b = answer[map][i];
    int a = b-'0';
    win1 = newwin(5,5,5*row,5*col);
    wbkgd(win1, COLOR_PAIR(a+1));//번호에따른 팔레트 배치
    wattron(win1, COLOR_PAIR(a+1));//
    if (row == (int)((char)position[map][0]-'0')&&col == (int)((char)position[map][1]-'0')){
      //n번쨰 단계에서의 캐릭터위치
      cpos = i;
      mvwprintw(win1,1,1,"0");
    }
    wrefresh(win1);
    col++;
    if(col == 10){//한줄을 모두 출력했을 때
      row++;
      col = 0;
    }
    delwin(win1);
  }
  refresh();
  scanw("%s",direct);//(wasd키중 하나 누르고 엔터키) 이 과정을 반복
  while (count != 0){
    count = 0;
    if (direct[0] == 'q'){
      answer[map] = reanswer;
      position[map] = repos;
      map--;
      break;
    }
    if (direct[0] == 's'){//캐릭터가 아래로
      push++;
        if(answer[map][cpos+10] == '1'){}
        else if (answer[map][cpos+10] == '2'){
          if (answer[map][cpos+20] == '0'){
            char temp = answer[map][cpos+20];
            answer[map][cpos+20] = '2';
            answer[map][cpos+10] = temp;
            cpos += 10;
            step += 1;
            position[map][0] += 1;//이 부분 한 맵이 종료될때 마다 [0][0] -> [1][0] ->[2][0] 이런식으로 넘어감
          }
          else if (answer[map][cpos+20] == '3'){
            answer[map][cpos+20] = '2';
            if (start_answer[cpos+10] == '3'){//초기단계에서 목적지였을 때
              answer[map][cpos+10] = '3';
            }
            else{
              answer[map][cpos+10] = '0';
            }
            cpos += 10;
            step += 1;
            position[map][0] += 1;//맵 넘어갈때마다 수정
          }
          else {}
        }
        else{
          cpos += 10;
          position[map][0] += 1;//맵 넘어갈때마다 수정
        }
    }
    else if (direct[0] == 'w'){//위로
      push++;
      if (answer[map][cpos-10] == '1'){}
      else if (answer[map][cpos-10] == '2'){
        if (answer[map][cpos-20] == '0'){
          char temp = answer[map][cpos-20];
          answer[map][cpos-20] = '2';
          answer[map][cpos-10] = temp;
          cpos -= 10;
          step += 1;
          position[map][0] -= 1;//맵 넘어갈때마다 수정
        }
        else if (answer[map][cpos-20] == '3'){
          answer[map][cpos-20] = '2';
          if (start_answer[cpos-10] == '3'){//초기에 목적지였을 때
            answer[map][cpos-10] = '3';
          }
          else{
            answer[map][cpos-10] = '0';
          }
          cpos -= 10;
          step += 1;
          position[map][0] -= 1;//맵 넘어갈때마다 수정
        }
        else{
        }
      }
      else{
        cpos -= 10;
        position[map][0] -= 1;//맵 넘어갈때마다 수정
      }
    }
    else if (direct[0] == 'a'){//왼쪽
      push++;
      if (answer[map][cpos-1] == '1'){
      }
      else if (answer[map][cpos-1] == '2'){
        if (answer[map][cpos-2] == '0'){
          char temp = answer[map][cpos-2];
          answer[map][cpos-2] = '2';
          answer[map][cpos-1] = temp;
          cpos -= 1;
          step += 1;
          position[map][1] -= 1;//맵 넘어갈때마다 수정
        }
        else if (answer[map][cpos-2] == '3'){
          answer[map][cpos-2] = '2';
          if (start_answer[cpos-1] == '3'){//초기에 목적지였을 때
            answer[map][cpos-1] = '3';
          }
          else{
            answer[map][cpos-1] = '0';
          }
          cpos -= 1;
          step += 1;
          position[map][1] -= 1;//맵 넘어갈때마다 수정
        }
        else{
        }
      }
      else{
        cpos -= 1;
        position[map][1] -= 1;//맵 넘어갈때마다 수정
      }
    }
    else if (direct[0] == 'd'){//오른쪽
      push++;
      if (answer[map][cpos+1] == '1'){
      }
      else if (answer[map][cpos+1] == '2'){
        if (answer[map][cpos+2] == '0'){
          char temp = answer[map][cpos+2];
          answer[map][cpos+2] = '2';
          answer[map][cpos+1] = temp;
          cpos += 1;
          step += 1;
          position[map][1] += 1;//맵 넘어갈때마다 수정
        }
        else if (answer[map][cpos+2] == '3'){
          answer[map][cpos+2] = '2';
          if (start_answer[cpos+1] == '3'){//초기에 목적지였을 때
            answer[map][cpos+1] = '3';
          }
          else{
            answer[map][cpos+1] = '0';
          }
          cpos += 1;
          step += 1;
          position[map][1] += 1;//맵 넘어갈때마다 수정
        }
        else{
        }
      }
      else{
        cpos += 1;
        position[map][1] += 1;//맵 넘어갈때마다 수정
      }
    }
    clear();
    mvprintw(50,30,"press the q button to try again");
    mvprintw(51,30,"tries: %d",push);
    mvprintw(52,30,"pushes: %d", step);
    mvprintw(53,30,"level: %d",level);
    refresh();
    row = 0;
    col = 0;
    for (int i = 0;i<size;i++){//초기화면 출력과정
      WINDOW *win1;
      char b = answer[map][i];
      int a = b-'0';
      win1 = newwin(5,5,5*row,5*col);
      wbkgd(win1, COLOR_PAIR(a+1));//번호에따른 팔레트 배치
      wattron(win1, COLOR_PAIR(a+1));//
      if (row == (int)((char)position[map][0]-'0')&&col == (int)((char)position[map][1]-'0')){
        //n번쨰 단계에서의 캐릭터위치
        cpos = i;
        mvwprintw(win1,1,1,"0");
      }
      wrefresh(win1);
      col++;
      if(col == 10){//한줄을 모두 출력했을 때
        row++;
        col = 0;
      }
      delwin(win1);
    }
    refresh();
    for (int i = 0;i<size;i++){
      if (answer[map][i] == '3'){
        count += 1;
      }
    }
    scanw("%s", direct);
  }
}
  refresh();
  getch();
  endwin();
  return 0;
}
