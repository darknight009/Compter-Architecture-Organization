#include <iostream>

using namespace std;

class SRLatch{
  bool set, reset;
  bool out1, out2;
  public: 
    SRLatch(){
      out1=1;
      out2=0;
    }
    void inputs(bool s=0, bool r=0){
        set=s;
        reset=r;
        if(s&r) cout<<"Not Allowed"<< " ";
      }
    void calculate(){
        out1 = !(reset|out2);
        out2 = !(set|out1);
        cout<<out1<<" "<<out2<<endl;
    }
};

int main() {
  SRLatch latch;
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
