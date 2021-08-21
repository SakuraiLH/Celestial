#include "GlobalVariable.h"

int ReadNotes(string &plain, bool &HasPermission,GroupMessage &m)
{
    if (plain.length() < 6){
        return 0;
    }
    if (plain.substr(0,6) == ".notes")
    {
        if (plain.length() <= 6)
        {
            // 从文件读取笔记列表
            int GroupNumTemp = (int64_t)m.Sender.Group.GID;
            const string ReadLocation = "./notes/" + to_string(GroupNumTemp) + "_list.txt";
            ifstream inputnotes;
            inputnotes.open(ReadLocation);
            string note_number[10] = {
                "", "", "", "", "", "", "", "", "", ""
            };

            int Note_Range = 0;
            for (int i = 0; i <= 9; i ++)
            {
                inputnotes >> note_number[i];
                if (note_number[i] == "")
                {
                    Note_Range = i;
                    break;
                }
            }
            
            // 如果本群尚未创建列表
            if (note_number[0] == "")
            {
                int notedir;
                notedir = mkdir("./notes", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                ofstream CreateNewNoteList;
                CreateNewNoteList.open(ReadLocation);
                CreateNewNoteList << "";
                CreateNewNoteList.close();
                m.Reply(MessageChain().Plain(Celestial_Notes_New));
                return 0;
            }
            inputnotes.close();

            string note_list = Celestial_Notes_Header;
            for (int i = 0; i < Note_Range; i ++)
            {
                string tempNum = to_string(i + 1);
                note_list = note_list + '\n' + tempNum + '.' + ' ' + note_number[i];
            }
            m.Reply(MessageChain().Plain(note_list));
            return 0;
        }

        // 放到这里，免得substr又冒出来exception ".mute"

        string OrderedNote = plain.substr(7);

        // 从文件读取笔记列表
        int GroupNumTemp = (int64_t)m.Sender.Group.GID;

        // 获取笔记列表存放位置
        const string ReadLocation = "./notes/" + to_string(GroupNumTemp) + "_list.txt";
        ifstream inputnotes;

        // 打开文件输入流
        inputnotes.open(ReadLocation);

        int NoteReadTarget = 11;

        // 共10个的笔记的title的初始化
        string note_number[10] = {
            "", "", "", "", "", "", "", "", "", ""
        };        

        for (int i = 0; i <= 9; i ++)
        {
            // 从 list -> Note[]
            inputnotes >> note_number[i];

            // 调试 cout << "FindSequence: " << note_number[i] << " Number:" << i << " Requested Value: " << OrderedNote << endl;
            // 若寻找到目标笔记则 break;
            if (note_number[i] == OrderedNote)
            {
                NoteReadTarget = i;
                break;
            }
        }

        // 关闭 输入流
        inputnotes.close();

        // 如果本群尚未创建列表
        if (note_number[0] == "")
        {
            int notedir;
            notedir = mkdir("./notes", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            ofstream CreateNewNoteList;
            CreateNewNoteList.open(ReadLocation);
            CreateNewNoteList << "";
            CreateNewNoteList.close();
            m.Reply(MessageChain().Plain(Celestial_Notes_Not_Found));
            return 0;
        }
        
        // 没有寻找到目标
        if (NoteReadTarget == 11)
        {
            m.Reply(MessageChain().Plain(Celestial_Notes_Not_Found));
            return 0;
        }

        // 找到目标

        ifstream Specified_Notes;

        // 笔记具体位置读取
        const string ReadSpecifiedLocation = "./notes/" + to_string(GroupNumTemp) + "_" + to_string(NoteReadTarget) + ".txt";
        Specified_Notes.open(ReadSpecifiedLocation);

        stringstream buffer;
        buffer << Specified_Notes.rdbuf();

        string contents(buffer.str());

        m.Reply(MessageChain().Plain(contents.substr(0,contents.length() - 1))); 
        Specified_Notes.close();

        return 0;
    }
    return 0;
}

int SaveNotes(string &plain, bool &HasPermission, GroupMessage &m)
{
    if (plain.length() < 5){
        return 0;
    }

    if (plain.substr(0,5) == ".save")
    {
        // save function
    }
    return 0;
}
/*
void ReadNotes(Cyan::GID_t &GroupNum, string OrderedNote, GroupMessage &m)
{
    int GroupNumTemp = (int64_t)GroupNum;
    string ReadLocation = "./notes/" + to_string(GroupNumTemp) + "_Sequence.txt";
    ifstream inputnum;
    inputnum.open(ReadLocation);
    string note[10];
    int target = 11;

    for (int i = 0; i < 10; i ++)
    {
        inputnum >> note[i];
        if (OrderedNote == note[i])
        {
            target = i;
        }
    }
    inputnum.close();

    if (target == 11){
        m.Reply(MessageChain().Plain(Celestial_Notes_Not_Found));
        return;
    }

    ReadLocation = "./notes/" + to_string(GroupNumTemp) + ".txt";
    inputnum.open(ReadLocation);
    
    inputnum.close();
}

void SaveNotes(Cyan::GID_t &GroupNum, string OrderedNote)
{




}

void DeleteNotes(Cyan::GID_t &GroupNum, string OrderedNote)
{


}
*/