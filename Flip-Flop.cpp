#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>

using namespace std;

class Clock{
  static inline bool clk=0; //c++ 17
  public:
  static void func(){
    while(1){
      clk=1-clk;
      this_thread::sleep_for(chrono::milliseconds(100));
    }
  }
  bool getVal(){
    return clk;
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
  thread clock = thread(clk.func);
  
  JKff latch;
  latch.inputs(1, 0, clk.getVal());
  latch.calculate();
  usleep(100000);//microseconds
  latch.inputs(0, 0, clk.getVal());
  latch.calculate();
  usleep(100000);//microseconds
  latch.inputs(0, 1, clk.getVal());
  latch.calculate();
  usleep(100000);//microseconds
  latch.inputs(0, 0, clk.getVal());
  latch.calculate();
  usleep(100000);//microseconds
  latch.inputs(1, 0, clk.getVal());
  latch.calculate();//microseconds
  latch.inputs(0, 0, clk.getVal());
  latch.calculate();//microseconds
  latch.inputs(1, 1, clk.getVal());
  latch.calculate();//microseconds
  //clock.join(); clock should stop when main ends
  return 0;
}
