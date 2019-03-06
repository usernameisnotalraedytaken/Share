#include <cmath>
#include <cstdio>
#include <cstring>
#include <climits>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 20005;

struct bg;/**高精度整数结构体*/

bg modn(bg a, bg b);/**高对高求余*/
bg divn(bg a, bg b);/**高对高除法*/
bg muln(bg a, bg b);/**高对高乘法*/
bg absdivn(bg a, bg b);/**绝对值相除*/
bg div(bg a, int b);/**高对低除法*/
bg absmodn(bg a, bg k);/**绝对值求余*/
bg mod(bg a, int k);/**高对低求余*/
bg fac_sum(bg a);/**阶乘和*/
bg fastfaclow(int a);/**低对高阶乘优化*/
bg fastfac(bg a);/**高对高阶乘优化*/
bg fac(bg a);/**高对高阶乘*/
bg pown(bg a,bg b);/**高对高乘方*/
bg pow(bg a,int b);/**高对低乘方*/
bg absmuln(bg a,bg b);/**绝对值相乘*/
bg mul(bg a,int b);/**高对低乘法*/
bg zero();/**高精度0*/
bg one();/**高精度1*/
bg int_to_bg(int x);/**int转高精度*/
bg sub(bg a,bg b);/**高对高减法*/
bg add(bg a,bg b);/**高对高加法*/
bg abssub(bg a,bg b);/**绝对值相减*/
bg absadd(bg a, bg b);/**绝对值相加*/
bg scan();/**读入高精度数*/
void pp(bg &i);/**自增1*/
bg get();/**读入高精度数*/
int compare(bg a, bg b);/**比较 a>b 1; a=b 0; a<b -1*/
void output(bg a, bool z);/**输出*/

struct bg {
    int d[maxn];
    int len;
    bool flag;
    bg() {
        memset(d, 0, sizeof(d));
        len = 0;
        flag = true;
    }
    bg(int a) {
        *this = int_to_bg(a);
    }
    //operator=(int a)
    //{
    //	*this = int_to_bg(a);
    //}
};

bg operator!(bg a) {
    return fac(a);
}

bg operator^(bg a, bg b) {
    return pown(a,b);
}

bg operator^(bg a, int b) {
    return pow(a,b);
}

bg operator+(bg a, bg b) {
    return add(a,b);
}

bg operator-(bg a, bg b) {
    return sub(a,b);
}

bg operator*(bg a, bg b) {
    return muln(a,b);
}

bg operator/(bg a, bg b) {
    return divn(a,b);
}

bg operator%(bg a, bg b) {
    return modn(a,b);
}

void operator--(bg &a) {
    a = a-one();
}

void operator++(bg &a) {
    a = a+one();
}

bool operator>(bg a, bg b) {
    if(compare(a,b)==1) {
        return true;
    }
    else {
        return false;
    }
}

bool operator==(bg a, bg b) {
    if(compare(a,b)==0) {
        return true;
    }
    else {
        return false;
    }
}

bool operator<(bg a, bg b) {
    if(compare(a,b)==-1) {
        return true;
    }
    else {
        return false;
    }
}

bool operator<=(bg a, bg b)
{
    if(a<b||a==b)
        return true;
    return false;
}

bool operator>=(bg a, bg b)
{
    if(a>b||a==b)
        return true;
    return false;
}

void operator+=(bg &a, bg &b) {
    a = a + b;
}

void operator-=(bg &a, bg &b) {
    a = a - b;
}

void operator*=(bg &a, bg &b) {
    a = a * b;
}

void operator/=(bg &a, bg &b) {
    a = a / b;
}

ostream & operator<<(ostream &os, bg a) {
    output(a,true);
    return os;
}

istream & operator>>(istream &ist, bg &a) {
    a = scan();
    return ist;
}


void output(bg a, bool z)
{
    if(a.flag==false)
        printf("-");
    if(a.d[0] == 0 && a.len == 1) {
        printf("0");
        return;
    }
    if(!z) {
        for(int i = a.len - 1; i >= 0; i--)
        {
            putchar(a.d[i] + '0');
        }
        return;
    }
    else {
        bool zr = false;
        for(int i = a.len - 1; i >= 0; i--) {
            if(a.d[i]!=0) {
                zr = true;
            }
            if(zr)
            {
                putchar(a.d[i] + '0');
			}
        }
        return;
    }
}
int compare(bg a, bg b)
{
    if(a.len > b.len)
        return 1;
    else if(a.len < b.len)
        return -1;
    else {
        for(int i = a.len - 1; i >= 0; i--) {
            if(a.d[i] > b.d[i])
                return 1;
            else if(a.d[i] < b.d[i])
                return -1;
        }
        return 0;
    }
}
bg get()
{
    char s[maxn];
    fgets(s,maxn,stdin);
    bg a;
    a.len = strlen(s);
    for(int i = 0; i < a.len; i++) {
        a.d[i] = s[a.len - i - 1] - '0';
    }
    return a;
}
void pp(bg &i)
{
    bg c;
    c.d[0]=1;
    c.len=1;
    i = add(i,c);
}
bg scan()
{
    char s[maxn];
    scanf("%s",s);
    if(s[0]!='-')
    {
        bg a;
        a.len = strlen(s);
        for(int i = 0; i < a.len; i++)
        {
            a.d[i] = s[a.len - i - 1] - '0';
        }
        return a;
    }
    else { //-1
        bg a;
        a.len = strlen(s)-1;//1=2-1
        for(int i = 1; i < a.len+1; i++)
        {
            a.d[i-1] = s[a.len - i + 1] - '0';
        }
        a.flag = false;
        return a;
    }
}
bg absadd(bg a, bg b)
{
    if(compare(a,b)==0&&a.d[0]==0&&a.len==1)
        {
        bg c;
        c.len = 1;
        c.d[0]=0;
        return c;
    }
    bg c;
    int temp = 0;
    for(int i = 0; i < a.len || i < b.len; ++i) {
        int ans = a.d[i] + b.d[i] + temp;
        c.d[c.len++] = ans % 10;
        temp = ans / 10;
    }
    if(temp != 0) {
        c.d[c.len++] = temp;
    }
    return c;
}
bg abssub(bg a,bg b)
{
    if(compare(a,b)==0)
    {
        bg c;
        c.len = 1;
        c.d[0]=0;
        return c;
    }
    else {
        bg c;
        for(int i = 0; i < a.len || i < b.len; i++)
        {
            if(a.d[i] < b.d[i])
            {
                a.d[i + 1]--;
                a.d[i] += 10;
            }
            c.d[c.len++] = a.d[i] - b.d[i];
        }
        while(c.len - 1 >= 1 && c.d[c.len - 1] == 0)
        {
            c.len--;
        }
        return c;
    }
}
bg add(bg a,bg b)
{
    if(a.flag!=b.flag)
        {
        bg c;
        if(compare(a,b)==0)
        {
            c.len = 1;
            c.d[0]=0;
            return c;
        }
        else if(compare(a,b)==1)
        {
            c = abssub(a,b);
            c.flag = a.flag;
            return c;
        }
        else
        {
            c = abssub(b,a);
            c.flag = b.flag;
            return c;
        }
    }
    else if(a.flag==b.flag&&a.flag==false)
    {
        bg c;
        c = absadd(a,b);
        c.flag = a.flag;
        return c;
    }
    else
    {
        return absadd(a,b);
    }
}
bg sub(bg a,bg b)
{
    bg c = b;
    c.flag = !b.flag;
    return add(a,c);
}
bg int_to_bg(int x)
{
    bg c;
    do
    {
        c.d[c.len++] = x % 10;
    }while(x /= 10);
    return c;
}
bg one()
{
    return int_to_bg(1);
}
bg zero()
{
    return int_to_bg(0);
}
bg mul(bg a,int b)
{
    bg c;
    int d = 0;
    for(int i = 0; i < a.len; ++i)
    {
        int t = d + a.d[i] * b;
        d = t / 10;
        c.d[i] = t % 10;
        c.len++;
    }
    while(d != 0)
    {
        c.d[c.len++] = d % 10;
        d /= 10;
    }
    return c;
}
void moving(int a[], int p, int &len)
{
    for(int i = len - 1; i >= 0; --i)
    {
        swap(a[i], a[i + p]);
    }
    len += p;
}
bg absmuln(bg a,bg b)
{
    bg c = zero();
    if(a<b)
        swap(a, b);
    for(int i = 0; i < b.len; ++i)
    {
        bg ans(0);
        int temp = 0;
        for(int j = 0; j < a.len; ++j)
        {
            int cs = a.d[j] * b.d[i] + temp;
            temp = cs / 10;
            ans.d[j] = cs % 10;
        }
        ans.len = a.len;
        while(temp != 0)
        {
            ans.d[ans.len] = temp % 10;
            ++ans.len;
            temp /= 10;
        }
        moving(ans.d, i, ans.len);
        c = c + ans;
    }
    return c;
}
bg pow(bg a,int b)
{
    int t = 2;
    if(b == 0)
    	return 1;
    if(b == 1)
    	return a;
    if(b % t == 0)
    	return pow(a, b / 2) * pow(a, b / 2);
    else
    	return pow(a, b - 1) * a;
}
bg pown(bg a,bg b)
{
    bg t(2);
    if(b == zero())
    	return one();
    if(b == one())
    	return a;
    if(b % t == zero())
    	return pown(a, b / 2) * pown(a, b / 2);
    else
    	return pown(a, b - one()) * a;
}
bg fac(bg a)
{
    bg c = one();
    for(bg i = one(); compare(i,a)!=1; ++i)
    {
        c=muln(c,i);
    }
    return c;
}
bg fastfac(bg a)
{
    bg c = int_to_bg(1);
    for(int i = 1; int_to_bg(i)<(a+one()); ++i)
    {
        c=mul(c,i);
    }
    return c;
}
bg fastfaclow(int a)
{
    bg c = one();
    for(int i = 1; i<=a; ++i)
    {
        c = mul(c,i);
    }
    return c;
}
bg fac_sum(bg a)
{
    bg c = zero();
    for(bg i = one(); compare(i,a)<=0; i=add(i,one()))
    {
        c = add(c,fac(i));
    }
    return c;
}
bg mod(bg a, int k)
{
    bg last = a;
    bg ki = int_to_bg(k);
    while(compare(last,ki)!=-1)
    {
        last = sub(last,ki);
    }
    return last;
}
bg absmodn(bg a, bg k)
{
    return a - (a / k) * k;
}
bg div(bg a, int b)
{
    bg c = zero();
    return c;
}
bg absdivn(bg b, bg a)
{
    if(a > b)
        return zero();
    bg c;
    if(a == one())
        return b;
    bg g = b;
    if(a.len == b.len)
    {
        for(int i = 1; i < 10; ++i)
        {
            if((b - (a * int_to_bg(i))) < a)
            {
                return int_to_bg(i);
            }
        }
    }
    for(int i = b.len - a.len; i >= 0; --i)
    {
        bg ds = a;
        if(i != 0)
            moving(ds.d, i, ds.len);
        if(ds < b)
        {
            int s = 0;
            while(ds <= b)
            {
                b = b - ds;
                ++s;
            }
            c.d[i] = s;
        }
        else
        {
            if(b < ds && i == 0)
                break;
            if(b == ds && i == 0)
            {
                c.d[i] = 1;
                break;
            }
        }
    }
    bool zr = false;
    for(int i = g.len; i >= 0; --i)
    {
        if(c.d[i]!=0)
            zr = true;
        if(zr)
        {
        	++c.len;
        }
    }
    return c;
}
bg muln(bg a, bg b)
{
    bg c = absmuln(a,b);
    if(a.flag==b.flag)
        return c;
    else {
        c.flag = false;
        return c;
    }
}
bg divn(bg a, bg b)
{
    if(a == zero())
        return zero();
    bg c = absdivn(a,b);
    if(a.flag==b.flag)
        return c;
    else
    {
        c.flag = false;
        return c;
    }
}
bg modn(bg a, bg b)
{
    bg c = absmodn(a,b);
    if(a.flag==b.flag)
        return c;
    else
    {
        c.flag = false;
        return c;
    }
}
bg a, b;
int main()
{
	
	cin >> a >> b;
	cout << (a/b); 
    return 0;
}
