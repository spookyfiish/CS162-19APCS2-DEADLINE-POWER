#include"function.h"
using namespace std;

int numberOfDay(Date x, Date y)
{
    if (x.month < 3)
    {
        x.year--;
        x.month += 12;
    }
    return 365 * x.year + x.year / 4 - x.year / 100 + x.year / 400 + (153 * x.month - 457) / 5 + x.day - 307-(365 * y.year + y.year / 4 - y.year / 100 + y.year / 400 + (153 * y.month - 457) / 5 + y.day - 307)+1;
}

void memset(short int checkinList[10][10],int x,int  y)
{
    for(int i=1; i<=x; i++)
        for(int j=1; j<=y; j++)
            checkinList[i][j]=0;
}
bool Tick(int week, string Course,ViewCheckin *&checkin )
{
    ViewCheckin *cur=checkin;

    int i=1;
    string *x=new string(Course+" X");
    string *v=new string(Course+" Y");

    while(cur!=NULL&& i!=week)
    {
        cur=cur->next;
        i++;
    }
    for(i=1; i<=6; i++)
        for(int j=1; j<=4; j++)
            if(*x==cur->viewWeek[i][j])
            {
                cur->viewWeek[i][j]=*v;
                return true;
            }
            else if(*v==cur->viewWeek[i][j])
            {
                cout<<"You've already checked in";
                return false;
            }
    cout<<"Cannot check  in Course";
    return false;




}
void viewCheckIn(string checkInWeek[6][4], int week)
{
    cout<<"Week: "<<week<<endl;
    cout<<setw(10);
    cout<<"Monay";
    cout<<setw(10);
    cout<<"Tueseday";
    cout<<setw(10);
    cout<<"Wednesday";
    cout<<setw(10);
    cout<<"Thursday";
    cout<<setw(10);
    cout<<"Friday";
    cout<<setw(10);
    cout<<"Saturday";
    cout<<setw(10);

    for(int i=1; i<=6; i++)
        for(int j=1; j<=4; j++ )

            cout<<setw(10)<<checkInWeek[i][j];


}

void viewSchedule(Classes *Class)
{
    cout<<setw(10);
    cout<<"Monay";
    cout<<setw(10);
    cout<<"Tueseday";
    cout<<setw(10);
    cout<<"Wednesday";
    cout<<setw(10);
    cout<<"Thursday";
    cout<<setw(10);
    cout<<"Friday";
    cout<<setw(10);
    cout<<"Saturday";
    cout<<setw(10);

    for(int i=1; i<=6; i++)
        for(int j=1; j<=4; j++ )

            cout<<setw(10)<<Class->schedule[i][j];

}
void viewScoreCourse(Students *&student,string course)
{
    Scoreboards *scoreboard=student->scoreboards;
    while(scoreboard->courseName!=course)
        scoreboard=scoreboard->next;
                   //cout
    }

void changeCheckinList(ViewCheckin *&checkinList,int day,int nth,string courseID)
{
    ViewCheckin *cur=checkinList;
    string *x=new string(courseID+" X");
    string *v=new string(courseID+" Y");
    while(cur!=NULL)
    {
        for(int i=1; i<=6; i++)
            for(int j=1; j<=4; j++)
                if(cur->viewWeek[i][j]== *v)
                    break;
                else if(cur->viewWeek[i][j]== *x)
                {
                    cur->viewWeek[i][j]="//";
                    cur->viewWeek[day][nth]=*x;
                    break;
                }
        cur=cur->next;
    }
}
void EditScheduleCourseOfClass(Courses*&course,string classID,string courseID,Classes *&Class)
{
    Classes *curClass=Class;
    Courses* curCourse=course;
    while(curClass->classID!=classID)
        curClass=curClass->next;
    while(curCourse->courseID!=courseID)
        curCourse=curCourse->next;

    int day,nth,day0,nth0;
    cout<<"Day in week: ";
    cin>>day0;
    cout<<"nth: ";
    cin>>nth0;
    //change schedule
    for(int i=1; i<=6; i++)
        for(int j=1; j<=4; j++)
            if(curClass->schedule[i][j]==courseID)
            {
                curClass->schedule[i][j]=="//";
                day=i;
                nth=j;
                break;
            }
    curClass->schedule[day0][nth0]=courseID;


    Students *student=curClass->students;
    while(student!= NULL)
    {
        changeCheckinList(student->checkinList,day0,nth0,courseID);
        student=student->next;
    }

// change schedule chechou base in courseClass of Course


}
void EditCourseId(Courses*& course,string NewID,string OldID)
{
    Courses*cur=course;
    while(cur->courseID!=OldID)
        cur->next;
    cur->courseID=NewID;
}
void EditCourseroom(Courses*& course,string courseID,string room)
{
    Courses*cur=course;

    while(cur->courseID!=courseID)
        cur->next;
    cur->room=room;
}
void EditCourseLecture(Courses*& course,string name,string courseID)
{
    Courses*cur=course;
    while(cur->courseID!=courseID)
        cur->next;
    cur->LectureName=name;

}

void EditCourse(Courses*& course,Classes *&Class)
{
    int n;
    cin>>n;
    string courseID,room,NewID, OldID,name,classID;
    switch(n)
    {
    case 1:

        getline(cin,OldID);
        getline(cin,NewID);
        EditCourseId(course,NewID,OldID);
        break;
    case 2:

        cin>>courseID;
        cin>>room;
        EditCourseroom( course, courseID, room);
                break;

    case 3:


        cin>>classID;
        cin>>courseID;
        EditScheduleCourseOfClass(course,classID,courseID,Class);
        break;

    case 4:

        EditCourseLecture(course,name,courseID);
                break;




    }


}
void DeleteCourseSchedule(Classes *&Class,string courseID,string classID)
{
    Classes*cur=Class;
    while(cur!=NULL)
    {
        if(cur->classID==classID)
        {
            for(int i=1; i<=6; i++)
                for(int j=1; j<=4; j++)
                    if(cur->schedule[i][j]==courseID)
                        cur->schedule[i][j]="//";
        }
        cur=cur->next;
    }

}
bool RemoveCourse(Courses*& course,string courseID,Classes * &Class)
{
    Courses* cur=course;
    Courses* tmp=new Courses;
    Courses* pre=new Courses;
    if(cur-> courseID==courseID)
    {
        cur=cur->next;
        course=NULL;
        course=cur;
    }
    while(cur!=NULL)
    {
        if(cur->courseID==courseID)
        {
            while(cur->courseclass!=NULL)
                DeleteCourseSchedule(Class,courseID,cur->courseclass->classID);
            pre->next=cur->next;
            Courses* tmp=cur->next;
            cur=NULL;
            cur=tmp;
            return true;
        }
        pre= cur;
        cur=cur->next;
    }
    return false;

}
void RemovedStudentFromCourseClass(Courses*& course,string courseID,string classID,int studentID )
{
    Courses* curCourse= course;
    while(curCourse->courseID !=courseID)
        curCourse = curCourse->next;
    CourseClass* courseclass = curCourse->courseclass;
    while(courseclass->classID != classID)
        courseclass = courseclass->next;
        int i=0;
        Students* students= courseclass->students;
        while(students->studentID != studentID)i++;
        courseclass->BitAttend -= 2>>i;
       changeCheckinList(students->checkinList,0,0,courseID);
//1 inside
//0 outsie
}
void AddStudentToCourseClass(Courses*& course,string courseID,string classID,int studentID )
{
    Courses* curCourse= course;
    while(curCourse->courseID != courseID)
        curCourse = curCourse->next;
    CourseClass* courseclass = curCourse->courseclass;
    while(courseclass->classID != classID)
        courseclass = courseclass->next;

    OutsideStudent* Outsider=   new OutsideStudent;
    Outsider->classID= classID;
    Outsider->studentID= studentID;
    Outsider->next= courseclass->Outsider;
    courseclass->Outsider = Outsider;

}


