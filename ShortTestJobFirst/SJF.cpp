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
        cout << "��" << name << "       ��" << arrivalTime << "       ��" << runTime <<"       ��" << endl;
    };

private:
    string name;
    int arrivalTime;
    int runTime;
    process* next;
    process* TemporaryNext;//���ڹ�����ʱ�������ʱָ�룻
};


class processLinkList
{
public:
    processLinkList(process* h = 0, process* l = 0, int n = 0) :head(h), last(l), num(n) {}

    void InitNode();
    void SJFPrint();//���ն̽��������㷨����������б�
    void Show(process* next);
    process* GetHead();
    //���������㷨�������������ʱ����ĺ���


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

    cout << "��ʼ���ݣ�" << endl;
    cout << "�ڵ�����" << num << endl;
    
    cout << "�����������Щ��������Щ���������" << endl;
    cout << "��������  ������ʱ�䩦����ʱ�䩦" << endl;
    Show(head);
}

void processLinkList::Show(process* node)
{
    cout << "�����������੤�������੤��������" << endl;
    node->Show();
    if (node->GetNext() == 0)
    {
        cout << "�����������ة��������ة���������" << endl;
        cout << endl << "������" << endl;
    }
    else
        Show(node->GetNext());
}

process* processLinkList::GetHead()
{
    return head;
}

//Ϊ�˱���ԭʼ���ݣ�ͬʱ������������̣�������ʱ�������һ���ڵ����ʱ������ɾ���˽ڵ㣬
void processLinkList::SJFPrint()
{
    process* ThisNode;//���ҹ��̵�ǰ�ڵ�
    process* PriorNode;//���ҹ���ǰһ���ڵ�
    process* MinRunTimeNode;//��̽��̽ڵ� 
    process* PMNode;//��̽��̽ڵ�ǰһ���ڵ�
    process* TemporaryHead;//��ʱ����ͷ���

    int NowTime = 0;

    TemporaryHead = head;
    PMNode = MinRunTimeNode = PriorNode = ThisNode= nullptr;
    cout << "SJF�̽������ȣ�" << endl;
    cout << "�����������Щ��������Щ��������Щ���������" << endl;
    cout << "��������  ������ʱ�䩦����ʱ�䩦����ʱ�䩦" << endl;
    //cout << "�����������੤�������੤�������੤��������" << endl;

    //����������̱� ������ʱ����Ϊ��ʱ��������
    while (TemporaryHead != nullptr)
    {
        MinRunTimeNode = nullptr;
        ThisNode = TemporaryHead;

        //������ʱ�����ҵ���ǰʱ������̽���
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

        //��ǰʱ�����Ƿ��н��̵���Ƿ���ҵ���
        if (MinRunTimeNode == nullptr)
            NowTime++;
        else
        {
            NowTime = NowTime + MinRunTimeNode->GetRunTime();
            cout << "�����������੤�������੤�������੤��������" << endl;
            cout << "��" << MinRunTimeNode->GetName() << "       ��" << MinRunTimeNode->GetArrivalTime() << "       ��" << MinRunTimeNode->GetRunTime() << "       ��" << NowTime << "       ��" << endl;
        
            //��ʱ����ɾ���˽ڵ�
            if (MinRunTimeNode == TemporaryHead)
                TemporaryHead = TemporaryHead->GetTemporaryNext();
            else
                PMNode->SetTemporaryNext(MinRunTimeNode->GetTemporaryNext());
        }

        
    }
    cout << "�����������ة��������ة��������ة���������" << endl;
    
}


int main()
{
    int i = 9;
    processLinkList PL1;
    while (i != 0) {
        PL1.InitNode();
        cout << "���ټ��������롤0:";
        cin >> i;
    }
    PL1.Show(PL1.GetHead());
    PL1.SJFPrint();
    return 0;

}