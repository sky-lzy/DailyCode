#include "score.h"

Score::Score() {}

Score::Score(const std::string &s, const std::string &sn, const std::string &tn, const int hg, const int c)
    : subject(s), student_name(sn), teacher_name(tn), credit(c)
{
    setScore(hg);
}

void Score::print() const
{
    std::cout << subject << "  " << credit << " " << HundredMark_Score << "  "
              << Graded_Score << "  " << courseGPA << std::endl;
}

void Score::setScore(const int hg)
{
    HundredMark_Score = hg;
    if (HundredMark_Score >= 98)
    {
        Graded_Score = "A+";
        courseGPA = 4;
    }
    else if (HundredMark_Score >= 95)
    {
        Graded_Score = "A";
        courseGPA = 4;
    }
    else if (HundredMark_Score >= 90)
    {
        Graded_Score = "A-";
        courseGPA = 4;
    }
    else if (HundredMark_Score >= 85)
    {
        Graded_Score = "B+";
        courseGPA = 3.6;
    }
    else if (HundredMark_Score >= 80)
    {
        Graded_Score = "B";
        courseGPA = 3.3;
    }
    else if (HundredMark_Score >= 77)
    {
        Graded_Score = "B-";
        courseGPA = 3.0;
    }
    else if (HundredMark_Score >= 73)
    {
        Graded_Score = "C+";
        courseGPA = 2.6;
    }
    else if (HundredMark_Score >= 70)
    {
        Graded_Score = "C";
        courseGPA = 2.3;
    }
    else if (HundredMark_Score >= 67)
    {
        Graded_Score = "C-";
        courseGPA = 2.0;
    }
    else if (HundredMark_Score >= 63)
    {
        Graded_Score = "D+";
        courseGPA = 1.6;
    }
    else if (HundredMark_Score >= 60)
    {
        Graded_Score = "D";
        courseGPA = 1.3;
    }
    else
    {
        Graded_Score = "F";
        courseGPA = 1.0;
    }
}

std::istream &operator>>(std::istream &input, Score &sc)
{
    int temp;
    input >> sc.subject >> sc.student_name >> sc.teacher_name >> temp >> sc.credit;
    sc.setScore(temp);
    return input;
}

std::ostream &operator<<(std::ostream &output, const Score &sc)
{
    output << sc.getSubject() << " " << sc.getStudentName() << " " << sc.getTeacherName() << " " << sc.getHundredMarkScore()
           << " " << sc.getGradedScore() << " " << sc.getCourseGPA() << " " << sc.getCredit() << std::endl;
    return output;
}
