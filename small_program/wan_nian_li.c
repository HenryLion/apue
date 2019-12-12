#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* 本程序输入./a.out year month 可以得到本月份的万年历展示 */

char *g_month[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jule", "July", "Aug", "Sep", "Oct", "Nov", "Dec" };

char *g_week[7] = {"Sun", "Mon", "Tue", "Wes", "Thu", "Fri", "Sai" };

int g_month_days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

int is_leap_year (int year)
{
	return (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
}

static int cal_week (int y, int m, int d)
{
	if (m < 1 || m > 12 || d < 1 || d > 31)
		return -1;
	if (m == 1)
	{
		m = 13;
		--y;
	}
	else if (m == 2)
	{
		m = 14; 
		--y;
	}
	int c = y / 100;
	y = y - c * 100;
	int week = y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + d - 1;
	week %= 7;
	week = week < 0 ? week + 7 : week;
	return week;
}

time_t get_time ()
{
	return time (NULL);
}

void print_blank (int first_day_week)
{
	int idx = 0;
	int blank_num = (first_day_week % 7) * 4;
	for (idx = 0; idx < blank_num; ++idx)
	{
		printf ("%s", " ");
	}
}

void print_days (int days_num, int first_day_week)
{
	int line_feed_flag = first_day_week;
	int idx = 0;
	print_blank (first_day_week);
	for (idx = 0; idx < days_num; ++idx,++line_feed_flag)
	{
		if (line_feed_flag == 7)
		{
			line_feed_flag = 0;
			printf ("\n");
		}
		printf ("%3d ", idx + 1);
	}
	printf ("\n");
}

void print_head (int year, int month)
{
	int idx = 0;
	printf ("%11s %d\n", g_month[month-1], year);
	for (idx = 0; idx < sizeof (g_week) / sizeof (g_week[0]); ++idx)
	{
		printf ("%-3s ", g_week[idx]);
	}
	printf ("\n");
}


void print_calander_month (int year, int month)
{
	int month_days = g_month_days[month-1];
	month_days = ( (month == 2) && is_leap_year (year) ) ? month_days + 1 : month_days;
	int week = cal_week (year, month, 1);
	print_head (year, month);
	print_days (month_days, week);
}
	

int main (int argc, char* argv[])
{
	int year = 0;
	int month = 0;
	struct tm *time = NULL;
	if (argc != 3)
	{
		if (argc != 1)
		{
			printf ("Usage: cal [{year} {month}]\n");
			return -1;
		}
		time_t now = get_time (NULL);
		time = localtime (&now);
		year = time->tm_year + 1900;
		month = time->tm_mon + 1;
	}
	else
	{
		year = atoi (argv[1]);
		month = atoi (argv[2]);
	}
	print_calander_month (year, month);
	return 0;
}

