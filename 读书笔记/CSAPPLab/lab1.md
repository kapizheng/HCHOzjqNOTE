### bitXor(int x,int y);

> 第一题算是蛮简单的，但是比起之前的版本要难一些，多拿纸笔推敲一下就可以解决了。

```c++
int bitXor(int x, int y) {
  int ans=(~((~x)&(~y)))&(~(x&y));
  return ans;
}
```

### int tmin(void);

> 好好看书应该能知道tmin就等于Tmax+1也是就是(1<<31)-1+1，送分题

```c++
int tmin(void) {
  int ans=(1<<31);
  return ans;
}
```

### int isTmax(int x);

> 如何判断一个数是Tmax，也就是`(1<<31)-1`，但是题目不让用`<<`
>
> 最大嘛，也就是31个1，那么我们给他+1，再与其本身进行一个异或操作，就得到了全是1的情况，之后用`~`判断一波就好了，但是有那么一种情况就-1也会出现这样子的情况，-1本身就是32个1，所以这个时候可以对其本身进行`~`，也就是说假如是-1，就不能出现也就是`!(~x)`的情况再或上`!~((x+1)|x)`

```c++
int isTmax(int x) {
  int y=x+1;
  int z=~x;
  y^=x;
  y=!(~y);
  z=!z;
  return (!z)&y;
}
```

### int allOddBits(int x);

> 直接一个骚操作？AA（10101010）判断一下，或者直接与然后将位数变为2位，再与一次，然后两次!!，两次！！经常用来判断数字是否为0

```c++
int allOddBits(int x) {
  int a=(x>>16)&x;
  int b=(a>>8)&a;
  int c=(b>>4)&b;

  return !(c&0xA^0xA);
}
```

### int negate(int x);

> 送分题，看书就可以了

```c++
int negate(int x) {
  return (~x)+1;
}
```

### int isAsciiDigit(int x);

> 判断是否在一个范围内，这是技巧题，也就是说0x30加一个数得是一个负数，0x39加一个数还是正数，0x3A就是负数，利用溢出原理，具体看代码？0x3f+一个数要是一个负数就得那个数字+03f为最大数字+1，0x39加一个数字还是正数就得0x39+一个数字恰好等于最大数字。最后判断符号位就好了。但是这里得要好好运用所给的符号，注意溢出细节

```c++
int isAsciiDigit(int x) {
  int a=1<<31;
  int up=~(a|0x39);
  int down=~(a|0x30);
  int upp=(x+up)>>31&1;
  int doo=(x+down+1)>>31&1;
  int ans=(!upp)&(doo);
  return ans;
}
```

- 这道题需要注意在计算upp的时候的>>操作符是逻辑左移还是算术移动，后来最后加了一个&就过了，我也不太清楚咋回事，就算是算术左移，最后用(!upp)以及后面的&也还是可以推出来的= =

### int conditional(int x,int z);

> 两次`!`判断x是否有值，有的话直接(~x+1)

```c++
int conditional(int x, int y, int z) {
        int t=!!x;
        t=~t+1;
        return (t&y)|(~t&z);
}
```

### int isLessOrEqual(int x,int y);

> 使用位运算判断大小，分几种情况，位数全相同，符号相同，符号不同，符号不同直接判断符号就好了，相同的话给两者进行一个减法，当需要用到减法的时候，肯定是符号一样的情况，那么对于加法来说，减去一个数就等于加上该数的补，负数的补码等于该数绝对值？（这点没有验证，但是找几个数字演算一下可以成立）两个数字相减法，就可知道谁大谁小了

```c++
int isLessOrEqual(int x, int y) {
    int z=!(x^y);
    int a=(x>>31)&1;
    int b=(y>>31)&1;
    int c1=a&(~b);
    int c2=((~a)&b);
    int c3=x;
    x=x+(~y+1);
    x=(x>>31)&1;
    return z|c1|(!c2)&x;
}
```

### int logicalNeg(int x);

> 模拟取反，先判断有没有位是1，然后再通过一些操作解决。。。

```c++
int logicalNeg(int x) {
        int y=x>>16|x;
        int z=y>>8|y;
        int l=z>>4|z;
        int m=l>>2|l;
        int n=m>>1|m;
        n=n&1;
        return n^1;
}
```

### int howManyBits(int x);

> 问有多少位可以表示该数的有符号形式

```
int howManyBits(int x) {
  int flag=x>>31;
  int b16,b8,b4,b2,b1;
  x=(~flag&x)|(flag&~x);//1.positive 2.negative
  b16=(!!(x>>16))<<4;
  x>>=b16;
  b8=(!!(x>>8))<<3;
  x>>=b8;
  b4=(!!(x>>4))<<2;
  x>>=b4;
  b2=(!!(x>>2))<<1;
  x>>=b2;
  b1=(!!(x>>1));
  x>>=b1;
  return b16+b8+b4+b2+b1+x+1;
}
```

### unsigned floatScale2(unsigned uf);

> 这题感觉是用来熟悉浮点数的结构的，课本对乘法运算讲的比较少，so...，不过会这题大概就知道每个结构是干嘛的了
>
> 假如是Nan或者无限，也就是阶码为255的时候直接返回原数
>
> 假如是非规格的也就是该数字太小，就将尾数直接移动就好了
>
> 假如是规格的，就需要将阶码+1，因为阶码代表的是小数点在二进制数的哪里.

```c++
unsigned floatScale2(unsigned uf) {
  unsigned sign=uf>>31&1;
  unsigned exp=0xff&(uf>>23);//jiema
  unsigned frac=uf&(0x7fffff);
  unsigned ans;
  if(exp==255)return uf;
  else if(exp==0){
        frac=(frac<<1);
        ans=sign<<31|exp<<23|frac;
  }else {
        exp++;
        ans=sign<<31|exp<<23|frac;
  }
  return ans;
}
```

### int floatFloat2Int(unsigned uf) ;

> 将浮点数转为int类型，这里得考虑会超出范围的情况，也就是整数部分太大，溢出，所以阶码不能大于31。
>
> 之后对其小数点进行一个左右移动的操作，对该浮点数进行调制
>
> 正负判断返回

```c++




int floatFloat2Int(unsigned uf) {
  int sign=uf>>31&1;
  unsigned exp=(uf>>23)&0xff;
  unsigned frac=uf&0x7fffff;

  int E=exp-(127);
  if(E>=31)return 0x80000000u;
  else if(E<0){return 0;}
  else {
     frac|=(1<<23);
     if(E<=23){
        frac>>=(23-E);
     }else frac<<=(E-23);
     if(sign)frac=-frac;
     return frac;
  }
}
```

### unsigned floatPower2(int x);

> pow的浮点数运算，算出规格化数的阶码就好了：x+127

```c++
unsigned floatPower2(int x) {
    int E=x+127;
    int INF=0xff<<23;
    unsigned ans=E<<23;
    if(E>=255)return INF;
    else if(E<0)return 0;
    else return ans;
}
```

....