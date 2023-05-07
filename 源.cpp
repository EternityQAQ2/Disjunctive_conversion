#include <iostream>
#include <bitset>
#include <vector>

using namespace std;
// ����ֵ
//���ν���Ħ��ʽ��ʾ
//���� A+B A*B !A+!B
//һ��ʶ��δ֪�������� 65~90  
//����Y = A*B+A*C+B*C 
//�����б�  
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
    int i = 0;//ѭ��P����ʹ��
    int r = 0;//ѭ����Fcounterǰ���µ���ѭ����
    int F_Counter = 0;//������� ���м���ʽ��
    int words = 0;//������ٸ���������ĸ��
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
                    if (p[i] == W[u]) value = 1;//֤��w�������һ������ĸ��
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
    //����Final���� ����˼����û�������Ҫ...��������
    //int levelconter = 0;//��¼Ŀǰ��Final�Ĳ���
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
    //cout << "�ܹ����ٸ���ĸ";
    //cout << W;
    //cout << endl;
    //cout << "���ٸ�����" << endl;
    //for (int q = 0; q < F_Counter + 1; q++) cout << Fenbu[q] << " ";
    //cout << endl;
    //cout << "�ܱ�" << endl;
    //cout << Final[0];
    //cout << endl;
    int Result = 2 << words - 1;//8
    for (i = 0; i < Result; i++)
    {
        bool Zhangguanzhe = false;
        //�����ÿһ�ж��Զ����ɣ�ÿһ���Զ����㡣 �����ö���������...
        bitset<8> bits(i);
        //bits[0]����C bits[1]����B bits[2]����A
        //�� words������λ��
        int max = words - 1;
        vector<int> Second_True;
        for (int counter = 0; counter <= F_Counter; counter++)//������Fenbu ÿ���������*�ͣ� ����ȫ��ͻ�ơ�
        //!A*B|| A*!C ...
        {
            int Temp = 1;
            vector<int> First_True;
            for (int y = 0; Fenbu[counter][y] != '\0'; y++)//����conter�е��ַ��� ����һ����
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
                for (; m<words; m++)//W[0~words] ��Ӧ bits��[0~words]λ ǰ����û�У�
                //�ٸ����� W = A B C ��������A ��Ϊ 0 ���Ӧ0 0 0 �����һλ ��ô�����Ժ���ô���� ���һλ����A������㹻�ˡ�
                {
                    if (W[m] == Fenbu[counter][y])
                    {
                        recorder = m;
                        break;
                    }
                   
                }
                //��ʱ���ҵ��� A ��Ӧ����ֵ��(1����
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