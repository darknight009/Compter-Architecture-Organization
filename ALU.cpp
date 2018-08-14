#include <iostream>
#include <math.h>
using namespace std;

class Adder{
  bool c_out;
  bool out;
  public:
    void add(bool a, bool b, bool c_in){
      out = a^b^c_in;
      c_out = ((a^b)&&c_in) || (a&&b);
    }
    bool Out(){
      return out;
    }
    bool Carry(){
      return c_out;
    }
};

class MUX2{
  bool x;
  bool y;
  public:
    void inputs(bool a=0, bool b=0){
      this->x=a;
      this->y=b;
    }
    bool select(bool s){
      bool xs = (this->x)&&(!s);
      bool ys = (this->y)&&(s);
      return(xs||ys);
    }
};

class MUX4{
  bool x;
  bool y;
  bool z;
  bool w;
  public:
    void inputs(bool a=0, bool b=0, bool c=0, bool d=0){
      this->x=a;
      this->y=b;
      this->z=c;
      this->w=d;
    }
    bool select(bool s1, bool s2){
      bool xs = (this->x)&&(!s1&&!s2);
      bool ys = (this->y)&&(!s1&&s2);
      bool zs = (this->z)&&(s1&&!s2);
      bool ws = (this->w)&&(s1&&s2);
      return(xs||ys||zs||ws);
    }
};

class ALU{
  bool a; 
  bool b;
  bool carry;
  bool output;
  MUX2 muxa;
  MUX2 muxb;
  MUX4 otpt;
  Adder adder;
  public:
    void inputs(bool a, bool b){
      this->a=a;
      this->muxa.inputs(a, !a);
      this->b=b;
      this->muxb.inputs(b, !b);
    }
    void operation(bool ai,bool bi, bool c, bool s1, bool s2){
      bool aout=muxa.select(ai);
      bool bout=muxb.select(bi);
      adder.add(aout, bout, c);
      bool sum=adder.Out();
      carry=adder.Carry();
      otpt.inputs(aout&&bout, aout||bout, sum);
      output=otpt.select(s1, s2);//00 for AND 01 for OR 10 for AND
    }
    bool Carry(){
      return carry;
    }
    bool Out(){
      return output;
    }
};

int main() {
  int a=594, b=873;
  int out=0;
  ALU alus[32];
  int shift=1;
  for(int i=0; i<32; i++){
    ALU alu;
    alu.inputs(a&shift, b&shift);
    alus[i]=alu;
    shift=shift<<1;
  }
  alus[0].operation(1, 0, 1, 1, 0); 
  out+=alus[0].Out();
  for(int i=1; i<32; i++){
    alus[i].operation(1, 0, alus[i-1].Carry(), 1, 0);
    out+=alus[i].Out()*pow(2, i);
  }
  cout<<out;
}