/* See LICENSE file for copyright and license details. */
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include "../slstatus.h"
#include "../util.h"

const char *
bluetooth_icon(const char *unused)
{
	DIR *d;
	struct dirent *de;
	char path[64], line[16];
	FILE *fp;

	if (!(d = opendir("/proc")))
		return "󰂲";

	while ((de = readdir(d))) {
		if (de->d_name[0] < '0')
			continue;
		snprintf(path, sizeof(path), "/proc/%s/comm", de->d_name);
		if (!(fp = fopen(path, "r")))
			continue;
		if (fgets(line, sizeof(line), fp) && !strncmp(line, "bluetoothd", 10)) {
			fclose(fp);
			break;
		}
		fclose(fp);
	}
	closedir(d);

	if (!de)
		return "󰂲";

	if (!(d = opendir("/sys/class/bluetooth/hci0")))
		return "󰂯";

	while ((de = readdir(d)))
		if (strchr(de->d_name, ':'))
			break;
	closedir(d);

	return de ? "󰂱" : "󰂯";
}
