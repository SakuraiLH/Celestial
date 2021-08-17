#include "GlobalVariable.h"
#include "PermissionSensor.h"

GroupPermission gp;
void whoami(string plain, bool &HasPermission, GroupMessage &m)
{
    PermissionSensor(gp, HasPermission, m);
    if (plain == ".whoami")
    {
        // 如果沒有權限
        if (HasPermission == false) {
            m.Reply(MessageChain().Plain(Celestial_WhoAmI_Denied));
            return;
        }

        // 如果有權限
        m.Reply(MessageChain().Plain(Celestial_WhoAmI_Permitted));
        return;
    }
}