#include "customRSA.h"
#include <QMessageBox>
#include <QStringList>

// نسخ static خاصة بالملف ده فقط (لن تتعارض مع rsa.cpp)
static bool isPrime(int n) { if(n<=1) return false; if(n<=3) return true; for(int i=2;i*i<=n;i++) if(n%i==0) return false; return true;}
static int gcd(int a,int b){while(b){int t=b;b=a%b;a=t;} return a;}
static int modInverse(int e,int phi){int t=0,newt=1,r=phi,newr=e; while(newr!=0){int q=r/newr; int tmp=t;t=newt;newt=tmp-q*newt; tmp=r;r=newr;newr=tmp-q*newr;} if(r>1) return -1; if(t<0) t+=phi; return t;}

static long long power(long long base, long long exp, long long mod) {
    long long res = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        exp = exp >> 1; base = (base * base) % mod;
    }
    return res;
}

static int charToNum(QChar c) { return c.toUpper().unicode() - 'A'; }
static QChar numToChar(int num) { return QChar(num + 'A'); }


QString rsaEncryptCustom(const QString &text, const QString &keyP_str, const QString &keyQ_str){
    bool okP, okQ;
    int p = keyP_str.toInt(&okP);
    int q = keyQ_str.toInt(&okQ);

    if (!okP || !okQ || !isPrime(p) || !isPrime(q) || p == q) {
        QMessageBox::critical(nullptr, "Error", "P and Q must be distinct prime numbers!");
        return "";
    }

    long long n = (long long)p * q;
    int phi = (p - 1) * (q - 1);

    int e = 3;
    while(gcd(e, phi) != 1) e += 2;

    int d = modInverse(e, phi);

    QString cipherText;
    for(QChar c : text){
        if (c.isLetter()) {
            long long m = charToNum(c);
            long long cipher = power(m, e, n);
            cipherText += QString::number(cipher) + ' ';
        } else {
            cipherText += c;
        }
    }

    QString report;
    report += "=== RSA Calculation Report ===\n";
    report += QString("P = %1,  Q = %2\n").arg(p).arg(q);
    report += QString("N = P * Q = %1\n").arg(n);
    report += QString("Phi(N) = (P-1)*(Q-1) = %1\n").arg(phi);
    report += QString("Public Key (e) = %1\n").arg(e);
    report += QString("Private Key (d) = %1\n").arg(d); // مهم جداً يظهر
    report += "----------------------------\n";
    report += "Encrypted Result:\n";
    report += cipherText;

    return report;
}

QString rsaDecryptCustom(const QString &text, const QString &keyP_str, const QString &keyQ_str){
    bool okP, okQ;
    int p = keyP_str.toInt(&okP);
    int q = keyQ_str.toInt(&okQ);

    if (!okP || !okQ || !isPrime(p) || !isPrime(q) || p == q) {
        QMessageBox::critical(nullptr, "Error", "P and Q must be distinct prime numbers!");
        return "";
    }

    long long n = (long long)p * q;
    int phi = (p - 1) * (q - 1);

    int e = 3;
    while(gcd(e, phi) != 1) e += 2;
    int d = modInverse(e, phi);

    if (d == -1) {
        QMessageBox::critical(nullptr, "Error", "Private exponent 'd' does not exist!");
        return "";
    }

    QStringList nums = text.split(' ', Qt::SkipEmptyParts);
    QString plainText;

    for(QString num:nums){
        bool ok;
        long long c = num.toLongLong(&ok);
        if (!ok) continue;

        long long m = power(c, d, n);
        plainText += numToChar(static_cast<int>(m));
    }

    QString report;
    report += "=== RSA Decryption Details ===\n";
    report += QString("Calculated N = %1\n").arg(n);
    report += QString("Calculated Phi = %1\n").arg(phi);
    report += QString("Using Private Key (d) = %1\n").arg(d);
    report += "----------------------------\n";
    report += "Decrypted Text:\n";
    report += plainText;

    return report;
}
