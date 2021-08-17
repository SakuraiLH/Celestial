#include "GlobalVariable.h"
void PermissionSensor(GroupPermission &gp, bool &HasPermission, GroupMessage &m)
{
    gp = m.Sender.Permission;
    if(GroupPermissionStr("ADMINISTRATOR") == gp || GroupPermissionStr("OWNER") == gp)
    {
        HasPermission = true;
    }
}