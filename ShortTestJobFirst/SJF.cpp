#include <iostream>
#include <string>

using namespace std;

class process
{
public:
    process(string n = "process", int a = 0, int r = 0, int e = 0, process* ne = 0, process* ne1 = 0) :name(n), arrivalTime(a), runTime(r), next(ne), next1(ne1) {  }

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
    inline process* GetNext1()
    {
        return next1;
    };
    inline void SetNext1(process* n)
    {
        next1 = n;
    }
    inline void Show()
    {
        cout << "name:" << name << "\t" << "arrival time:" << arrivalTime << "\t" << "run time:" << runTime << endl;
    };

private:
    string name;
    int arrivalTime;
    int runTime;
    process* next;
    process* next1;



};


class processLinkList
{
public:
    processLinkList(process* h = 0, process* l = 0, int n = 0) :head(h), last(l), num(n) {}

    void InitNode();
    void Stro(process* next);
    void Show(process* next);
    process* GetHead();

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
        last->SetNext1(last->GetNext());
        last = last->GetNext();
    }
    num++;
    cout << num << endl;
    Show(head);
}

void processLinkList::Show(process* node)
{
    node->Show();
    if (node->GetNext() == 0)
        cout << endl << "输出完成" << endl;
    else
        Show(node->GetNext());
}
void processLinkList::Stro(process* LinkList)
{
    process* ThisNode;
    process* LastNode;//L用于保存上一个节点
    process* MinRunTimeNode;//最短进程节点 
    int NowTime = 0;
    MinRunTimeNode = LastNode = ThisNode = LinkList;


    cout << "---------------------------------------------------" << endl;
    cout << "进程名\t到达时间\t运行时间\t结束时间" << endl;
    cout << "---------------------------------------------------" << endl;

    while (LinkList->GetNext1() != 0)
    {
        MinRunTimeNode = 0;
        while (ThisNode->GetNext1() != 0)
        {
            if (ThisNode->GetArrivalTime() <= NowTime)
            {
                if (ThisNode->GetRunTime() < MinRunTimeNode->GetRunTime())
                {
                    MinRunTimeNode = ThisNode;
                    ThisNode = ThisNode->GetNext1();

                }
            }
        }
        if (ThisNode == LastNode)
            NowTime++;
        else
        {
            ThisNode->Show();
            NowTime = NowTime + ThisNode->GetRunTime();
            LastNode->SetNext1(ThisNode->GetNext1());
        }
    }
    cout << "-----------------------------------";
    /*else
    {
    if (NODE->GetRunTime()<minRT)
    {
    minAT = NODE;
    minRT = NODE->GetRunTime();
    }
    }
    }//	cout <<NODE->GetName() <<"\t" <<NODE->GetArrivalTime <<"\t" <<NODE->GetRunTime() <<"\t" <<NowTime <<endl;*/
}

process* processLinkList::GetHead()
{
    return head;
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
    PL1.Stro(PL1.GetHead());

    return 0;

}