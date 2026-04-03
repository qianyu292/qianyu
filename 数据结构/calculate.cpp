#include<string>
#include<cctype>
#include<stack>
#include<unordered_map>
using namespace std;

class solution
{
public:
    int calculate(string s)
    {
        unordered_map<int, int>rightindex;
        stack<int>stk;
        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] == '(')
            {
                stk.push(i);
            }
            else if (s[i] == ')')
            {
                rightindex[stk.top()] = i;
                stk.pop();
            }
        }
        return _calculate(s, 0, s.length() - 1, rightindex);
    }
private:
    int _calculate(string s, int start, int end, unordered_map<int, int>& rightIndex)
    {
        stack<int>stk;
        int num = 0;
        char sign = '+';

        for (int i = start; i <= end; ++i)
        {
            char c = s[i];

            if (isdigit(c))
            {
                num = 10 * num + (c - '0');
            }
            else if (c == '(')
            {
                // 递归计算括号内的值，赋值给num
                num = _calculate(s, i + 1, rightIndex[i] - 1, rightIndex);
                i = rightIndex[i];  // 跳过已处理的括号部分
            }

            // 遇到运算符或者到达末尾时，处理上一个运算
            if ((!isdigit(c) && c != ' ') || i == end)
            {
                // 如果是运算符但不是括号，才进行处理
                if (c == '(' || (c == ' ' && i != end))
                    continue;

                int pre;
                switch (sign)
                {
                case '+':
                    stk.push(num);
                    break;
                case '-':
                    stk.push(-num);
                    break;
                case '*':
                    pre = stk.top(); stk.pop();
                    stk.push(pre * num);
                    break;
                case '/':
                    pre = stk.top(); stk.pop();
                    stk.push(pre / num);
                    break;
                }

                // 更新符号
                if (c == '+' || c == '-' || c == '*' || c == '/')
                {
                    sign = c;
                }
                else
                {
                    sign = '+';  // 重置符号
                }
                num = 0;
            }
        }

        // 处理栈中剩余的数字
        int res = 0;
        while (!stk.empty())
        {
            res += stk.top();
            stk.pop();
        }
        return res;
    }
};