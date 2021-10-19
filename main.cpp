#include "CFile.h"

#include "print.h"

int main()
{
    const char *filepath = "/var/log/syslog";

    CFile file;
    if (!file.read(filepath))
        return 1;

    CString line;
    while (file.getLine(line))
    {
        if (line.contains("rtkit-daemon["))
            continue;

        print(line);
    }

    return 0;
}


