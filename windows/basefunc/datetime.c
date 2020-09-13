struct maxdays_t
{
    int year;
    int mon[12];
};

struct datetime_t
{
    int year;
    int mon;
    int day;
    int hour;
    int min;
    int sec;
};

static void get_maxdays(const int year, struct maxdays_t *maxdays)
{
    maxdays->year=365;
    maxdays->mon[0]=31;
    maxdays->mon[1]=28;
    maxdays->mon[2]=31;
    maxdays->mon[3]=30;
    maxdays->mon[4]=31;
    maxdays->mon[5]=30;
    maxdays->mon[6]=31;
    maxdays->mon[7]=31;
    maxdays->mon[8]=30;
    maxdays->mon[9]=31;
    maxdays->mon[10]=30;
    maxdays->mon[11]=31;

    if(year%100==0)
    {
        if(year%400==0)
        {
            maxdays->year++;
            maxdays->mon[1]++;
        }
    }
    else
    {
        if(year%4==0)
        {
            maxdays->year++;
            maxdays->mon[1]++;
        }
    }
}

static void get_pre_year(struct maxdays_t *maxdays, struct datetime_t *datetime)
{
    datetime->mon+=12;
    datetime->year--;
    get_maxdays(datetime->year, maxdays);
}

static void put_next_year(struct maxdays_t *maxdays, struct datetime_t *datetime)
{
    datetime->mon-=12;
    datetime->year++;
    get_maxdays(datetime->year, maxdays);
}

static void get_pre_mon(struct maxdays_t *maxdays, struct datetime_t *datetime)
{
    if(datetime->mon<2)
        get_pre_year(maxdays, datetime);
    datetime->day+=maxdays->mon[datetime->mon-2];
    datetime->mon--;
}

static void put_next_mon(struct maxdays_t *maxdays, struct datetime_t *datetime)
{
    if(datetime->mon>12)
        put_next_year(maxdays, datetime);
    datetime->day-=maxdays->mon[datetime->mon-1];
    datetime->mon++;
}

static void get_pre_day(struct maxdays_t *maxdays, struct datetime_t *datetime)
{
    datetime->hour+=24;
    datetime->day--;
    if(datetime->day<1)
        get_pre_mon(maxdays, datetime);
}

static void put_next_day(struct maxdays_t *maxdays, struct datetime_t *datetime)
{
    datetime->hour-=24;
    datetime->day++;
    if(datetime->day>maxdays->mon[datetime->mon-1])
        put_next_mon(maxdays, datetime);
}

static void get_pre_hour(struct maxdays_t *maxdays, struct datetime_t *datetime)
{
    datetime->min+=60;
    datetime->hour--;
    if(datetime->hour<0)
        get_pre_day(maxdays, datetime);
}

static void put_next_hour(struct maxdays_t *maxdays, struct datetime_t *datetime)
{
    datetime->min-=60;
    datetime->hour++;
    if(datetime->hour>23)
        put_next_day(maxdays, datetime);
}

static void get_pre_min(struct maxdays_t *maxdays, struct datetime_t *datetime)
{
    datetime->sec+=60;
    datetime->min--;
    if(datetime->min<0)
        get_pre_hour(maxdays, datetime);
}

static void put_next_min(struct maxdays_t *maxdays, struct datetime_t *datetime)
{
    datetime->sec-=60;
    datetime->min++;
    if(datetime->min>59)
        put_next_hour(maxdays, datetime);
}

int chk_datetime(struct datetime_t *datetime)
{
    int ret=0;
    struct maxdays_t maxdays;

    get_maxdays(datetime->year, &maxdays);
    while(1)
    {
        int flag=0;
        if(datetime->sec<0)
            get_pre_min(&maxdays, datetime);
        else if(datetime->sec>59)
            put_next_min(&maxdays, datetime);
        else
            flag++;
        if(datetime->min<0)
            get_pre_hour(&maxdays, datetime);
        else if(datetime->min>59)
            put_next_hour(&maxdays, datetime);
        else
            flag++;
        if(datetime->hour<0)
            get_pre_day(&maxdays, datetime);
        else if(datetime->hour>23)
            put_next_day(&maxdays, datetime);
        else
            flag++;
        if(datetime->day<1)
            get_pre_mon(&maxdays, datetime);
        else if(datetime->day>maxdays.mon[datetime->mon-1])
            put_next_mon(&maxdays, datetime);
        else
            flag++;
        if(datetime->mon<1)
            get_pre_year(&maxdays, datetime);
        else if(datetime->mon>12)
            put_next_year(&maxdays, datetime);
        else
            flag++;
        if(flag==5)
            break;
        else
            ret=-1;
    }
    return ret;
}













