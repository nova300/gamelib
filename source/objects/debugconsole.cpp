#include "objects/commandproc.h"
#include "objects/debugconsole.h"
#include <raylib.h>
#include <iostream>
#include "utils.h"
#include <string>
#include <sstream>
#include "core/programstack.h"

#include "games/cmd.h"
#include "games/test.h"

#include <map>
#include <string>

template <class T> void* constructor() { return (void*)new T(); }

struct factory
{
    typedef void *(*constructor_t)();
    typedef std::map<std::string, constructor_t> map_type;
    map_type m_classes;
    std::string classlist;

    template <class T>
    void register_class(std::string const &n)
    {
        static_assert(std::is_base_of<Program, T>::value, "T is not a program");
        m_classes.insert(std::make_pair(n, &constructor<T>));
        classlist.append(n);
        classlist.append("\n");
    }

    void *construct(std::string const &n)
    {
        map_type::iterator i = m_classes.find(n);
        if (i == m_classes.end())
            return 0; // or throw or whatever you want
        return i->second();
    }

    bool exists(std::string const &n)
    {
        map_type::iterator i = m_classes.find(n);
        if (i == m_classes.end())
            return false;
        return true;
    }
};

factory g_factory;

#define REGISTER_CLASS(n) g_factory.register_class<n>(#n)

void DebugConsole::RegisterPrograms()
{
    REGISTER_CLASS(Terminal);
    REGISTER_CLASS(TestProgram);
}

std::string DebugConsole::RunCommand(std::string command, Program *prg)
{
    std::stringstream output;
    std::vector<std::string> args = splitstring(command, " ");
    switch(hash(convertToLowercase(args[0]).c_str()))
    {
        case hash("help"):
        {
            output << "Commands:\nHELP\nVER\nSTAT\nBOOT\nLIST\nCRC\nHASH\n";
            break;
        }
        case hash("ver"):
        {
            output << "LIBG V.2\n";
            break;
        }
        case hash("stat"):
        {
            output << "--------------------------------\nSystem Statistics:\nTIME: " << GetTime() << "\nPROG: " << prg->GetStack()->ProgramsRunning() << "\nPROG2: " << prg->GetStack()->ProgramsCapacity() <<"\n--------------------------------\n";
            break;
        }
        case hash("boot"):
        {
            if (args.size() < 2)
            {
                output << "Too few arguments\n";
            }
            else
            {
                if (!args[1].empty())
                {
                    if (g_factory.exists(args[1]))
                    {
                        prg->GetStack()->Switch((Program *)g_factory.construct(args[1]));
                        break;
                    }
                    else
                    {
                        output << "Program " << args[1] << " not found\n";
                        break;
                    }
                }
            }
            output << "USAGE: BOOT <ProgramName>\nSwitches to the specified program.\nFor a list of programs type 'LIST'.\n";
            break;
        }
        case hash("list"):
        {
            output << "**************************\nREGISTERED PROGRAMS:\n" << g_factory.classlist << "\n**************************\n";
            break;
        }
        case hash("crc"):
        {
            if (args.size() < 2) break;
            if (!args[1].empty())
            {
                const char* value = args[1].data();
                int size = args[1].size();
                output << value << "     " << size << " bytes" << std::endl;
                unsigned short crcv = crc(value, size);
                output << "crc: " << crcv << std::endl;
            }
            break;
        }
        case hash("hash"):
        {
            if (args.size() < 2) break;
            if (!args[1].empty())
            {
                const char* value = args[1].data();
                int size = args[1].size();
                output << value << "     " << size << " bytes" << std::endl;
                unsigned short crcv = hash(value);
                output << "hash: " << crcv << std::endl;
            }
            break;
        }
        case hash("exit"):
        {   
            output << "Goodbye!\n";
            prg->GetStack()->Reload();
            break;
        }
        default:
        {
            output << args[0] << " is not a command.\n";
            break;
        }
    }

    output << std::endl << CmdPrompt();

    return output.str();
}