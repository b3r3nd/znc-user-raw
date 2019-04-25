#include "Chan.h"
#include "User.h"
#include "Modules.h"

class CUserRawMod : public CModule {
public:
        MODCONSTRUCTOR(CUserRawMod) {}

        virtual bool OnBoot() {
                return true;
        }

        virtual EModRet OnStatusCommand(CString& sCommand) {
                if (sCommand.Equals("user_raw")) {
                        PutModule("loadmod user_raw");
                        return HALT;
                }

                return CONTINUE;
        }

        virtual void OnModCommand(const CString& sCommand) {
                if(sCommand.Equals("help")) {
                        CTable Table;
                        Table.AddColumn("Command");
                        Table.AddColumn("Description");
                        Table.AddRow();
                        Table.SetCell("Command", "sucks");
                        Table.SetCell("Description", "prints appel in developers channel");
                        Table.AddRow();
                        Table.SetCell("Command", "help");
                        Table.SetCell("Description", "Prints this help table");
                        Table.AddRow();
                        Table.SetCell("Command", "raws");
                        Table.SetCell("Description", "Shows the raws and usage");
                        PutModule(Table);
                }
                if(sCommand.Equals("raws")) {
                        CTable Table;
                        Table.AddColumn("Command");
                        Table.AddColumn("Usage");
                        Table.AddRow();
                        Table.SetCell("Command", "raw");
                        Table.SetCell("Usage", "Any raw usage, use /raw help");
                        Table.AddRow();
                        Table.SetCell("Command", "say");
                        Table.SetCell("Usage", "say #yourchannel <text>");
                        Table.AddRow();
                        Table.SetCell("Command", "action");
                        Table.SetCell("Usage", "action #yourchannel <action>");
                        Table.AddRow();
                        Table.AddRow();
                        Table.SetCell("Command", "nick");
                        Table.SetCell("Usage", "nick <newnick>");
                        Table.AddRow();
                        Table.SetCell("Command", "join");
                        Table.SetCell("Usage", "join #yourchannel");
                        Table.AddRow();
                        Table.SetCell("Command", "part");
                        Table.SetCell("Usage", "part #yourchannel");
                        Table.AddRow();
                        Table.SetCell("Command", "topic");
                        Table.SetCell("Usage", "topic #yourchannel <yourtopic>");
                        Table.AddRow();
                        Table.SetCell("Command", "mode");
                        Table.SetCell("Usage", "mode #yourchannel +-modes");
                        Table.AddRow();
                        Table.SetCell("Command", "kick");
                        Table.SetCell("Usage", "kick #yourchannel <kicknick>");
                        Table.AddRow();
                        Table.SetCell("Command", "auth");
                        Table.SetCell("Usage", "auth <authname> <password>");
                        PutModule(Table);
                }
        }
        virtual EModRet OnPrivMsg(CNick& Nick, CString& sMessage) {
                const CString& sCommand = sMessage.Token(0);
                if (Nick.GetNick().Equals("berend")) {
                        if (sCommand.Equals("say")) {
                                if (sMessage.Token(2).empty()) {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Usage: say #yourchannel <yourmessage>");
                                }
                                else {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Done.");
                                        PutIRC("PRIVMSG " + sMessage.Token(1) + " :" + sMessage.Token(2, true));
                                        PutModule(sMessage);
                                }
                        } else if (sCommand.Equals("raw")) {
                                PutIRC("PRIVMSG " + Nick.GetNick() + " :Done.");
                                PutIRC(sMessage.Token(1, true));
                                PutModule(sMessage);
                        } else if (sCommand.Equals("join")) {
                                if (sMessage.Token(1).empty()) {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Usage: join #yourchannel");
                                }
                                else {
                                        PutIRC("Done.");
                                        PutIRC("JOIN " + sMessage.Token(1));
                                        PutModule(sMessage);
                                }
                        } else if (sCommand.Equals("part")) {
                                if (sMessage.Token(1).empty()) {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Usage: part #yourchannel");
                                }
                                else {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Done.");
                                        PutIRC("PART " + sMessage.Token(1));
                                        PutModule(sMessage);
                                }
                        } else if (sCommand.Equals("nick")) {
                                if (sMessage.Token(1).empty()) {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Usage: nick <newnick>");
                                }
                                else {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Done");
                                        PutIRC("NICK " + sMessage.Token(1));
                                        PutModule(sMessage);
                                }
                        } else if (sCommand.Equals("kick")) {
                                if(sMessage.Token(2).empty()) {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Usage: kick #yourchannel <kicknick>");
                                }
                                else {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Done");
                                        PutIRC("KICK " + sMessage.Token(1, true));
                                        PutModule(sMessage);
                                }
                        } else if (sCommand.Equals("mode")) {
                                if(sMessage.Token(2).empty()) {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Usage: mode #yourchannel +Modes");
                                }
                                else {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Done");
                                        PutIRC("MODE " + sMessage.Token(1) + " : " + sMessage.Token(2, true));
                                        PutModule(sMessage);
                                }
                        } else if (sCommand.Equals("action")) {
                                if(sMessage.Token(2).empty()) {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Usage: action #yourchannel <action>");
                                }
                                else {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Done");
                                        PutIRC("PRIVMSG " + sMessage.Token(1) + " :" + char(1) + "ACTION " + sMessage.Token(2, true) + char(1));
                                        PutModule(sMessage);
                                }
                        } else if (sCommand.Equals("topic")) {
                                if(sMessage.Token(2).empty()) {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Usage topic #yourchannel <newtopic>");
                                }
                                else {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Done");
                                        PutIRC("TOPIC " + sMessage.Token(1) + " :" + sMessage.Token(2, true));
                                        PutModule(sMessage);
                                }
                        } else if (sCommand.Equals("auth")) {
                                if(sMessage.Token(2).empty()) {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Usage auth <authname> <password>");
                                }
                                else {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Done");
                                        PutIRC("PRIVMSG AuthServ@Services.OnlineGamesNet.net : AUTH " + sMessage.Token(1, true));
                                        PutModule(sMessage);
                                }
                        } else if (sCommand.Equals("ban")) {
                                if(sMessage.Token(2).empty()) {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Usage: ban #yourchannel <*!*@host.*>");
                                }
                                else {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Done");
                                        PutIRC("MODE " + sMessage.Token(1) + " +b " + sMessage.Token(2, true));
                                        PutModule("MODE " + sMessage.Token(1) + " +b " + sMessage.Token(2, true));
                                        PutModule(sMessage);
                                }
                        } else if (sCommand.Equals("unban")) {
                                if(sMessage.Token(2).empty()) {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Usage: unban #yourchannel <*!*@host.*>");
                                }
                                else {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Done");
                                        PutIRC("MODE " + sMessage.Token(1) + " -b " + sMessage.Token(2, true));
                                        PutModule("MODE " + sMessage.Token(1) + " -b " + sMessage.Token(2, true));
                                        PutModule(sMessage);
                                }
                        } else if (sCommand.Equals("centravi")) {
                                if(sMessage.Token(2).empty()) {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Usage: centravi #yourchannel <parameters>");
                                }
                                else {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Done");
                                        PutIRC("PRIVMSG centravi :" + sMessage.Token(1, true));
                                        PutModule(sMessage);
                                }
                        } else if (sCommand.Equals("chanserv")) {
                                if(sMessage.Token(2).empty()) {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Usage: chanserv #yourchannel <parameters>");
                                }
                                else {
                                        PutIRC("PRIVMSG " + Nick.GetNick() + " :Done");
                                        PutIRC("PRIVMSG chanserv :" + sMessage.Token(1, true));
                                        PutModule(sMessage);
                               }
                        }

                }
                else {
                        PutIRC("PRIVMSG " + Nick.GetNick() + " : Do you even look bald?");
                        PutIRC("PRIVMSG #Centravi.Dev : You are not bald " + Nick.GetNick());
                }
                return CONTINUE;
        }
};

template<> void TModInfo<CUserRawMod>(CModInfo& Info) {
        Info.SetWikiPage("user_raw");
}

MODULEDEFS(CUserRawMod, "Shit module door een shit coder")