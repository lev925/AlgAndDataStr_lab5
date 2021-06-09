#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
int Priority(string c)
 
{
// Функция Priority – приоритет операции
// Вход:  символ операции
// Выход: приоритет или 100, если не операция
    switch (c[0]) {
    case '+': case '-':
        return 1;
    case '*': case '/':
        return 2;
    }
    return 100;
}
 
int LastOperation(vector <string> Expr, int first, int last)
 
{
    // Функция LastOperation – номер последней операции
    // Вход:  строка, номера первого и последнего
    //        символов рассматриваемой части
    // Выход: номер символа - последней операции
    int MinPrt, i, k=-1, prt;
    MinPrt = 100;
    for (i = first; i < last; i++) {
        prt = Priority(Expr[i]);
        if (prt <= MinPrt) {
            MinPrt = prt;
            k = i;
        }
    }
    return k;
}
 
typedef string Elem;
 
struct BinNode {
    Elem elem;
    BinNode* lc, * rc;
};
 
float CalcTree(BinNode* root)
{
// Функция CalcTree – вычисление по дереву
// Вход:  адрес дерева
// Выход: значение выражения
    float num1, num2;
    if (!root->lc)
    {
        return stof(root->elem);
    }
        
    num1 = CalcTree(root->lc);
    num2 = CalcTree(root->rc);
    switch (root->elem[0]) {
    case '+': return  num1 + num2;
    case '-': return  num1 - num2;
    case '*': return  num1 * num2;
    case '/': return  num1 / num2;
    }
    return 32767;
}
 
BinNode* mkNumberNode(string c)
{
    BinNode *root = new BinNode;
    root->elem = c;
    root->lc = NULL;
    root->rc = NULL;
    return root;
}
vector<string> pars(string s, vector<string> str)
{
// Функция pars – Разделяет операторы и числа
// Вход:  строка и вектор для записи
// Выход: вектор
    int k, min = INT32_MAX;
    char oper[] = { '+','-','*','/' };
    for (auto c : oper)
    {
 
        k = s.find(c);
        if (k < min && k != -1)min = k;
    }
    if (min != INT32_MAX)
    {
        str.push_back(s.substr(0, min));
        str.push_back(s.substr(min, 1));
        return pars(s.substr(min + 1, s.length() - min), str);
    }
    str.push_back(s);
    return str;
}
 
BinNode* MakeTree(vector<string> Expr, int first, int last)
{
// Функция MakeTree – построение дерева
// Вход:  вектор с париснгом данных, номера первого и последнего
// Выход: адрес построенного дерева
    BinNode* root;
    int k;
    if (first == last)
        return mkNumberNode(Expr[first]);
    k = LastOperation(Expr, first, last);
    root = new BinNode;
    root->elem = Expr[k];
    root->lc = MakeTree(Expr, first, k - 1);
    root->rc = MakeTree(Expr, k + 1, last);
    return root;
}
 
BinNode* MakeTree(string Expr, int first, int last)
{
// Функция MakeTree – построение дерева
// Вход:  строка, номера первого и последнего
// Выход: адрес построенного дерева
    vector <string> str=pars(Expr,str);
    return MakeTree(str, 0, str.size()-1);
}
 
 
 
int main()
{
    setlocale(LC_ALL, "ru");
    string s;
    BinNode* MyTreeRoot;
    printf("Введите выражение > ");
    getline(cin,s);
    MyTreeRoot = MakeTree(s, 0, s.length() - 1);
    cout<<CalcTree(MyTreeRoot);
    getchar();
 
}
