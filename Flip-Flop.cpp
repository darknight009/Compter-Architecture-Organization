#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <iomanip>  

using namespace std;


class Clock{
  static inline bool clk=0; //c++ 17
  static inline bool prev=0; //c++ 17
  int t;
  //static thread drw;
  public:
  void drawClk(){
    while(1){
      std::cout.flush();
      bool temp=clk;
      if (temp) cout << "-";
      else cout<<"_";
      this_thread::sleep_for(chrono::milliseconds(200));
      prev=temp;
    }
  }

  void calc(){
    while(1){
      clk=1-clk;
      this_thread::sleep_for(chrono::milliseconds(1000));
    }
  }

  static void ini(){
    Clock clk_obj;
    thread t1(&Clock::drawClk, clk_obj);
    thread t2(&Clock::calc, clk_obj);
    t1.join();
    t2.join();
  }

  bool getVal(){
    bool edge;
    if (clk&&!prev) edge=1;
    else edge=0;
    return edge;
  }
};

class SRff{
  bool set, reset;
  bool out1, out2;
  bool clk;
  public:
    SRff(){
      out1=0;
      out2=0;
    }
    void inputs(bool s=0, bool r=0, bool c=0){
          clk=c;
          set=s;
          reset=r;
    }
    bool calculate(){
      set=clk&set;
      reset=clk&reset;
      if(set&reset&clk) cout<<"Not Allowed"<< " ";
      out1 = !(reset|out2);
      out2 = !(set|out1);
      cout<<clk<<" "<<set<<" "<<reset<<" "<<out1<<" "<<out2<<endl;
      return out1;
    }
};

class Dff{
  bool set, clk;
  SRff sr_ff;
  public:
    void inputs(bool d=0, bool c=0){
          clk=c;
          set=d;
          sr_ff.inputs(set, 1-set, clk);
    }
    bool calculate(){
      return sr_ff.calculate();
    }
};

class JKff{
  bool J, K;
  bool out1, out2;
  bool clk;
  public:
    JKff(){
      out1=0;
      out2=0;
    }
    void inputs(bool j=0, bool k=0, bool c=0){
          J=j;
          K=k;
          clk=c;
    }
    bool calculate(){
      cout<<clk<<" "<<J<<" "<<K;
      J=clk&J;
      K=clk&K;
      J=out2&J;
      K=out1&K;
      out1 = !(K|out2);
      out2 = !(J|out1);
      cout<<" "<<out1<<" "<<out2<<endl;
      return out1;
    }
};


int main() {
  Clock clk;
  thread clock = thread(clk.ini);
  JKff latch;
  latch.inputs(1, 0, clk.getVal());
  latch.calculate();
  usleep(500000);//microseconds
  latch.inputs(0, 0, clk.getVal());
  latch.calculate();
  usleep(500000);//microseconds
  latch.inputs(0, 1, clk.getVal());
  latch.calculate();
  usleep(500000);//microseconds
  latch.inputs(0, 0, clk.getVal());
  latch.calculate();
  usleep(500000);//microseconds
  latch.inputs(1, 0, clk.getVal());
  latch.calculate();//microseconds
  usleep(500000);//microseconds
  latch.inputs(0, 0, clk.getVal());
  latch.calculate();//microseconds
  usleep(500000);//microseconds
  latch.inputs(1, 1, clk.getVal());
  latch.calculate();//microseconds
  usleep(500000);//microseconds
  latch.inputs(1, 1, clk.getVal());
  latch.calculate();//
  usleep(500000);//microseconds
  latch.inputs(1, 1, clk.getVal());
  latch.calculate();//microseconds
  usleep(500000);//microseconds
  //clock.join(); //clock should stop when main ends
  return 0;
}
