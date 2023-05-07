#include <iostream>
#include <bitset>
#include <vector>

using namespace std;
// 极大值
//本次将以摩尔式表示
//比如 A+B A*B !A+!B
//一。识别未知量的数量 65~90  
//二。Y = A*B+A*C+B*C 
//三。列表。  
/*
     A B C AB AC BC Y   
     0 0 0 0  0  0  0
     0 0 1 0  0  0  0
     0 1 0 0  0  0  0
     0 1 1 0  0  1  1
     1 0 0 0  0  0  0
     1 0 1 0  1  0  1
     1 1 0 1  0  0  1
     1 1 1 1  1  1  1
     Y = !ABC+A!BC+AB!C+ABC

*/
const int  MAX = 100;
void Qufan2(int& q)
{
    if (q == 1) q = 0;
    if (q == 0) q = 1;
}
void Select(char p[])
{
    int i = 0;//循环P数组使用
    int r = 0;//循环在Fcounter前提下的列循环，
    int F_Counter = 0;//代表隔间 即有几个式子
    int words = 0;//代表多少个独立的字母。
    char Final[100][30] = { NULL };
    char W[26] = { NULL };
    char Fenbu[50][26] = {NULL};
    while (p[i] != '\0')
    {
        if ('A' <= p[i]&&p[i]<= 'Z')
        {
            int value = 0;
            for (int u = 0; u < words; u++)
            {
                    if (p[i] == W[u]) value = 1;//证明w里面存在一样的字母了
            }
            if (value == 0)
            {
                W[words++] = p[i];
            }
        }
        i++;
    }
    i = 0;
    while (p[i] != '\0')
    {
      
        if (p[i] != '+')
        {
            Fenbu[F_Counter][r] = p[i];
            r++;
        }
        else
        {
            F_Counter++;
            r = 0;
        }
        i++;
    }
    //方入Final里面 我在思考有没有这个必要...先这样吧
    //int levelconter = 0;//记录目前的Final的层数
    //for (i = 0; W[i] != '\0'; i++) Final[levelconter][i] = W[i];
    //for (int l = 0; l < 50; l++)
    //{
    //    for (r = 0; Fenbu[l][r] != '\0'; r++)
    //    {
    //        Final[levelconter][i] = Fenbu[l][r];
    //        i++;
    //    }
    //}
    //000~111

    //char ABC[26] = { NULL };
    //int Shunxu[26] = { NULL };
    //cout << "总共多少个字母";
    //cout << W;
    //cout << endl;
    //cout << "多少个变量" << endl;
    //for (int q = 0; q < F_Counter + 1; q++) cout << Fenbu[q] << " ";
    //cout << endl;
    //cout << "总表" << endl;
    //cout << Final[0];
    //cout << endl;
    int Result = 2 << words - 1;//8
    for (i = 0; i < Result; i++)
    {
        bool Zhangguanzhe = false;
        //最好是每一列都自动生成，每一行自动计算。 不能用二进制数组...
        bitset<8> bits(i);
        //bits[0]代表C bits[1]代表B bits[2]代表A
        //由 words决定几位。
        int max = words - 1;
        vector<int> Second_True;
        for (int counter = 0; counter <= F_Counter; counter++)//逐层击破Fenbu 每层可能遇到*和！ 必须全部突破。
        //!A*B|| A*!C ...
        {
            int Temp = 1;
            vector<int> First_True;
            for (int y = 0; Fenbu[counter][y] != '\0'; y++)//遍历conter行的字符串 代表一个。
            {
                int m = 0;
                int a = 0;
                
                int recorder = 0;
                bool flag = false;
                if (Fenbu[counter][y] == '!')
                {
                    flag = true;
                    y++;
                }
                if (Fenbu[counter][y] == '*') y++;
                for (; m<words; m++)//W[0~words] 对应 bits的[0~words]位 前提是没有！
                //举个例子 W = A B C 则若遇到A 记为 0 则对应0 0 0 的最后一位 那么无论以后怎么样， 最后一位都是A。这就足够了。
                {
                    if (W[m] == Fenbu[counter][y])
                    {
                        recorder = m;
                        break;
                    }
                   
                }
                //此时，找到了 A 对应的真值。(1个）
                 a = bits[recorder];//0
                 if (flag) Qufan2(a);

                //cout << a;
                First_True.push_back(a);
            }
            for (vector<int>::iterator it = First_True.begin(); it != First_True.end(); it++) {
               // cout << *it << " ";
               Temp *= *it;
            }
            Second_True.push_back(Temp);
        }
        for (vector<int>::iterator it = Second_True.begin(); it != Second_True.end(); it++) {
            //cout << *it << " ";
            if (*it == 1)
            {
                for (int u = 0; u < words; u++)
                {
                    if (bits[u] == 1)
                    {
                        cout << W[u];
                        if (u != words - 1) cout << "*";
                    }
                    else if (bits[u] == 0)
                    {
                        cout << "!" << W[u];
                        if (u != words - 1) cout << "*";
                    }
                }
                if(bits.to_ulong()!=Result-1) cout << "+";
                break;
            }
        }
        //cout << endl;
    }
}

int main() {
    char Input[MAX];
    cin >> Input;
    Select(Input);
}