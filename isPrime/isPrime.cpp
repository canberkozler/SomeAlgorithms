// can detect being prime number at compile time
constexpr bool isprime(int val){
    if(val==0|| val==1) return false;
    if(val%2 ==0) return val ==2;
    if(val%3 ==0) return val ==3;
    if(val%5 ==0) return val ==5;

    for(int i =7; i*i<=val; i+=2){
        if(val%i==0) return false;
    }
    return true;
}

constexpr int square(int x){// operand can not be constexpr
    return x*x;
}

constexpr int doSth(int x, int y){// operands can not be constexpr
    return x*x+y*y;
}

int main(){
    constexpr int y1 =2;
    constexpr int y2 =233;

    constexpr bool b1 = isprime(20); 
    constexpr bool b2 = isprime(square(y1)+3);
    constexpr bool b3 = isprime(doSth(y1,y2)); 
    constexpr bool b4 = isprime(doSth(y1,y2)+3);

    int y3 =23;
    // y3 need to be constexpr if desiring gettting value at compile time.
    bool b = isprime(y3); // syntax error occurs if type of b is constexpr bool.
}