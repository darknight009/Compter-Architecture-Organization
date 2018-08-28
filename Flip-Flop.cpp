#include <iostream>

using namespace std;

class SRff{
  bool set, reset;
  bool out1, out2;
  bool clk;
  public:
    SRff(){
      out1=0;
      out2=0;
      clk =0;
    }
    void inputs(bool s=0, bool r=0){
          set=s;
          reset=r;
    }
    bool calculate(){
      clk=1-clk;
      set=clk&set;
      reset=clk&reset;
      if(set&reset&clk) cout<<"Not Allowed"<< " ";
      out1 = !(reset|out2);
      out2 = !(set|out1);
      return out1;
    }
};

int main() {
  SRff latch;
  latch.inputs(1, 0);
  latch.calculate();
  latch.inputs(0, 0);
  latch.calculate();
  latch.inputs(0, 1);
  latch.calculate();
  latch.inputs(0, 0);
  latch.calculate();
  latch.inputs(1, 1);
  latch.calculate();
}
