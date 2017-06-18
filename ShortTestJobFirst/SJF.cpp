#include <iostream>
#include <string>

using namespace std;

class process
{
public:
    process(string n = "process", int a = 0, int r = 0, int e = 0, process* ne = 0, process* ne1 = 0) :name(n), arrivalTime(a), runTime(r), next(ne), TemporaryNext(ne1) {  }

    inline string GetName()
    {
        return name;
    };
    inline int GetArrivalTime()
    {
        return arrivalTime;
    };
    inline int GetRunTime()
    {
        return runTime;
    };
    inline process* GetNext()
    {
        return next;
    };
    inline void SetNext(process* n)
    {
        next = n;
    }
    inline process* GetTemporaryNext()
    {
        return TemporaryNext;
    };
    inline void SetTemporaryNext(process* n)
    {
        TemporaryNext = n;
    }
    inline void Show()
    {
        cout << "│" << name << "       │" << arrivalTime << "       │" << runTime <<"       │" << endl;
    };

private:
    string name;
    int arrivalTime;
    int runTime;
    process* next;
    process* TemporaryNext;//用于构建临时链表的临时指针；
};


class processLinkList
{
public:
    processLinkList(process* h = 0, process* l = 0, int n = 0) :head(h), last(l), num(n) {}

    void InitNode();
    void SJFPrint();//按照短进程优先算法输出进程运行表
    void Show(process* next);
    process* GetHead();
    //便于其他算法排序，添加重做临时链表的函数


private:
    process* head;
    process* last;
    int num;
};

void processLinkList::InitNode()
{
    string name;
    int aT;
    int rT;
    cin >> name >> aT >> rT;

    if (head == 0)
    {
        head = new process(name, aT, rT);
        last = head;
    }
    else
    {
        last->SetNext(new process(name, aT, rT));
        last->SetTemporaryNext(last->GetNext());
        last = last->GetNext();
    }
    num++;

    cout << "初始数据：" << endl;
    cout << "节点数：" << num << endl;
    
    cout << "┌────┬────┬────┐" << endl;
    cout << "│进程名  │到达时间│运行时间│" << endl;
    Show(head);
}

void processLinkList::Show(process* node)
{
    cout << "├────┼────┼────┤" << endl;
    node->Show();
    if (node->GetNext() == 0)
    {
        cout << "└────┴────┴────┘" << endl;
        cout << endl << "输出完成" << endl;
    }
    else
        Show(node->GetNext());
}

process* processLinkList::GetHead()
{
    return head;
}

//为了保存原始数据，同时简化排序输出过程，创建临时链表，输出一个节点后临时链表中删除此节点，
void processLinkList::SJFPrint()
{
    process* ThisNode;//查找过程当前节点
    process* PriorNode;//查找过程前一个节点
    process* MinRunTimeNode;//最短进程节点 
    process* PMNode;//最短进程节点前一个节点
    process* TemporaryHead;//临时链表头结点

    int NowTime = 0;

    TemporaryHead = head;
    PMNode = MinRunTimeNode = PriorNode = ThisNode= nullptr;
    cout << "SJF短进程优先：" << endl;
    cout << "┌────┬────┬────┬────┐" << endl;
    cout << "│进程名  │到达时间│运行时间│结束时间│" << endl;
    //cout << "├────┼────┼────┼────┤" << endl;

    //排序输出进程表 ，当临时链表为空时，输出完成
    while (TemporaryHead != nullptr)
    {
        MinRunTimeNode = nullptr;
        ThisNode = TemporaryHead;

        //遍历临时链表，找到当前时刻内最短进程
        do
        {
            if (ThisNode->GetArrivalTime() <= NowTime)
            {
                if (MinRunTimeNode == nullptr||ThisNode->GetRunTime() < MinRunTimeNode->GetRunTime())
                {
                    MinRunTimeNode = ThisNode;
                    PMNode = PriorNode;
                }
            }
            PriorNode = ThisNode;
            ThisNode = ThisNode->GetTemporaryNext();
        } while (ThisNode!= nullptr);

        //当前时刻内是否有进程到达（是否查找到）
        if (MinRunTimeNode == nullptr)
            NowTime++;
        else
        {
            NowTime = NowTime + MinRunTimeNode->GetRunTime();
            cout << "├────┼────┼────┼────┤" << endl;
            cout << "│" << MinRunTimeNode->GetName() << "       │" << MinRunTimeNode->GetArrivalTime() << "       │" << MinRunTimeNode->GetRunTime() << "       │" << NowTime << "       │" << endl;
        
            //临时链表删除此节点
            if (MinRunTimeNode == TemporaryHead)
                TemporaryHead = TemporaryHead->GetTemporaryNext();
            else
                PMNode->SetTemporaryNext(MinRunTimeNode->GetTemporaryNext());
        }

        
    }
    cout << "└────┴────┴────┴────┘" << endl;
    
}


int main()
{
    int i = 9;
    processLinkList PL1;
    while (i != 0) {
        PL1.InitNode();
        cout << "不再继续请输入·0:";
        cin >> i;
    }
    PL1.Show(PL1.GetHead());
    PL1.SJFPrint();
    return 0;

}