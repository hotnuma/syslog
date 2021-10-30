#include <CProcess.h>
#include <CFile.h>
#include <libapp.h>
#include <libpath.h>
#include <string.h>

#include <print.h>

int main()
{
    CString outpath =  pathJoin(getHomeDirectory(), "sys_log.txt");

    CString cmd = "journalctl -b 0 --no-pager";

    CProcess process;
    if (!process.start(cmd, CP_PIPEOUT))
    {
        print("start failed");

        return -1;
    }

    int status = process.exitStatus();

    if (status != 0)
    {
        print("program returned : %d", status);

        return -1;
    }

    CString &buffer = process.outBuff;
    char *ptr = buffer.data();
    char *result;
    int length;

    CFile outfile;
    if (!outfile.open(outpath, "wb"))
        return 1;

    while (strGetLinePtr(&ptr, &result, &length))
    {
        result[length] = '\0';

        if (strstr(result, "rtkit-daemon[") != nullptr)
            continue;

        outfile << result;
        outfile << "\n";

        print(result);
    }

    return 0;
}


