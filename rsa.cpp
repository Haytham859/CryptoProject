#include "rsa.h"
#include <QStringList>

bool isPrime(int n) { if(n<=1) return false; if(n<=3) return true; for(int i=2;i*i<=n;i++) if(n%i==0) return false; return true;}
int gcd(int a,int b){while(b){int t=b;b=a%b;a=t;} return a;}
int modInverse(int e,int phi){int t=0,newt=1,r=phi,newr=e; while(newr!=0){int q=r/newr; int tmp=t;t=newt;newt=tmp-q*newt; tmp=r;r=newr;newr=tmp-q*newr;} if(r>1) return -1; if(t<0) t+=phi; return t;}
std::tuple<int,int,int> generateRSAKeys(){
    int primes[]={101,103,107,109,113,127,131,137,139};
    int p=primes[QRandomGenerator::global()->bounded(0,9)];
    int q=primes[QRandomGenerator::global()->bounded(0,9)];
    while(q==p) q=primes[QRandomGenerator::global()->bounded(0,9)];
    int n=p*q;
    int phi=(p-1)*(q-1);
    int e=3; while(gcd(e,phi)!=1) e+=2;
    int d=modInverse(e,phi);
    return std::make_tuple(n,e,d);
}

// Simple character-based RSA for demonstration
QString rsaEncrypt(const QString &text,const QString &n_e,const QString &d_e){
    QString temp = n_e; // عمل نسخة قبل التعديل
    QStringList parts=temp.remove('(').remove(')').split(',');
    int n=parts[0].toInt(); int e=parts[1].toInt();
    QString result;
    for(QChar c:text){
        int m=c.unicode();
        int cipher=1;
        for(int i=0;i<e;i++) cipher=(cipher*m)%n;
        result+=QString::number(cipher)+' ';
    }
    return result;
}

QString rsaDecrypt(const QString &text,const QString &n_d,const QString &e_d){
    QString temp = n_d; // عمل نسخة قبل التعديل
    QStringList parts=temp.remove('(').remove(')').split(',');
    int n=parts[0].toInt(); int d=parts[1].toInt();
    QStringList nums=text.split(' ',Qt::SkipEmptyParts);
    QString result;
    for(QString num:nums){
        int c=num.toInt();
        int m=1;
        for(int i=0;i<d;i++) m=(m*c)%n;
        result+=QChar(m);
    }
    return result;
}
